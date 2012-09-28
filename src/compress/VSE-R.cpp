/*-----------------------------------------------------------------------------
 *  VSE-R.hpp - A alternative implementation of VSEncoding
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

#include <compress/policy/VSE-R.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSER_LOGS_LEN = 32;

/* FIXME: It complies with MAXLEN in vcompress.hpp */
const uint64_t MAXLEN = 100000000;

inline void VSER_UNPACK1(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 1, out += 32, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 1) | ((val >> 31));
    out[1] = (1U << 1) | ((val >> 30) & 0x01);
    out[2] = (1U << 1) | ((val >> 29) & 0x01);
    out[3] = (1U << 1) | ((val >> 28) & 0x01);
    out[4] = (1U << 1) | ((val >> 27) & 0x01);
    out[5] = (1U << 1) | ((val >> 26) & 0x01);
    out[6] = (1U << 1) | ((val >> 25) & 0x01);
    out[7] = (1U << 1) | ((val >> 24) & 0x01);
    out[8] = (1U << 1) | ((val >> 23) & 0x01);
    out[9] = (1U << 1) | ((val >> 22) & 0x01);
    out[10] = (1U << 1) | ((val >> 21) & 0x01);
    out[11] = (1U << 1) | ((val >> 20) & 0x01);
    out[12] = (1U << 1) | ((val >> 19) & 0x01);
    out[13] = (1U << 1) | ((val >> 18) & 0x01);
    out[14] = (1U << 1) | ((val >> 17) & 0x01);
    out[15] = (1U << 1) | ((val >> 16) & 0x01);
    out[16] = (1U << 1) | ((val >> 15) & 0x01);
    out[17] = (1U << 1) | ((val >> 14) & 0x01);
    out[18] = (1U << 1) | ((val >> 13) & 0x01);
    out[19] = (1U << 1) | ((val >> 12) & 0x01);
    out[20] = (1U << 1) | ((val >> 11) & 0x01);
    out[21] = (1U << 1) | ((val >> 10) & 0x01);
    out[22] = (1U << 1) | ((val >> 9) & 0x01);
    out[23] = (1U << 1) | ((val >> 8) & 0x01);
    out[24] = (1U << 1) | ((val >> 7) & 0x01);
    out[25] = (1U << 1) | ((val >> 6) & 0x01);
    out[26] = (1U << 1) | ((val >> 5) & 0x01);
    out[27] = (1U << 1) | ((val >> 4) & 0x01);
    out[28] = (1U << 1) | ((val >> 3) & 0x01);
    out[29] = (1U << 1) | ((val >> 2) & 0x01);
    out[30] = (1U << 1) | ((val >> 1) & 0x01);
    out[31] = (1U << 1) | (val & 0x01);
  }
}

inline void VSER_UNPACK2(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 1, out += 16, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 2) | ((val >> 30));
    out[1] = (1U << 2) | ((val >> 28) & 0x03);
    out[2] = (1U << 2) | ((val >> 26) & 0x03);
    out[3] = (1U << 2) | ((val >> 24) & 0x03);
    out[4] = (1U << 2) | ((val >> 22) & 0x03);
    out[5] = (1U << 2) | ((val >> 20) & 0x03);
    out[6] = (1U << 2) | ((val >> 18) & 0x03);
    out[7] = (1U << 2) | ((val >> 16) & 0x03);
    out[8] = (1U << 2) | ((val >> 14) & 0x03);
    out[9] = (1U << 2) | ((val >> 12) & 0x03);
    out[10] = (1U << 2) | ((val >> 10) & 0x03);
    out[11] = (1U << 2) | ((val >> 8) & 0x03);
    out[12] = (1U << 2) | ((val >> 6) & 0x03);
    out[13] = (1U << 2) | ((val >> 4) & 0x03);
    out[14] = (1U << 2) | ((val >> 2) & 0x03);
    out[15] = (1U << 2) | (val & 0x03);
  }
}

inline void VSER_UNPACK3(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 3, out += 32, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 3) | ((val >> 29));
    out[1] = (1U << 3) | ((val >> 26) & 0x07);
    out[2] = (1U << 3) | ((val >> 23) & 0x07);
    out[3] = (1U << 3) | ((val >> 20) & 0x07);
    out[4] = (1U << 3) | ((val >> 17) & 0x07);
    out[5] = (1U << 3) | ((val >> 14) & 0x07);
    out[6] = (1U << 3) | ((val >> 11) & 0x07);
    out[7] = (1U << 3) | ((val >> 8) & 0x07);
    out[8] = (1U << 3) | ((val >> 5) & 0x07);
    out[9] = (1U << 3) | ((val >> 2) & 0x07);
    out[10] = (val << 1) & 0x07;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[10] |= (1U << 3) | ((val >> 31));
    out[11] = (1U << 3) | ((val >> 28) & 0x07);
    out[12] = (1U << 3) | ((val >> 25) & 0x07);
    out[13] = (1U << 3) | ((val >> 22) & 0x07);
    out[14] = (1U << 3) | ((val >> 19) & 0x07);
    out[15] = (1U << 3) | ((val >> 16) & 0x07);
    out[16] = (1U << 3) | ((val >> 13) & 0x07);
    out[17] = (1U << 3) | ((val >> 10) & 0x07);
    out[18] = (1U << 3) | ((val >> 7) & 0x07);
    out[19] = (1U << 3) | ((val >> 4) & 0x07);
    out[20] = (1U << 3) | ((val >> 1) & 0x07);
    out[21] = (val << 2) & 0x07;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[21] |= (1U << 3) | ((val >> 30));
    out[22] = (1U << 3) | ((val >> 27) & 0x07);
    out[23] = (1U << 3) | ((val >> 24) & 0x07);
    out[24] = (1U << 3) | ((val >> 21) & 0x07);
    out[25] = (1U << 3) | ((val >> 18) & 0x07);
    out[26] = (1U << 3) | ((val >> 15) & 0x07);
    out[27] = (1U << 3) | ((val >> 12) & 0x07);
    out[28] = (1U << 3) | ((val >> 9) & 0x07);
    out[29] = (1U << 3) | ((val >> 6) & 0x07);
    out[30] = (1U << 3) | ((val >> 3) & 0x07);
    out[31] = (1U << 3) | (val & 0x07);
  }
}

inline void VSER_UNPACK4(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 1, out += 8, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 4) | ((val >> 28));
    out[1] = (1U << 4) | ((val >> 24) & 0x0f);
    out[2] = (1U << 4) | ((val >> 20) & 0x0f);
    out[3] = (1U << 4) | ((val >> 16) & 0x0f);
    out[4] = (1U << 4) | ((val >> 12) & 0x0f);
    out[5] = (1U << 4) | ((val >> 8) & 0x0f);
    out[6] = (1U << 4) | ((val >> 4) & 0x0f);
    out[7] = (1U << 4) | (val & 0x0f);
  }
}

inline void VSER_UNPACK5(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 5, out += 32, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 5) | ((val >> 27));
    out[1] = (1U << 5) | ((val >> 22) & 0x1f);
    out[2] = (1U << 5) | ((val >> 17) & 0x1f);
    out[3] = (1U << 5) | ((val >> 12) & 0x1f);
    out[4] = (1U << 5) | ((val >> 7) & 0x1f);
    out[5] = (1U << 5) | ((val >> 2) & 0x1f);
    out[6] = (val << 3) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[6] |=  (1U << 5) | ((val >> 29));
    out[7] = (1U << 5) | ((val >> 24) & 0x1f);
    out[8] = (1U << 5) | ((val >> 19) & 0x1f);
    out[9] = (1U << 5) | ((val >> 14) & 0x1f);
    out[10] = (1U << 5) | ((val >> 9) & 0x1f);
    out[11] = (1U << 5) | ((val >> 4) & 0x1f);
    out[12] = (val << 1) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[12] |=  (1U << 5) | ((val >> 31));
    out[13] = (1U << 5) | ((val >> 26) & 0x1f);
    out[14] = (1U << 5) | ((val >> 21) & 0x1f);
    out[15] = (1U << 5) | ((val >> 16) & 0x1f);
    out[16] = (1U << 5) | ((val >> 11) & 0x1f);
    out[17] = (1U << 5) | ((val >> 6) & 0x1f);
    out[18] = (1U << 5) | ((val >> 1) & 0x1f);
    out[19] = (val << 4) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[19] |=  (1U << 5) | ((val >> 28));
    out[20] = (1U << 5) | ((val >> 23) & 0x1f);
    out[21] = (1U << 5) | ((val >> 18) & 0x1f);
    out[22] = (1U << 5) | ((val >> 13) & 0x1f);
    out[23] = (1U << 5) | ((val >> 8) & 0x1f);
    out[24] = (1U << 5) | ((val >> 3) & 0x1f);
    out[25] = (val << 2) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[25] |=  (1U << 5) | ((val >> 30));
    out[26] = (1U << 5) | ((val >> 25) & 0x1f);
    out[27] = (1U << 5) | ((val >> 20) & 0x1f);
    out[28] = (1U << 5) | ((val >> 15) & 0x1f);
    out[29] = (1U << 5) | ((val >> 10) & 0x1f);
    out[30] = (1U << 5) | ((val >> 5) & 0x1f);
    out[31] = (1U << 5) | (val & 0x1f);
  }
}

inline void VSER_UNPACK6(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 3, out += 16, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 6) | ((val >> 26));
    out[1] = (1U << 6) | ((val >> 20) & 0x3f);
    out[2] = (1U << 6) | ((val >> 14) & 0x3f);
    out[3] = (1U << 6) | ((val >> 8) & 0x3f);
    out[4] = (1U << 6) | ((val >> 2) & 0x3f);
    out[5] = (val << 4) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[5] |=  (1U << 6) | ((val >> 28));
    out[6] = (1U << 6) | ((val >> 22) & 0x3f);
    out[7] = (1U << 6) | ((val >> 16) & 0x3f);
    out[8] = (1U << 6) | ((val >> 10) & 0x3f);
    out[9] = (1U << 6) | ((val >> 4) & 0x3f);
    out[10] = (val << 2) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[10] |=  (1U << 6) | ((val >> 30));
    out[11] = (1U << 6) | ((val >> 24) & 0x3f);
    out[12] = (1U << 6) | ((val >> 18) & 0x3f);
    out[13] = (1U << 6) | ((val >> 12) & 0x3f);
    out[14] = (1U << 6) | ((val >> 6) & 0x3f);
    out[15] = (1U << 6) | (val & 0x3f);
  }
}

inline void VSER_UNPACK7(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 7, out += 32, in += 7) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 7) | ((val >> 25));
    out[1] = (1U << 7) | ((val >> 18) & 0x7f);
    out[2] = (1U << 7) | ((val >> 11) & 0x7f);
    out[3] = (1U << 7) | ((val >> 4) & 0x7f);
    out[4] = (val << 3) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[4] |=  (1U << 7) | ((val >> 29));
    out[5] = (1U << 7) | ((val >> 22) & 0x7f);
    out[6] = (1U << 7) | ((val >> 15) & 0x7f);
    out[7] = (1U << 7) | ((val >> 8) & 0x7f);
    out[8] = (1U << 7) | ((val >> 1) & 0x7f);
    out[9] = (val << 6) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[9] |=  (1U << 7) | ((val >> 26));
    out[10] = (1U << 7) | ((val >> 19) & 0x7f);
    out[11] = (1U << 7) | ((val >> 12) & 0x7f);
    out[12] = (1U << 7) | ((val >> 5) & 0x7f);
    out[13] = (val << 2) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[13] |=  (1U << 7) | ((val >> 30));
    out[14] = (1U << 7) | ((val >> 23) & 0x7f);
    out[15] = (1U << 7) | ((val >> 16) & 0x7f);
    out[16] = (1U << 7) | ((val >> 9) & 0x7f);
    out[17] = (1U << 7) | ((val >> 2) & 0x7f);
    out[18] = (val << 5) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[18] |=  (1U << 7) | ((val >> 27));
    out[19] = (1U << 7) | ((val >> 20) & 0x7f);
    out[20] = (1U << 7) | ((val >> 13) & 0x7f);
    out[21] = (1U << 7) | ((val >> 6) & 0x7f);
    out[22] = (val << 1) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[22] |=  (1U << 7) | ((val >> 31));
    out[23] = (1U << 7) | ((val >> 24) & 0x7f);
    out[24] = (1U << 7) | ((val >> 17) & 0x7f);
    out[25] = (1U << 7) | ((val >> 10) & 0x7f);
    out[26] = (1U << 7) | ((val >> 3) & 0x7f);
    out[27] = (val << 4) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[27] |=  (1U << 7) | ((val >> 28));
    out[28] = (1U << 7) | ((val >> 21) & 0x7f);
    out[29] = (1U << 7) | ((val >> 14) & 0x7f);
    out[30] = (1U << 7) | ((val >> 7) & 0x7f);
    out[31] = (1U << 7) | (val & 0x7f);
  }
}

inline void VSER_UNPACK8(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 1, out += 4, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 8) | ((val >> 24));
    out[1] = (1U << 8) | ((val >> 16) & 0xff);
    out[2] = (1U << 8) | ((val >> 8) & 0xff);
    out[3] = (1U << 8) | (val & 0xff);
  }
}

inline void VSER_UNPACK9(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 9, out += 32, in += 9) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 9) | ((val >> 23));
    out[1] = (1U << 9) | ((val >> 14) & 0x01ff);
    out[2] = (1U << 9) | ((val >> 5) & 0x01ff);
    out[3] = (val << 4) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[3] |=  (1U << 9) | ((val >> 28));
    out[4] = (1U << 9) | ((val >> 19) & 0x01ff);
    out[5] = (1U << 9) | ((val >> 10) & 0x01ff);
    out[6] = (1U << 9) | ((val >> 1) & 0x01ff);
    out[7] = (val << 8) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[7] |=  (1U << 9) | ((val >> 24));
    out[8] = (1U << 9) | ((val >> 15) & 0x01ff);
    out[9] = (1U << 9) | ((val >> 6) & 0x01ff);
    out[10] = (val << 3) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[10] |=  (1U << 9) | ((val >> 29));
    out[11] = (1U << 9) | ((val >> 20) & 0x01ff);
    out[12] = (1U << 9) | ((val >> 11) & 0x01ff);
    out[13] = (1U << 9) | ((val >> 2) & 0x01ff);
    out[14] = (val << 7) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[14] |=  (1U << 9) | ((val >> 25));
    out[15] = (1U << 9) | ((val >> 16) & 0x01ff);
    out[16] = (1U << 9) | ((val >> 7) & 0x01ff);
    out[17] = (val << 2) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[17] |=  (1U << 9) | ((val >> 30));
    out[18] = (1U << 9) | ((val >> 21) & 0x01ff);
    out[19] = (1U << 9) | ((val >> 12) & 0x01ff);
    out[20] = (1U << 9) | ((val >> 3) & 0x01ff);
    out[21] = (val << 6) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[21] |=  (1U << 9) | ((val >> 26));
    out[22] = (1U << 9) | ((val >> 17) & 0x01ff);
    out[23] = (1U << 9) | ((val >> 8) & 0x01ff);
    out[24] = (val << 1) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[24] |=  (1U << 9) | ((val >> 31));
    out[25] = (1U << 9) | ((val >> 22) & 0x01ff);
    out[26] = (1U << 9) | ((val >> 13) & 0x01ff);
    out[27] = (1U << 9) | ((val >> 4) & 0x01ff);
    out[28] = (val << 5) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[28] |=  (1U << 9) | ((val >> 27));
    out[29] = (1U << 9) | ((val >> 18) & 0x01ff);
    out[30] = (1U << 9) | ((val >> 9) & 0x01ff);
    out[31] = (1U << 9) | (val & 0x01ff);
  }
}

inline void VSER_UNPACK10(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 5, out += 16, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 10) | ((val >> 22));
    out[1] = (1U << 10) | ((val >> 12) & 0x03ff);
    out[2] = (1U << 10) | ((val >> 2) & 0x03ff);
    out[3] = (val << 8) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[3] |=  (1U << 10) | ((val >> 24));
    out[4] = (1U << 10) | ((val >> 14) & 0x03ff);
    out[5] = (1U << 10) | ((val >> 4) & 0x03ff);
    out[6] = (val << 6) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[6] |=  (1U << 10) | ((val >> 26));
    out[7] = (1U << 10) | ((val >> 16) & 0x03ff);
    out[8] = (1U << 10) | ((val >> 6) & 0x03ff);
    out[9] = (val << 4) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[9] |=  (1U << 10) | ((val >> 28));
    out[10] = (1U << 10) | ((val >> 18) & 0x03ff);
    out[11] = (1U << 10) | ((val >> 8) & 0x03ff);
    out[12] = (val << 2) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[12] |=  (1U << 10) | ((val >> 30));
    out[13] = (1U << 10) | ((val >> 20) & 0x03ff);
    out[14] = (1U << 10) | ((val >> 10) & 0x03ff);
    out[15] = (1U << 10) | (val & 0x03ff);
  }
}

inline void VSER_UNPACK11(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 11, out += 32, in += 11) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 11) | ((val >> 21));
    out[1] = (1U << 11) | ((val >> 10) & 0x07ff);
    out[2] = (val << 1) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |=  (1U << 11) | ((val >> 31));
    out[3] = (1U << 11) | ((val >> 20) & 0x07ff);
    out[4] = (1U << 11) | ((val >> 9) & 0x07ff);
    out[5] = (val << 2) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[5] |=  (1U << 11) | ((val >> 30));
    out[6] = (1U << 11) | ((val >> 19) & 0x07ff);
    out[7] = (1U << 11) | ((val >> 8) & 0x07ff);
    out[8] = (val << 3) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[8] |=  (1U << 11) | ((val >> 29));
    out[9] = (1U << 11) | ((val >> 18) & 0x07ff);
    out[10] = (1U << 11) | ((val >> 7) & 0x07ff);
    out[11] = (val << 4) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[11] |=  (1U << 11) | ((val >> 28));
    out[12] = (1U << 11) | ((val >> 17) & 0x07ff);
    out[13] = (1U << 11) | ((val >> 6) & 0x07ff);
    out[14] = (val << 5) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[14] |=  (1U << 11) | ((val >> 27));
    out[15] = (1U << 11) | ((val >> 16) & 0x07ff);
    out[16] = (1U << 11) | ((val >> 5) & 0x07ff);
    out[17] = (val << 6) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[17] |=  (1U << 11) | ((val >> 26));
    out[18] = (1U << 11) | ((val >> 15) & 0x07ff);
    out[19] = (1U << 11) | ((val >> 4) & 0x07ff);
    out[20] = (val << 7) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[20] |=  (1U << 11) | ((val >> 25));
    out[21] = (1U << 11) | ((val >> 14) & 0x07ff);
    out[22] = (1U << 11) | ((val >> 3) & 0x07ff);
    out[23] = (val << 8) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[23] |=  (1U << 11) | ((val >> 24));
    out[24] = (1U << 11) | ((val >> 13) & 0x07ff);
    out[25] = (1U << 11) | ((val >> 2) & 0x07ff);
    out[26] = (val << 9) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[26] |=  (1U << 11) | ((val >> 23));
    out[27] = (1U << 11) | ((val >> 12) & 0x07ff);
    out[28] = (1U << 11) | ((val >> 1) & 0x07ff);
    out[29] = (val << 10) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[29] |=  (1U << 11) | ((val >> 22));
    out[30] = (1U << 11) | ((val >> 11) & 0x07ff);
    out[31] = (1U << 11) | (val & 0x07ff);
  }
}

inline void VSER_UNPACK12(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 3, out += 8, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 12) | ((val >> 20));
    out[1] = (1U << 12) | ((val >> 8) & 0x0fff);
    out[2] = (val << 4) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |=  (1U << 12) | ((val >> 28));
    out[3] = (1U << 12) | ((val >> 16) & 0x0fff);
    out[4] = (1U << 12) | ((val >> 4) & 0x0fff);
    out[5] = (val << 8) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[5] |=  (1U << 12) | ((val >> 24));
    out[6] = (1U << 12) | ((val >> 12) & 0x0fff);
    out[7] = (1U << 12) | (val & 0x0fff);
  }
}

inline void VSER_UNPACK13(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 13, out += 32, in += 13) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 13) | ((val >> 19));
    out[1] = (1U << 13) | ((val >> 6) & 0x1fff);
    out[2] = (val << 7) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |=  (1U << 13) | ((val >> 25));
    out[3] = (1U << 13) | ((val >> 12) & 0x1fff);
    out[4] = (val << 1) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[4] |=  (1U << 13) | ((val >> 31));
    out[5] = (1U << 13) | ((val >> 18) & 0x1fff);
    out[6] = (1U << 13) | ((val >> 5) & 0x1fff);
    out[7] = (val << 8) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[7] |=  (1U << 13) | ((val >> 24));
    out[8] = (1U << 13) | ((val >> 11) & 0x1fff);
    out[9] = (val << 2) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[9] |=  (1U << 13) | ((val >> 30));
    out[10] = (1U << 13) | ((val >> 17) & 0x1fff);
    out[11] = (1U << 13) | ((val >> 4) & 0x1fff);
    out[12] = (val << 9) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[12] |=  (1U << 13) | ((val >> 23));
    out[13] = (1U << 13) | ((val >> 10) & 0x1fff);
    out[14] = (val << 3) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[14] |=  (1U << 13) | ((val >> 29));
    out[15] = (1U << 13) | ((val >> 16) & 0x1fff);
    out[16] = (1U << 13) | ((val >> 3) & 0x1fff);
    out[17] = (val << 10) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[17] |=  (1U << 13) | ((val >> 22));
    out[18] = (1U << 13) | ((val >> 9) & 0x1fff);
    out[19] = (val << 4) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[19] |=  (1U << 13) | ((val >> 28));
    out[20] = (1U << 13) | ((val >> 15) & 0x1fff);
    out[21] = (1U << 13) | ((val >> 2) & 0x1fff);
    out[22] = (val << 11) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[22] |=  (1U << 13) | ((val >> 21));
    out[23] = (1U << 13) | ((val >> 8) & 0x1fff);
    out[24] = (val << 5) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[24] |=  (1U << 13) | ((val >> 27));
    out[25] = (1U << 13) | ((val >> 14) & 0x1fff);
    out[26] = (1U << 13) | ((val >> 1) & 0x1fff);
    out[27] = (val << 12) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[27] |=  (1U << 13) | ((val >> 20));
    out[28] = (1U << 13) | ((val >> 7) & 0x1fff);
    out[29] = (val << 6) & 0x1fff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[29] |=  (1U << 13) | ((val >> 26));
    out[30] = (1U << 13) | ((val >> 13) & 0x1fff);
    out[31] = (1U << 13) | (val & 0x1fff);
  }
}

inline void VSER_UNPACK14(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 7, out += 16, in += 7) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 14) | ((val >> 18));
    out[1] = (1U << 14) | ((val >> 4) & 0x3fff);
    out[2] = (val << 10) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |=  (1U << 14) | ((val >> 22));
    out[3] = (1U << 14) | ((val >> 8) & 0x3fff);
    out[4] = (val << 6) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[4] |=  (1U << 14) | ((val >> 26));
    out[5] = (1U << 14) | ((val >> 12) & 0x3fff);
    out[6] = (val << 2) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[6] |=  (1U << 14) | ((val >> 30));
    out[7] = (1U << 14) | ((val >> 16) & 0x3fff);
    out[8] = (1U << 14) | ((val >> 2) & 0x3fff);
    out[9] = (val << 12) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[9] |=  (1U << 14) | ((val >> 20));
    out[10] = (1U << 14) | ((val >> 6) & 0x3fff);
    out[11] = (val << 8) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[11] |=  (1U << 14) | ((val >> 24));
    out[12] = (1U << 14) | ((val >> 10) & 0x3fff);
    out[13] = (val << 4) & 0x3fff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[13] |=  (1U << 14) | ((val >> 28));
    out[14] = (1U << 14) | ((val >> 14) & 0x3fff);
    out[15] = (1U << 14) | (val & 0x3fff);
  }
}

inline void VSER_UNPACK15(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 15, out += 32, in += 15) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 15) | ((val >> 17));
    out[1] = (1U << 15) | ((val >> 2) & 0x7fff);
    out[2] = (val << 13) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[2] |=  (1U << 15) | ((val >> 19));
    out[3] = (1U << 15) | ((val >> 4) & 0x7fff);
    out[4] = (val << 11) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[4] |=  (1U << 15) | ((val >> 21));
    out[5] = (1U << 15) | ((val >> 6) & 0x7fff);
    out[6] = (val << 9) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[6] |=  (1U << 15) | ((val >> 23));
    out[7] = (1U << 15) | ((val >> 8) & 0x7fff);
    out[8] = (val << 7) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[8] |=  (1U << 15) | ((val >> 25));
    out[9] = (1U << 15) | ((val >> 10) & 0x7fff);
    out[10] = (val << 5) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[10] |=  (1U << 15) | ((val >> 27));
    out[11] = (1U << 15) | ((val >> 12) & 0x7fff);
    out[12] = (val << 3) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[12] |=  (1U << 15) | ((val >> 29));
    out[13] = (1U << 15) | ((val >> 14) & 0x7fff);
    out[14] = (val << 1) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[14] |=  (1U << 15) | ((val >> 31));
    out[15] = (1U << 15) | ((val >> 16) & 0x7fff);
    out[16] = (1U << 15) | ((val >> 1) & 0x7fff);
    out[17] = (val << 14) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[17] |=  (1U << 15) | ((val >> 18));
    out[18] = (1U << 15) | ((val >> 3) & 0x7fff);
    out[19] = (val << 12) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[19] |=  (1U << 15) | ((val >> 20));
    out[20] = (1U << 15) | ((val >> 5) & 0x7fff);
    out[21] = (val << 10) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[21] |=  (1U << 15) | ((val >> 22));
    out[22] = (1U << 15) | ((val >> 7) & 0x7fff);
    out[23] = (val << 8) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[23] |=  (1U << 15) | ((val >> 24));
    out[24] = (1U << 15) | ((val >> 9) & 0x7fff);
    out[25] = (val << 6) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[25] |=  (1U << 15) | ((val >> 26));
    out[26] = (1U << 15) | ((val >> 11) & 0x7fff);
    out[27] = (val << 4) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[27] |=  (1U << 15) | ((val >> 28));
    out[28] = (1U << 15) | ((val >> 13) & 0x7fff);
    out[29] = (val << 2) & 0x7fff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[29] |=  (1U << 15) | ((val >> 30));
    out[30] = (1U << 15) | ((val >> 15) & 0x7fff);
    out[31] = (1U << 15) | (val & 0x7fff);
  }
}

inline void VSER_UNPACK16(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 1, out += 2, in += 1) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 16) | ((val >> 16));
    out[1] = (1U << 16) | (val & 0xffff);
  }
}

inline void VSER_UNPACK17(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 17, out += 32, in += 17) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 17) | ((val >> 15));
    out[1] = (val << 2) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 17) | ((val >> 30));
    out[2] = (1U << 17) | ((val >> 13) & 0x01ffff);
    out[3] = (val << 4) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |=  (1U << 17) | ((val >> 28));
    out[4] = (1U << 17) | ((val >> 11) & 0x01ffff);
    out[5] = (val << 6) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[5] |=  (1U << 17) | ((val >> 26));
    out[6] = (1U << 17) | ((val >> 9) & 0x01ffff);
    out[7] = (val << 8) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[7] |=  (1U << 17) | ((val >> 24));
    out[8] = (1U << 17) | ((val >> 7) & 0x01ffff);
    out[9] = (val << 10) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[9] |=  (1U << 17) | ((val >> 22));
    out[10] = (1U << 17) | ((val >> 5) & 0x01ffff);
    out[11] = (val << 12) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[11] |=  (1U << 17) | ((val >> 20));
    out[12] = (1U << 17) | ((val >> 3) & 0x01ffff);
    out[13] = (val << 14) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[13] |=  (1U << 17) | ((val >> 18));
    out[14] = (1U << 17) | ((val >> 1) & 0x01ffff);
    out[15] = (val << 16) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[15] |=  (1U << 17) | ((val >> 16));
    out[16] = (val << 1) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[16] |=  (1U << 17) | ((val >> 31));
    out[17] = (1U << 17) | ((val >> 14) & 0x01ffff);
    out[18] = (val << 3) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[18] |=  (1U << 17) | ((val >> 29));
    out[19] = (1U << 17) | ((val >> 12) & 0x01ffff);
    out[20] = (val << 5) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[20] |=  (1U << 17) | ((val >> 27));
    out[21] = (1U << 17) | ((val >> 10) & 0x01ffff);
    out[22] = (val << 7) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[22] |=  (1U << 17) | ((val >> 25));
    out[23] = (1U << 17) | ((val >> 8) & 0x01ffff);
    out[24] = (val << 9) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[24] |=  (1U << 17) | ((val >> 23));
    out[25] = (1U << 17) | ((val >> 6) & 0x01ffff);
    out[26] = (val << 11) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[26] |=  (1U << 17) | ((val >> 21));
    out[27] = (1U << 17) | ((val >> 4) & 0x01ffff);
    out[28] = (val << 13) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[28] |=  (1U << 17) | ((val >> 19));
    out[29] = (1U << 17) | ((val >> 2) & 0x01ffff);
    out[30] = (val << 15) & 0x01ffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[30] |=  (1U << 17) | ((val >> 17));
    out[31] = (1U << 17) | (val & 0x01ffff);
  }
}

inline void VSER_UNPACK18(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 9, out += 16, in += 9) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 18) | ((val >> 14));
    out[1] = (val << 4) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 18) | ((val >> 28));
    out[2] = (1U << 18) | ((val >> 10) & 0x03ffff);
    out[3] = (val << 8) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |=  (1U << 18) | ((val >> 24));
    out[4] = (1U << 18) | ((val >> 6) & 0x03ffff);
    out[5] = (val << 12) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[5] |=  (1U << 18) | ((val >> 20));
    out[6] = (1U << 18) | ((val >> 2) & 0x03ffff);
    out[7] = (val << 16) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[7] |=  (1U << 18) | ((val >> 16));
    out[8] = (val << 2) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[8] |=  (1U << 18) | ((val >> 30));
    out[9] = (1U << 18) | ((val >> 12) & 0x03ffff);
    out[10] = (val << 6) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[10] |=  (1U << 18) | ((val >> 26));
    out[11] = (1U << 18) | ((val >> 8) & 0x03ffff);
    out[12] = (val << 10) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[12] |=  (1U << 18) | ((val >> 22));
    out[13] = (1U << 18) | ((val >> 4) & 0x03ffff);
    out[14] = (val << 14) & 0x03ffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[14] |=  (1U << 18) | ((val >> 18));
    out[15] = (1U << 18) | (val & 0x03ffff);
  }
}

inline void VSER_UNPACK19(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 19, out += 32, in += 19) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 19) | ((val >> 13));
    out[1] = (val << 6) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 19) | ((val >> 26));
    out[2] = (1U << 19) | ((val >> 7) & 0x07ffff);
    out[3] = (val << 12) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |=  (1U << 19) | ((val >> 20));
    out[4] = (1U << 19) | ((val >> 1) & 0x07ffff);
    out[5] = (val << 18) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[5] |=  (1U << 19) | ((val >> 14));
    out[6] = (val << 5) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[6] |=  (1U << 19) | ((val >> 27));
    out[7] = (1U << 19) | ((val >> 8) & 0x07ffff);
    out[8] = (val << 11) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[8] |=  (1U << 19) | ((val >> 21));
    out[9] = (1U << 19) | ((val >> 2) & 0x07ffff);
    out[10] = (val << 17) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[10] |=  (1U << 19) | ((val >> 15));
    out[11] = (val << 4) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[11] |=  (1U << 19) | ((val >> 28));
    out[12] = (1U << 19) | ((val >> 9) & 0x07ffff);
    out[13] = (val << 10) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[13] |=  (1U << 19) | ((val >> 22));
    out[14] = (1U << 19) | ((val >> 3) & 0x07ffff);
    out[15] = (val << 16) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[15] |=  (1U << 19) | ((val >> 16));
    out[16] = (val << 3) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[16] |=  (1U << 19) | ((val >> 29));
    out[17] = (1U << 19) | ((val >> 10) & 0x07ffff);
    out[18] = (val << 9) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[18] |=  (1U << 19) | ((val >> 23));
    out[19] = (1U << 19) | ((val >> 4) & 0x07ffff);
    out[20] = (val << 15) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[20] |=  (1U << 19) | ((val >> 17));
    out[21] = (val << 2) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[21] |=  (1U << 19) | ((val >> 30));
    out[22] = (1U << 19) | ((val >> 11) & 0x07ffff);
    out[23] = (val << 8) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[23] |=  (1U << 19) | ((val >> 24));
    out[24] = (1U << 19) | ((val >> 5) & 0x07ffff);
    out[25] = (val << 14) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[25] |=  (1U << 19) | ((val >> 18));
    out[26] = (val << 1) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[26] |=  (1U << 19) | ((val >> 31));
    out[27] = (1U << 19) | ((val >> 12) & 0x07ffff);
    out[28] = (val << 7) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[28] |=  (1U << 19) | ((val >> 25));
    out[29] = (1U << 19) | ((val >> 6) & 0x07ffff);
    out[30] = (val << 13) & 0x07ffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[30] |=  (1U << 19) | ((val >> 19));
    out[31] = (1U << 19) | (val & 0x07ffff);
  }
}

inline void VSER_UNPACK20(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 5, out += 8, in += 5) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 20) | ((val >> 12));
    out[1] = (val << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 20) | ((val >> 24));
    out[2] = (1U << 20) | ((val >> 4) & 0x0fffff);
    out[3] = (val << 16) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |=  (1U << 20) | ((val >> 16));
    out[4] = (val << 4) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[4] |=  (1U << 20) | ((val >> 28));
    out[5] = (1U << 20) | ((val >> 8) & 0x0fffff);
    out[6] = (val << 12) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[6] |=  (1U << 20) | ((val >> 20));
    out[7] = (1U << 20) | (val & 0x0fffff);
  }
}

inline void VSER_UNPACK21(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 21, out += 32, in += 21) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 21) | ((val >> 11));
    out[1] = (val << 10) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 21) | ((val >> 22));
    out[2] = (1U << 21) | ((val >> 1) & 0x1fffff);
    out[3] = (val << 20) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[3] |=  (1U << 21) | ((val >> 12));
    out[4] = (val << 9) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[4] |=  (1U << 21) | ((val >> 23));
    out[5] = (1U << 21) | ((val >> 2) & 0x1fffff);
    out[6] = (val << 19) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[6] |=  (1U << 21) | ((val >> 13));
    out[7] = (val << 8) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[7] |=  (1U << 21) | ((val >> 24));
    out[8] = (1U << 21) | ((val >> 3) & 0x1fffff);
    out[9] = (val << 18) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[9] |=  (1U << 21) | ((val >> 14));
    out[10] = (val << 7) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[10] |=  (1U << 21) | ((val >> 25));
    out[11] = (1U << 21) | ((val >> 4) & 0x1fffff);
    out[12] = (val << 17) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[12] |=  (1U << 21) | ((val >> 15));
    out[13] = (val << 6) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[13] |=  (1U << 21) | ((val >> 26));
    out[14] = (1U << 21) | ((val >> 5) & 0x1fffff);
    out[15] = (val << 16) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[15] |=  (1U << 21) | ((val >> 16));
    out[16] = (val << 5) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[16] |=  (1U << 21) | ((val >> 27));
    out[17] = (1U << 21) | ((val >> 6) & 0x1fffff);
    out[18] = (val << 15) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[18] |=  (1U << 21) | ((val >> 17));
    out[19] = (val << 4) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[19] |=  (1U << 21) | ((val >> 28));
    out[20] = (1U << 21) | ((val >> 7) & 0x1fffff);
    out[21] = (val << 14) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[21] |=  (1U << 21) | ((val >> 18));
    out[22] = (val << 3) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[22] |=  (1U << 21) | ((val >> 29));
    out[23] = (1U << 21) | ((val >> 8) & 0x1fffff);
    out[24] = (val << 13) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[24] |=  (1U << 21) | ((val >> 19));
    out[25] = (val << 2) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[25] |=  (1U << 21) | ((val >> 30));
    out[26] = (1U << 21) | ((val >> 9) & 0x1fffff);
    out[27] = (val << 12) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[27] |=  (1U << 21) | ((val >> 20));
    out[28] = (val << 1) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[28] |=  (1U << 21) | ((val >> 31));
    out[29] = (1U << 21) | ((val >> 10) & 0x1fffff);
    out[30] = (val << 11) & 0x1fffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[30] |=  (1U << 21) | ((val >> 21));
    out[31] = (1U << 21) | (val & 0x1fffff);
  }
}

inline void VSER_UNPACK22(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 11, out += 16, in += 11) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 22) | ((val >> 10));
    out[1] = (val << 12) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 22) | ((val >> 20));
    out[2] = (val << 2) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 22) | ((val >> 30));
    out[3] = (1U << 22) | ((val >> 8) & 0x3fffff);
    out[4] = (val << 14) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[4] |=  (1U << 22) | ((val >> 18));
    out[5] = (val << 4) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[5] |=  (1U << 22) | ((val >> 28));
    out[6] = (1U << 22) | ((val >> 6) & 0x3fffff);
    out[7] = (val << 16) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[7] |=  (1U << 22) | ((val >> 16));
    out[8] = (val << 6) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[8] |=  (1U << 22) | ((val >> 26));
    out[9] = (1U << 22) | ((val >> 4) & 0x3fffff);
    out[10] = (val << 18) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[10] |=  (1U << 22) | ((val >> 14));
    out[11] = (val << 8) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[11] |=  (1U << 22) | ((val >> 24));
    out[12] = (1U << 22) | ((val >> 2) & 0x3fffff);
    out[13] = (val << 20) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[13] |=  (1U << 22) | ((val >> 12));
    out[14] = (val << 10) & 0x3fffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[14] |=  (1U << 22) | ((val >> 22));
    out[15] = (1U << 22) | (val & 0x3fffff);
  }
}

inline void VSER_UNPACK23(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 23, out += 32, in += 23) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 23) | ((val >> 9));
    out[1] = (val << 14) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 23) | ((val >> 18));
    out[2] = (val << 5) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 23) | ((val >> 27));
    out[3] = (1U << 23) | ((val >> 4) & 0x7fffff);
    out[4] = (val << 19) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[4] |=  (1U << 23) | ((val >> 13));
    out[5] = (val << 10) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[5] |=  (1U << 23) | ((val >> 22));
    out[6] = (val << 1) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[6] |=  (1U << 23) | ((val >> 31));
    out[7] = (1U << 23) | ((val >> 8) & 0x7fffff);
    out[8] = (val << 15) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[8] |=  (1U << 23) | ((val >> 17));
    out[9] = (val << 6) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[9] |=  (1U << 23) | ((val >> 26));
    out[10] = (1U << 23) | ((val >> 3) & 0x7fffff);
    out[11] = (val << 20) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[11] |=  (1U << 23) | ((val >> 12));
    out[12] = (val << 11) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[12] |=  (1U << 23) | ((val >> 21));
    out[13] = (val << 2) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[13] |=  (1U << 23) | ((val >> 30));
    out[14] = (1U << 23) | ((val >> 7) & 0x7fffff);
    out[15] = (val << 16) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[15] |=  (1U << 23) | ((val >> 16));
    out[16] = (val << 7) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[16] |=  (1U << 23) | ((val >> 25));
    out[17] = (1U << 23) | ((val >> 2) & 0x7fffff);
    out[18] = (val << 21) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[18] |=  (1U << 23) | ((val >> 11));
    out[19] = (val << 12) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[19] |=  (1U << 23) | ((val >> 20));
    out[20] = (val << 3) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[20] |=  (1U << 23) | ((val >> 29));
    out[21] = (1U << 23) | ((val >> 6) & 0x7fffff);
    out[22] = (val << 17) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[22] |=  (1U << 23) | ((val >> 15));
    out[23] = (val << 8) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[23] |=  (1U << 23) | ((val >> 24));
    out[24] = (1U << 23) | ((val >> 1) & 0x7fffff);
    out[25] = (val << 22) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[25] |=  (1U << 23) | ((val >> 10));
    out[26] = (val << 13) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[26] |=  (1U << 23) | ((val >> 19));
    out[27] = (val << 4) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[27] |=  (1U << 23) | ((val >> 28));
    out[28] = (1U << 23) | ((val >> 5) & 0x7fffff);
    out[29] = (val << 18) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 21);
    out[29] |=  (1U << 23) | ((val >> 14));
    out[30] = (val << 9) & 0x7fffff;

    val = BYTEORDER_FREE_LOAD32(in + 22);
    out[30] |=  (1U << 23) | ((val >> 23));
    out[31] = (1U << 23) | (val & 0x7fffff);
  }
}

inline void VSER_UNPACK24(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 3, out += 4, in += 3) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 24) | ((val >> 8));
    out[1] = (val << 16) & 0xffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 24) | ((val >> 16));
    out[2] = (val << 8) & 0xffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 24) | ((val >> 24));
    out[3] = (1U << 24) | (val & 0xffffff);
  }
}

inline void VSER_UNPACK25(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 25, out += 32, in += 25) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 25) | ((val >> 7));
    out[1] = (val << 18) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 25) | ((val >> 14));
    out[2] = (val << 11) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 25) | ((val >> 21));
    out[3] = (val << 4) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 25) | ((val >> 28));
    out[4] = (1U << 25) | ((val >> 3) & 0x01ffffff);
    out[5] = (val << 22) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[5] |=  (1U << 25) | ((val >> 10));
    out[6] = (val << 15) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[6] |=  (1U << 25) | ((val >> 17));
    out[7] = (val << 8) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[7] |=  (1U << 25) | ((val >> 24));
    out[8] = (val << 1) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[8] |=  (1U << 25) | ((val >> 31));
    out[9] = (1U << 25) | ((val >> 6) & 0x01ffffff);
    out[10] = (val << 19) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[10] |=  (1U << 25) | ((val >> 13));
    out[11] = (val << 12) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[11] |=  (1U << 25) | ((val >> 20));
    out[12] = (val << 5) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[12] |=  (1U << 25) | ((val >> 27));
    out[13] = (1U << 25) | (((val >> 2) & 0x01ffffff));
    out[14] = (val << 23) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[14] |=  (1U << 25) | ((val >> 9));
    out[15] = (val << 16) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[15] |=  (1U << 25) | ((val >> 16));
    out[16] = (val << 9) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[16] |=  (1U << 25) | ((val >> 23));
    out[17] = (val << 2) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[17] |=  (1U << 25) | ((val >> 30));
    out[18] = (1U << 25) | ((val >> 5) & 0x01ffffff);
    out[19] = (val << 20) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[19] |=  (1U << 25) | ((val >> 12));
    out[20] = (val << 13) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[20] |=  (1U << 25) | ((val >> 19));
    out[21] = (val << 6) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[21] |=  (1U << 25) | ((val >> 26));
    out[22] = (1U << 25) | ((val >> 1) & 0x01ffffff);
    out[23] = (val << 24) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[23] |=  (1U << 25) | ((val >> 8));
    out[24] = (val << 17) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[24] |=  (1U << 25) | ((val >> 15));
    out[25] = (val << 10) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[25] |=  (1U << 25) | ((val >> 22));
    out[26] = (val << 3) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 21);
    out[26] |=  (1U << 25) | ((val >> 29));
    out[27] = (1U << 25) | ((val >> 4) & 0x01ffffff);
    out[28] = (val << 21) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 22);
    out[28] |=  (1U << 25) | ((val >> 11));
    out[29] = (val << 14) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 23);
    out[29] |=  (1U << 25) | ((val >> 18));
    out[30] = (val << 7) & 0x01ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 24);
    out[30] |=  (1U << 25) | ((val >> 25));
    out[31] = (1U << 25) | (val & 0x01ffffff);
  }
}

inline void VSER_UNPACK26(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 13, out += 16, in += 13) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 26) | ((val >> 6));
    out[1] = (val << 20) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 26) | ((val >> 12));
    out[2] = (val << 14) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 26) | ((val >> 18));
    out[3] = (val << 8) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 26) | ((val >> 24));
    out[4] = (val << 2) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 26) | ((val >> 30));
    out[5] = (1U << 26) | ((val >> 4) & 0x03ffffff);
    out[6] = (val << 22) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[6] |=  (1U << 26) | ((val >> 10));
    out[7] = (val << 16) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[7] |=  (1U << 26) | ((val >> 16));
    out[8] = (val << 10) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[8] |=  (1U << 26) | ((val >> 22));
    out[9] = (val << 4) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[9] |=  (1U << 26) | ((val >> 28));
    out[10] = (1U << 26) | ((val >> 2) & 0x03ffffff);
    out[11] = (val << 24) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[11] |=  (1U << 26) | ((val >> 8));
    out[12] = (val << 18) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[12] |=  (1U << 26) | ((val >> 14));
    out[13] = (val << 12) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[13] |=  (1U << 26) | ((val >> 20));
    out[14] = (val << 6) & 0x03ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[14] |=  (1U << 26) | ((val >> 26));
    out[15] = (1U << 26) | (val & 0x03ffffff);
  }
}

inline void VSER_UNPACK27(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 27, out += 32, in += 27) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 27) | ((val >> 5));
    out[1] = (val << 22) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 27) | ((val >> 10));
    out[2] = (val << 17) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 27) | ((val >> 15));
    out[3] = (val << 12) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 27) | ((val >> 20));
    out[4] = (val << 7) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 27) | ((val >> 25));
    out[5] = (val << 2) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[5] |=  (1U << 27) | ((val >> 30));
    out[6] = (1U << 27) | ((val >> 3) & 0x07ffffff);
    out[7] = (val << 24) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[7] |=  (1U << 27) | ((val >> 8));
    out[8] = (val << 19) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[8] |=  (1U << 27) | ((val >> 13));
    out[9] = (val << 14) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[9] |=  (1U << 27) | ((val >> 18));
    out[10] = (val << 9) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[10] |=  (1U << 27) | ((val >> 23));
    out[11] = (val << 4) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[11] |=  (1U << 27) | ((val >> 28));
    out[12] = (1U << 27) | ((val >> 1) & 0x07ffffff);
    out[13] = (val << 26) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[13] |=  (1U << 27) | ((val >> 6));
    out[14] = (val << 21) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[14] |=  (1U << 27) | ((val >> 11));
    out[15] = (val << 16) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[15] |=  (1U << 27) | ((val >> 16));
    out[16] = (val << 11) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[16] |=  (1U << 27) | ((val >> 21));
    out[17] = (val << 6) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[17] |=  (1U << 27) | ((val >> 26));
    out[18] = (val << 1) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[18] |=  (1U << 27) | ((val >> 31));
    out[19] = (1U << 27) | ((val >> 4) & 0x07ffffff);
    out[20] = (val << 23) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[20] |=  (1U << 27) | ((val >> 9));
    out[21] = (val << 18) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[21] |=  (1U << 27) | ((val >> 14));
    out[22] = (val << 13) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[22] |=  (1U << 27) | ((val >> 19));
    out[23] = (val << 8) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[23] |=  (1U << 27) | ((val >> 24));
    out[24] = (val << 3) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 21);
    out[24] |=  (1U << 27) | ((val >> 29));
    out[25] = (1U << 27) | ((val >> 2) & 0x07ffffff);
    out[26] = (val << 25) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 22);
    out[26] |=  (1U << 27) | ((val >> 7));
    out[27] = (val << 20) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 23);
    out[27] |=  (1U << 27) | ((val >> 12));
    out[28] = (val << 15) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 24);
    out[28] |=  (1U << 27) | ((val >> 17));
    out[29] = (val << 10) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 25);
    out[29] |=  (1U << 27) | ((val >> 22));
    out[30] = (val << 5) & 0x07ffffff;

    val = BYTEORDER_FREE_LOAD32(in + 26);
    out[30] |=  (1U << 27) | ((val >> 27));
    out[31] = (1U << 27) | (val & 0x07ffffff);
  }
}

inline void VSER_UNPACK28(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 7, out += 8, in += 7) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 28) | ((val >> 4));
    out[1] = (val << 24) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 28) | ((val >> 8));
    out[2] = (val << 20) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 28) | ((val >> 12));
    out[3] = (val << 16) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 28) | ((val >> 16));
    out[4] = (val << 12) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 28) | ((val >> 20));
    out[5] = (val << 8) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[5] |=  (1U << 28) | ((val >> 24));
    out[6] = (val << 4) & 0x0fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[6] |=  (1U << 28) | ((val >> 28));
    out[7] = (1U << 28) | (val & 0x0fffffff);
  }
}

inline void VSER_UNPACK29(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 29, out += 32, in += 29) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 29) | ((val >> 3));
    out[1] = (val << 26) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 29) | ((val >> 6));
    out[2] = (val << 23) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 29) | ((val >> 9));
    out[3] = (val << 20) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 29) | ((val >> 12));
    out[4] = (val << 17) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 29) | ((val >> 15));
    out[5] = (val << 14) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[5] |=  (1U << 29) | ((val >> 18));
    out[6] = (val << 11) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[6] |=  (1U << 29) | ((val >> 21));
    out[7] = (val << 8) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[7] |=  (1U << 29) | ((val >> 24));
    out[8] = (val << 5) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[8] |=  (1U << 29) | ((val >> 27));
    out[9] = (val << 2) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[9] |=  (1U << 29) | ((val >> 30));
    out[10] = (1U << 29) | ((val >> 1) & 0x1fffffff);
    out[11] = (val << 28) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[11] |=  (1U << 29) | ((val >> 4));
    out[12] = (val << 25) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[12] |=  (1U << 29) | ((val >> 7));
    out[13] = (val << 22) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[13] |=  (1U << 29) | ((val >> 10));
    out[14] = (val << 19) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[14] |=  (1U << 29) | ((val >> 13));
    out[15] = (val << 16) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[15] |=  (1U << 29) | ((val >> 16));
    out[16] = (val << 13) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[16] |=  (1U << 29) | ((val >> 19));
    out[17] = (val << 10) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[17] |=  (1U << 29) | ((val >> 22));
    out[18] = (val << 7) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[18] |=  (1U << 29) | ((val >> 25));
    out[19] = (val << 4) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[19] |=  (1U << 29) | ((val >> 28));
    out[20] = (val << 1) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[20] |=  (1U << 29) | ((val >> 31));
    out[21] = (1U << 29) | ((val >> 2) & 0x1fffffff);
    out[22] = (val << 27) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[22] |=  (1U << 29) | ((val >> 5));
    out[23] = (val << 24) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 21);
    out[23] |=  (1U << 29) | ((val >> 8));
    out[24] = (val << 21) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 22);
    out[24] |=  (1U << 29) | ((val >> 11));
    out[25] = (val << 18) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 23);
    out[25] |=  (1U << 29) | ((val >> 14));
    out[26] = (val << 15) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 24);
    out[26] |=  (1U << 29) | ((val >> 17));
    out[27] = (val << 12) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 25);
    out[27] |=  (1U << 29) | ((val >> 20));
    out[28] = (val << 9) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 26);
    out[28] |=  (1U << 29) | ((val >> 23));
    out[29] = (val << 6) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 27);
    out[29] |=  (1U << 29) | ((val >> 26));
    out[30] = (val << 3) & 0x1fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 28);
    out[30] |=  (1U << 29) | ((val >> 29));
    out[31] = (1U << 29) | (val & 0x1fffffff);
  }
}

inline void VSER_UNPACK30(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 15, out += 16, in += 15) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 30) | ((val >> 2));
    out[1] = (val << 28) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 30) | ((val >> 4));
    out[2] = (val << 26) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 30) | ((val >> 6));
    out[3] = (val << 24) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 30) | ((val >> 8));
    out[4] = (val << 22) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 30) | ((val >> 10));
    out[5] = (val << 20) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[5] |=  (1U << 30) | ((val >> 12));
    out[6] = (val << 18) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[6] |=  (1U << 30) | ((val >> 14));
    out[7] = (val << 16) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[7] |=  (1U << 30) | ((val >> 16));
    out[8] = (val << 14) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[8] |=  (1U << 30) | ((val >> 18));
    out[9] = (val << 12) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[9] |=  (1U << 30) | ((val >> 20));
    out[10] = (val << 10) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[10] |=  (1U << 30) | ((val >> 22));
    out[11] = (val << 8) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[11] |=  (1U << 30) | ((val >> 24));
    out[12] = (val << 6) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[12] |=  (1U << 30) | ((val >> 26));
    out[13] = (val << 4) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[13] |=  (1U << 30) | ((val >> 28));
    out[14] = (val << 2) & 0x3fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[14] |=  (1U << 30) | ((val >> 30));
    out[15] = (1U << 30) | (val & 0x3fffffff);
  }
}

inline void VSER_UNPACK31(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0;
          i < bs; i += 31, out += 32, in += 31) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);
    out[0] = (1U << 31) | ((val >> 1));
    out[1] = (val << 30) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 1);
    out[1] |=  (1U << 31) | ((val >> 2));
    out[2] = (val << 29) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 2);
    out[2] |=  (1U << 31) | ((val >> 3));
    out[3] = (val << 28) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 3);
    out[3] |=  (1U << 31) | ((val >> 4));
    out[4] = (val << 27) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 4);
    out[4] |=  (1U << 31) | ((val >> 5));
    out[5] = (val << 26) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 5);
    out[5] |=  (1U << 31) | ((val >> 6));
    out[6] = (val << 25) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 6);
    out[6] |=  (1U << 31) | ((val >> 7));
    out[7] = (val << 24) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 7);
    out[7] |=  (1U << 31) | ((val >> 8));
    out[8] = (val << 23) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 8);
    out[8] |=  (1U << 31) | ((val >> 9));
    out[9] = (val << 22) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 9);
    out[9] |=  (1U << 31) | ((val >> 10));
    out[10] = (val << 21) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 10);
    out[10] |=  (1U << 31) | ((val >> 11));
    out[11] = (val << 20) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 11);
    out[11] |=  (1U << 31) | ((val >> 12));
    out[12] = (val << 19) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 12);
    out[12] |=  (1U << 31) | ((val >> 13));
    out[13] = (val << 18) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 13);
    out[13] |=  (1U << 31) | ((val >> 14));
    out[14] = (val << 17) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 14);
    out[14] |=  (1U << 31) | ((val >> 15));
    out[15] = (val << 16) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 15);
    out[15] |=  (1U << 31) | ((val >> 16));
    out[16] = (val << 15) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 16);
    out[16] |=  (1U << 31) | ((val >> 17));
    out[17] = (val << 14) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 17);
    out[17] |=  (1U << 31) | ((val >> 18));
    out[18] = (val << 13) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 18);
    out[18] |=  (1U << 31) | ((val >> 19));
    out[19] = (val << 12) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 19);
    out[19] |=  (1U << 31) | ((val >> 20));
    out[20] = (val << 11) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 20);
    out[20] |=  (1U << 31) | ((val >> 21));
    out[21] = (val << 10) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 21);
    out[21] |=  (1U << 31) | ((val >> 22));
    out[22] = (val << 9) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 22);
    out[22] |=  (1U << 31) | ((val >> 23));
    out[23] = (val << 8) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 23);
    out[23] |=  (1U << 31) | ((val >> 24));
    out[24] = (val << 7) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 24);
    out[24] |=  (1U << 31) | ((val >> 25));
    out[25] = (val << 6) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 25);
    out[25] |=  (1U << 31) | ((val >> 26));
    out[26] = (val << 5) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 26);
    out[26] |=  (1U << 31) | ((val >> 27));
    out[27] = (val << 4) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 27);
    out[27] |=  (1U << 31) | ((val >> 28));
    out[28] = (val << 3) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 28);
    out[28] |=  (1U << 31) | ((val >> 29));
    out[29] = (val << 2) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 29);
    out[29] |=  (1U << 31) | ((val >> 30));
    out[30] = (val << 1) & 0x7fffffff;

    val = BYTEORDER_FREE_LOAD32(in + 30);
    out[30] |=  (1U << 31) | ((val >> 31));
    out[31] = (1U << 31) | (val & 0x7fffffff);
  }
}

inline void VSER_UNPACK32(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {
  for (uint32_t i = 0; i < bs;
          i += 32, out += 1, in += 1)
    out[0] = BYTEORDER_FREE_LOAD32(in);
}

/* A interface of unpacking functions above */
typedef void (*vser_unpack_t)(uint32_t *out,
                              const uint32_t *in,
                              uint32_t bs);

vser_unpack_t VSER_UNPACK[] = {
  VSER_UNPACK1, VSER_UNPACK2,
  VSER_UNPACK3, VSER_UNPACK4,
  VSER_UNPACK5, VSER_UNPACK6,
  VSER_UNPACK7, VSER_UNPACK8,
  VSER_UNPACK9, VSER_UNPACK10,
  VSER_UNPACK11, VSER_UNPACK12,
  VSER_UNPACK13, VSER_UNPACK14,
  VSER_UNPACK15, VSER_UNPACK16,
  VSER_UNPACK17, VSER_UNPACK18,
  VSER_UNPACK19, VSER_UNPACK20,
  VSER_UNPACK21, VSER_UNPACK22,
  VSER_UNPACK23, VSER_UNPACK24,
  VSER_UNPACK25, VSER_UNPACK26,
  VSER_UNPACK27, VSER_UNPACK28,
  VSER_UNPACK29, VSER_UNPACK30,
  VSER_UNPACK31, VSER_UNPACK32
};

} /* namespace: */

VSE_R::VSE_R()
    : EncodingBase(E_VSER),
      wmem_(INITIALIZE_SPTR(uint32_t, MAXLEN)) {}

VSE_R::~VSE_R() throw() {}

void VSE_R::encodeArray(const uint32_t *in,
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

  uint64_t ntotal = 0;

  /* Compute logs of all numbers */
  REGISTER_VECTOR_RAII(uint32_t, logs, len);
  for (uint32_t i = 0; i < len; i++) {
    if (in[i] != 0)
      logs[i] = 31 - MSB32(in[i] + 1);
    else
      logs[i] = 0;
  }

  /* Compress a sequence of logs with VSEncodingNaive */
  VSEncodingNaive vnav;
  uint64_t csize = *nvalue - 2;
  vnav.encodeArray(logs, len, out + 2, &csize);

  /* Output the information of a 1st section */
  BYTEORDER_FREE_STORE64(out, csize);
  out += csize + 2;
  ntotal = csize + 2;
  ASSERT(ntotal < *nvalue);

  /*
   * hist[i] stores the number of occs of number whose
   * log is equal to i.
   */
  uint32_t  hist[VSER_LOGS_LEN + 1];

  for (uint32_t i = 0; i <= VSER_LOGS_LEN; i++)
    hist[i] = 0;

  /* Count the number of occs */
  uint32_t maxL = 0;

  for (uint32_t i = 0; i < len; i++) {
    if (logs[i] != 0)
      hist[logs[i]]++;
  }

  for (uint32_t i = 0; i <= VSER_LOGS_LEN; i++) {
    if (hist[i] != 0)
      maxL = i;
  }

  /* Write the number of occs resorting to Delta code */
  F_Delta fd;
  hist[0] = maxL;
  csize = *nvalue - ntotal - 2;
  fd.encodeArray(hist, maxL + 1, out + 2, &csize);

  /* Output the information of a 2nd section */
  BYTEORDER_FREE_STORE64(out, csize);
  out += csize + 2;
  ntotal += csize + 2;
  ASSERT(ntotal < *nvalue);

  /* Ready to write each integer */
  BitsWriter  *wt[VSER_LOGS_LEN];

  for (uint32_t i = 1; i <= maxL; i++) {
    if (hist[i] != 0) {
      wt[i - 1] = new BitsWriter(out, *nvalue - ntotal);
      uint32_t offset = DIV_ROUNDUP(i * hist[i], 32);
      ntotal += offset, out += offset;
    }

    ASSERT(ntotal < *nvalue);
  }

  /* Write the number in blocks depending on their logs */
  for (uint32_t i = 0; i < len; i++) {
    if (logs[i] != 0)
      wt[logs[i] - 1]->write_bits(in[i] + 1, logs[i]);
  }

  for (uint32_t i = 0; i < maxL; i++) {
    if (hist[i + 1] != 0) {
      wt[i]->flush_bits();
      delete wt[i];
    }
  }

  *nvalue = ntotal;
}

void VSE_R::decodeArray(const uint32_t *in,
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

  const uint32_t *iterm = in + len;

  VSEncodingNaive vnav;
  uint64_t n = BYTEORDER_FREE_LOAD64(in);
  vnav.decodeArray(in + 2, n, out, nvalue);
  in += n + 2;

  /* *in stores the length of the Delta encoded block */
  uint32_t  *blk[VSER_LOGS_LEN];

  n = BYTEORDER_FREE_LOAD64(in);
  in += 2;

  BitsReader rd(in, iterm - in);
  uint32_t maxL = rd.read_fdelta();
  in += n;

  uint32_t nlen = 0;
  uint32_t *outs = wmem_.get();

  for (uint32_t i = 1; i <= maxL; i++) {
    if (UNLIKELY(rd.pos() >= iterm))
      break;

    uint32_t n = rd.read_fdelta();

    if (n != 0) {
      blk[i - 1] = &outs[nlen];
      (VSER_UNPACK[i - 1])(&outs[nlen], in, DIV_ROUNDUP(n * i, 32));
      in += DIV_ROUNDUP(n * i, 32);
      nlen +=  n;
    }
  }

  for (uint32_t i = 0; i < nvalue; i++)
    out[i] = (out[i] == 0)? 0 : *(blk[out[i] - 1])++ - 1;
}

uint64_t VSE_R::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
