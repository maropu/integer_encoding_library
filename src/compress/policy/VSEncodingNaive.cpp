/*-----------------------------------------------------------------------------
 *  VSEncodingNaive.cpp - A naive implementation of VSEncoding
 *      This implementation is used by VSE-R.
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

#include "compress/policy/VSEncodingNaive.hpp"

using namespace std;
using namespace integer_coding::compressor;
using namespace integer_coding::utility;

void
VSEncodingNaive::encodeArray(uint32_t *in,
                uint32_t len, uint32_t *out, uint32_t &nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        /* Compute logs of all numbers */
        vector<uint32_t>        logs;

        __init_vector(logs, len);
        for (uint32_t i = 0; i < len; i++)
                logs[i] = __vsenaive_remapLogs[1 + __get_msb(in[i])];

        /* Compute optimal partition */
        vector<uint32_t>        parts;

        vdp->compute_OptPartition(logs,
                        VSENAIVE_LOGLEN + VSENAIVE_LOGLOG, parts);

        uint32_t numBlocks = parts.size() - 1;

    	/* Ready to write */ 
        uint32_t        maxB;
        BitsWriter      wt(out);

        for (uint32_t i = 0; i < numBlocks; i++) {
                /* Compute max B in the block */
                maxB = 0;

                for (uint32_t j = parts[i]; j < parts[i + 1]; j++) {
                        if (maxB < logs[j])
                                maxB = logs[j];
                }

                /* Writes the value of B and K */
                wt.bit_writer(__vsenaive_codeLogs[maxB], VSENAIVE_LOGLOG);
                wt.bit_writer(__vsenaive_codeLens[parts[i + 1] -
                                parts[i]], VSENAIVE_LOGLEN);

                for (uint32_t j = parts[i]; j < parts[i + 1]; j++)
                        wt.bit_writer(in[j], maxB);
        }

        wt.bit_flush(); 

        nvalue = wt.get_written();
}

void
VSEncodingNaive::decodeArray(uint32_t *in,
                uint32_t len, uint32_t *out, uint32_t nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        if (nvalue == 0)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: nvalue");

        BitsReader      rd(in);

        uint32_t *iterm = in + len;
        uint32_t *oterm = out + nvalue;

        while (1) {
                if (__unlikely(out >= oterm || rd.get_pos() >= iterm))
                        break;

                uint32_t B = __vsenaive_possLogs[rd.bit_reader(VSENAIVE_LOGLOG)];
                uint32_t K = __vsenaive_possLens[rd.bit_reader(VSENAIVE_LOGLEN)];

                for (uint32_t i = 0; i < K; i++)
                        out[i] = (B != 0)? rd.bit_reader(B) : 0;

                out += K;
        }
}
