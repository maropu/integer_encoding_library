/*-----------------------------------------------------------------------------
 *  VariableByte_utest.cpp - A unit test for VariableByte code.
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
#include "compress/VariableByte.hpp"

TEST(VariableByteTest, ValidationEncode1b) {
        int             i;
        uint32_t        len;
        uint32_t        input[8];
        uint32_t        output[8];
        uint32_t        cdata[2];

        for (i = 0; i < 8; i++)
                input[i] = 1U;

        VariableByte::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(2U, len);

        VariableByte::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(VariableByteTest, ValidationEncode2b) {
        int             i;
        uint32_t        len;
        uint32_t        input[8];
        uint32_t        output[8];
        uint32_t        cdata[2];

        for (i = 0; i < 8; i++)
                input[i] = 1U << 1;

        VariableByte::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(2U, len);

        VariableByte::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 1, output[i]);
}

