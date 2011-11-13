/*-----------------------------------------------------------------------------
 *  VSEncodingSimpleV2_utest.cpp - A unit test for VSEncodingSimpleV2.
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

#include <gtest/gtest.h>
#include "compress/VSEncodingSimpleV2.hpp"

TEST(VSEncodingSimpleV2Test, ValidationEncode1b) {
        int             i;
        uint32_t        len;
        uint32_t        input[256];
        uint32_t        output[256];
        uint32_t        cdata[2 + TAIL_MERGIN];

        for (i = 0; i < 256; i++)
                input[i] = 1;

        VSEncodingSimpleV2::encodeArray(&input[0], 256U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingSimpleV2::decodeArray(&cdata[0], 0U, &output[0], 256U);

        for (i = 0; i < 256; i++)
                EXPECT_EQ(1U, output[i]);
}

