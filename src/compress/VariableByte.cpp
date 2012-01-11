/*-----------------------------------------------------------------------------
 *  VariableByte.cpp - A implementation of VariableByte.
 *
 *  Coding-Style:
 *      emacs) Mode: C, tab-width: 8, c-basic-offset: 8, indent-tabs-mode: nil
 *      vi) tabstop: 8, expandtab
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *-----------------------------------------------------------------------------
 */

#include "compress/VariableByte.hpp"

#define VARIABLEBYTE_DESC       0x80
#define VARIABLEBYTE_DATA       (VARIABLEBYTE_DESC - 1)

#define VARIABLEBYTE_EXT7BITS(value, num)         (value >> (7 * num)) & 0x7f

void
VariableByte::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue)
{
        uint32_t        i;
        uint32_t        nwords;
        BitsWriter      *wt;

        wt = new BitsWriter(out);

        uint32_t t;

        for (i = 0; i < len; i++) {
                nwords = int_utils::get_msb(in[i]) / 7;

                switch(nwords) {
                case 0:
                        wt->bit_writer(1, 1);
                        t = VARIABLEBYTE_EXT7BITS(in[i], 0);
                        wt->bit_writer(t, 7);
                        break;

                case 1:
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 0), 7);
                        wt->bit_writer(1, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 1), 7);
                        break;

                case 2:
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 0), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 1), 7);
                        wt->bit_writer(1, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 2), 7);
                        break;

                case 3:
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 0), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 1), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 2), 7);
                        wt->bit_writer(1, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 3), 7);
                        break;

                case 4:
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 0), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 1), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 2), 7);
                        wt->bit_writer(0, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 3), 7);
                        wt->bit_writer(1, 1);
                        wt->bit_writer(VARIABLEBYTE_EXT7BITS(in[i], 4), 7);
                        break;

                default:
                        eoutput("Exception: nwords's out of range");

                }
        }

        wt->bit_flush();
        nvalue = wt->written;

        delete wt;
}

void
VariableByte::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue)
{
        uint32_t        i;
        uint32_t        j;
        uint32_t        d;
        BitsReader      *rd;

        rd = new BitsReader(in);

        for (i = 0; i < nvalue; i++) {
                d = rd->bit_reader(8);

                *out = d & VARIABLEBYTE_DATA;

                for (j = 1; (d & VARIABLEBYTE_DESC) == 0; j++) {
                        __assert(j <= 5);

                        d = rd->bit_reader(8);
                        *out |= (d & VARIABLEBYTE_DATA) << (7 * j);
                }

                out++;
        }

        delete rd;
}

