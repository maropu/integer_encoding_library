/*-----------------------------------------------------------------------------
 *  VSEncodingRest_utest.cpp - A unit test for VSEncodingRest.
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
#include "compress/VSEncodingRest.hpp"

TEST(VSEncodingRestTest, ValidationEncode1b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[4 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode2b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[6 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 1;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 1, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 1, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode3b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[8 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 2;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 2, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 2, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode4b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[10 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 3;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 3, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 3, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode5b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[12 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 4;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 4, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 4, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode6b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[14 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 5;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 5, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(14U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 5, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode7b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[16 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 6;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 6, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(16U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 6, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode8b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[18 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 7;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 7, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(18U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 7, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode9b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[20 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 8;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 8, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(20U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 8, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode10b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[22 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 9;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 9, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(22U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 9, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode11b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[24 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 10;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(13U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 10, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(24U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 10, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode12b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[26 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 11;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(14U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 11, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(26U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 11, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode16b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[34 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 15;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(18U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 15, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(34U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 15, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode20b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[42 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 19;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(22U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 19, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(42U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 19, output[i]);
}

TEST(VSEncodingRestTest, ValidationEncode32b) {
        int             i;
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[66 + TAIL_MERGIN];

        for (i = 0; i < 64; i++)
                input[i] = 1U << 31;

        /* length: 1 */
        VSEncodingRest::encodeArray(&input[0], 1U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 1U);

        for (i = 0; i < 1; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 2 */
        VSEncodingRest::encodeArray(&input[0], 2U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 2U);

        for (i = 0; i < 2; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 3 */
        VSEncodingRest::encodeArray(&input[0], 3U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 3U);

        for (i = 0; i < 3; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 4 */
        VSEncodingRest::encodeArray(&input[0], 4U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 4U);

        for (i = 0; i < 4; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 5 */
        VSEncodingRest::encodeArray(&input[0], 5U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 5U);

        for (i = 0; i < 5; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 6 */
        VSEncodingRest::encodeArray(&input[0], 6U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 6U);

        for (i = 0; i < 6; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 7 */
        VSEncodingRest::encodeArray(&input[0], 7U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 7U);

        for (i = 0; i < 7; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 8 */
        VSEncodingRest::encodeArray(&input[0], 8U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 8U);

        for (i = 0; i < 8; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 9 */
        VSEncodingRest::encodeArray(&input[0], 9U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 9U);

        for (i = 0; i < 9; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 10 */
        VSEncodingRest::encodeArray(&input[0], 10U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 10U);

        for (i = 0; i < 10; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 11 */
        VSEncodingRest::encodeArray(&input[0], 11U, &cdata[0], len);

        EXPECT_EQ(13U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 11U);

        for (i = 0; i < 11; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 12 */
        VSEncodingRest::encodeArray(&input[0], 12U, &cdata[0], len);

        EXPECT_EQ(14U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 12U);

        for (i = 0; i < 12; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 14 */
        VSEncodingRest::encodeArray(&input[0], 14U, &cdata[0], len);

        EXPECT_EQ(16U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 14U);

        for (i = 0; i < 14; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 16 */
        VSEncodingRest::encodeArray(&input[0], 16U, &cdata[0], len);

        EXPECT_EQ(18U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 16U);

        for (i = 0; i < 16; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 32 */
        VSEncodingRest::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(34U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 32U);

        for (i = 0; i < 32; i++)
                EXPECT_EQ(1U << 31, output[i]);

        /* length: 64 */
        VSEncodingRest::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(66U, len);

        VSEncodingRest::decodeArray(&cdata[0], 0U, &output[0], 64U);

        for (i = 0; i < 64; i++)
                EXPECT_EQ(1U << 31, output[i]);
}

