/*-----------------------------------------------------------------------------
 *  BinaryInterpolative_utest.cpp - A unit test for BinaryInterpolative code.
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
#include "compress/BinaryInterpolative.hpp"

TEST(BinaryInterpolativeTest, ValidationEncode1gap) {
        int             i;
        uint32_t        len;
        uint32_t        input[8];
        uint32_t        output[8];
        uint32_t        cdata[2];
        uint32_t        exp;

        for (i = 1, input[0] = 1U; i < 8; i++)
                input[i] = 1U + input[i - 1];

        BinaryInterpolative::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(2U, len);

        BinaryInterpolative::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0, exp = 1U; i < 8; i++, exp += 1U) 
                EXPECT_EQ(exp, output[i]);
}

