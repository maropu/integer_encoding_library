/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks.hpp - A original and simple implementation of VSEncoding.
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

#ifndef VSENCODINGBLOCKS_HPP
#define VSENCODINGBLOCKS_HPP

#include "open_coders.hpp"
#include "compress/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

class VSEncodingBlocks {
        public:
                static void encodeVS(uint32_t len, uint32_t *in,
                                uint32_t &size, uint32_t *out);

                static void decodeVS(uint32_t len, uint32_t *in,
                                uint32_t *out, uint32_t *aux);

                /*
                 * It assumes that values start form 0.
                 *  - *in: points to the first d-gap to be encoded
                 *  - *out: points to the first int that will countain the compress
                 * It returns the compress size in number of int   
                 *
                 * Note: *out must be large enough to contain the compress.
                 */
                static void encodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t &nvalue);

                static void decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue);
};

#endif /* VSENCODINGBLOCKS_HPP */
