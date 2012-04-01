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

#include "compress/VSEncodingBlocksHybrid.hpp"

using namespace opc;

void
VSEncodingBlocksHybrid::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue)
{
        uint32_t        res;
        uint32_t        *lin;
        uint32_t        *lout;
        uint32_t        csize;

        if (len > MAXLEN)
                eoutput("Overflowed input length (CHECK: MAXLEN)");

        for (nvalue = 0, res = len, lin = in, lout = out; 
                        res > VSENCODING_BLOCKSZ;
                        res -= VSENCODING_BLOCKSZ, lin += VSENCODING_BLOCKSZ,
                        lout += csize, nvalue += csize + 1) {
                VSEncodingBlocks::encodeVS(VSENCODING_BLOCKSZ, lin, csize, ++lout);
                *(lout - 1) = csize;
        }

        if (res <= VSEHYBRID_THRES)
                VSEncodingRest::encodeArray(lin, res, lout, csize);
        else
                VSEncodingBlocks::encodeVS(res, lin, csize, lout);

        nvalue += csize;
}

void
VSEncodingBlocksHybrid::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue)
{
        uint32_t        res;
        uint32_t        sum;

        for (res = nvalue; res > VSENCODING_BLOCKSZ;
                        out += VSENCODING_BLOCKSZ, in += sum,
                        len -= sum, res -= VSENCODING_BLOCKSZ) {
                sum = *in++;
                VSEncodingBlocks::decodeVS(
                                VSENCODING_BLOCKSZ,
                                in, out, __vsencoding_aux);
        }

        if (res <= VSEHYBRID_THRES)
                VSEncodingRest::decodeArray(in, len, out, res);
        else
                VSEncodingBlocks::decodeVS(res, in, out, __vsencoding_aux);
}

