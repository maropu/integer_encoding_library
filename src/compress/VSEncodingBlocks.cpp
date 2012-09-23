/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks.cpp - A naive implementation of VSEncoding
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

#include <compress/policy/VSEncodingBlocks.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSEBLOCKS_LOGLEN = 4;
const uint32_t VSEBLOCKS_LOGLOG = 4;
const uint32_t VSEBLOCKS_LOGDESC =
    VSEBLOCKS_LOGLEN + VSEBLOCKS_LOGLOG;

const uint32_t VSEBLOCKS_LENS_LEN = 1U << VSEBLOCKS_LOGLEN;
const uint32_t VSEBLOCKS_LOGS_LEN = 1U << VSEBLOCKS_LOGLOG;
const uint32_t VSEBLOCKS_DESC_LEN = 1U << VSEBLOCKS_LOGDESC;

inline void VSEBLOCKS_UNPACK1(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK2(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK3(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK4(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK5(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK6(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK7(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 32, out += 32, in += 7) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 25;
    out[1] = (val >> 18) & 0x7f;
    out[2] = (val >> 11) & 0x7f;
    out[3] = (val >> 4) & 0x7f;
    out[4] = (val << 3) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 1);

    out[4] |= val >> 29;
    out[5] = (val >> 22) & 0x7f;
    out[6] = (val >> 15) & 0x7f;
    out[7] = (val >> 8) & 0x7f;
    out[8] = (val >> 1) & 0x7f;
    out[9] = (val << 6) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 2);

    out[9] |= val >> 26;
    out[10] = (val >> 19) & 0x7f;
    out[11] = (val >> 12) & 0x7f;
    out[12] = (val >> 5) & 0x7f;
    out[13] = (val << 2) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 3);

    out[13] |= val >> 30;
    out[14] = (val >> 23) & 0x7f;
    out[15] = (val >> 16) & 0x7f;
    out[16] = (val >> 9) & 0x7f;
    out[17] = (val >> 2) & 0x7f;
    out[18] = (val << 5) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 4);

    out[18] |= val >> 27;
    out[19] = (val >> 20) & 0x7f;
    out[20] = (val >> 13) & 0x7f;
    out[21] = (val >> 6) & 0x7f;
    out[22] = (val << 1) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 5);

    out[22] |= val >> 31;
    out[23] = (val >> 24) & 0x7f;
    out[24] = (val >> 17) & 0x7f;
    out[25] = (val >> 10) & 0x7f;
    out[26] = (val >> 3) & 0x7f;
    out[27] = (val << 4) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 6);

    out[27] |= val >> 28;
    out[28] = (val >> 21) & 0x7f;
    out[29] = (val >> 14) & 0x7f;
    out[30] = (val >> 7) & 0x7f;
    out[31] = val & 0x7f;
  }
}

inline void VSEBLOCKS_UNPACK8(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 4, out += 4, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 24;
    out[1] = (val >> 16) & 0xff;
    out[2] = (val >> 8) & 0xff;
    out[3] = val & 0xff;
  }
}

inline void VSEBLOCKS_UNPACK9(uint32_t * restrict out,
                              const uint32_t * restrict in,
                              uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 32, out += 32, in += 9) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 23;
    out[1] = (val >> 14) & 0x01ff;
    out[2] = (val >> 5) & 0x01ff;
    out[3] = (val << 4) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);

    out[3] |= val >> 28;
    out[4] = (val >> 19) & 0x01ff;
    out[5] = (val >> 10) & 0x01ff;
    out[6] = (val >> 1) & 0x01ff;
    out[7] = (val << 8) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);

    out[7] |= val >> 24;
    out[8] = (val >> 15) & 0x01ff;
    out[9] = (val >> 6) & 0x01ff;
    out[10] = (val << 3) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);

    out[10] |= val >> 29;
    out[11] = (val >> 20) & 0x01ff;
    out[12] = (val >> 11) & 0x01ff;
    out[13] = (val >> 2) & 0x01ff;
    out[14] = (val << 7) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);

    out[14] |= val >> 25;
    out[15] = (val >> 16) & 0x01ff;
    out[16] = (val >> 7) & 0x01ff;
    out[17] = (val << 2) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 5);

    out[17] |= val >> 30;
    out[18] = (val >> 21) & 0x01ff;
    out[19] = (val >> 12) & 0x01ff;
    out[20] = (val >> 3) & 0x01ff;
    out[21] = (val << 6) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 6);

    out[21] |= val >> 26;
    out[22] = (val >> 17) & 0x01ff;
    out[23] = (val >> 8) & 0x01ff;
    out[24] = (val << 1) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 7);

    out[24] |= val >> 31;
    out[25] = (val >> 22) & 0x01ff;
    out[26] = (val >> 13) & 0x01ff;
    out[27] = (val >> 4) & 0x01ff;
    out[28] = (val << 5) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 8);

    out[28] |= val >> 27;
    out[29] = (val >> 18) & 0x01ff;
    out[30] = (val >> 9) & 0x01ff;
    out[31] = val & 0x01ff;
  }
}

inline void VSEBLOCKS_UNPACK10(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 16, out += 16, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 22;
    out[1] = (val >> 12) & 0x03ff;
    out[2] = (val >> 2) & 0x03ff;
    out[3] = (val << 8) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);

    out[3] |= val >> 24;
    out[4] = (val >> 14) & 0x03ff;
    out[5] = (val >> 4) & 0x03ff;
    out[6] = (val << 6) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);

    out[6] |= val >> 26;
    out[7] = (val >> 16) & 0x03ff;
    out[8] = (val >> 6) & 0x03ff;
    out[9] = (val << 4) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);

    out[9] |= val >> 28;
    out[10] = (val >> 18) & 0x03ff;
    out[11] = (val >> 8) & 0x03ff;
    out[12] = (val << 2) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);

    out[12] |= val >> 30;
    out[13] = (val >> 20) & 0x03ff;
    out[14] = (val >> 10) & 0x03ff;
    out[15] = val & 0x03ff;
  }
}

inline void VSEBLOCKS_UNPACK11(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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
    out[31] = val  & 0x07ff;
  }
}

inline void VSEBLOCKS_UNPACK12(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
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

inline void VSEBLOCKS_UNPACK16(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 2, out += 2, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 16;
    out[1] = val & 0xffff;
  }
}

inline void VSEBLOCKS_UNPACK20(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 8, out += 8, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    out[0] = val >> 12;
    out[1] = (val << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);

    out[1] |= val >> 24;
    out[2] = (val >> 4) & 0x0fffff;
    out[3] = (val << 16) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);

    out[3] |= val >> 16;
    out[4] = (val << 4) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);

    out[4] |= val >> 28;
    out[5] = (val >> 8) & 0x0fffff;
    out[6] = (val << 12) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);

    out[6] |= val >> 20;
    out[7] = val & 0x0fffff;
  }
}

inline void VSEBLOCKS_UNPACK32(uint32_t * restrict out,
                               const uint32_t * restrict in,
                               uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 8, out += 8, in += 8) {
    MEMCPY128(in, out);
    MEMCPY128(in + 4, out + 4);
  }
}

/* A interface of unpacking functions above */
typedef void (*vseblocks_unpack_t)(uint32_t *out,
                                   const uint32_t *in,
                                   uint32_t bs);

vseblocks_unpack_t VSEBLOCKS_UNPACK[] = {
  NULL,
  VSEBLOCKS_UNPACK1,
  VSEBLOCKS_UNPACK2,
  VSEBLOCKS_UNPACK3,
  VSEBLOCKS_UNPACK4,
  VSEBLOCKS_UNPACK5,
  VSEBLOCKS_UNPACK6,
  VSEBLOCKS_UNPACK7,
  VSEBLOCKS_UNPACK8,
  VSEBLOCKS_UNPACK9,
  VSEBLOCKS_UNPACK10,
  VSEBLOCKS_UNPACK11,
  VSEBLOCKS_UNPACK12,
  VSEBLOCKS_UNPACK16,
  VSEBLOCKS_UNPACK20,
  VSEBLOCKS_UNPACK32
};

const uint32_t VSEBLOCKS_LENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 14, 15, 16
};

const uint32_t VSEBLOCKS_ZLENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 14, 16, 32
};

const uint32_t VSEBLOCKS_LOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 20, 32
};

const uint32_t VSEBLOCKS_REMAPLOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 16, 16, 16, 20, 20, 20, 20,
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t VSEBLOCKS_CODELOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 13, 13, 13, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

} /* namespace: */

VSEncodingBlocks::VSEncodingBlocks()
    : EncodingBase(E_VSEBLOCKS),
      wmem_(INITIALIZE_SPTR(
              uint32_t, VSENCODING_BLOCKSZ * 2 + 128)),
      vdp_(new VSEncodingDP(VSEBLOCKS_LENS,
                            VSEBLOCKS_ZLENS,
                            VSEBLOCKS_LENS_LEN, false)){}

VSEncodingBlocks::~VSEncodingBlocks() throw() {}

void VSEncodingBlocks::encodeVS(const uint32_t *in,
                                uint32_t len,
                                uint32_t *out,
                                uint32_t *size) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);
  ASSERT(out != NULL);
  ASSERT(*size != 0);

  /* Compute optimal partition */
  std::vector<uint32_t> logs;
  std::vector<uint32_t> parts;

  for (uint32_t i = 0; i < len; i++)
    logs.push_back(
        VSEBLOCKS_REMAPLOGS[32 - MSB32(in[i])]);

  ASSERT(logs.size() == len);
  ASSERT(parts.size() == 0);

  vdp_->computePartition(logs, &parts,
                         VSEBLOCKS_LOGLEN + VSEBLOCKS_LOGLOG);
  ASSERT(parts.size() > 1);

  uint32_t numBlocks = parts.size() - 1;

  /* countBlocksLogs[i] says how many blocks uses i bits */
  uint32_t  countBlocksLogs[VSEBLOCKS_LOGS_LEN];

  for (uint32_t i = 0; i < VSEBLOCKS_LOGS_LEN; i++)
    countBlocksLogs[i] = 0;

  /* Count number of occs of each log */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    countBlocksLogs[VSEBLOCKS_CODELOGS[maxB]] +=
        parts[i + 1] - parts[i];
  }

  uint32_t ntotal = 0;
  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0)
      ntotal++;
  }

  /* Write occs. zero is assumed to be present */
  BitsWriter wt(out, *size);
  wt.write_bits(ntotal, 32);

  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0) {
      wt.write_bits(countBlocksLogs[i], 28);
      wt.write_bits(i, 4);
    }
  }

  /* Prepare arrays to store groups of elements */
  std::vector<uint32_t> blocks[VSEBLOCKS_LOGS_LEN];

  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0)
      blocks[i].reserve(countBlocksLogs[i]);
  }

  /* Permute the elements based on their values of B */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    if (!maxB)
      continue;

    for (auto j = parts[i]; j < parts[i + 1]; j++)
      /* Save current element in its bucket */
      blocks[VSEBLOCKS_CODELOGS[maxB]].push_back(in[j]);
  }

  /* Write each bucket ... keeping byte alligment */
  for (uint32_t i = 1; i < VSEBLOCKS_LOGS_LEN; i++) {
    for (uint32_t j = 0; j < countBlocksLogs[i]; j++)
      wt.write_bits(blocks[i][j], VSEBLOCKS_LOGS[i]);
    wt.flush_bits();
  }

  /* write block codes... a byte each */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    uint32_t idx = 0;

    if (maxB) {
      /* Compute the code for the block length */
      for (; idx < VSEBLOCKS_LENS_LEN; idx++) {
        if (parts[i + 1] - parts[i] ==
                VSEBLOCKS_LENS[idx])
          break;
      }
    } else {
      /*
       * Treat runs of 0 in a different way.
       * Compute the code for the block length.
       */
      for (; idx < VSEBLOCKS_LENS_LEN; idx++) {
        if (parts[i + 1] - parts[i] ==
                VSEBLOCKS_ZLENS[idx])
          break;
      }
    }

    /* Writes the value of B and K */
    wt.write_bits(VSEBLOCKS_CODELOGS[maxB], VSEBLOCKS_LOGLOG);
    wt.write_bits(idx, VSEBLOCKS_LOGLEN);
  }

  wt.flush_bits();
  *size = wt.size();
}

namespace {

inline void CopySubLists(uint32_t offset,
                         uint32_t in,
                         uint32_t ** restrict out,
                         uint32_t ** restrict blk) {
  /* Permuting integers with a first 8-bit */
  uint32_t info = (in >> (VSEBLOCKS_LOGDESC * offset));
  info &= VSEBLOCKS_DESC_LEN - 1;

  uint32_t b = info >> VSEBLOCKS_LOGLEN;
  uint32_t k = info & (VSEBLOCKS_LENS_LEN - 1);

  if (LIKELY(b)) {
#if 0
    MEMCPY(*out, blk[b], VSEBLOCKS_LENS[k]);
#else
    if (LIKELY(k > (VSEBLOCKS_LENS_LEN >> 1) - 1)) {
      MEMCPY128(blk[b], *out);
      MEMCPY128(blk[b] + 4, *out + 4);
      MEMCPY128(blk[b] + 8, *out + 8);
      MEMCPY128(blk[b] + 12, *out + 12);
    } else {
      MEMCPY128(blk[b], *out);
      MEMCPY128(blk[b] + 4, *out + 4);
    }
#endif

    blk[b] += VSEBLOCKS_LENS[k];
    *out += VSEBLOCKS_LENS[k];
  } else {
#if 0
    ZMEMCPY(*out, VSEBLOCKS_ZLENS[k]);
#else
    if (LIKELY(k > (VSEBLOCKS_LENS_LEN >> 1) - 1)) {
      ZMEMCPY128(*out);
      ZMEMCPY128(*out + 4);
      ZMEMCPY128(*out + 8);
      ZMEMCPY128(*out + 12);
      ZMEMCPY128(*out + 16);
      ZMEMCPY128(*out + 20);
      ZMEMCPY128(*out + 24);
      ZMEMCPY128(*out + 28);
    } else {
      ZMEMCPY128(*out);
      ZMEMCPY128(*out + 4);
    }
#endif
    *out += VSEBLOCKS_ZLENS[k];
  }
}

} /* namespace: */

void VSEncodingBlocks::decodeVS(const uint32_t *in,
                                uint32_t len,
                                uint32_t *out,
                                uint32_t nvalue) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);
  ASSERT(out != NULL);
  ASSERT(nvalue != 0);

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  uint32_t  *pblk[VSEBLOCKS_LOGS_LEN];

  const uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  /* All values unpacked in advance */
  int64_t ntotal = BYTEORDER_FREE_LOAD32(in);
  const uint32_t *data = ++in + ntotal;

  ASSERT(data < iterm);

  /* Get a working memory */
  uint32_t *aux = wmem_.get();

  while (LIKELY(ntotal-- > 0)) {
    uint32_t info = BYTEORDER_FREE_LOAD32(in);

    uint32_t b = info & (VSEBLOCKS_LOGS_LEN - 1);
    uint32_t nblk = info >> VSEBLOCKS_LOGLEN;

    /* Do unpacking */
    VSEBLOCKS_UNPACK[b](aux, data, nblk);
    pblk[b] = aux, aux += nblk;

    /* Move to next */
    in++;
    data += DIV_ROUNDUP(nblk * VSEBLOCKS_LOGS[b], 32);
  }

  while  (LIKELY(out < oterm && data < iterm)) {
    CopySubLists(3, *data, &out, pblk);
    CopySubLists(2, *data, &out, pblk);
    CopySubLists(1, *data, &out, pblk);
    CopySubLists(0, *data++, &out, pblk);
  }
}

void VSEncodingBlocks::encodeArray(const uint32_t *in,
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
  if (len > UINT32_MAX || *nvalue > UINT32_MAX)
    THROW_ENCODING_EXCEPTION(
        "VSEncodingBlocks only supports 32-bit length");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  uint32_t *oterm = out + *nvalue;

  uint64_t res = len;
  uint32_t csize = static_cast<uint32_t>(*nvalue);

  uint64_t ntotal = 0;
  while (LIKELY(res > VSENCODING_BLOCKSZ &&
                out < oterm)) {
    encodeVS(in, VSENCODING_BLOCKSZ, out + 1, &csize);
    in += VSENCODING_BLOCKSZ;

    BYTEORDER_FREE_STORE32(out, csize);
    out += csize + 1;

    /* Move to next */
    res -= VSENCODING_BLOCKSZ;
    ntotal += csize + 1;
    csize = static_cast<uint32_t>(*nvalue - ntotal);
  }

  /* If necessary, pack left values */
  if (LIKELY(res > 0 && out < oterm)) {
    encodeVS(in, res, out + 1, &csize);
    BYTEORDER_FREE_STORE32(
        out, static_cast<uint32_t>(csize));

    ntotal += csize + 1;
  }

  *nvalue = ntotal;
}

void VSEncodingBlocks::decodeArray(const uint32_t *in,
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
  if (len > UINT32_MAX || nvalue > UINT32_MAX)
    THROW_ENCODING_EXCEPTION(
        "VSEncodingBlocks only supports 32-bit length");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  uint32_t res = static_cast<uint32_t>(nvalue);

  const uint32_t *iterm = in + len;

  while (LIKELY(res > VSENCODING_BLOCKSZ &&
                in < iterm)) {
    uint32_t sum = BYTEORDER_FREE_LOAD32(in);
    decodeVS(in + 1, sum, out, VSENCODING_BLOCKSZ);
    in += sum + 1;
    out += VSENCODING_BLOCKSZ;

    /* Move to next */
    res -= VSENCODING_BLOCKSZ;
  }

  if (LIKELY(res > 0 && in < iterm)) {
    uint32_t sum = BYTEORDER_FREE_LOAD32(in);
    decodeVS(in + 1, sum, out, res);
  }
}

uint64_t VSEncodingBlocks::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len + 17;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
