/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks_utest.cpp - A unit test for VSEncodingBlocks.
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
#include "compress/VSEncodingBlocks.hpp"

TEST(VSEncodingBlocksTest, ValidationEncode1b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[4 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 1;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 4U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode1b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[5 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 1;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 5U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode2b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[5 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 2;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 5U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(2U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode2b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[7 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 2;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 7U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(2U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode3b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[6 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 4;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 6U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(4U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode3b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[9 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 4;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 9U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(4U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode4b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[7 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 8;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 7U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(8U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode4b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[11 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 8;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 11U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(8U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode5b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[8 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 16;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 8U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(16U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode5b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[13 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 16;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(13U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 13U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(16U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode6b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[9 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 32;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 9U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(32U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode6b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[15 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 32;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(15U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 15U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(32U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode7b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[10 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 64;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 10U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(64U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode7b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[17 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 64;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(17U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 17U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(64U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode8b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[11 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 128;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 11U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(128U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode8b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[19 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 128;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(19U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 19U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(128U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode9b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[12 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 256;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 12U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(256U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode9b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[21 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 256;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(21U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 21U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(256U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode10b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[13 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 512;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(13U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 13U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(512U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode10b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[23 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 512;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(23U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 23U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(512U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode11b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[14 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 1024;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(14U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 14U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(1024U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode11b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[25 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 1024;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(25U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 25U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(1024U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode12b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[15 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 2048;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(15U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 15U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(2048U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode12b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[27 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 2048;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(27U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 27U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(2048U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode16b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[19 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 32768;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(19U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 19U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(32768U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode16b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[35 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 32768;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(35U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 35U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(32768U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode20b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[23 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 524288;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(23U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 23U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(524288U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode20b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[43 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 524288;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(43U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 43U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(524288U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode32b_1p) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32];
        uint32_t        cdata[35 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 214483648;

        VSEncodingBlocks::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(35U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 35U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(214483648U, output[i]);
}

TEST(VSEncodingBlocksTest, ValidationEncode32b_2p) {
        uint32_t        len;
        uint32_t        input[64];
        uint32_t        output[64];
        uint32_t        cdata[67 + TAIL_MERGIN];

        for (int i = 0; i < 64; i++)
                input[i] = 214483648;

        VSEncodingBlocks::encodeArray(&input[0], 64U, &cdata[0], len);

        EXPECT_EQ(67U, len);

        VSEncodingBlocks::decodeArray(&cdata[0], 67U, &output[0], 64U);

        for (int i = 0; i < 64; i++)
                EXPECT_EQ(214483648U, output[i]);
}

