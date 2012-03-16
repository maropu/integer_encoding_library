/*-----------------------------------------------------------------------------
 *  Simple9.hpp - A encoder/decoder for Simple9.
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

#ifndef SIMPLE9_HPP
#define SIMPLE9_HPP

#include "open_coders.hpp"
#include "io/BitsWriter.hpp"

class Simple9 {
private:
        /*
         * These functions judging how many integers to
         * include in a single 32-bit area.
         */
        static bool try28_1bit (uint32_t *n, uint32_t nvalue);
        static bool try14_2bit (uint32_t *n, uint32_t nvalue);
        static bool try9_3bit (uint32_t *n, uint32_t nvalue);
        static bool try7_4bit (uint32_t *n, uint32_t nvalue);
        static bool try5_5bit (uint32_t *n, uint32_t nvalue);
        static bool try4_7bit (uint32_t *n, uint32_t nvalue);
        static bool try3_9bit (uint32_t *n, uint32_t nvalue);
        static bool try2_14bit (uint32_t *n, uint32_t nvalue);

public:
        static void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue);
        static void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue);
};

#endif /* SIMPLE9_HPP */
