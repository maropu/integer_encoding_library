/*-----------------------------------------------------------------------------
 *  VSEncodingBlocksHybrid.cpp - A hybrid implementation of VSEncoding
 *      VSEncodingBlocksHybrid uses VSEncodingRest for lists of length up to
 *      VSEHYBRID_THRES and VSEncodingBlocks for longer lists.
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

#include "compress/policy/VSEncodingBlocksHybrid.hpp"

using namespace std;
using namespace integer_coding::compressor;

void
VSEncodingBlocksHybrid::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        uint32_t        res;
        uint32_t        *lin;
        uint32_t        *lout;
        uint32_t        csize;

        for (nvalue = 0, res = len, lin = in, lout = out; 
                        res > VSENCODING_BLOCKSZ;
                        res -= VSENCODING_BLOCKSZ, lin += VSENCODING_BLOCKSZ,
                        lout += csize, nvalue += csize + 1) {
                encodeVS(VSENCODING_BLOCKSZ, lin, csize, ++lout);
                *(lout - 1) = csize;
        }

        VSEncodingRest  vr;

        if (res <= VSEHYBRID_THRES)
                vr.encodeArray(lin, res, lout, csize);
        else
                encodeVS(res, lin, csize, lout);

        nvalue += csize;
}

void
VSEncodingBlocksHybrid::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        if (nvalue == 0)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: nvalue");

        uint32_t        res;
        uint32_t        sum;

        for (res = nvalue; res > VSENCODING_BLOCKSZ;
                        out += VSENCODING_BLOCKSZ, in += sum,
                        len -= sum, res -= VSENCODING_BLOCKSZ) {
                sum = *in++;
                decodeVS(VSENCODING_BLOCKSZ,
                                in, out, wmem_aux.get());
        }

        VSEncodingRest  vr;

        if (res <= VSEHYBRID_THRES)
                vr.decodeArray(in, len, out, res);
        else
                decodeVS(res, in, out, wmem_aux.get());
}
