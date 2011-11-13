/*-----------------------------------------------------------------------------
 *  OPTPForDelta.hpp - A encoder/decoder for optimized PForDelta.
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

#ifndef OPTPFORDELTA_HPP
#define OPTPFORDELTA_HPP

#include <stdint.h>

#include "open_coders.hpp"
#include "compress/Simple16.hpp"
#include "compress/PForDelta.hpp"
#include "io/BitsWriter.hpp"

class OPTPForDelta {
        public:
                static uint32_t tryB(uint32_t b, uint32_t *in,
                                uint32_t len);
                static uint32_t findBestB(uint32_t *in, uint32_t len);

                static void encodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t &nvalue);
                static void decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue);
};

#endif /* OPTPFORDELTA_HPP */
