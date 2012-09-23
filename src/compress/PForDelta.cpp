/*-----------------------------------------------------------------------------
 *  PForDelta.cpp - A original implementation of PForDelta
 *
 *  Coding-Style: google-styleguide
 *      https://code.google.com/p/google-styleguide/
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *
 *  Copyright 2012 Integer Encoding Library <integerencoding_at_isti.cnr.it>
 *      http://integerencoding.ist.cnr.it/
 *-----------------------------------------------------------------------------
 */

#include <compress/policy/PForDelta.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const double PFORDELTA_RATIO = 0.1;

/*
 * Lemme resume the block's format here:
 *  |--------------------------------------------------|
 *  |     b   | nExceptions | s16encodedExceptionSize  |
 *  |  6 bits |   10 bits   |         16 bits          |
 *  |--------------------------------------------------|
 *  |              fixed_b(codewords)                  |
 *  |--------------------------------------------------|
 *  |                s16(exceptions)                   |
 *  |--------------------------------------------------|
 */
const size_t PFORDELTA_B = 6;
const size_t PFORDELTA_NEXCEPT = 10;
const size_t PFORDELTA_EXCEPTSZ = 16;

inline void PFORDELTA_UNPACK0(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0;
          i < PFORDELTA_BLOCKSZ; i += 16, out += 16) {
    ZMEMCPY128(out);
    ZMEMCPY128(out + 4);
    ZMEMCPY128(out + 8);
    ZMEMCPY128(out + 12);
  }
}

inline void PFORDELTA_UNPACK1(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 31;
    out[1] = (val >> 30) & 0x01;
    out[2] = (val >> 29) & 0x01;
    out[3] = (val >> 28) & 0x01;
    out[4] = (val >> 27) & 0x01;
    out[5] = (val >> 26) & 0x01;
    out[6] = (val >> 25) & 0x01;
    out[7] = (val >> 24) & 0x01;
    out[8] = (val >> 23) & 0x01;
    out[9] = (val >> 22) & 0x01;
    out[10] = (val >> 21) & 0x01;
    out[11] = (val >> 20) & 0x01;
    out[12] = (val >> 19) & 0x01;
    out[13] = (val >> 18) & 0x01;
    out[14] = (val >> 17) & 0x01;
    out[15] = (val >> 16) & 0x01;
    out[16] = (val >> 15) & 0x01;
    out[17] = (val >> 14) & 0x01;
    out[18] = (val >> 13) & 0x01;
    out[19] = (val >> 12) & 0x01;
    out[20] = (val >> 11) & 0x01;
    out[21] = (val >> 10) & 0x01;
    out[22] = (val >> 9) & 0x01;
    out[23] = (val >> 8) & 0x01;
    out[24] = (val >> 7) & 0x01;
    out[25] = (val >> 6) & 0x01;
    out[26] = (val >> 5) & 0x01;
    out[27] = (val >> 4) & 0x01;
    out[28] = (val >> 3) & 0x01;
    out[29] = (val >> 2) & 0x01;
    out[30] = (val >> 1) & 0x01;
    out[31] = val & 0x01;
  }
}

inline void PFORDELTA_UNPACK2(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 16, out += 16, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 30;
    out[1] = (val >> 28) & 0x03;
    out[2] = (val >> 26) & 0x03;
    out[3] = (val >> 24) & 0x03;
    out[4] = (val >> 22) & 0x03;
    out[5] = (val >> 20) & 0x03;
    out[6] = (val >> 18) & 0x03;
    out[7] = (val >> 16) & 0x03;
    out[8] = (val >> 14) & 0x03;
    out[9] = (val >> 12) & 0x03;
    out[10] = (val >> 10) & 0x03;
    out[11] = (val >> 8) & 0x03;
    out[12] = (val >> 6) & 0x03;
    out[13] = (val >> 4) & 0x03;
    out[14] = (val >> 2) & 0x03;
    out[15] = val & 0x03;
  }
}

inline void PFORDELTA_UNPACK3(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 29;
    out[1] = (val >> 26) & 0x07;
    out[2] = (val >> 23) & 0x07;
    out[3] = (val >> 20) & 0x07;
    out[4] = (val >> 17) & 0x07;
    out[5] = (val >> 14) & 0x07;
    out[6] = (val >> 11) & 0x07;
    out[7] = (val >> 8) & 0x07;
    out[8] = (val >> 5) & 0x07;
    out[9] = (val >> 2) & 0x07;
    out[10] = (val << 1) & 0x07;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[10] |= val >> 31;
    out[11] = (val >> 28) & 0x07;
    out[12] = (val >> 25) & 0x07;
    out[13] = (val >> 22) & 0x07;
    out[14] = (val >> 19) & 0x07;
    out[15] = (val >> 16) & 0x07;
    out[16] = (val >> 13) & 0x07;
    out[17] = (val >> 10) & 0x07;
    out[18] = (val >> 7) & 0x07;
    out[19] = (val >> 4) & 0x07;
    out[20] = (val >> 1) & 0x07;
    out[21] = (val << 2) & 0x07;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[21] |= val >> 30;
    out[22] = (val >> 27) & 0x07;
    out[23] = (val >> 24) & 0x07;
    out[24] = (val >> 21) & 0x07;
    out[25] = (val >> 18) & 0x07;
    out[26] = (val >> 15) & 0x07;
    out[27] = (val >> 12) & 0x07;
    out[28] = (val >> 9) & 0x07;
    out[29] = (val >> 6) & 0x07;
    out[30] = (val >> 3) & 0x07;
    out[31] = val & 0x07;
  }
}

inline void PFORDELTA_UNPACK4(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 8, out += 8, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 28;
    out[1] = (val >> 24) & 0x0f;
    out[2] = (val >> 20) & 0x0f;
    out[3] = (val >> 16) & 0x0f;
    out[4] = (val >> 12) & 0x0f;
    out[5] = (val >> 8) & 0x0f;
    out[6] = (val >> 4) & 0x0f;
    out[7] = val & 0x0f;
  }
}

inline void PFORDELTA_UNPACK5(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 27;
    out[1] = (val >> 22) & 0x1f;
    out[2] = (val >> 17) & 0x1f;
    out[3] = (val >> 12) & 0x1f;
    out[4] = (val >> 7) & 0x1f;
    out[5] = (val >> 2) & 0x1f;
    out[6] = (val << 3) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[6] |= val >> 29;
    out[7] = (val >> 24) & 0x1f;
    out[8] = (val >> 19) & 0x1f;
    out[9] = (val >> 14) & 0x1f;
    out[10] = (val >> 9) & 0x1f;
    out[11] = (val >> 4) & 0x1f;
    out[12] = (val << 1) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[12] |= val >> 0x1f;
    out[13] = (val >> 26) & 0x1f;
    out[14] = (val >> 21) & 0x1f;
    out[15] = (val >> 16) & 0x1f;
    out[16] = (val >> 11) & 0x1f;
    out[17] = (val >> 6) & 0x1f;
    out[18] = (val >> 1) & 0x1f;
    out[19] = (val << 4) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[19] |= val >> 28;
    out[20] = (val >> 23) & 0x1f;
    out[21] = (val >> 18) & 0x1f;
    out[22] = (val >> 13) & 0x1f;
    out[23] = (val >> 8) & 0x1f;
    out[24] = (val >> 3) & 0x1f;
    out[25] = (val << 2) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[25] |= val >> 30;
    out[26] = (val >> 25) & 0x1f;
    out[27] = (val >> 20) & 0x1f;
    out[28] = (val >> 15) & 0x1f;
    out[29] = (val >> 10) & 0x1f;
    out[30] = (val >> 5) & 0x1f;
    out[31] = val & 0x1f;
  }
}

inline void PFORDELTA_UNPACK6(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 16, out += 16, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 26;
    out[1] = (val >> 20) & 0x3f;
    out[2] = (val >> 14) & 0x3f;
    out[3] = (val >> 8) & 0x3f;
    out[4] = (val >> 2) & 0x3f;
    out[5] = (val << 4) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[5] |= val >> 28;
    out[6] = (val >> 22) & 0x3f;
    out[7] = (val >> 16) & 0x3f;
    out[8] = (val >> 10) & 0x3f;
    out[9] = (val >> 4) & 0x3f;
    out[10] = (val << 2) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[10] |= val >> 30;
    out[11] = (val >> 24) & 0x3f;
    out[12] = (val >> 18) & 0x3f;
    out[13] = (val >> 12) & 0x3f;
    out[14] = (val >> 6) & 0x3f;
    out[15] = val & 0x3f;
  }
}

inline void PFORDELTA_UNPACK7(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 7) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 25;
    out[1] = (in[0] >> 18) & 0x7f;
    out[2] = (in[0] >> 11) & 0x7f;
    out[3] = (in[0] >> 4) & 0x7f;
    out[4] = (in[0] << 3) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[4] |= in[1] >> 29;
    out[5] = (in[1] >> 22) & 0x7f;
    out[6] = (in[1] >> 15) & 0x7f;
    out[7] = (in[1] >> 8) & 0x7f;
    out[8] = (in[1] >> 1) & 0x7f;
    out[9] = (in[1] << 6) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[9] |= in[2] >> 26;
    out[10] = (in[2] >> 19) & 0x7f;
    out[11] = (in[2] >> 12) & 0x7f;
    out[12] = (in[2] >> 5) & 0x7f;
    out[13] = (in[2] << 2) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[13] |= in[3] >> 30;
    out[14] = (in[3] >> 23) & 0x7f;
    out[15] = (in[3] >> 16) & 0x7f;
    out[16] = (in[3] >> 9) & 0x7f;
    out[17] = (in[3] >> 2) & 0x7f;
    out[18] = (in[3] << 5) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[18] |= in[4] >> 27;
    out[19] = (in[4] >> 20) & 0x7f;
    out[20] = (in[4] >> 13) & 0x7f;
    out[21] = (in[4] >> 6) & 0x7f;
    out[22] = (in[4] << 1) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[22] |= in[5] >> 31;
    out[23] = (in[5] >> 24) & 0x7f;
    out[24] = (in[5] >> 17) & 0x7f;
    out[25] = (in[5] >> 10) & 0x7f;
    out[26] = (in[5] >> 3) & 0x7f;
    out[27] = (in[5] << 4) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[27] |= in[6] >> 28;
    out[28] = (in[6] >> 21) & 0x7f;
    out[29] = (in[6] >> 14) & 0x7f;
    out[30] = (in[6] >> 7) & 0x7f;
    out[31] = in[6] & 0x7f;
  }
}

inline void PFORDELTA_UNPACK8(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 4, out += 4, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 24;
    out[1] = (in[0] >> 16) & 0xff;
    out[2] = (in[0] >> 8) & 0xff;
    out[3] = in[0] & 0xff;
  }
}

inline void PFORDELTA_UNPACK9(uint32_t * restrict out,
                              const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 9) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 23;
    out[1] = (in[0] >> 14) & 0x01ff;
    out[2] = (in[0] >> 5) & 0x01ff;
    out[3] = (in[0] << 4) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[3] |= in[1] >> 28;
    out[4] = (in[1] >> 19) & 0x01ff;
    out[5] = (in[1] >> 10) & 0x01ff;
    out[6] = (in[1] >> 1) & 0x01ff;
    out[7] = (in[1] << 8) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[7] |= in[2] >> 24;
    out[8] = (in[2] >> 15) & 0x01ff;
    out[9] = (in[2] >> 6) & 0x01ff;
    out[10] = (in[2] << 3) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[10] |= in[3] >> 29;
    out[11] = (in[3] >> 20) & 0x01ff;
    out[12] = (in[3] >> 11) & 0x01ff;
    out[13] = (in[3] >> 2) & 0x01ff;
    out[14] = (in[3] << 7) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[14] |= in[4] >> 25;
    out[15] = (in[4] >> 16) & 0x01ff;
    out[16] = (in[4] >> 7) & 0x01ff;
    out[17] = (in[4] << 2) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[17] |= in[5] >> 30;
    out[18] = (in[5] >> 21) & 0x01ff;
    out[19] = (in[5] >> 12) & 0x01ff;
    out[20] = (in[5] >> 3) & 0x01ff;
    out[21] = (in[5] << 6) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[21] |= in[6] >> 26;
    out[22] = (in[6] >> 17) & 0x01ff;
    out[23] = (in[6] >> 8) & 0x01ff;
    out[24] = (in[6] << 1) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[24] |= in[7] >> 31;
    out[25] = (in[7] >> 22) & 0x01ff;
    out[26] = (in[7] >> 13) & 0x01ff;
    out[27] = (in[7] >> 4) & 0x01ff;
    out[28] = (in[7] << 5) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[28] |= in[8] >> 27;
    out[29] = (in[8] >> 18) & 0x01ff;
    out[30] = (in[8] >> 9) & 0x01ff;
    out[31] = in[8] & 0x01ff;
  }
}

inline void PFORDELTA_UNPACK10(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 16, out += 16, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 22;
    out[1] = (in[0] >> 12) & 0x03ff;
    out[2] = (in[0] >> 2) & 0x03ff;
    out[3] = (in[0] << 8) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[3] |= in[1] >> 24;
    out[4] = (in[1] >> 14) & 0x03ff;
    out[5] = (in[1] >> 4) & 0x03ff;
    out[6] = (in[1] << 6) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[6] |= in[2] >> 26;
    out[7] = (in[2] >> 16) & 0x03ff;
    out[8] = (in[2] >> 6) & 0x03ff;
    out[9] = (in[2] << 4) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[9] |= in[3] >> 28;
    out[10] = (in[3] >> 18) & 0x03ff;
    out[11] = (in[3] >> 8) & 0x03ff;
    out[12] = (in[3] << 2) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[12] |= in[4] >> 30;
    out[13] = (in[4] >> 20) & 0x03ff;
    out[14] = (in[4] >> 10) & 0x03ff;
    out[15] = in[4] & 0x03ff;
  }
}

inline void PFORDELTA_UNPACK11(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 11) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 21;
    out[1] = (val >> 10) & 0x07ff;
    out[2] = (val << 1) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |= val >> 31;
    out[3] = (val >> 20) & 0x07ff;
    out[4] = (val >> 9) & 0x07ff;
    out[5] = (val << 2) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[5] |= val >> 30;
    out[6] = (val >> 19) & 0x07ff;
    out[7] = (val >> 8) & 0x07ff;
    out[8] = (val << 3) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[8] |= val >> 29;
    out[9] = (val >> 18) & 0x07ff;
    out[10] = (val >> 7) & 0x07ff;
    out[11] = (val << 4) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[11] |= val >> 28;
    out[12] = (val >> 17) & 0x07ff;
    out[13] = (val >> 6) & 0x07ff;
    out[14] = (val << 5) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[14] |= val >> 27;
    out[15] = (val >> 16) & 0x07ff;
    out[16] = (val >> 5) & 0x07ff;
    out[17] = (val << 6) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[17] |= val >> 26;
    out[18] = (val >> 15) & 0x07ff;
    out[19] = (val >> 4) & 0x07ff;
    out[20] = (val << 7) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[20] |= val >> 25;
    out[21] = (val >> 14) & 0x07ff;
    out[22] = (val >> 3) & 0x07ff;
    out[23] = (val << 8) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[23] |= val >> 24;
    out[24] = (val >> 13) & 0x07ff;
    out[25] = (val >> 2) & 0x07ff;
    out[26] = (val << 9) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[26] |= val >> 23;
    out[27] = (val >> 12) & 0x07ff;
    out[28] = (val >> 1) & 0x07ff;
    out[29] = (val << 10) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[29] |= val >> 22;
    out[30] = (val >> 11) & 0x07ff;
    out[31] = val & 0x07ff;
  }
}

inline void PFORDELTA_UNPACK12(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 8, out += 8, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 20;
    out[1] = (val >> 8) & 0x0fff;
    out[2] = (val << 4) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |= val >> 28;
    out[3] = (val >> 16) & 0x0fff;
    out[4] = (val >> 4) & 0x0fff;
    out[5] = (val << 8) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[5] |= val >> 24;
    out[6] = (val >> 12) & 0x0fff;
    out[7] = val & 0x0fff;
  }
}

inline void PFORDELTA_UNPACK13(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 32, out += 32, in += 13) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = val >> 19;
    out[1] = (val >> 6) & 0x1fff;
    out[2] = (val << 7) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |= val >> 25;
    out[3] = (val >> 12) & 0x1fff;
    out[4] = (val << 1) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[4] |= val >> 31;
    out[5] = (val >> 18) & 0x1fff;
    out[6] = (val >> 5) & 0x1fff;
    out[7] = (val << 8) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[7] |= val >> 24;
    out[8] = (val >> 11) & 0x1fff;
    out[9] = (val << 2) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[9] |= val >> 30;
    out[10] = (val >> 17) & 0x1fff;
    out[11] = (val >> 4) & 0x1fff;
    out[12] = (val << 9) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[12] |= val >> 23;
    out[13] = (val >> 10) & 0x1fff;
    out[14] = (val << 3) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[14] |= val >> 29;
    out[15] = (val >> 16) & 0x1fff;
    out[16] = (val >> 3) & 0x1fff;
    out[17] = (val << 10) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[17] |= val >> 22;
    out[18] = (val >> 9) & 0x1fff;
    out[19] = (val << 4) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[19] |= val >> 28;
    out[20] = (val >> 15) & 0x1fff;
    out[21] = (val >> 2) & 0x1fff;
    out[22] = (val << 11) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[22] |= val >> 21;
    out[23] = (val >> 8) & 0x1fff;
    out[24] = (val << 5) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[24] |= val >> 27;
    out[25] = (val >> 14) & 0x1fff;
    out[26] = (val >> 1) & 0x1fff;
    out[27] = (val << 12) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[27] |= val >> 20;
    out[28] = (val >> 7) & 0x1fff;
    out[29] = (val << 6) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[29] |= val >> 26;
    out[30] = (val >> 13) & 0x1fff;
    out[31] = val & 0x1fff;
  }
}

inline void PFORDELTA_UNPACK16(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 2, out += 2, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 16;
    out[1] = in[0] & 0xffff;
  }
}

inline void PFORDELTA_UNPACK20(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 8, out += 8, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = in[0] >> 12;
    out[1] = (in[0] << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |= in[1] >> 24;
    out[2] = (in[1] >> 4) & 0x0fffff;
    out[3] = (in[1] << 16) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |= in[2] >> 16;
    out[4] = (in[2] << 4) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[4] |= in[3] >> 28;
    out[5] = (in[3] >> 8) & 0x0fffff;
    out[6] = (in[3] << 12) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[6] |= in[4] >> 20;
    out[7] = in[4] & 0x0fffff;
  }
}

inline void PFORDELTA_UNPACK32(uint32_t * restrict out,
                               const uint32_t * restrict in) {
  for (uint32_t i = 0; i < PFORDELTA_BLOCKSZ;
          i += 1, out += 1, in += 1)
    out[0] = BYTEORDER_FREE_LOAD32(in);
}

/* A interface of unpacking functions above */
typedef void (*p4delta_unpack_t)(uint32_t *out,
                                 const uint32_t *in);

p4delta_unpack_t PFORDELTA_UNPACK[] = {
  PFORDELTA_UNPACK0,
  PFORDELTA_UNPACK1,
  PFORDELTA_UNPACK2,
  PFORDELTA_UNPACK3,
  PFORDELTA_UNPACK4,
  PFORDELTA_UNPACK5,
  PFORDELTA_UNPACK6,
  PFORDELTA_UNPACK7,
  PFORDELTA_UNPACK8,
  PFORDELTA_UNPACK9,
  PFORDELTA_UNPACK10,
  PFORDELTA_UNPACK11,
  PFORDELTA_UNPACK12,
  PFORDELTA_UNPACK13,
  NULL,
  NULL,
  PFORDELTA_UNPACK16,
  NULL,
  NULL,
  NULL,
  PFORDELTA_UNPACK20,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  PFORDELTA_UNPACK32
};

/* A hard-corded Simple16 decoder wirtten in the original code */
inline void PFORDELTA_S16_DECODE(const uint32_t * restrict in,
                                 uint32_t len,
                                 uint32_t * restrict out,
                                 uint32_t nvalue) {
  ASSERT(in != NULL);
  ASSERT(out != NULL);

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  uint32_t nlen = 0;

  while (LIKELY(len > nlen)) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    in++;

    uint32_t hd = val >> 28;

    switch (hd) {
      case 0: {
        *out++ = (val >> 27) & 0x01;
        *out++ = (val >> 26) & 0x01;
        *out++ = (val >> 25) & 0x01;
        *out++ = (val >> 24) & 0x01;
        *out++ = (val >> 23) & 0x01;
        *out++ = (val >> 22) & 0x01;
        *out++ = (val >> 21) & 0x01;
        *out++ = (val >> 20) & 0x01;
        *out++ = (val >> 19) & 0x01;
        *out++ = (val >> 18) & 0x01;
        *out++ = (val >> 17) & 0x01;
        *out++ = (val >> 16) & 0x01;
        *out++ = (val >> 15) & 0x01;
        *out++ = (val >> 14) & 0x01;
        *out++ = (val >> 13) & 0x01;
        *out++ = (val >> 12) & 0x01;
        *out++ = (val >> 11) & 0x01;
        *out++ = (val >> 10) & 0x01;
        *out++ = (val >> 9) & 0x01;
        *out++ = (val >> 8) & 0x01;
        *out++ = (val >> 7) & 0x01;
        *out++ = (val >> 6) & 0x01;
        *out++ = (val >> 5) & 0x01;
        *out++ = (val >> 4) & 0x01;
        *out++ = (val >> 3) & 0x01;
        *out++ = (val >> 2) & 0x01;
        *out++ = (val >> 1) & 0x01;
        *out++ = val & 0x01;
        nlen += 28;
        break;
      }

      case 1: {
        *out++ = (val >> 26) & 0x03;
        *out++ = (val >> 24) & 0x03;
        *out++ = (val >> 22) & 0x03;
        *out++ = (val >> 20) & 0x03;
        *out++ = (val >> 18) & 0x03;
        *out++ = (val >> 16) & 0x03;
        *out++ = (val >> 14) & 0x03;
        *out++ = (val >> 13) & 0x01;
        *out++ = (val >> 12) & 0x01;
        *out++ = (val >> 11) & 0x01;
        *out++ = (val >> 10) & 0x01;
        *out++ = (val >> 9) & 0x01;
        *out++ = (val >> 8) & 0x01;
        *out++ = (val >> 7) & 0x01;
        *out++ = (val >> 6) & 0x01;
        *out++ = (val >> 5) & 0x01;
        *out++ = (val >> 4) & 0x01;
        *out++ = (val >> 3) & 0x01;
        *out++ = (val >> 2) & 0x01;
        *out++ = (val >> 1) & 0x01;
        *out++ = val & 0x01;
        nlen += 21;
        break;
      }

      case 2: {
        *out++ = (val >> 27) & 0x01;
        *out++ = (val >> 26) & 0x01;
        *out++ = (val >> 25) & 0x01;
        *out++ = (val >> 24) & 0x01;
        *out++ = (val >> 23) & 0x01;
        *out++ = (val >> 22) & 0x01;
        *out++ = (val >> 21) & 0x01;
        *out++ = (val >> 19) & 0x03;
        *out++ = (val >> 17) & 0x03;
        *out++ = (val >> 15) & 0x03;
        *out++ = (val >> 13) & 0x03;
        *out++ = (val >> 11) & 0x03;
        *out++ = (val >> 9) & 0x03;
        *out++ = (val >> 7) & 0x03;
        *out++ = (val >> 6) & 0x01;
        *out++ = (val >> 5) & 0x01;
        *out++ = (val >> 4) & 0x01;
        *out++ = (val >> 3) & 0x01;
        *out++ = (val >> 2) & 0x01;
        *out++ = (val >> 1) & 0x01;
        *out++ = val & 0x01;
        nlen += 21;
        break;
      }

      case 3: {
        *out++ = (val >> 27) & 0x01;
        *out++ = (val >> 26) & 0x01;
        *out++ = (val >> 25) & 0x01;
        *out++ = (val >> 24) & 0x01;
        *out++ = (val >> 23) & 0x01;
        *out++ = (val >> 22) & 0x01;
        *out++ = (val >> 21) & 0x01;
        *out++ = (val >> 20) & 0x01;
        *out++ = (val >> 19) & 0x01;
        *out++ = (val >> 18) & 0x01;
        *out++ = (val >> 17) & 0x01;
        *out++ = (val >> 16) & 0x01;
        *out++ = (val >> 15) & 0x01;
        *out++ = (val >> 14) & 0x01;
        *out++ = (val >> 12) & 0x03;
        *out++ = (val >> 10) & 0x03;
        *out++ = (val >> 8) & 0x03;
        *out++ = (val >> 6) & 0x03;
        *out++ = (val >> 4) & 0x03;
        *out++ = (val >> 2) & 0x03;
        *out++ = val & 0x03;
        nlen += 21;
        break;
      }

      case 4: {
        *out++ = (val >> 26) & 0x03;
        *out++ = (val >> 24) & 0x03;
        *out++ = (val >> 22) & 0x03;
        *out++ = (val >> 20) & 0x03;
        *out++ = (val >> 18) & 0x03;
        *out++ = (val >> 16) & 0x03;
        *out++ = (val >> 14) & 0x03;
        *out++ = (val >> 12) & 0x03;
        *out++ = (val >> 10) & 0x03;
        *out++ = (val >> 8) & 0x03;
        *out++ = (val >> 6) & 0x03;
        *out++ = (val >> 4) & 0x03;
        *out++ = (val >> 2) & 0x03;
        *out++ = val & 0x03;
        nlen += 14;
        break;
      }

      case 5: {
        *out++ = (val >> 24) & 0x0f;
        *out++ = (val >> 21) & 0x07;
        *out++ = (val >> 18) & 0x07;
        *out++ = (val >> 15) & 0x07;
        *out++ = (val >> 12) & 0x07;
        *out++ = (val >> 9) & 0x07;
        *out++ = (val >> 6) & 0x07;
        *out++ = (val >> 3) & 0x07;
        *out++ = val & 0x07;

        nlen += 9;
        break;
      }

      case 6: {
        *out++ = (val >> 25) & 0x07;
        *out++ = (val >> 21) & 0x0f;
        *out++ = (val >> 17) & 0x0f;
        *out++ = (val >> 13) & 0x0f;
        *out++ = (val >> 9) & 0x0f;
        *out++ = (val >> 6) & 0x07;
        *out++ = (val >> 3) & 0x07;
        *out++ = val & 0x07;
        nlen += 8;
        break;
      }

      case 7: {
        *out++ = (val >> 24) & 0x0f;
        *out++ = (val >> 20) & 0x0f;
        *out++ = (val >> 16) & 0x0f;
        *out++ = (val >> 12) & 0x0f;
        *out++ = (val >> 8) & 0x0f;
        *out++ = (val >> 4) & 0x0f;
        *out++ = val & 0x0f;
        nlen += 7;
        break;
      }

      case 8: {
        *out++ = (val >> 23) & 0x1f;
        *out++ = (val >> 18) & 0x1f;
        *out++ = (val >> 13) & 0x1f;
        *out++ = (val >> 8) & 0x1f;
        *out++ = (val >> 4) & 0x0f;
        *out++ = val & 0x0f;
        nlen += 6;
        break;
      }

      case 9: {
        *out++ = (val >> 24) & 0x0f;
        *out++ = (val >> 20) & 0x0f;
        *out++ = (val >> 15) & 0x1f;
        *out++ = (val >> 10) & 0x1f;
        *out++ = (val >> 5) & 0x1f;
        *out++ = val & 0x1f;
        nlen += 6;
        break;
      }

      case 10: {
        *out++ = (val >> 22) & 0x3f;
        *out++ = (val >> 16) & 0x3f;
        *out++ = (val >> 10) & 0x3f;
        *out++ = (val >> 5) & 0x1f;
        *out++ = val & 0x1f;
        nlen += 5;
        break;
      }

      case 11: {
        *out++ = (val >> 23) & 0x1f;
        *out++ = (val >> 18) & 0x1f;
        *out++ = (val >> 12) & 0x3f;
        *out++ = (val >> 6) & 0x3f;
        *out++ = val & 0x3f;
        nlen += 5;
        break;
      }

      case 12: {
        *out++ = (val >> 21) & 0x7f;
        *out++ = (val >> 14) & 0x7f;
        *out++ = (val >> 7) & 0x7f;
        *out++ = val & 0x7f;
        nlen += 4;
        break;
      }

      case 13: {
        *out++ = (val >> 18) & 0x03ff;
        *out++ = (val >> 9) & 0x01ff;
        *out++ = val & 0x01ff;
        nlen += 3;
        break;
      }

      case 14: {
        *out++ = (val >> 14) & 0x3fff;
        *out++ = val & 0x3fff;
        nlen += 2;
        break;
      }

      case 15: {
        *out++ = val & 0x0fffffff;
        nlen += 1;
        break;
      }
    }
  }
}

const uint32_t PFORDELTA_LOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 20, 32
};

} /* namespace: */

PForDelta::PForDelta()
    : EncodingBase(E_P4D),
      s16_(),
      codewords_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptionsPositions_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptionsValues_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptions_(INITIALIZE_SPTR(
              uint32_t, 2 * PFORDELTA_BLOCKSZ)),
      encodedExceptions_(INITIALIZE_SPTR(
              uint32_t, s16_.require(2 * PFORDELTA_BLOCKSZ))) {}

PForDelta::PForDelta(int policy)
    : EncodingBase(policy),
      s16_(),
      codewords_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptionsPositions_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptionsValues_(INITIALIZE_SPTR(
              uint32_t, PFORDELTA_BLOCKSZ)),
      exceptions_(INITIALIZE_SPTR(
              uint32_t, 2 * PFORDELTA_BLOCKSZ)),
      encodedExceptions_(INITIALIZE_SPTR(
              uint32_t, s16_.require(2 * PFORDELTA_BLOCKSZ))) {}

PForDelta::~PForDelta() throw() {}

uint32_t PForDelta::tryB(uint32_t b,
                         const uint32_t *in,
                         uint64_t len) const {
  ASSERT(b <= 32);
  ASSERT(in != NULL);
  ASSERT(len != 0);

  ASSERT_ADDR(in, len);

  if (b == 32)
    return 0;

  uint32_t curExcept = 0;

  for (uint32_t i = 0; i < len; i++) {
    if (in[i] >= (1ULL << b))
      curExcept++;
  }

  return curExcept;
}

uint32_t PForDelta::findBestB(const uint32_t *in,
                              uint64_t len) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);

  ASSERT_ADDR(in, len);

  for (uint32_t i = 0; i < ARRAYSIZE(PFORDELTA_LOGS) - 1; i++) {
    uint32_t nExceptions = tryB(PFORDELTA_LOGS[i], in, len);

    if (nExceptions <= len * PFORDELTA_RATIO)
      return PFORDELTA_LOGS[i];
  }

  return PFORDELTA_LOGS[ARRAYSIZE(PFORDELTA_LOGS) - 1];
}

void PForDelta::encodeBlock(const uint32_t *in,
                            uint64_t len,
                            uint32_t *out,
                            uint64_t *nvalue) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);
  ASSERT(out != NULL);

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  /* Get working spaces */
  uint32_t *codewords = codewords_.get();
  uint32_t *exceptionsPositions = exceptionsPositions_.get();
  uint32_t *exceptionsValues = exceptionsValues_.get();
  uint32_t *exceptions = exceptions_.get();
  uint32_t *encodedExceptions = encodedExceptions_.get();

  BitsWriter wt(codewords, len);

  uint32_t b = findBestB(in, len);
  ASSERT(b <= 32);

  uint64_t curExcept = 0;
  uint64_t encodedExceptions_sz = 0;

  if (b < 32) {
    for (uint32_t i = 0; i < len; i++) {
      wt.write_bits(in[i], b);

      if (in[i] >= (1U << b)) {
        uint32_t e = in[i] >> b;
        exceptionsPositions[curExcept] = i;
        exceptionsValues[curExcept] = e;
        curExcept++;
      }
    }

    if (curExcept > 0) {
      for (uint32_t i = curExcept - 1; i > 0; i--) {
        uint32_t cur = exceptionsPositions[i];
        uint32_t prev = exceptionsPositions[i - 1];
        exceptionsPositions[i] = cur - prev;
      }

      for (uint32_t i = 0; i < curExcept; i++) {
        uint32_t excPos = (i > 0)?
            exceptionsPositions[i] - 1 : exceptionsPositions[i];
        uint32_t excVal = exceptionsValues[i] - 1;

        exceptions[i] = excPos;
        exceptions[i + curExcept] = excVal;
      }

      encodedExceptions_sz = s16_.require(len * 2);
      s16_.encodeArray(exceptions,
                      2 * curExcept,
                      encodedExceptions,
                      &encodedExceptions_sz);
    }
  } else {
    for (uint32_t i = 0; i < len; i++)
      wt.write_bits(in[i], 32);
  }

  wt.flush_bits();

  /* Write a header following the format */
  BYTEORDER_FREE_STORE32(out,
                         (b << (PFORDELTA_NEXCEPT + PFORDELTA_EXCEPTSZ)) |
                         (curExcept << PFORDELTA_EXCEPTSZ) | encodedExceptions_sz);
  out++;

  /* Write exceptional values */
  memcpy(out,
         encodedExceptions,
         encodedExceptions_sz * sizeof(uint32_t));
  out += encodedExceptions_sz;

  /* Write fix-length values */
  uint32_t codewords_sz = wt.size();
  memcpy(out,
         codewords,
         codewords_sz * sizeof(uint32_t));

  *nvalue = 1 + encodedExceptions_sz + codewords_sz;
}

void PForDelta::encodeArray(const uint32_t *in,
                            uint64_t len,
                            uint32_t *out,
                            uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (*nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  /* Output the number of blocks */
  uint64_t numBlocks = DIV_ROUNDUP(len, PFORDELTA_BLOCKSZ);
  BYTEORDER_FREE_STORE64(out, numBlocks);
  out += 2, *nvalue = 2;

  for (uint64_t i = 0; i < numBlocks; i++) {
    uint64_t csize = 0;

    if (LIKELY(i != numBlocks - 1)) {
      encodeBlock(in, PFORDELTA_BLOCKSZ, out, &csize);

      in += PFORDELTA_BLOCKSZ;
      out += csize;
    } else {
      /*
      * This is a code to pack gabage in the tail of lists.
      * I think it couldn't be a bottleneck.
      */
      uint32_t nblk = ((len % PFORDELTA_BLOCKSZ) != 0)?
          len % PFORDELTA_BLOCKSZ : PFORDELTA_BLOCKSZ;
      encodeBlock(in, nblk, out, &csize);
    }

    *nvalue += csize;
  }
}

void PForDelta::decodeArray(const uint32_t *in,
                            uint64_t len,
                            uint32_t *out,
                            uint64_t nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  /* If exists, exceptional values are packed in */
  uint32_t  except[2 * PFORDELTA_BLOCKSZ + 128];

  uint64_t numBlocks = BYTEORDER_FREE_LOAD64(in);
  in += 2;

  const uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  for (uint64_t i = 0; i < numBlocks; i++) {
    if (UNLIKELY(out >= oterm || in >= iterm))
      break;

    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    uint32_t b = val >> (32 - PFORDELTA_B);
    uint32_t nExceptions =
        (val >> (32 - (PFORDELTA_B + PFORDELTA_NEXCEPT))) &
        ((1 << PFORDELTA_NEXCEPT) - 1);
    uint32_t encodedExceptionsSize =
        val & ((1 << PFORDELTA_EXCEPTSZ) - 1);

    PFORDELTA_S16_DECODE(++in, 2 * nExceptions, except, 2 * nExceptions);
    in += encodedExceptionsSize;

    PFORDELTA_UNPACK[b](out, in);

    if (UNLIKELY(nExceptions > 0)) {
      int32_t lpos = -1;
      for (uint32_t j = 0; j < nExceptions; j++) {
        lpos += except[j] + 1;
        uint32_t excVal = except[j + nExceptions] + 1;
        excVal <<= b;
        out[lpos] |= excVal;

        ASSERT(lpos >= 0);
        ASSERT(uint32_t(lpos) < PFORDELTA_BLOCKSZ);
      }
    }

    out += PFORDELTA_BLOCKSZ;
    in += b * PFORDELTA_NBLOCK;
  }
}

uint64_t PForDelta::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
