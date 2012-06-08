/*-----------------------------------------------------------------------------
 *  BitsReader.cpp - A code to read compressed data for decoding
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

#include "io/BitsReader.hpp"

#define BITSRD_M64      0x000000000000ffff
#define BITSRD_M32      0x0000ffff

#define BITSRD_BUFFILL()        \
        if (Fill < 16) {        \
                buffer = (buffer << 32) | *data;        \
                data++;         \
                Fill += 32;     \
        }

using namespace integer_coding::utility;
using namespace integer_coding::compressor;

uint32_t
BitsReader::bit_reader(uint32_t bits)
{
        __assert(bits <= 32 && data != NULL);

        if (bits == 0)
                return 0;

        if (Fill < bits) {
                buffer = (buffer << 32) | *data++;
                Fill += 32;
        }

        Fill -= bits;

        return (buffer >> Fill) & ((1ULL << bits) - 1);
}

uint32_t *
BitsReader::get_pos() const
{
        if (data == NULL)
                return NULL;

        return data - 1;
}

uint32_t
BitsReader::N_Unary()
{
        uint32_t count = 0;

        while (bit_reader(1) == 0)
                count++;

        return count;
}

void
BitsReader::N_UnaryArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;
        uint32_t count = 0;

        while (i < nvalues) {
                while (bit_reader(1) == 0)
                        count++;

                out[i++] = count;
                count = 0;
        }
}

void
BitsReader::F_UnaryArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = F_Unary();
}

/*
* The F_Unary decoding uses decUn:2exp16 Unary
* indicized table, from decUnary.h
*/
uint32_t
BitsReader::F_Unary()
{
        return BitsReader::F_Unary32();
}

uint32_t
BitsReader::F_Unary32()
{
        BITSRD_BUFFILL();

        uint32_t dec = decUnary[
                (buffer >> (Fill - 16)) & BITSRD_M64];

        if (dec == 16) {
                Fill -= 16;
                return F_Unary() + dec;
        } else {
                Fill -= dec + 1;
                return dec;
        }

        /* Not reach here */
        return 0;
}

uint32_t
BitsReader::F_Unary16()
{
        BITSRD_BUFFILL();

        uint32_t dec = decUnary[
                (buffer >> (Fill - 16)) & BITSRD_M64];
        Fill -= dec + 1;

        return dec;
}

uint32_t
BitsReader::N_Gamma()
{
        uint32_t count = 0;

        while (bit_reader(1) == 0)
                count++;

        uint32_t d = ((1 << count)
                        | bit_reader(count));

        return d - 1;
}

/*
 * The F_Gamma decoding uses decUn:2exp16 Gamma
 * indicized table, from decGamma.hpp
 */
uint32_t
BitsReader::F_Gamma()
{
        BITSRD_BUFFILL();

        uint32_t dec = decGamma[
                (buffer >> (Fill - 16)) & BITSRD_M64];

        if (dec == 0) {
                return N_Gamma();
        } else {
                Fill -= (dec >> 16);
                return (dec & BITSRD_M32) - 1;
        }
}

uint32_t
BitsReader::FU_Gamma()
{
        uint32_t count = F_Unary32();

        return ((1 << count)
                        | bit_reader(count)) - 1;
}

void
BitsReader::N_GammaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = N_Gamma();
}

void
BitsReader::F_GammaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = F_Gamma();
}

void
BitsReader::FU_GammaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = FU_Gamma();
}

uint32_t
BitsReader::N_Delta()
{
        uint32_t count = N_Gamma();
        return ((1 << count)
                        | bit_reader(count)) - 1;
}

/*
 * The Delta decoding uses decUn:2exp16 Delta
 * indicized table, from decDelta.h
 */
uint32_t
BitsReader::F_Delta()
{
        BITSRD_BUFFILL();

        uint32_t dec = decDelta[
                (buffer >> (Fill - 16)) & BITSRD_M64];

        if (dec == 0) {
                return N_Delta();
        } else {
                Fill -= (dec >> 16);
                return (dec & BITSRD_M32) - 1;
        }
}

uint32_t
BitsReader::FU_Delta()
{
        uint32_t count = F_Unary16();
        uint32_t log = ((1 << count)
                        | bit_reader(count)) - 1;

        return ((1 << log) | bit_reader(log)) - 1;
}

void
BitsReader::N_DeltaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = N_Delta();
}

void
BitsReader::FU_DeltaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = FU_Delta();
}

void
BitsReader::FG_DeltaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues) {
                uint32_t count = F_Gamma();
                out[i++] = ((1 << count) | bit_reader(count)) - 1;
        }
}

void
BitsReader::F_DeltaArray(uint32_t *out, uint32_t nvalues)
{
        uint32_t i = 0;

        while (i < nvalues)
                out[i++] = F_Delta();
}

/*
* readMinmalBinary()
*      requirements: b >= 1
*/
uint32_t
BitsReader::readMinimalBinary(uint32_t b)
{
        __assert(data != NULL);

        uint32_t d = __get_msb(b);
        uint32_t m = (1ULL << (d + 1)) - b;

        uint32_t x = bit_reader(d);

        if (x < m)
                return x;
        else
                return (x << 1) + bit_reader(1) - m;
}

void
BitsReader::InterpolativeArray(uint32_t *out, uint32_t nvalues, 
                uint32_t offset, uint32_t lo, uint32_t hi)
{
        __assert(lo <= hi);

        if (nvalues == 0)
                return;

        if (nvalues == 1) {
                if (out != NULL)
                        out[offset] = readMinimalBinary(hi - lo + 1) + lo;
                else
                        readMinimalBinary(hi - lo + 1);

                return;
        }

        uint32_t h = nvalues / 2;
        uint32_t m = readMinimalBinary(
                        hi - nvalues + h + 1 - (lo + h) + 1) + lo + h;

        if (out != NULL)
                out[offset + h] = m;

        InterpolativeArray(out, h, offset, lo, m - 1);
        InterpolativeArray(out, nvalues - h - 1,
                        offset + h + 1, m + 1, hi);
}
