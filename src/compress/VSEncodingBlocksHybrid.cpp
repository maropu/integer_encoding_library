/*-----------------------------------------------------------------------------
 *  VSEncodingBlocksHybrid.cpp - A hybrid implementation of VSEncoding.
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

void
VSEncodingBlocksHybrid::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue)
{
        eoutput("Not implemented yet");
}

void
VSEncodingBlocksHybrid::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue)
{
        eoutput("Not implemented yet");
}

