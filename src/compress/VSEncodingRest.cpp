/*-----------------------------------------------------------------------------
 *  VSEncodingRest.hpp - A compact-oriented implementation of VSEncoding
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

#include <compress/policy/VSEncodingRest.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSEREST_LOGLEN = 4;
const uint32_t VSEREST_LOGLOG = 4;

const uint32_t VSEREST_LOGDESC =
    VSEREST_LOGLEN + VSEREST_LOGLOG;

const uint32_t VSEREST_LENS_LEN = 1U << VSEREST_LOGLEN;
const uint32_t VSEREST_LOGS_LEN = 1U << VSEREST_LOGLOG;
const uint32_t VSEREST_LEN = 1U << VSEREST_LOGDESC;

/* Unpacker: 0 */
inline void VSEREST_UNPACK0_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  *out += 1;
}

inline void VSEREST_UNPACK0_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  *out += 2;
}

inline void VSEREST_UNPACK0_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  *out += 3;
}

inline void VSEREST_UNPACK0_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  *out += 4;
}

inline void VSEREST_UNPACK0_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  *out += 5;
}

inline void VSEREST_UNPACK0_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  *out += 6;
}

inline void VSEREST_UNPACK0_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  *out += 7;
}

inline void VSEREST_UNPACK0_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  *out += 8;
}

inline void VSEREST_UNPACK0_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  *out += 9;
}

inline void VSEREST_UNPACK0_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  *out += 10;
}

inline void VSEREST_UNPACK0_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  *out += 11;
}

inline void VSEREST_UNPACK0_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  *out += 12;
}

inline void VSEREST_UNPACK0_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {

  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  ZMEMCPY128(*out + 12);
  *out += 14;
}

inline void VSEREST_UNPACK0_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  ZMEMCPY128(*out + 12);
  *out += 16;
}

inline void VSEREST_UNPACK0_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {

  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  ZMEMCPY128(*out + 12);
  ZMEMCPY128(*out + 16);
  ZMEMCPY128(*out + 20);
  ZMEMCPY128(*out + 24);
  ZMEMCPY128(*out + 28);
  *out += 32;
}

inline void VSEREST_UNPACK0_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  ZMEMCPY128(*out);
  ZMEMCPY128(*out + 4);
  ZMEMCPY128(*out + 8);
  ZMEMCPY128(*out + 12);
  ZMEMCPY128(*out + 16);
  ZMEMCPY128(*out + 20);
  ZMEMCPY128(*out + 24);
  ZMEMCPY128(*out + 28);
  ZMEMCPY128(*out + 32);
  ZMEMCPY128(*out + 36);
  ZMEMCPY128(*out + 40);
  ZMEMCPY128(*out + 44);
  ZMEMCPY128(*out + 48);
  ZMEMCPY128(*out + 52);
  ZMEMCPY128(*out + 56);
  ZMEMCPY128(*out + 60);
  *out += 64;
}

namespace {

#define VSEREST_PUSH_BUF(__val__, __bit__, __fill__, __buf__) \
    ({  \
      ASSERT(__bit__ < 32); \
      __buf__ = (__buf__ << __bit__) | (__val__ & ((1U << __bit__) - 1)); \
      __fill__ += __bit__;    \
    })

/* FIXME: Need to fix in a thread-safe way */
uint32_t number_of_filled_bits;
uint64_t buffer_data;

} /* namespace: */

/* UNPACKER: 1 */
inline void VSEREST_UNPACK1_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;

  VSEREST_PUSH_BUF(val, 31, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK1_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;

  VSEREST_PUSH_BUF(val, 30, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK1_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK1_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK1_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;

  VSEREST_PUSH_BUF(val, 27, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK1_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 1, *out += 6;
}

inline void VSEREST_UNPACK1_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;

  VSEREST_PUSH_BUF(val, 25, number_of_filled_bits, buffer_data);
  *in += 1, *out += 7;
}

inline void VSEREST_UNPACK1_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 1, *out += 8;
}

inline void VSEREST_UNPACK1_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;

  VSEREST_PUSH_BUF(val, 23, number_of_filled_bits, buffer_data);
  *in += 1, *out += 9;
}

inline void VSEREST_UNPACK1_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 1, *out += 10;
}

inline void VSEREST_UNPACK1_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;
  (*out)[10] = (val >> 21) & 0x01;

  VSEREST_PUSH_BUF(val, 21, number_of_filled_bits, buffer_data);
  *in += 1, *out += 11;
}

inline void VSEREST_UNPACK1_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;
  (*out)[10] = (val >> 21) & 0x01;
  (*out)[11] = (val >> 20) & 0x01;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 12;
}

inline void VSEREST_UNPACK1_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;
  (*out)[10] = (val >> 21) & 0x01;
  (*out)[11] = (val >> 20) & 0x01;
  (*out)[12] = (val >> 19) & 0x01;
  (*out)[13] = (val >> 18) & 0x01;

  VSEREST_PUSH_BUF(val, 18, number_of_filled_bits, buffer_data);
  *in += 1, *out += 14;
}

inline void VSEREST_UNPACK1_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;
  (*out)[10] = (val >> 21) & 0x01;
  (*out)[11] = (val >> 20) & 0x01;
  (*out)[12] = (val >> 19) & 0x01;
  (*out)[13] = (val >> 18) & 0x01;
  (*out)[14] = (val >> 17) & 0x01;
  (*out)[15] = (val >> 16) & 0x01;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 16;
}

inline void VSEREST_UNPACK1_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 31;
  (*out)[1] = (val >> 30) & 0x01;
  (*out)[2] = (val >> 29) & 0x01;
  (*out)[3] = (val >> 28) & 0x01;
  (*out)[4] = (val >> 27) & 0x01;
  (*out)[5] = (val >> 26) & 0x01;
  (*out)[6] = (val >> 25) & 0x01;
  (*out)[7] = (val >> 24) & 0x01;
  (*out)[8] = (val >> 23) & 0x01;
  (*out)[9] = (val >> 22) & 0x01;
  (*out)[10] = (val >> 21) & 0x01;
  (*out)[11] = (val >> 20) & 0x01;
  (*out)[12] = (val >> 19) & 0x01;
  (*out)[13] = (val >> 18) & 0x01;
  (*out)[14] = (val >> 17) & 0x01;
  (*out)[15] = (val >> 16) & 0x01;
  (*out)[16] = (val >> 15) & 0x01;
  (*out)[17] = (val >> 14) & 0x01;
  (*out)[18] = (val >> 13) & 0x01;
  (*out)[19] = (val >> 12) & 0x01;
  (*out)[20] = (val >> 11) & 0x01;
  (*out)[21] = (val >> 10) & 0x01;
  (*out)[22] = (val >> 9) & 0x01;
  (*out)[23] = (val >> 8) & 0x01;
  (*out)[24] = (val >> 7) & 0x01;
  (*out)[25] = (val >> 6) & 0x01;
  (*out)[26] = (val >> 5) & 0x01;
  (*out)[27] = (val >> 4) & 0x01;
  (*out)[28] = (val >> 3) & 0x01;
  (*out)[29] = (val >> 2) & 0x01;
  (*out)[30] = (val >> 1) & 0x01;
  (*out)[31] = val & 0x01;

  *in += 1, *out += 32;
}

inline void VSEREST_UNPACK1_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 31;
    (*out)[1] = (val >> 30) & 0x01;
    (*out)[2] = (val >> 29) & 0x01;
    (*out)[3] = (val >> 28) & 0x01;
    (*out)[4] = (val >> 27) & 0x01;
    (*out)[5] = (val >> 26) & 0x01;
    (*out)[6] = (val >> 25) & 0x01;
    (*out)[7] = (val >> 24) & 0x01;
    (*out)[8] = (val >> 23) & 0x01;
    (*out)[9] = (val >> 22) & 0x01;
    (*out)[10] = (val >> 21) & 0x01;
    (*out)[11] = (val >> 20) & 0x01;
    (*out)[12] = (val >> 19) & 0x01;
    (*out)[13] = (val >> 18) & 0x01;
    (*out)[14] = (val >> 17) & 0x01;
    (*out)[15] = (val >> 16) & 0x01;
    (*out)[16] = (val >> 15) & 0x01;
    (*out)[17] = (val >> 14) & 0x01;
    (*out)[18] = (val >> 13) & 0x01;
    (*out)[19] = (val >> 12) & 0x01;
    (*out)[20] = (val >> 11) & 0x01;
    (*out)[21] = (val >> 10) & 0x01;
    (*out)[22] = (val >> 9) & 0x01;
    (*out)[23] = (val >> 8) & 0x01;
    (*out)[24] = (val >> 7) & 0x01;
    (*out)[25] = (val >> 6) & 0x01;
    (*out)[26] = (val >> 5) & 0x01;
    (*out)[27] = (val >> 4) & 0x01;
    (*out)[28] = (val >> 3) & 0x01;
    (*out)[29] = (val >> 2) & 0x01;
    (*out)[30] = (val >> 1) & 0x01;
    (*out)[31] = val & 0x01;
  }
}

/* UNPACKER: 2 */
inline void VSEREST_UNPACK2_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;

  VSEREST_PUSH_BUF(val, 30, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK2_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK2_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK2_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK2_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK2_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 6;
}

inline void VSEREST_UNPACK2_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;

  VSEREST_PUSH_BUF(val, 18, number_of_filled_bits, buffer_data);
  *in += 1, *out += 7;
}

inline void VSEREST_UNPACK2_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 8;
}

inline void VSEREST_UNPACK2_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 1, *out += 9;
}

inline void VSEREST_UNPACK2_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;
  (*out)[9] = (val >> 12) & 0x03;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 1, *out += 10;
}

inline void VSEREST_UNPACK2_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;
  (*out)[9] = (val >> 12) & 0x03;
  (*out)[10] = (val >> 10) & 0x03;

  VSEREST_PUSH_BUF(val, 10, number_of_filled_bits, buffer_data);
  *in += 1, *out += 11;
}

inline void VSEREST_UNPACK2_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;
  (*out)[9] = (val >> 12) & 0x03;
  (*out)[10] = (val >> 10) & 0x03;
  (*out)[11] = (val >> 8) & 0x03;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 12;
}

inline void VSEREST_UNPACK2_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;
  (*out)[9] = (val >> 12) & 0x03;
  (*out)[10] = (val >> 10) & 0x03;
  (*out)[11] = (val >> 8) & 0x03;
  (*out)[12] = (val >> 6) & 0x03;
  (*out)[13] = (val >> 4) & 0x03;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 1, *out += 14;
}

inline void VSEREST_UNPACK2_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 30;
  (*out)[1] = (val >> 28) & 0x03;
  (*out)[2] = (val >> 26) & 0x03;
  (*out)[3] = (val >> 24) & 0x03;
  (*out)[4] = (val >> 22) & 0x03;
  (*out)[5] = (val >> 20) & 0x03;
  (*out)[6] = (val >> 18) & 0x03;
  (*out)[7] = (val >> 16) & 0x03;
  (*out)[8] = (val >> 14) & 0x03;
  (*out)[9] = (val >> 12) & 0x03;
  (*out)[10] = (val >> 10) & 0x03;
  (*out)[11] = (val >> 8) & 0x03;
  (*out)[12] = (val >> 6) & 0x03;
  (*out)[13] = (val >> 4) & 0x03;
  (*out)[14] = (val >> 2) & 0x03;
  (*out)[15] = val & 0x03;

  *in += 1, *out += 16;
}

inline void VSEREST_UNPACK2_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 30;
    (*out)[1] = (val >> 28) & 0x03;
    (*out)[2] = (val >> 26) & 0x03;
    (*out)[3] = (val >> 24) & 0x03;
    (*out)[4] = (val >> 22) & 0x03;
    (*out)[5] = (val >> 20) & 0x03;
    (*out)[6] = (val >> 18) & 0x03;
    (*out)[7] = (val >> 16) & 0x03;
    (*out)[8] = (val >> 14) & 0x03;
    (*out)[9] = (val >> 12) & 0x03;
    (*out)[10] = (val >> 10) & 0x03;
    (*out)[11] = (val >> 8) & 0x03;
    (*out)[12] = (val >> 6) & 0x03;
    (*out)[13] = (val >> 4) & 0x03;
    (*out)[14] = (val >> 2) & 0x03;
    (*out)[15] = val & 0x03;
  }
}

inline void VSEREST_UNPACK2_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 30;
    (*out)[1] = (val >> 28) & 0x03;
    (*out)[2] = (val >> 26) & 0x03;
    (*out)[3] = (val >> 24) & 0x03;
    (*out)[4] = (val >> 22) & 0x03;
    (*out)[5] = (val >> 20) & 0x03;
    (*out)[6] = (val >> 18) & 0x03;
    (*out)[7] = (val >> 16) & 0x03;
    (*out)[8] = (val >> 14) & 0x03;
    (*out)[9] = (val >> 12) & 0x03;
    (*out)[10] = (val >> 10) & 0x03;
    (*out)[11] = (val >> 8) & 0x03;
    (*out)[12] = (val >> 6) & 0x03;
    (*out)[13] = (val >> 4) & 0x03;
    (*out)[14] = (val >> 2) & 0x03;
    (*out)[15] = val & 0x03;
  }
}

/* UNPACKER: 3 */
inline void VSEREST_UNPACK3_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK3_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK3_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;

  VSEREST_PUSH_BUF(val, 23, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK3_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK3_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;

  VSEREST_PUSH_BUF(val, 17, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK3_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 1, *out += 6;
}

inline void VSEREST_UNPACK3_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;

  VSEREST_PUSH_BUF(val, 11, number_of_filled_bits, buffer_data);
  *in += 1, *out += 7;
}

inline void VSEREST_UNPACK3_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 8;
}

inline void VSEREST_UNPACK3_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;

  VSEREST_PUSH_BUF(val, 5, number_of_filled_bits, buffer_data);
  *in += 1, *out += 9;
}

inline void VSEREST_UNPACK3_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;

  VSEREST_PUSH_BUF(val, 2, number_of_filled_bits, buffer_data);
  *in += 1, *out += 10;
}

inline void VSEREST_UNPACK3_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;
  (*out)[10] = (val << 1) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[10] |= val >> 31;

  VSEREST_PUSH_BUF(val, 31, number_of_filled_bits, buffer_data);
  *in += 2, *out += 11;
}

inline void VSEREST_UNPACK3_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;
  (*out)[10] = (val << 1) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[10] |= val >> 31;
  (*out)[11] = (val >> 28) & 0x07;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 2, *out += 12;
}

inline void VSEREST_UNPACK3_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;
  (*out)[10] = (val << 1) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[10] |= val >> 31;
  (*out)[11] = (val >> 28) & 0x07;
  (*out)[12] = (val >> 25) & 0x07;
  (*out)[13] = (val >> 22) & 0x07;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 2, *out += 14;
}

inline void VSEREST_UNPACK3_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;
  (*out)[10] = (val << 1) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[10] |= val >> 31;
  (*out)[11] = (val >> 28) & 0x07;
  (*out)[12] = (val >> 25) & 0x07;
  (*out)[13] = (val >> 22) & 0x07;
  (*out)[14] = (val >> 19) & 0x07;
  (*out)[15] = (val >> 16) & 0x07;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 16;
}

inline void VSEREST_UNPACK3_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 29;
  (*out)[1] = (val >> 26) & 0x07;
  (*out)[2] = (val >> 23) & 0x07;
  (*out)[3] = (val >> 20) & 0x07;
  (*out)[4] = (val >> 17) & 0x07;
  (*out)[5] = (val >> 14) & 0x07;
  (*out)[6] = (val >> 11) & 0x07;
  (*out)[7] = (val >> 8) & 0x07;
  (*out)[8] = (val >> 5) & 0x07;
  (*out)[9] = (val >> 2) & 0x07;
  (*out)[10] = (val << 1) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[10] |= val >> 31;
  (*out)[11] = (val >> 28) & 0x07;
  (*out)[12] = (val >> 25) & 0x07;
  (*out)[13] = (val >> 22) & 0x07;
  (*out)[14] = (val >> 19) & 0x07;
  (*out)[15] = (val >> 16) & 0x07;
  (*out)[16] = (val >> 13) & 0x07;
  (*out)[17] = (val >> 10) & 0x07;
  (*out)[18] = (val >> 7) & 0x07;
  (*out)[19] = (val >> 4) & 0x07;
  (*out)[20] = (val >> 1) & 0x07;
  (*out)[21] = (val << 2) & 0x07;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[21] |= val >> 30;
  (*out)[22] = (val >> 27) & 0x07;
  (*out)[23] = (val >> 24) & 0x07;
  (*out)[24] = (val >> 21) & 0x07;
  (*out)[25] = (val >> 18) & 0x07;
  (*out)[26] = (val >> 15) & 0x07;
  (*out)[27] = (val >> 12) & 0x07;
  (*out)[28] = (val >> 9) & 0x07;
  (*out)[29] = (val >> 6) & 0x07;
  (*out)[30] = (val >> 3) & 0x07;
  (*out)[31] = val & 0x07;

  *in += 3, *out += 32;
}

inline void VSEREST_UNPACK3_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 3, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 29;
    (*out)[1] = (val >> 26) & 0x07;
    (*out)[2] = (val >> 23) & 0x07;
    (*out)[3] = (val >> 20) & 0x07;
    (*out)[4] = (val >> 17) & 0x07;
    (*out)[5] = (val >> 14) & 0x07;
    (*out)[6] = (val >> 11) & 0x07;
    (*out)[7] = (val >> 8) & 0x07;
    (*out)[8] = (val >> 5) & 0x07;
    (*out)[9] = (val >> 2) & 0x07;
    (*out)[10] = (val << 1) & 0x07;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[10] |= val >> 31;
    (*out)[11] = (val >> 28) & 0x07;
    (*out)[12] = (val >> 25) & 0x07;
    (*out)[13] = (val >> 22) & 0x07;
    (*out)[14] = (val >> 19) & 0x07;
    (*out)[15] = (val >> 16) & 0x07;
    (*out)[16] = (val >> 13) & 0x07;
    (*out)[17] = (val >> 10) & 0x07;
    (*out)[18] = (val >> 7) & 0x07;
    (*out)[19] = (val >> 4) & 0x07;
    (*out)[20] = (val >> 1) & 0x07;
    (*out)[21] = (val << 2) & 0x07;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[21] |= val >> 30;
    (*out)[22] = (val >> 27) & 0x07;
    (*out)[23] = (val >> 24) & 0x07;
    (*out)[24] = (val >> 21) & 0x07;
    (*out)[25] = (val >> 18) & 0x07;
    (*out)[26] = (val >> 15) & 0x07;
    (*out)[27] = (val >> 12) & 0x07;
    (*out)[28] = (val >> 9) & 0x07;
    (*out)[29] = (val >> 6) & 0x07;
    (*out)[30] = (val >> 3) & 0x07;
    (*out)[31] = val & 0x07;
  }
}

/* UNPACKER: 4 */
inline void VSEREST_UNPACK4_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK4_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK4_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK4_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK4_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK4_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 6;
}

inline void VSEREST_UNPACK4_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 1, *out += 7;
}

inline void VSEREST_UNPACK4_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  *in += 1, *out += 8;
}

inline void VSEREST_UNPACK4_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[8] = val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 2, *out += 9;
}

inline void VSEREST_UNPACK4_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[8] = val >> 28;
  (*out)[9] = (val >> 24) & 0x0f;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 2, *out += 10;
}

inline void VSEREST_UNPACK4_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[8] = val >> 28;
  (*out)[9] = (val >> 24) & 0x0f;
  (*out)[10] = (val >> 20) & 0x0f;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 2, *out += 11;
}

inline void VSEREST_UNPACK4_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[8] = val >> 28;
  (*out)[9] = (val >> 24) & 0x0f;
  (*out)[10] = (val >> 20) & 0x0f;
  (*out)[11] = (val >> 16) & 0x0f;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 12;
}

inline void VSEREST_UNPACK4_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 28;
  (*out)[1] = (val >> 24) & 0x0f;
  (*out)[2] = (val >> 20) & 0x0f;
  (*out)[3] = (val >> 16) & 0x0f;
  (*out)[4] = (val >> 12) & 0x0f;
  (*out)[5] = (val >> 8) & 0x0f;
  (*out)[6] = (val >> 4) & 0x0f;
  (*out)[7] = val  & 0x0f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[8] = val >> 28;
  (*out)[9] = (val >> 24) & 0x0f;
  (*out)[10] = (val >> 20) & 0x0f;
  (*out)[11] = (val >> 16) & 0x0f;
  (*out)[12] = (val >> 12) & 0x0f;
  (*out)[13] = (val >> 8) & 0x0f;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 2, *out += 14;
}

inline void VSEREST_UNPACK4_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 28;
    (*out)[1] = (val >> 24) & 0x0f;
    (*out)[2] = (val >> 20) & 0x0f;
    (*out)[3] = (val >> 16) & 0x0f;
    (*out)[4] = (val >> 12) & 0x0f;
    (*out)[5] = (val >> 8) & 0x0f;
    (*out)[6] = (val >> 4) & 0x0f;
    (*out)[7] = val  & 0x0f;
  }
}

inline void VSEREST_UNPACK4_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 28;
    (*out)[1] = (val >> 24) & 0x0f;
    (*out)[2] = (val >> 20) & 0x0f;
    (*out)[3] = (val >> 16) & 0x0f;
    (*out)[4] = (val >> 12) & 0x0f;
    (*out)[5] = (val >> 8) & 0x0f;
    (*out)[6] = (val >> 4) & 0x0f;
    (*out)[7] = val  & 0x0f;
  }
}

inline void VSEREST_UNPACK4_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8;
          i++, *in += 1, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 28;
    (*out)[1] = (val >> 24) & 0x0f;
    (*out)[2] = (val >> 20) & 0x0f;
    (*out)[3] = (val >> 16) & 0x0f;
    (*out)[4] = (val >> 12) & 0x0f;
    (*out)[5] = (val >> 8) & 0x0f;
    (*out)[6] = (val >> 4) & 0x0f;
    (*out)[7] = val  & 0x0f;
  }
}

/* UNPACKER: 5 */
inline void VSEREST_UNPACK5_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;

  VSEREST_PUSH_BUF(val, 27, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK5_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK5_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;

  VSEREST_PUSH_BUF(val, 17, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK5_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK5_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;

  VSEREST_PUSH_BUF(val, 7, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK5_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;

  VSEREST_PUSH_BUF(val, 2, number_of_filled_bits, buffer_data);
  *in += 1, *out += 6;
}

inline void VSEREST_UNPACK5_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 2, *out += 7;
}

inline void VSEREST_UNPACK5_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 2, *out += 8;
}

inline void VSEREST_UNPACK5_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;

  VSEREST_PUSH_BUF(val, 19, number_of_filled_bits, buffer_data);
  *in += 2, *out += 9;
}

inline void VSEREST_UNPACK5_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 2, *out += 10;
}

inline void VSEREST_UNPACK5_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;
  (*out)[10] = (val >> 9) & 0x1f;

  VSEREST_PUSH_BUF(val, 9, number_of_filled_bits, buffer_data);
  *in += 2, *out += 11;
}

inline void VSEREST_UNPACK5_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;
  (*out)[10] = (val >> 9) & 0x1f;
  (*out)[11] = (val >> 4) & 0x1f;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 2, *out += 12;
}

inline void VSEREST_UNPACK5_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;
  (*out)[10] = (val >> 9) & 0x1f;
  (*out)[11] = (val >> 4) & 0x1f;
  (*out)[12] = (val << 1) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[12] |= val >> 31;
  (*out)[13] = (val >> 26) & 0x1f;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 3, *out += 14;
}

inline void VSEREST_UNPACK5_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;
  (*out)[10] = (val >> 9) & 0x1f;
  (*out)[11] = (val >> 4) & 0x1f;
  (*out)[12] = (val << 1) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[12] |= val >> 31;
  (*out)[13] = (val >> 26) & 0x1f;
  (*out)[14] = (val >> 21) & 0x1f;
  (*out)[15] = (val >> 16) & 0x1f;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 3, *out += 16;
}

inline void VSEREST_UNPACK5_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 27;
  (*out)[1] = (val >> 22) & 0x1f;
  (*out)[2] = (val >> 17) & 0x1f;
  (*out)[3] = (val >> 12) & 0x1f;
  (*out)[4] = (val >> 7) & 0x1f;
  (*out)[5] = (val >> 2) & 0x1f;
  (*out)[6] = (val << 3) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[6] |= val >> 29;
  (*out)[7] = (val >> 24) & 0x1f;
  (*out)[8] = (val >> 19) & 0x1f;
  (*out)[9] = (val >> 14) & 0x1f;
  (*out)[10] = (val >> 9) & 0x1f;
  (*out)[11] = (val >> 4) & 0x1f;
  (*out)[12] = (val << 1) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[12] |= val >> 31;
  (*out)[13] = (val >> 26) & 0x1f;
  (*out)[14] = (val >> 21) & 0x1f;
  (*out)[15] = (val >> 16) & 0x1f;
  (*out)[16] = (val >> 11) & 0x1f;
  (*out)[17] = (val >> 6) & 0x1f;
  (*out)[18] = (val >> 1) & 0x1f;
  (*out)[19] = (val << 4) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[19] |= val >> 28;
  (*out)[20] = (val >> 23) & 0x1f;
  (*out)[21] = (val >> 18) & 0x1f;
  (*out)[22] = (val >> 13) & 0x1f;
  (*out)[23] = (val >> 8) & 0x1f;
  (*out)[24] = (val >> 3) & 0x1f;
  (*out)[25] = (val << 2) & 0x1f;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[25] |= val >> 30;
  (*out)[26] = (val >> 25) & 0x1f;
  (*out)[27] = (val >> 20) & 0x1f;
  (*out)[28] = (val >> 15) & 0x1f;
  (*out)[29] = (val >> 10) & 0x1f;
  (*out)[30] = (val >> 5) & 0x1f;
  (*out)[31] = val & 0x1f;

  *in += 5, *out += 32;
}

inline void VSEREST_UNPACK5_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 5, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 27;
    (*out)[1] = (val >> 22) & 0x1f;
    (*out)[2] = (val >> 17) & 0x1f;
    (*out)[3] = (val >> 12) & 0x1f;
    (*out)[4] = (val >> 7) & 0x1f;
    (*out)[5] = (val >> 2) & 0x1f;
    (*out)[6] = (val << 3) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[6] |= val >> 29;
    (*out)[7] = (val >> 24) & 0x1f;
    (*out)[8] = (val >> 19) & 0x1f;
    (*out)[9] = (val >> 14) & 0x1f;
    (*out)[10] = (val >> 9) & 0x1f;
    (*out)[11] = (val >> 4) & 0x1f;
    (*out)[12] = (val << 1) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[12] |= val >> 31;
    (*out)[13] = (val >> 26) & 0x1f;
    (*out)[14] = (val >> 21) & 0x1f;
    (*out)[15] = (val >> 16) & 0x1f;
    (*out)[16] = (val >> 11) & 0x1f;
    (*out)[17] = (val >> 6) & 0x1f;
    (*out)[18] = (val >> 1) & 0x1f;
    (*out)[19] = (val << 4) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[19] |= val >> 28;
    (*out)[20] = (val >> 23) & 0x1f;
    (*out)[21] = (val >> 18) & 0x1f;
    (*out)[22] = (val >> 13) & 0x1f;
    (*out)[23] = (val >> 8) & 0x1f;
    (*out)[24] = (val >> 3) & 0x1f;
    (*out)[25] = (val << 2) & 0x1f;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[25] |= val >> 30;
    (*out)[26] = (val >> 25) & 0x1f;
    (*out)[27] = (val >> 20) & 0x1f;
    (*out)[28] = (val >> 15) & 0x1f;
    (*out)[29] = (val >> 10) & 0x1f;
    (*out)[30] = (val >> 5) & 0x1f;
    (*out)[31] = val & 0x1f;
  }
}

/* UNPACKER: 6 */
inline void VSEREST_UNPACK6_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK6_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK6_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK6_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK6_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;

  VSEREST_PUSH_BUF(val, 2, number_of_filled_bits, buffer_data);
  *in += 1, *out += 5;
}

inline void VSEREST_UNPACK6_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 2, *out += 6;
}

inline void VSEREST_UNPACK6_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 2, *out += 7;
}

inline void VSEREST_UNPACK6_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 8;
}

inline void VSEREST_UNPACK6_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;

  VSEREST_PUSH_BUF(val, 10, number_of_filled_bits, buffer_data);
  *in += 2, *out += 9;
}

inline void VSEREST_UNPACK6_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;
  (*out)[9] = (val >> 4) & 0x3f;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 2, *out += 10;
}

inline void VSEREST_UNPACK6_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;
  (*out)[9] = (val >> 4) & 0x3f;
  (*out)[10] = (val << 2) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[10] |= val >> 30;

  VSEREST_PUSH_BUF(val, 30, number_of_filled_bits, buffer_data);
  *in += 3, *out += 11;
}

inline void VSEREST_UNPACK6_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;
  (*out)[9] = (val >> 4) & 0x3f;
  (*out)[10] = (val << 2) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[10] |= val >> 30;
  (*out)[11] = (val >> 24) & 0x3f;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 3, *out += 12;
}

inline void VSEREST_UNPACK6_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;
  (*out)[9] = (val >> 4) & 0x3f;
  (*out)[10] = (val << 2) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[10] |= val >> 30;
  (*out)[11] = (val >> 24) & 0x3f;
  (*out)[12] = (val >> 18) & 0x3f;
  (*out)[13] = (val >> 12) & 0x3f;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 3, *out += 14;
}

inline void VSEREST_UNPACK6_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 26;
  (*out)[1] = (val >> 20) & 0x3f;
  (*out)[2] = (val >> 14) & 0x3f;
  (*out)[3] = (val >> 8) & 0x3f;
  (*out)[4] = (val >> 2) & 0x3f;
  (*out)[5] = (val << 4) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[5] |= val >> 28;
  (*out)[6] = (val >> 22) & 0x3f;
  (*out)[7] = (val >> 16) & 0x3f;
  (*out)[8] = (val >> 10) & 0x3f;
  (*out)[9] = (val >> 4) & 0x3f;
  (*out)[10] = (val << 2) & 0x3f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[10] |= val >> 30;
  (*out)[11] = (val >> 24) & 0x3f;
  (*out)[12] = (val >> 18) & 0x3f;
  (*out)[13] = (val >> 12) & 0x3f;
  (*out)[14] = (val >> 6) & 0x3f;
  (*out)[15] = val & 0x3f;

  *in += 3, *out += 16;
}

inline void VSEREST_UNPACK6_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 3, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 26;
    (*out)[1] = (val >> 20) & 0x3f;
    (*out)[2] = (val >> 14) & 0x3f;
    (*out)[3] = (val >> 8) & 0x3f;
    (*out)[4] = (val >> 2) & 0x3f;
    (*out)[5] = (val << 4) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[5] |= val >> 28;
    (*out)[6] = (val >> 22) & 0x3f;
    (*out)[7] = (val >> 16) & 0x3f;
    (*out)[8] = (val >> 10) & 0x3f;
    (*out)[9] = (val >> 4) & 0x3f;
    (*out)[10] = (val << 2) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[10] |= val >> 30;
    (*out)[11] = (val >> 24) & 0x3f;
    (*out)[12] = (val >> 18) & 0x3f;
    (*out)[13] = (val >> 12) & 0x3f;
    (*out)[14] = (val >> 6) & 0x3f;
    (*out)[15] = val & 0x3f;
  }
}

inline void VSEREST_UNPACK6_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 3, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 26;
    (*out)[1] = (val >> 20) & 0x3f;
    (*out)[2] = (val >> 14) & 0x3f;
    (*out)[3] = (val >> 8) & 0x3f;
    (*out)[4] = (val >> 2) & 0x3f;
    (*out)[5] = (val << 4) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[5] |= val >> 28;
    (*out)[6] = (val >> 22) & 0x3f;
    (*out)[7] = (val >> 16) & 0x3f;
    (*out)[8] = (val >> 10) & 0x3f;
    (*out)[9] = (val >> 4) & 0x3f;
    (*out)[10] = (val << 2) & 0x3f;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[10] |= val >> 30;
    (*out)[11] = (val >> 24) & 0x3f;
    (*out)[12] = (val >> 18) & 0x3f;
    (*out)[13] = (val >> 12) & 0x3f;
    (*out)[14] = (val >> 6) & 0x3f;
    (*out)[15] = val & 0x3f;
  }
}

/* UNPACKER: 7 */
inline void VSEREST_UNPACK7_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;

  VSEREST_PUSH_BUF(val, 25, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK7_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;

  VSEREST_PUSH_BUF(val, 18, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK7_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;

  VSEREST_PUSH_BUF(val, 11, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK7_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK7_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK7_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 2, *out += 6;
}

inline void VSEREST_UNPACK7_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;

  VSEREST_PUSH_BUF(val, 15, number_of_filled_bits, buffer_data);
  *in += 2, *out += 7;
}

inline void VSEREST_UNPACK7_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 2, *out += 8;
}

inline void VSEREST_UNPACK7_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;

  VSEREST_PUSH_BUF(val, 1, number_of_filled_bits, buffer_data);
  *in += 2, *out += 9;
}

inline void VSEREST_UNPACK7_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 3, *out += 10;
}

inline void VSEREST_UNPACK7_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;
  (*out)[10] = (val >> 19) & 0x7f;

  VSEREST_PUSH_BUF(val, 19, number_of_filled_bits, buffer_data);
  *in += 3, *out += 11;
}

inline void VSEREST_UNPACK7_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;
  (*out)[10] = (val >> 19) & 0x7f;
  (*out)[11] = (val >> 12) & 0x7f;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 3, *out += 12;
}

inline void VSEREST_UNPACK7_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;
  (*out)[10] = (val >> 19) & 0x7f;
  (*out)[11] = (val >> 12) & 0x7f;
  (*out)[12] = (val >> 5) & 0x7f;
  (*out)[13] = (val << 2) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[13] |= val >> 30;

  VSEREST_PUSH_BUF(val, 30, number_of_filled_bits, buffer_data);
  *in += 4, *out += 14;
}

inline void VSEREST_UNPACK7_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;
  (*out)[10] = (val >> 19) & 0x7f;
  (*out)[11] = (val >> 12) & 0x7f;
  (*out)[12] = (val >> 5) & 0x7f;
  (*out)[13] = (val << 2) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[13] |= val >> 30;
  (*out)[14] = (val >> 23) & 0x7f;
  (*out)[15] = (val >> 16) & 0x7f;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 4, *out += 16;
}

inline void VSEREST_UNPACK7_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 25;
  (*out)[1] = (val >> 18) & 0x7f;
  (*out)[2] = (val >> 11) & 0x7f;
  (*out)[3] = (val >> 4) & 0x7f;
  (*out)[4] = (val << 3) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] |= val >> 29;
  (*out)[5] = (val >> 22) & 0x7f;
  (*out)[6] = (val >> 15) & 0x7f;
  (*out)[7] = (val >> 8) & 0x7f;
  (*out)[8] = (val >> 1) & 0x7f;
  (*out)[9] = (val << 6) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[9] |= val >> 26;
  (*out)[10] = (val >> 19) & 0x7f;
  (*out)[11] = (val >> 12) & 0x7f;
  (*out)[12] = (val >> 5) & 0x7f;
  (*out)[13] = (val << 2) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[13] |= val >> 30;
  (*out)[14] = (val >> 23) & 0x7f;
  (*out)[15] = (val >> 16) & 0x7f;
  (*out)[16] = (val >> 9) & 0x7f;
  (*out)[17] = (val >> 2) & 0x7f;
  (*out)[18] = (val << 5) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[18] |= val >> 27;
  (*out)[19] = (val >> 20) & 0x7f;
  (*out)[20] = (val >> 13) & 0x7f;
  (*out)[21] = (val >> 6) & 0x7f;
  (*out)[22] = (val << 1) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[22] |= val >> 31;
  (*out)[23] = (val >> 24) & 0x7f;
  (*out)[24] = (val >> 17) & 0x7f;
  (*out)[25] = (val >> 10) & 0x7f;
  (*out)[26] = (val >> 3) & 0x7f;
  (*out)[27] = (val << 4) & 0x7f;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[27] |= val >> 28;
  (*out)[28] = (val >> 21) & 0x7f;
  (*out)[29] = (val >> 14) & 0x7f;
  (*out)[30] = (val >> 7) & 0x7f;
  (*out)[31] = val & 0x7f;

  *in += 7, *out += 32;
}

inline void VSEREST_UNPACK7_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 7, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 25;
    (*out)[1] = (val >> 18) & 0x7f;
    (*out)[2] = (val >> 11) & 0x7f;
    (*out)[3] = (val >> 4) & 0x7f;
    (*out)[4] = (val << 3) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[4] |= val >> 29;
    (*out)[5] = (val >> 22) & 0x7f;
    (*out)[6] = (val >> 15) & 0x7f;
    (*out)[7] = (val >> 8) & 0x7f;
    (*out)[8] = (val >> 1) & 0x7f;
    (*out)[9] = (val << 6) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[9] |= val >> 26;
    (*out)[10] = (val >> 19) & 0x7f;
    (*out)[11] = (val >> 12) & 0x7f;
    (*out)[12] = (val >> 5) & 0x7f;
    (*out)[13] = (val << 2) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[13] |= val >> 30;
    (*out)[14] = (val >> 23) & 0x7f;
    (*out)[15] = (val >> 16) & 0x7f;
    (*out)[16] = (val >> 9) & 0x7f;
    (*out)[17] = (val >> 2) & 0x7f;
    (*out)[18] = (val << 5) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[18] |= val >> 27;
    (*out)[19] = (val >> 20) & 0x7f;
    (*out)[20] = (val >> 13) & 0x7f;
    (*out)[21] = (val >> 6) & 0x7f;
    (*out)[22] = (val << 1) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 5);
    (*out)[22] |= val >> 31;
    (*out)[23] = (val >> 24) & 0x7f;
    (*out)[24] = (val >> 17) & 0x7f;
    (*out)[25] = (val >> 10) & 0x7f;
    (*out)[26] = (val >> 3) & 0x7f;
    (*out)[27] = (val << 4) & 0x7f;

    val = BYTEORDER_FREE_LOAD32(*in + 6);
    (*out)[27] |= val >> 28;
    (*out)[28] = (val >> 21) & 0x7f;
    (*out)[29] = (val >> 14) & 0x7f;
    (*out)[30] = (val >> 7) & 0x7f;
    (*out)[31] = val & 0x7f;
  }
}

/* UNPACKER: 8 */
inline void VSEREST_UNPACK8_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK8_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK8_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK8_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;
  (*out)[3] = val & 0xff;

  *in += 1, *out += 4;
}

inline void VSEREST_UNPACK8_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;
  (*out)[3] = val & 0xff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] = val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK8_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;
  (*out)[3] = val & 0xff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] = val >> 24;
  (*out)[5] = (val >> 16) & 0xff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 6;
}

inline void VSEREST_UNPACK8_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;
  (*out)[3] = val & 0xff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[4] = val >> 24;
  (*out)[5] = (val >> 16) & 0xff;
  (*out)[6] = (val >> 8) & 0xff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 2, *out += 7;
}

inline void VSEREST_UNPACK8_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }
}

inline void VSEREST_UNPACK8_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK8_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK8_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;
  (*out)[2] = (val >> 8) & 0xff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK8_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 3;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }
}

inline void VSEREST_UNPACK8_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 3;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 24;
  (*out)[1] = (val >> 16) & 0xff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK8_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }
}

inline void VSEREST_UNPACK8_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }
}

inline void VSEREST_UNPACK8_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 16;
          i++, *in += 1, *out += 4) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 24;
    (*out)[1] = (val >> 16) & 0xff;
    (*out)[2] = (val >> 8) & 0xff;
    (*out)[3] = val & 0xff;
  }
}

/* UNPACKER: 9 */
inline void VSEREST_UNPACK9_1(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;

  VSEREST_PUSH_BUF(val, 23, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK9_2(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK9_3(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;

  VSEREST_PUSH_BUF(val, 5, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK9_4(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 2, *out += 4;
}

inline void VSEREST_UNPACK9_5(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;

  VSEREST_PUSH_BUF(val, 19, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK9_6(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;

  VSEREST_PUSH_BUF(val, 10, number_of_filled_bits, buffer_data);
  *in += 2, *out += 6;
}

inline void VSEREST_UNPACK9_7(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;

  VSEREST_PUSH_BUF(val, 1, number_of_filled_bits, buffer_data);
  *in += 2, *out += 7;
}

inline void VSEREST_UNPACK9_8(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 3, *out += 8;
}

inline void VSEREST_UNPACK9_9(uint32_t ** restrict out,
                              uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;

  VSEREST_PUSH_BUF(val, 15, number_of_filled_bits, buffer_data);
  *in += 3, *out += 9;
}

inline void VSEREST_UNPACK9_10(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;

  VSEREST_PUSH_BUF(val, 6, number_of_filled_bits, buffer_data);
  *in += 3, *out += 10;
}

inline void VSEREST_UNPACK9_11(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;
  (*out)[10] = (val << 3) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[10] |= val >> 29;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 4, *out += 11;
}

inline void VSEREST_UNPACK9_12(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;
  (*out)[10] = (val << 3) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[10] |= val >> 29;
  (*out)[11] = (val >> 20) & 0x01ff;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 4, *out += 12;
}

inline void VSEREST_UNPACK9_14(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;
  (*out)[10] = (val << 3) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[10] |= val >> 29;
  (*out)[11] = (val >> 20) & 0x01ff;
  (*out)[12] = (val >> 11) & 0x01ff;
  (*out)[13] = (val >> 2) & 0x01ff;

  VSEREST_PUSH_BUF(val, 2, number_of_filled_bits, buffer_data);
  *in += 4, *out += 14;
}

inline void VSEREST_UNPACK9_16(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;
  (*out)[10] = (val << 3) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[10] |= val >> 29;
  (*out)[11] = (val >> 20) & 0x01ff;
  (*out)[12] = (val >> 11) & 0x01ff;
  (*out)[13] = (val >> 2) & 0x01ff;
  (*out)[14] = (val << 7) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[14] |= val >> 25;
  (*out)[15] = (val >> 16) & 0x01ff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 5, *out += 16;
}

inline void VSEREST_UNPACK9_32(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 23;
  (*out)[1] = (val >> 14) & 0x01ff;
  (*out)[2] = (val >> 5) & 0x01ff;
  (*out)[3] = (val << 4) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 28;
  (*out)[4] = (val >> 19) & 0x01ff;
  (*out)[5] = (val >> 10) & 0x01ff;
  (*out)[6] = (val >> 1) & 0x01ff;
  (*out)[7] = (val << 8) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[7] |= val >> 24;
  (*out)[8] = (val >> 15) & 0x01ff;
  (*out)[9] = (val >> 6) & 0x01ff;
  (*out)[10] = (val << 3) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[10] |= val >> 29;
  (*out)[11] = (val >> 20) & 0x01ff;
  (*out)[12] = (val >> 11) & 0x01ff;
  (*out)[13] = (val >> 2) & 0x01ff;
  (*out)[14] = (val << 7) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[14] |= val >> 25;
  (*out)[15] = (val >> 16) & 0x01ff;
  (*out)[16] = (val >> 7) & 0x01ff;
  (*out)[17] = (val << 2) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[17] |= val >> 30;
  (*out)[18] = (val >> 21) & 0x01ff;
  (*out)[19] = (val >> 12) & 0x01ff;
  (*out)[20] = (val >> 3) & 0x01ff;
  (*out)[21] = (val << 6) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[21] |= val >> 26;
  (*out)[22] = (val >> 17) & 0x01ff;
  (*out)[23] = (val >> 8) & 0x01ff;
  (*out)[24] = (val << 1) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 7);
  (*out)[24] |= val >> 31;
  (*out)[25] = (val >> 22) & 0x01ff;
  (*out)[26] = (val >> 13) & 0x01ff;
  (*out)[27] = (val >> 4) & 0x01ff;
  (*out)[28] = (val << 5) & 0x01ff;

  val = BYTEORDER_FREE_LOAD32(*in + 8);
  (*out)[28] |= val >> 27;
  (*out)[29] = (val >> 18) & 0x01ff;
  (*out)[30] = (val >> 9) & 0x01ff;
  (*out)[31] = val & 0x01ff;

  *in += 9, *out += 32;
}

inline void VSEREST_UNPACK9_64(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 9, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 23;
    (*out)[1] = (val >> 14) & 0x01ff;
    (*out)[2] = (val >> 5) & 0x01ff;
    (*out)[3] = (val << 4) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[3] |= val >> 28;
    (*out)[4] = (val >> 19) & 0x01ff;
    (*out)[5] = (val >> 10) & 0x01ff;
    (*out)[6] = (val >> 1) & 0x01ff;
    (*out)[7] = (val << 8) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[7] |= val >> 24;
    (*out)[8] = (val >> 15) & 0x01ff;
    (*out)[9] = (val >> 6) & 0x01ff;
    (*out)[10] = (val << 3) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[10] |= val >> 29;
    (*out)[11] = (val >> 20) & 0x01ff;
    (*out)[12] = (val >> 11) & 0x01ff;
    (*out)[13] = (val >> 2) & 0x01ff;
    (*out)[14] = (val << 7) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[14] |= val >> 25;
    (*out)[15] = (val >> 16) & 0x01ff;
    (*out)[16] = (val >> 7) & 0x01ff;
    (*out)[17] = (val << 2) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 5);
    (*out)[17] |= val >> 30;
    (*out)[18] = (val >> 21) & 0x01ff;
    (*out)[19] = (val >> 12) & 0x01ff;
    (*out)[20] = (val >> 3) & 0x01ff;
    (*out)[21] = (val << 6) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 6);
    (*out)[21] |= val >> 26;
    (*out)[22] = (val >> 17) & 0x01ff;
    (*out)[23] = (val >> 8) & 0x01ff;
    (*out)[24] = (val << 1) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 7);
    (*out)[24] |= val >> 31;
    (*out)[25] = (val >> 22) & 0x01ff;
    (*out)[26] = (val >> 13) & 0x01ff;
    (*out)[27] = (val >> 4) & 0x01ff;
    (*out)[28] = (val << 5) & 0x01ff;

    val = BYTEORDER_FREE_LOAD32(*in + 8);
    (*out)[28] |= val >> 27;
    (*out)[29] = (val >> 18) & 0x01ff;
    (*out)[30] = (val >> 9) & 0x01ff;
    (*out)[31] = val & 0x01ff;
  }
}

/* UNPACKER: 10 */
inline void VSEREST_UNPACK10_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;

  VSEREST_PUSH_BUF(val, 22, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK10_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK10_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;

  VSEREST_PUSH_BUF(val, 2, number_of_filled_bits, buffer_data);
  *in += 1, *out += 3;
}

inline void VSEREST_UNPACK10_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 2, *out += 4;
}

inline void VSEREST_UNPACK10_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;

  VSEREST_PUSH_BUF(val, 14, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK10_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 2, *out += 6;
}

inline void VSEREST_UNPACK10_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;

  VSEREST_PUSH_BUF(val, 26, number_of_filled_bits, buffer_data);
  *in += 3, *out += 7;
}

inline void VSEREST_UNPACK10_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 3, *out += 8;
}

inline void VSEREST_UNPACK10_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;

  VSEREST_PUSH_BUF(val, 6, number_of_filled_bits, buffer_data);
  *in += 3, *out += 9;
}

inline void VSEREST_UNPACK10_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;
  (*out)[9] = (val << 4) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[9] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 4, *out += 10;
}

inline void VSEREST_UNPACK10_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;
  (*out)[9] = (val << 4) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[9] |= val >> 28;
  (*out)[10] = (val >> 18) & 0x03ff;

  VSEREST_PUSH_BUF(val, 18, number_of_filled_bits, buffer_data);
  *in += 4, *out += 11;
}

inline void VSEREST_UNPACK10_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;
  (*out)[9] = (val << 4) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[9] |= val >> 28;
  (*out)[10] = (val >> 18) & 0x03ff;
  (*out)[11] = (val >> 8) & 0x03ff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 4, *out += 12;
}

inline void VSEREST_UNPACK10_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;
  (*out)[9] = (val << 4) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[9] |= val >> 28;
  (*out)[10] = (val >> 18) & 0x03ff;
  (*out)[11] = (val >> 8) & 0x03ff;
  (*out)[12] = (val << 2) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[12] |= val >> 30;
  (*out)[13] = (val >> 20) & 0x03ff;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 5, *out += 14;
}

inline void VSEREST_UNPACK10_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 22;
  (*out)[1] = (val >> 12) & 0x03ff;
  (*out)[2] = (val >> 2) & 0x03ff;
  (*out)[3] = (val << 8) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[3] |= val >> 24;
  (*out)[4] = (val >> 14) & 0x03ff;
  (*out)[5] = (val >> 4) & 0x03ff;
  (*out)[6] = (val << 6) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[6] |= val >> 26;
  (*out)[7] = (val >> 16) & 0x03ff;
  (*out)[8] = (val >> 6) & 0x03ff;
  (*out)[9] = (val << 4) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[9] |= val >> 28;
  (*out)[10] = (val >> 18) & 0x03ff;
  (*out)[11] = (val >> 8) & 0x03ff;
  (*out)[12] = (val << 2) & 0x03ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[12] |= val >> 30;
  (*out)[13] = (val >> 20) & 0x03ff;
  (*out)[14] = (val >> 10) & 0x03ff;
  (*out)[15] = val & 0x03ff;

  *in += 5, *out += 16;
}

inline void VSEREST_UNPACK10_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 5, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 22;
    (*out)[1] = (val >> 12) & 0x03ff;
    (*out)[2] = (val >> 2) & 0x03ff;
    (*out)[3] = (val << 8) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[3] |= val >> 24;
    (*out)[4] = (val >> 14) & 0x03ff;
    (*out)[5] = (val >> 4) & 0x03ff;
    (*out)[6] = (val << 6) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[6] |= val >> 26;
    (*out)[7] = (val >> 16) & 0x03ff;
    (*out)[8] = (val >> 6) & 0x03ff;
    (*out)[9] = (val << 4) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[9] |= val >> 28;
    (*out)[10] = (val >> 18) & 0x03ff;
    (*out)[11] = (val >> 8) & 0x03ff;
    (*out)[12] = (val << 2) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[12] |= val >> 30;
    (*out)[13] = (val >> 20) & 0x03ff;
    (*out)[14] = (val >> 10) & 0x03ff;
    (*out)[15] = val & 0x03ff;
  }
}

inline void VSEREST_UNPACK10_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 5, *out += 16) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 22;
    (*out)[1] = (val >> 12) & 0x03ff;
    (*out)[2] = (val >> 2) & 0x03ff;
    (*out)[3] = (val << 8) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[3] |= val >> 24;
    (*out)[4] = (val >> 14) & 0x03ff;
    (*out)[5] = (val >> 4) & 0x03ff;
    (*out)[6] = (val << 6) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[6] |= val >> 26;
    (*out)[7] = (val >> 16) & 0x03ff;
    (*out)[8] = (val >> 6) & 0x03ff;
    (*out)[9] = (val << 4) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[9] |= val >> 28;
    (*out)[10] = (val >> 18) & 0x03ff;
    (*out)[11] = (val >> 8) & 0x03ff;
    (*out)[12] = (val << 2) & 0x03ff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[12] |= val >> 30;
    (*out)[13] = (val >> 20) & 0x03ff;
    (*out)[14] = (val >> 10) & 0x03ff;
    (*out)[15] = val & 0x03ff;
  }
}

/* UNPACKER: 11 */
inline void VSEREST_UNPACK11_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;

  VSEREST_PUSH_BUF(val, 21, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK11_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;

  VSEREST_PUSH_BUF(val, 10, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK11_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;

  VSEREST_PUSH_BUF(val, 31, number_of_filled_bits, buffer_data);
  *in += 2, *out += 3;
}

inline void VSEREST_UNPACK11_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 2, *out += 4;
}

inline void VSEREST_UNPACK11_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;

  VSEREST_PUSH_BUF(val, 9, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK11_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;

  VSEREST_PUSH_BUF(val, 30, number_of_filled_bits, buffer_data);
  *in += 3, *out += 6;
}

inline void VSEREST_UNPACK11_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;

  VSEREST_PUSH_BUF(val, 19, number_of_filled_bits, buffer_data);
  *in += 3, *out += 7;
}

inline void VSEREST_UNPACK11_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 3, *out += 8;
}

inline void VSEREST_UNPACK11_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;

  VSEREST_PUSH_BUF(val, 29, number_of_filled_bits, buffer_data);
  *in += 4, *out += 9;
}

inline void VSEREST_UNPACK11_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;

  VSEREST_PUSH_BUF(val, 18, number_of_filled_bits, buffer_data);
  *in += 4, *out += 10;
}

inline void VSEREST_UNPACK11_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;
  (*out)[10] = (val >> 7) & 0x07ff;

  VSEREST_PUSH_BUF(val, 7, number_of_filled_bits, buffer_data);
  *in += 4, *out += 11;
}

inline void VSEREST_UNPACK11_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;
  (*out)[10] = (val >> 7) & 0x07ff;
  (*out)[11] = (val << 4) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[11] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 5, *out += 12;
}

inline void VSEREST_UNPACK11_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;
  (*out)[10] = (val >> 7) & 0x07ff;
  (*out)[11] = (val << 4) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[11] |= val >> 28;
  (*out)[12] = (val >> 17) & 0x07ff;
  (*out)[13] = (val >> 6) & 0x07ff;

  VSEREST_PUSH_BUF(val, 6, number_of_filled_bits, buffer_data);
  *in += 5, *out += 14;
}

inline void VSEREST_UNPACK11_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;
  (*out)[10] = (val >> 7) & 0x07ff;
  (*out)[11] = (val << 4) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[11] |= val >> 28;
  (*out)[12] = (val >> 17) & 0x07ff;
  (*out)[13] = (val >> 6) & 0x07ff;
  (*out)[14] = (val << 5) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[14] |= val >> 27;
  (*out)[15] = (val >> 16) & 0x07ff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 6, *out += 16;
}

inline void VSEREST_UNPACK11_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 21;
  (*out)[1] = (val >> 10) & 0x07ff;
  (*out)[2] = (val << 1) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 31;
  (*out)[3] = (val >> 20) & 0x07ff;
  (*out)[4] = (val >> 9) & 0x07ff;
  (*out)[5] = (val << 2) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 30;
  (*out)[6] = (val >> 19) & 0x07ff;
  (*out)[7] = (val >> 8) & 0x07ff;
  (*out)[8] = (val << 3) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] |= val >> 29;
  (*out)[9] = (val >> 18) & 0x07ff;
  (*out)[10] = (val >> 7) & 0x07ff;
  (*out)[11] = (val << 4) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[11] |= val >> 28;
  (*out)[12] = (val >> 17) & 0x07ff;
  (*out)[13] = (val >> 6) & 0x07ff;
  (*out)[14] = (val << 5) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[14] |= val >> 27;
  (*out)[15] = (val >> 16) & 0x07ff;
  (*out)[16] = (val >> 5) & 0x07ff;
  (*out)[17] = (val << 6) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[17] |= val >> 26;
  (*out)[18] = (val >> 15) & 0x07ff;
  (*out)[19] = (val >> 4) & 0x07ff;
  (*out)[20] = (val << 7) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 7);
  (*out)[20] |= val >> 25;
  (*out)[21] = (val >> 14) & 0x07ff;
  (*out)[22] = (val >> 3) & 0x07ff;
  (*out)[23] = (val << 8) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 8);
  (*out)[23] |= val >> 24;
  (*out)[24] = (val >> 13) & 0x07ff;
  (*out)[25] = (val >> 2) & 0x07ff;
  (*out)[26] = (val << 9) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 9);
  (*out)[26] |= val >> 23;
  (*out)[27] = (val >> 12) & 0x07ff;
  (*out)[28] = (val >> 1) & 0x07ff;
  (*out)[29] = (val << 10) & 0x07ff;

  val = BYTEORDER_FREE_LOAD32(*in + 10);
  (*out)[29] |= val >> 22;
  (*out)[30] = (val >> 11) & 0x07ff;
  (*out)[31] = val & 0x07ff;

  *in += 11, *out += 32;
}

inline void VSEREST_UNPACK11_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 11, *out += 32) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 21;
    (*out)[1] = (val >> 10) & 0x07ff;
    (*out)[2] = (val << 1) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[2] |= val >> 31;
    (*out)[3] = (val >> 20) & 0x07ff;
    (*out)[4] = (val >> 9) & 0x07ff;
    (*out)[5] = (val << 2) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[5] |= val >> 30;
    (*out)[6] = (val >> 19) & 0x07ff;
    (*out)[7] = (val >> 8) & 0x07ff;
    (*out)[8] = (val << 3) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[8] |= val >> 29;
    (*out)[9] = (val >> 18) & 0x07ff;
    (*out)[10] = (val >> 7) & 0x07ff;
    (*out)[11] = (val << 4) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[11] |= val >> 28;
    (*out)[12] = (val >> 17) & 0x07ff;
    (*out)[13] = (val >> 6) & 0x07ff;
    (*out)[14] = (val << 5) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 5);
    (*out)[14] |= val >> 27;
    (*out)[15] = (val >> 16) & 0x07ff;
    (*out)[16] = (val >> 5) & 0x07ff;
    (*out)[17] = (val << 6) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 6);
    (*out)[17] |= val >> 26;
    (*out)[18] = (val >> 15) & 0x07ff;
    (*out)[19] = (val >> 4) & 0x07ff;
    (*out)[20] = (val << 7) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 7);
    (*out)[20] |= val >> 25;
    (*out)[21] = (val >> 14) & 0x07ff;
    (*out)[22] = (val >> 3) & 0x07ff;
    (*out)[23] = (val << 8) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 8);
    (*out)[23] |= val >> 24;
    (*out)[24] = (val >> 13) & 0x07ff;
    (*out)[25] = (val >> 2) & 0x07ff;
    (*out)[26] = (val << 9) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 9);
    (*out)[26] |= val >> 23;
    (*out)[27] = (val >> 12) & 0x07ff;
    (*out)[28] = (val >> 1) & 0x07ff;
    (*out)[29] = (val << 10) & 0x07ff;

    val = BYTEORDER_FREE_LOAD32(*in + 10);
    (*out)[29] |= val >> 22;
    (*out)[30] = (val >> 11) & 0x07ff;
    (*out)[31] = val & 0x07ff;
  }
}

/* UNPACKER: 12 */
inline void VSEREST_UNPACK12_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK12_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK12_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 2, *out += 3;
}

inline void VSEREST_UNPACK12_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 4;
}

inline void VSEREST_UNPACK12_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 2, *out += 5;
}

inline void VSEREST_UNPACK12_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 3, *out += 6;
}

inline void VSEREST_UNPACK12_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 3, *out += 7;
}

inline void VSEREST_UNPACK12_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  *in += 3, *out += 8;
}

inline void VSEREST_UNPACK12_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] = val >> 20;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 4, *out += 9;
}

inline void VSEREST_UNPACK12_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] = val >> 20;
  (*out)[9] = (val >> 8) & 0x0fff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 4, *out += 10;
}

inline void VSEREST_UNPACK12_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] = val >> 20;
  (*out)[9] = (val >> 8) & 0x0fff;
  (*out)[10] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[10] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 5, *out += 11;
}

inline void VSEREST_UNPACK12_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] = val >> 20;
  (*out)[9] = (val >> 8) & 0x0fff;
  (*out)[10] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[10] |= val >> 28;
  (*out)[11] = (val >> 16) & 0x0fff;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 5, *out += 12;
}

inline void VSEREST_UNPACK12_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 20;
  (*out)[1] = (val >> 8) & 0x0fff;
  (*out)[2] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] |= val >> 28;
  (*out)[3] = (val >> 16) & 0x0fff;
  (*out)[4] = (val >> 4) & 0x0fff;
  (*out)[5] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[5] |= val >> 24;
  (*out)[6] = (val >> 12) & 0x0fff;
  (*out)[7] = val & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[8] = val >> 20;
  (*out)[9] = (val >> 8) & 0x0fff;
  (*out)[10] = (val << 4) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[10] |= val >> 28;
  (*out)[11] = (val >> 16) & 0x0fff;
  (*out)[12] = (val >> 4) & 0x0fff;
  (*out)[13] = (val << 8) & 0x0fff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[13] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 6, *out += 14;
}

inline void VSEREST_UNPACK12_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 3, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 20;
    (*out)[1] = (val >> 8) & 0x0fff;
    (*out)[2] = (val << 4) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[2] |= val >> 28;
    (*out)[3] = (val >> 16) & 0x0fff;
    (*out)[4] = (val >> 4) & 0x0fff;
    (*out)[5] = (val << 8) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[5] |= val >> 24;
    (*out)[6] = (val >> 12) & 0x0fff;
    (*out)[7] = val & 0x0fff;
  }
}

inline void VSEREST_UNPACK12_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 3, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 20;
    (*out)[1] = (val >> 8) & 0x0fff;
    (*out)[2] = (val << 4) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[2] |= val >> 28;
    (*out)[3] = (val >> 16) & 0x0fff;
    (*out)[4] = (val >> 4) & 0x0fff;
    (*out)[5] = (val << 8) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[5] |= val >> 24;
    (*out)[6] = (val >> 12) & 0x0fff;
    (*out)[7] = val & 0x0fff;
  }
}

inline void VSEREST_UNPACK12_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8;
          i++, *in += 3, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 20;
    (*out)[1] = (val >> 8) & 0x0fff;
    (*out)[2] = (val << 4) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[2] |= val >> 28;
    (*out)[3] = (val >> 16) & 0x0fff;
    (*out)[4] = (val >> 4) & 0x0fff;
    (*out)[5] = (val << 8) & 0x0fff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[5] |= val >> 24;
    (*out)[6] = (val >> 12) & 0x0fff;
    (*out)[7] = val & 0x0fff;
  }
}

/* UNPACKER: 16 */
inline void VSEREST_UNPACK16_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK16_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;
  (*out)[1] = val & 0xffff;

  *in += 1, *out += 2;
}

inline void VSEREST_UNPACK16_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;
  (*out)[1] = val & 0xffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[2] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 2, *out += 3;
}

inline void VSEREST_UNPACK16_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK16_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 3;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 3;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK16_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK16_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 5;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 5;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK16_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 6;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 7;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 16;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

inline void VSEREST_UNPACK16_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 32;
          i++, *in += 1, *out += 2) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 16;
    (*out)[1] = val & 0xffff;
  }
}

/* UNPACKER: 20 */
inline void VSEREST_UNPACK20_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK20_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 2, *out += 2;
}

inline void VSEREST_UNPACK20_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 2, *out += 3;
}

inline void VSEREST_UNPACK20_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 3, *out += 4;
}

inline void VSEREST_UNPACK20_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;

  VSEREST_PUSH_BUF(val, 28, number_of_filled_bits, buffer_data);
  *in += 4, *out += 5;
}

inline void VSEREST_UNPACK20_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 4, *out += 6;
}

inline void VSEREST_UNPACK20_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;

  VSEREST_PUSH_BUF(val, 20, number_of_filled_bits, buffer_data);
  *in += 5, *out += 7;
}

inline void VSEREST_UNPACK20_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  *in += 5, *out += 8;
}

inline void VSEREST_UNPACK20_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[8] = val >> 12;

  VSEREST_PUSH_BUF(val, 12, number_of_filled_bits, buffer_data);
  *in += 6, *out += 9;
}

inline void VSEREST_UNPACK20_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[8] = val >> 12;
  (*out)[9] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[9] |= val >> 24;

  VSEREST_PUSH_BUF(val, 24, number_of_filled_bits, buffer_data);
  *in += 7, *out += 10;
}

inline void VSEREST_UNPACK20_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[8] = val >> 12;
  (*out)[9] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[9] |= val >> 24;
  (*out)[10] = (val >> 4) & 0xfffff;

  VSEREST_PUSH_BUF(val, 4, number_of_filled_bits, buffer_data);
  *in += 7, *out += 11;
}

inline void VSEREST_UNPACK20_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[8] = val >> 12;
  (*out)[9] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[9] |= val >> 24;
  (*out)[10] = (val >> 4) & 0xfffff;
  (*out)[11] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 7);
  (*out)[11] |= val >> 16;

  VSEREST_PUSH_BUF(val, 16, number_of_filled_bits, buffer_data);
  *in += 8, *out += 12;
}

inline void VSEREST_UNPACK20_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {

  uint32_t val = BYTEORDER_FREE_LOAD32(*in);
  (*out)[0] = val >> 12;
  (*out)[1] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 1);
  (*out)[1] |= val >> 24;
  (*out)[2] = (val >> 4) & 0xfffff;
  (*out)[3] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 2);
  (*out)[3] |= val >> 16;
  (*out)[4] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 3);
  (*out)[4] |= val >> 28;
  (*out)[5] = (val >> 8) & 0xfffff;
  (*out)[6] = (val << 12) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 4);
  (*out)[6] |= val >> 20;
  (*out)[7] = val & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 5);
  (*out)[8] = val >> 12;
  (*out)[9] = (val << 8) & 0x0fffff;

  val = BYTEORDER_FREE_LOAD32(*in + 6);
  (*out)[9] |= val >> 24;
  (*out)[10] = (val >> 4) & 0xfffff;
  (*out)[11] = (val << 16) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 7);
  (*out)[11] |= val >> 16;
  (*out)[12] = (val << 4) & 0xfffff;

  val = BYTEORDER_FREE_LOAD32(*in + 8);
  (*out)[12] |= val >> 28;
  (*out)[13] = (val >> 8) & 0xfffff;

  VSEREST_PUSH_BUF(val, 8, number_of_filled_bits, buffer_data);
  *in += 9, *out += 14;
}

inline void VSEREST_UNPACK20_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2; i++,
          *in += 5, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 12;
    (*out)[1] = (val << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[1] |= val >> 24;
    (*out)[2] = (val >> 4) & 0xfffff;
    (*out)[3] = (val << 16) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[3] |= val >> 16;
    (*out)[4] = (val << 4) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[4] |= val >> 28;
    (*out)[5] = (val >> 8) & 0xfffff;
    (*out)[6] = (val << 12) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[6] |= val >> 20;
    (*out)[7] = val & 0xfffff;
  }
}

inline void VSEREST_UNPACK20_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4; i++,
          *in += 5, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 12;
    (*out)[1] = (val << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[1] |= val >> 24;
    (*out)[2] = (val >> 4) & 0xfffff;
    (*out)[3] = (val << 16) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[3] |= val >> 16;
    (*out)[4] = (val << 4) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[4] |= val >> 28;
    (*out)[5] = (val >> 8) & 0xfffff;
    (*out)[6] = (val << 12) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[6] |= val >> 20;
    (*out)[7] = val & 0xfffff;
  }
}

inline void VSEREST_UNPACK20_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8; i++,
          *in += 5, *out += 8) {
    uint32_t val = BYTEORDER_FREE_LOAD32(*in);
    (*out)[0] = val >> 12;
    (*out)[1] = (val << 8) & 0x0fffff;

    val = BYTEORDER_FREE_LOAD32(*in + 1);
    (*out)[1] |= val >> 24;
    (*out)[2] = (val >> 4) & 0xfffff;
    (*out)[3] = (val << 16) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 2);
    (*out)[3] |= val >> 16;
    (*out)[4] = (val << 4) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 3);
    (*out)[4] |= val >> 28;
    (*out)[5] = (val >> 8) & 0xfffff;
    (*out)[6] = (val << 12) & 0xfffff;

    val = BYTEORDER_FREE_LOAD32(*in + 4);
    (*out)[6] |= val >> 20;
    (*out)[7] = val & 0xfffff;
  }
}

/* UNPACKER: 32 */
inline void VSEREST_UNPACK32_1(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
  *in += 1, *out += 1;
}

inline void VSEREST_UNPACK32_2(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 2;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_3(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 3;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_4(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 4;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_5(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 5;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_6(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 6;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_7(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 7;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_8(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 8;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_9(uint32_t ** restrict out,
                               uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 9;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);

}

inline void VSEREST_UNPACK32_10(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 10;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_11(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 11;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_12(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 12;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_14(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 14;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_16(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 16;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_32(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 32;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

inline void VSEREST_UNPACK32_64(uint32_t ** restrict out,
                                uint32_t ** restrict in) {
  for (uint32_t i = 0; i < 64;
          i++, *in += 1, *out += 1)
    (*out)[0] = BYTEORDER_FREE_LOAD32(*in);
}

const uint32_t VSEREST_LENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 14, 16, 32, 64
};

const uint32_t VSEREST_REMAPLOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 16, 16, 16, 20, 20, 20, 20,
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t VSEREST_CODELOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 13, 13, 13, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

} /* namespace: */

VSEncodingRest::VSEncodingRest()
    : EncodingBase(E_VSEREST),
      vdp_(new VSEncodingDP(VSEREST_LENS,
                            NULL,
                            ARRAYSIZE(VSEREST_LENS), false)) {}

VSEncodingRest::~VSEncodingRest() throw() {}

namespace {

/* A structure to harness padding areas */
struct rbuf_t {
  int n;
  int head;
  int tail;

  struct {
    int nleft;
    int nshift;
    uint32_t  *pos;
  } e[32];

  explicit rbuf_t() : n(0), head(0), tail(0) {}
};

#define CAN_FILL_PADDING()    (rbuf->n >= 32)
#define CAN_USE_CURBUF(bit)   (bit < rbuf->e[rbuf->head].nleft)

inline void USE_CURBUF(uint32_t val,
                       int *bit,
                       struct rbuf_t *rbuf) {
  *(rbuf->e[rbuf->head].pos) |=
      (val << rbuf->e[rbuf->head].nshift) <<
      (rbuf->e[rbuf->head].nleft - *bit);

  rbuf->e[rbuf->head].nleft -= *bit;
  rbuf->n -= *bit;
  *bit = 0;
}

inline void USE_CURBUF_ROTATE(uint32_t *val,
                              int *bit,
                              struct rbuf_t *rbuf) {
  *(rbuf->e[rbuf->head].pos) |=
      (*val >> (*bit - rbuf->e[rbuf->head].nleft))
      << rbuf->e[rbuf->head].nshift;

  rbuf->n -= rbuf->e[rbuf->head].nleft;

  *val &= (1ULL << (*bit - rbuf->e[rbuf->head].nleft)) - 1;
  *bit -= rbuf->e[rbuf->head].nleft;

  /* Move head to next */
  rbuf->head = (rbuf->head + 1) % 32;
}

inline void RECYCLE_CURBUF(int *nleft,
                           struct rbuf_t *rbuf) {
  rbuf->e[rbuf->head].nleft -= *nleft;

  rbuf->e[rbuf->tail].pos =
      rbuf->e[rbuf->head].pos;
  rbuf->e[rbuf->tail].nleft = *nleft;
  rbuf->e[rbuf->tail].nshift =
      rbuf->e[rbuf->head].nleft +
  rbuf->e[rbuf->head].nshift;

  /* Move tail to next */
  rbuf->tail = (rbuf->tail + 1) % 32;
  *nleft = 0;
}

inline void RECYCLE_CURBUF_ROTATE(int *nleft,
                                  struct rbuf_t *rbuf) {
  rbuf->e[rbuf->tail].pos =
      rbuf->e[rbuf->head].pos;
  rbuf->e[rbuf->tail].nleft =
      rbuf->e[rbuf->head].nleft;
  rbuf->e[rbuf->tail].nshift =
      rbuf->e[rbuf->head].nshift;
  rbuf->tail = (rbuf->tail + 1) % 32;

  /* Move head to next */
  *nleft -= rbuf->e[rbuf->head].nleft;
  rbuf->head = (rbuf->head + 1) % 32;
}

void VSEREST_PUSH_RBUF(uint32_t nleft,
                       struct rbuf_t *rbuf,
                       BitsWriter *wt) {
  ASSERT(nleft <= 32);
  ASSERT(wt != NULL);

  if (nleft != 32) {
    rbuf->n += nleft;
    rbuf->e[rbuf->tail].pos = wt->pos();
    rbuf->e[rbuf->tail].nleft = nleft;
    rbuf->e[rbuf->tail].nshift = 0;
    rbuf->tail = (rbuf->tail + 1) % 32;
  }
}

void VSEREST_FILL_PADDING(const uint32_t *base,
                          uint32_t *len,
                          uint32_t maxB,
                          struct rbuf_t *rbuf,
                          BitsWriter *wt) {
  ASSERT(base != NULL);
  ASSERT(len != NULL && *len != 0);
  ASSERT(maxB <= 32);
  ASSERT(wt != NULL);

  if (maxB == 0)
    return;

  uint32_t length = *len;
  *len = 0;

  if (CAN_FILL_PADDING()) {
    uint32_t pos = 0;

    for (pos = 1; pos <= (32 + maxB - 1) / maxB; pos++) {
      int bit = (maxB * pos <= 32)? maxB : 32 % maxB;

      if (pos <= length) {
        uint32_t val = base[pos - 1] >> (maxB - bit);

        while (bit > 0) {
          if (CAN_USE_CURBUF(bit))
            USE_CURBUF(val, &bit, rbuf);
          else
            USE_CURBUF_ROTATE(&val, &bit, rbuf);
        }
      } else {
        int nleft = 32 - maxB * (pos - 1);
        ASSERT(nleft > 0 && nleft < 32);

        while (nleft > 0) {
          if (CAN_USE_CURBUF(nleft))
            RECYCLE_CURBUF(&nleft, rbuf);
          else
            RECYCLE_CURBUF_ROTATE(&nleft, rbuf);
        }

        goto LOOP_END;
      }
    }

    if (32 % maxB > 0) {
      wt->write_bits(base[(pos - 1) - 1] & ((1ULL << (maxB - 32 % maxB)) - 1),
                     maxB - 32 % maxB);

      if (pos - 1 == length)
        VSEREST_PUSH_RBUF(32 - (length * maxB) % 32, rbuf, wt);
    }
LOOP_END:
    *len = pos - 1;
  }
}

} /* namespace: */

void VSEncodingRest::encodeArray(const uint32_t *in,
                                 uint64_t len,
                                 uint32_t *out,
                                 uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (*nvalue < 5)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  /* Compute optimal partition */
  std::vector<uint32_t> logs;
  std::vector<uint32_t> parts;

  for (uint64_t i = 0; i < len; i++)
    logs.push_back(
        VSEREST_REMAPLOGS[32 - MSB32(in[i])]);

  ASSERT(logs.size() == len);
  ASSERT(parts.size() == 0);

  vdp_->computePartition(logs, &parts,
                         VSEREST_LOGLEN + VSEREST_LOGLOG);
  ASSERT(parts.size() > 1);

  uint64_t num = parts.size() - 1;
  BYTEORDER_FREE_STORE64(out, num);
  *nvalue -= 2;
  out += 2;

  uint64_t offset = DIV_ROUNDUP(num, 4);

  /* Ready to write data */
  BitsWriter  wt1(out, offset);
  BitsWriter  wt2(out + offset, *nvalue - offset);

  struct rbuf_t ring_buffers;

  for (uint64_t i = 0; i < num; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    /* Compute the code for the block length */
    uint32_t idx = 0;

    for (; idx < ARRAYSIZE(VSEREST_LENS); idx++){
      if (parts[i + 1] - parts[i] == VSEREST_LENS[idx])
        break;
    }

    /* Fill the buffer */
    uint32_t offset = parts[i + 1] - parts[i];
    VSEREST_FILL_PADDING(&in[parts[i]],
                         &offset, maxB,
                         &ring_buffers,
                         &wt2);

    if (parts[i] + offset < parts[i + 1]) {
      /* Write left integers */
      for (uint64_t j = parts[i] + offset;
              j < parts[i + 1]; j++)
        wt2.write_bits(in[j], maxB);

      /* Remember the position of padding areas */
      VSEREST_PUSH_RBUF(
          32 - ((parts[i + 1] - parts[i]) * maxB) % 32,
          &ring_buffers,
          &wt2);
    }

    /* Align to 32-bit */
    wt2.flush_bits();

    /* Write the value of B and K */
    wt1.write_bits(VSEREST_CODELOGS[maxB],
                   VSEREST_LOGLOG);
    wt1.write_bits(idx, VSEREST_LOGLEN);
  }

  wt1.flush_bits();
  *nvalue = 2 + wt1.size() + wt2.size();
}

namespace {

typedef void (*vserest_unpack_t)(uint32_t **out, uint32_t **in);

vserest_unpack_t VSEREST_UNPACK[VSEREST_LEN] {
  /* UNPACKER: 0 */
  VSEREST_UNPACK0_1, VSEREST_UNPACK0_2,
  VSEREST_UNPACK0_3, VSEREST_UNPACK0_4,
  VSEREST_UNPACK0_5, VSEREST_UNPACK0_6,
  VSEREST_UNPACK0_7, VSEREST_UNPACK0_8,
  VSEREST_UNPACK0_9, VSEREST_UNPACK0_10,
  VSEREST_UNPACK0_11, VSEREST_UNPACK0_12,
  VSEREST_UNPACK0_14, VSEREST_UNPACK0_16,
  VSEREST_UNPACK0_32, VSEREST_UNPACK0_64,

  /* UNPACKER: 1 */
  VSEREST_UNPACK1_1, VSEREST_UNPACK1_2,
  VSEREST_UNPACK1_3, VSEREST_UNPACK1_4,
  VSEREST_UNPACK1_5, VSEREST_UNPACK1_6,
  VSEREST_UNPACK1_7, VSEREST_UNPACK1_8,
  VSEREST_UNPACK1_9, VSEREST_UNPACK1_10,
  VSEREST_UNPACK1_11, VSEREST_UNPACK1_12,
  VSEREST_UNPACK1_14, VSEREST_UNPACK1_16,
  VSEREST_UNPACK1_32, VSEREST_UNPACK1_64,

  /* UNPACKER: 2 */
  VSEREST_UNPACK2_1, VSEREST_UNPACK2_2,
  VSEREST_UNPACK2_3, VSEREST_UNPACK2_4,
  VSEREST_UNPACK2_5, VSEREST_UNPACK2_6,
  VSEREST_UNPACK2_7, VSEREST_UNPACK2_8,
  VSEREST_UNPACK2_9, VSEREST_UNPACK2_10,
  VSEREST_UNPACK2_11, VSEREST_UNPACK2_12,
  VSEREST_UNPACK2_14, VSEREST_UNPACK2_16,
  VSEREST_UNPACK2_32, VSEREST_UNPACK2_64,

  /* UNPACKER: 3 */
  VSEREST_UNPACK3_1, VSEREST_UNPACK3_2,
  VSEREST_UNPACK3_3, VSEREST_UNPACK3_4,
  VSEREST_UNPACK3_5, VSEREST_UNPACK3_6,
  VSEREST_UNPACK3_7, VSEREST_UNPACK3_8,
  VSEREST_UNPACK3_9, VSEREST_UNPACK3_10,
  VSEREST_UNPACK3_11, VSEREST_UNPACK3_12,
  VSEREST_UNPACK3_14, VSEREST_UNPACK3_16,
  VSEREST_UNPACK3_32, VSEREST_UNPACK3_64,

  /* UNPACKER: 4 */
  VSEREST_UNPACK4_1, VSEREST_UNPACK4_2,
  VSEREST_UNPACK4_3, VSEREST_UNPACK4_4,
  VSEREST_UNPACK4_5, VSEREST_UNPACK4_6,
  VSEREST_UNPACK4_7, VSEREST_UNPACK4_8,
  VSEREST_UNPACK4_9, VSEREST_UNPACK4_10,
  VSEREST_UNPACK4_11, VSEREST_UNPACK4_12,
  VSEREST_UNPACK4_14, VSEREST_UNPACK4_16,
  VSEREST_UNPACK4_32, VSEREST_UNPACK4_64,

  /* UNPACKER: 5 */
  VSEREST_UNPACK5_1, VSEREST_UNPACK5_2,
  VSEREST_UNPACK5_3, VSEREST_UNPACK5_4,
  VSEREST_UNPACK5_5, VSEREST_UNPACK5_6,
  VSEREST_UNPACK5_7, VSEREST_UNPACK5_8,
  VSEREST_UNPACK5_9, VSEREST_UNPACK5_10,
  VSEREST_UNPACK5_11, VSEREST_UNPACK5_12,
  VSEREST_UNPACK5_14, VSEREST_UNPACK5_16,
  VSEREST_UNPACK5_32, VSEREST_UNPACK5_64,

  /* UNPACKER: 6 */
  VSEREST_UNPACK6_1, VSEREST_UNPACK6_2,
  VSEREST_UNPACK6_3, VSEREST_UNPACK6_4,
  VSEREST_UNPACK6_5, VSEREST_UNPACK6_6,
  VSEREST_UNPACK6_7, VSEREST_UNPACK6_8,
  VSEREST_UNPACK6_9, VSEREST_UNPACK6_10,
  VSEREST_UNPACK6_11, VSEREST_UNPACK6_12,
  VSEREST_UNPACK6_14, VSEREST_UNPACK6_16,
  VSEREST_UNPACK6_32, VSEREST_UNPACK6_64,

  /* UNPACKER: 7 */
  VSEREST_UNPACK7_1, VSEREST_UNPACK7_2,
  VSEREST_UNPACK7_3, VSEREST_UNPACK7_4,
  VSEREST_UNPACK7_5, VSEREST_UNPACK7_6,
  VSEREST_UNPACK7_7, VSEREST_UNPACK7_8,
  VSEREST_UNPACK7_9, VSEREST_UNPACK7_10,
  VSEREST_UNPACK7_11, VSEREST_UNPACK7_12,
  VSEREST_UNPACK7_14, VSEREST_UNPACK7_16,
  VSEREST_UNPACK7_32, VSEREST_UNPACK7_64,

  /* UNPACKER: 8 */
  VSEREST_UNPACK8_1, VSEREST_UNPACK8_2,
  VSEREST_UNPACK8_3, VSEREST_UNPACK8_4,
  VSEREST_UNPACK8_5, VSEREST_UNPACK8_6,
  VSEREST_UNPACK8_7, VSEREST_UNPACK8_8,
  VSEREST_UNPACK8_9, VSEREST_UNPACK8_10,
  VSEREST_UNPACK8_11, VSEREST_UNPACK8_12,
  VSEREST_UNPACK8_14, VSEREST_UNPACK8_16,
  VSEREST_UNPACK8_32, VSEREST_UNPACK8_64,

  /* UNPACKER: 9 */
  VSEREST_UNPACK9_1, VSEREST_UNPACK9_2,
  VSEREST_UNPACK9_3, VSEREST_UNPACK9_4,
  VSEREST_UNPACK9_5, VSEREST_UNPACK9_6,
  VSEREST_UNPACK9_7, VSEREST_UNPACK9_8,
  VSEREST_UNPACK9_9, VSEREST_UNPACK9_10,
  VSEREST_UNPACK9_11, VSEREST_UNPACK9_12,
  VSEREST_UNPACK9_14, VSEREST_UNPACK9_16,
  VSEREST_UNPACK9_32, VSEREST_UNPACK9_64,

  /* UNPACKER: 10 */
  VSEREST_UNPACK10_1, VSEREST_UNPACK10_2,
  VSEREST_UNPACK10_3, VSEREST_UNPACK10_4,
  VSEREST_UNPACK10_5, VSEREST_UNPACK10_6,
  VSEREST_UNPACK10_7, VSEREST_UNPACK10_8,
  VSEREST_UNPACK10_9, VSEREST_UNPACK10_10,
  VSEREST_UNPACK10_11, VSEREST_UNPACK10_12,
  VSEREST_UNPACK10_14, VSEREST_UNPACK10_16,
  VSEREST_UNPACK10_32, VSEREST_UNPACK10_64,

  /* UNPACKER: 11 */
  VSEREST_UNPACK11_1, VSEREST_UNPACK11_2,
  VSEREST_UNPACK11_3, VSEREST_UNPACK11_4,
  VSEREST_UNPACK11_5, VSEREST_UNPACK11_6,
  VSEREST_UNPACK11_7, VSEREST_UNPACK11_8,
  VSEREST_UNPACK11_9, VSEREST_UNPACK11_10,
  VSEREST_UNPACK11_11, VSEREST_UNPACK11_12,
  VSEREST_UNPACK11_14, VSEREST_UNPACK11_16,
  VSEREST_UNPACK11_32, VSEREST_UNPACK11_64,

  /* UNPACKER: 12 */
  VSEREST_UNPACK12_1, VSEREST_UNPACK12_2,
  VSEREST_UNPACK12_3, VSEREST_UNPACK12_4,
  VSEREST_UNPACK12_5, VSEREST_UNPACK12_6,
  VSEREST_UNPACK12_7, VSEREST_UNPACK12_8,
  VSEREST_UNPACK12_9, VSEREST_UNPACK12_10,
  VSEREST_UNPACK12_11, VSEREST_UNPACK12_12,
  VSEREST_UNPACK12_14, VSEREST_UNPACK12_16,
  VSEREST_UNPACK12_32, VSEREST_UNPACK12_64,

  /* UNPACKER: 16 */
  VSEREST_UNPACK16_1, VSEREST_UNPACK16_2,
  VSEREST_UNPACK16_3, VSEREST_UNPACK16_4,
  VSEREST_UNPACK16_5, VSEREST_UNPACK16_6,
  VSEREST_UNPACK16_7, VSEREST_UNPACK16_8,
  VSEREST_UNPACK16_9, VSEREST_UNPACK16_10,
  VSEREST_UNPACK16_11, VSEREST_UNPACK16_12,
  VSEREST_UNPACK16_14, VSEREST_UNPACK16_16,
  VSEREST_UNPACK16_32, VSEREST_UNPACK16_64,

  /* UNPACKER: 20 */
  VSEREST_UNPACK20_1, VSEREST_UNPACK20_2,
  VSEREST_UNPACK20_3, VSEREST_UNPACK20_4,
  VSEREST_UNPACK20_5, VSEREST_UNPACK20_6,
  VSEREST_UNPACK20_7, VSEREST_UNPACK20_8,
  VSEREST_UNPACK20_9, VSEREST_UNPACK20_10,
  VSEREST_UNPACK20_11, VSEREST_UNPACK20_12,
  VSEREST_UNPACK20_14, VSEREST_UNPACK20_16,
  VSEREST_UNPACK20_32, VSEREST_UNPACK20_64,

  /* UNPACKER: 32 */
  VSEREST_UNPACK32_1, VSEREST_UNPACK32_2,
  VSEREST_UNPACK32_3, VSEREST_UNPACK32_4,
  VSEREST_UNPACK32_5, VSEREST_UNPACK32_6,
  VSEREST_UNPACK32_7, VSEREST_UNPACK32_8,
  VSEREST_UNPACK32_9, VSEREST_UNPACK32_10,
  VSEREST_UNPACK32_11, VSEREST_UNPACK32_12,
  VSEREST_UNPACK32_14, VSEREST_UNPACK32_16,
  VSEREST_UNPACK32_32, VSEREST_UNPACK32_64
};

} /* namespace: */

void VSEncodingRest::decodeArray(const uint32_t *in,
                                 uint64_t len,
                                 uint32_t *out,
                                 uint64_t nvalue) const {
  VSEncodingRest::decodeArray(const_cast<uint32_t *>(in),
                              len, out, nvalue);
}

void VSEncodingRest::decodeArray(uint32_t *in,
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

  uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  uint64_t num = BYTEORDER_FREE_LOAD64(in);
  in += 2;

  uint64_t offset = DIV_ROUNDUP(num, 4);
  uint32_t *data = in + offset;

#define VSEREST_DESC(__val__, __offset__) \
    (((__val__) >> VSEREST_LOGDESC * __offset__) & (VSEREST_LEN - 1))

#define VSEREST_RESTORE_BUF(__in__, __fill__, __buf__)  \
    UNLIKELY(__fill__ >= 32)? *(--__in__) = __buf__ >> (__fill__ -= 32) : 0

  /* Initialize a buffer for paddings */
  number_of_filled_bits = 0;
  buffer_data = 0;

  while (LIKELY(out < oterm && data < iterm)) {
    uint32_t d = *in++;

    /* Unpacking integers with a first 8-bit */
    (VSEREST_UNPACK[VSEREST_DESC(d, 3)])(&out, &data);
    VSEREST_RESTORE_BUF(data,
                        number_of_filled_bits,
                        buffer_data);

    /* Unpacking integers with a second 8-bit */
    (VSEREST_UNPACK[VSEREST_DESC(d, 2)])(&out, &data);
    VSEREST_RESTORE_BUF(data,
                        number_of_filled_bits,
                        buffer_data);

    /* Unpacking integers with a third 8-bit */
    (VSEREST_UNPACK[VSEREST_DESC(d, 1)])(&out, &data);
    VSEREST_RESTORE_BUF(data,
                        number_of_filled_bits,
                        buffer_data);

    /* Unpacking integers with a last 8-bit */
    (VSEREST_UNPACK[VSEREST_DESC(d, 0)])(&out, &data);
    VSEREST_RESTORE_BUF(data,
                        number_of_filled_bits,
                        buffer_data);
  }
}

uint64_t VSEncodingRest::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len + 5;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
