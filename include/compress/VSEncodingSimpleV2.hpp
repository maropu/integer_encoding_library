/*-----------------------------------------------------------------------------
 *  VSEncodingSimpleV2.hpp - A encoder/decoder for optimized VSEncoding.
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

#ifndef VSENCODING_SIMPLE_V2_HPP
#define VSENCODING_SIMPLE_V2_HPP

#include "open_coders.hpp"
#include "compress/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

class VSEncodingSimpleV2 {
        public:
                static void encodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t &nvalue);
                static void decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue);
};

#endif /* VSENCODING_SIMPLE_V2_HPP */
