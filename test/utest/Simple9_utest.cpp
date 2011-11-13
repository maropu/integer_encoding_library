/*-----------------------------------------------------------------------------
 *  Simple9_utest.cpp - A unit test for Simple9 code.
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
#include "compress/Simple9.hpp"

TEST(Simple9Test, ValidationEncode1b) {
        int             i;
        uint32_t        len;
        uint32_t        input[28];
        uint32_t        output[28];
        uint32_t        cdata;

        for (i = 0; i < 28; i++)
                input[i] = 1U;

        Simple9::encodeArray(&input[0], 28U, &cdata, len);

        EXPECT_EQ(1U, len);

        Simple9::decodeArray(&cdata, 0U, &output[0], 28U);

        for (i = 0; i < 28; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(Simple9Test, ValidationEncode2b) {
        int             i;
        uint32_t        len;
        uint32_t        input[14];
        uint32_t        output[14];
        uint32_t        cdata;

        for (i = 0; i < 14; i++)
                input[i] = 1U << 1;

        Simple9::encodeArray(&input[0], 14U, &cdata, len);

        EXPECT_EQ(1U, len);

        Simple9::decodeArray(&cdata, 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 1, output[i]);
}

