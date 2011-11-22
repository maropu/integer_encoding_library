/*-----------------------------------------------------------------------------
 *  OPTPForDelta_utest.cpp - A unit test for OPTPForDelta.
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
#include "compress/OPTPForDelta.hpp"

TEST(OPTPForDeltaTest, ValidationEncode32_0b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[2 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 0;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(2U, len);

        OPTPForDelta::decodeArray(&cdata[0], 2U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(0U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_1b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[3 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 1;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(3U, len);

        OPTPForDelta::decodeArray(&cdata[0], 3U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(1U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_2b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[4 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 2;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(4U, len);

        OPTPForDelta::decodeArray(&cdata[0], 4U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(2U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_3b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[5 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 4;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(5U, len);

        OPTPForDelta::decodeArray(&cdata[0], 5U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(4U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_4b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[6 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 8;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(6U, len);

        OPTPForDelta::decodeArray(&cdata[0], 6U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(8U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_5b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[7 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 16;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(7U, len);

        OPTPForDelta::decodeArray(&cdata[0], 7U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(16U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_6b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[8 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 32;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(8U, len);

        OPTPForDelta::decodeArray(&cdata[0], 8U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(32U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_7b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[9 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 64;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(9U, len);

        OPTPForDelta::decodeArray(&cdata[0], 9U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(64U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_8b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[10 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 128;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(10U, len);

        OPTPForDelta::decodeArray(&cdata[0], 10U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(128U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_9b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[11 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 256;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(11U, len);

        OPTPForDelta::decodeArray(&cdata[0], 11U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(256U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_10b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[12 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 512;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(12U, len);

        OPTPForDelta::decodeArray(&cdata[0], 12U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(512U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_11b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[13 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 1024;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(13U, len);

        OPTPForDelta::decodeArray(&cdata[0], 13U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(1024U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_12b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[14 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 2048;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(14U, len);

        OPTPForDelta::decodeArray(&cdata[0], 14U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(2048U, output[i]);
}

TEST(OPTPForDeltaTest, ValidationEncode32_13b) {
        uint32_t        len;
        uint32_t        input[32];
        uint32_t        output[32 + TAIL_MERGIN];
        uint32_t        cdata[15 + TAIL_MERGIN];

        for (int i = 0; i < 32; i++)
                input[i] = 4096;

        OPTPForDelta::encodeArray(&input[0], 32U, &cdata[0], len);

        EXPECT_EQ(15U, len);

        OPTPForDelta::decodeArray(&cdata[0], 15U, &output[0], 32U);

        for (int i = 0; i < 32; i++)
                EXPECT_EQ(4096U, output[i]);
}

