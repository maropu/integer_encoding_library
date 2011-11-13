/*-----------------------------------------------------------------------------
 *  PForDelta_utest.cpp - A unit test for PForDelta.
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
#include "compress/PForDelta.hpp"

TEST(PForDeltaTest, ValidationEncode1b) {
        int             i;
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[3 + TAIL_MERGIN];

        for (i = 0; i < 32; i++)
                input[i] = 1;

        PForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        PForDelta::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U, output[i]);
}

