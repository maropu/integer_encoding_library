/*-----------------------------------------------------------------------------
 *  VSEncodingSimple.hpp - A speed-oriented implementation of VSEncoding
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

#include <compress/policy/VSEncodingSimple.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSESIMPLE_LOGLEN = 4;
const uint32_t VSESIMPLE_LOGLOG = 4;

const uint32_t VSESIMPLE_LOGDESC =
    VSESIMPLE_LOGLEN + VSESIMPLE_LOGLOG;

const uint32_t VSESIMPLE_LENS_LEN = 1U << VSESIMPLE_LOGLEN;
const uint32_t VSESIMPLE_LOGS_LEN = 1U << VSESIMPLE_LOGLOG;
const uint32_t VSESIMPLE_LEN = 1U << VSESIMPLE_LOGDESC;

/* Unpacker: 0 */
inline void VSESIMPLE_UNPACK0_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  *out += 1;
}

inline void VSESIMPLE_UNPACK0_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  *out += 2;
}

inline void VSESIMPLE_UNPACK0_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  *out += 3;
}

inline void VSESIMPLE_UNPACK0_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  *out += 4;
}

inline void VSESIMPLE_UNPACK0_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  *out += 5;
}

inline void VSESIMPLE_UNPACK0_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  *out += 6;
}

inline void VSESIMPLE_UNPACK0_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  *out += 7;
}

inline void VSESIMPLE_UNPACK0_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  *out += 8;
}

inline void VSESIMPLE_UNPACK0_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  *out += 9;
}

inline void VSESIMPLE_UNPACK0_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  *out += 10;
}

inline void VSESIMPLE_UNPACK0_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  *out += 11;
}

inline void VSESIMPLE_UNPACK0_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  *out += 12;
}

inline void VSESIMPLE_UNPACK0_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  ZMEMCPY128(out + 12);
  *out += 14;
}

inline void VSESIMPLE_UNPACK0_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  ZMEMCPY128(out + 12);
  *out += 16;
}

inline void VSESIMPLE_UNPACK0_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  ZMEMCPY128(out + 12);
  ZMEMCPY128(out + 16);
  ZMEMCPY128(out + 20);
  ZMEMCPY128(out + 24);
  ZMEMCPY128(out + 28);
  *out += 32;
}

inline void VSESIMPLE_UNPACK0_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {
  ZMEMCPY128(out);
  ZMEMCPY128(out + 4);
  ZMEMCPY128(out + 8);
  ZMEMCPY128(out + 12);
  ZMEMCPY128(out + 16);
  ZMEMCPY128(out + 20);
  ZMEMCPY128(out + 24);
  ZMEMCPY128(out + 28);
  ZMEMCPY128(out + 32);
  ZMEMCPY128(out + 36);
  ZMEMCPY128(out + 40);
  ZMEMCPY128(out + 44);
  ZMEMCPY128(out + 48);
  ZMEMCPY128(out + 52);
  ZMEMCPY128(out + 56);
  ZMEMCPY128(out + 60);
  *out += 64;
}

/* UNPACKER: 1 */
inline void VSESIMPLE_UNPACK1_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK1_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK1_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK1_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK1_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK1_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK1_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK1_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK1_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK1_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK1_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK1_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK1_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK1_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK1_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK1_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 2 */
inline void VSESIMPLE_UNPACK2_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK2_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK2_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK2_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK2_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK2_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK2_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK2_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK2_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK2_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK2_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK2_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK2_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK2_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK2_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK2_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 3 */
inline void VSESIMPLE_UNPACK3_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK3_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK3_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK3_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK3_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK3_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK3_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK3_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK3_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK3_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK3_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK3_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK3_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK3_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK3_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK3_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 4 */
inline void VSESIMPLE_UNPACK4_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK4_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK4_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK4_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK4_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK4_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK4_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK4_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK4_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK4_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK4_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK4_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK4_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK4_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK4_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK4_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 5 */
inline void VSESIMPLE_UNPACK5_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK5_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK5_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK5_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK5_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK5_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK5_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK5_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK5_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK5_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK5_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK5_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK5_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK5_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK5_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK5_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 6 */
inline void VSESIMPLE_UNPACK6_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK6_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK6_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK6_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK6_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK6_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK6_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK6_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK6_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK6_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK6_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK6_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK6_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK6_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK6_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK6_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 7 */
inline void VSESIMPLE_UNPACK7_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK7_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK7_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK7_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK7_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK7_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK7_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK7_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK7_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK7_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK7_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK7_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK7_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK7_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK7_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK7_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 8 */
inline void VSESIMPLE_UNPACK8_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK8_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK8_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK8_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK8_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK8_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK8_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK8_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK8_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK8_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK8_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK8_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK8_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK8_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK8_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK8_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 9 */
inline void VSESIMPLE_UNPACK9_1(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK9_2(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK9_3(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK9_4(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK9_5(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK9_6(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK9_7(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK9_8(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK9_9(uint32_t ** restrict out,
                                const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK9_10(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK9_11(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK9_12(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK9_14(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK9_16(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK9_32(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK9_64(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 10 */
inline void VSESIMPLE_UNPACK10_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK10_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK10_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK10_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK10_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK10_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK10_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK10_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK10_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK10_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK10_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK10_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK10_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK10_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK10_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK10_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 11 */
inline void VSESIMPLE_UNPACK11_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK11_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK11_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK11_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK11_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK11_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK11_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK11_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK11_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK11_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK11_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK11_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK11_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK11_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK11_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK11_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 12 */
inline void VSESIMPLE_UNPACK12_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK12_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK12_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK12_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK12_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK12_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK12_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK12_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK12_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK12_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK12_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK12_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK12_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK12_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK12_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK12_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 16 */
inline void VSESIMPLE_UNPACK16_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK16_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK16_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK16_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK16_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK16_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK16_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK16_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK16_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK16_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK16_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK16_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK16_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK16_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK16_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK16_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 20 */
inline void VSESIMPLE_UNPACK20_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK20_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK20_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK20_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK20_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK20_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK20_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK20_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK20_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK20_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK20_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK20_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK20_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK20_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK20_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK20_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

/* UNPACKER: 32 */
inline void VSESIMPLE_UNPACK32_1(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 1;
}

inline void VSESIMPLE_UNPACK32_2(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 2;
}

inline void VSESIMPLE_UNPACK32_3(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 3;
}

inline void VSESIMPLE_UNPACK32_4(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 4;
}

inline void VSESIMPLE_UNPACK32_5(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 5;
}

inline void VSESIMPLE_UNPACK32_6(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 6;
}

inline void VSESIMPLE_UNPACK32_7(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 7;
}

inline void VSESIMPLE_UNPACK32_8(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 8;
}

inline void VSESIMPLE_UNPACK32_9(uint32_t ** restrict out,
                                 const uint32_t ** restrict in) {

  *out += 9;
}

inline void VSESIMPLE_UNPACK32_10(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 10;
}

inline void VSESIMPLE_UNPACK32_11(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 11;
}

inline void VSESIMPLE_UNPACK32_12(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 12;
}

inline void VSESIMPLE_UNPACK32_14(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 14;
}

inline void VSESIMPLE_UNPACK32_16(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 16;
}

inline void VSESIMPLE_UNPACK32_32(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {


  *out += 32;
}

inline void VSESIMPLE_UNPACK32_64(uint32_t ** restrict out,
                                  const uint32_t ** restrict in) {

  *out += 64;
}

const uint32_t VSESIMPLE_LENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 14, 16, 32, 64
};

const uint32_t VSESIMPLE_REMAPLOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 16, 16, 16, 20, 20, 20, 20,
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t VSESIMPLE_CODELOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 13, 13, 13, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

} /* NAMESPACE: */

VSEncodingSimple::VSEncodingSimple()
    : EncodingBase(E_VSESIMPLE),
      vdp_(new VSEncodingDP(VSESIMPLE_LENS,
                            NULL,
                            VSESIMPLE_LENS_LEN, true)) {}

VSEncodingSimple::~VSEncodingSimple() throw() {}

void VSEncodingSimple::encodeArray(const uint32_t *in,
                                   uint64_t len,
                                   uint32_t *out,
                                   uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: ou");
  if (*nvalue < 5)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  /* COMPUTE OPTIMAL PARTITION */
  std::vector<uint32_t> logs;
  std::vector<uint32_t> parts;

  for (uint64_t i = 0; i < len; i++) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in + i);
    logs.push_back(VSESIMPLE_REMAPLOGS[32 - MSB32(val)]);
  }

  ASSERT(logs.size() == len);
  ASSERT(parts.size() == 0);

  vdp_->computePartition(logs, &parts,
                         VSESIMPLE_LOGLEN + VSESIMPLE_LOGLOG);

  ASSERT(parts.size() > 1);

  uint64_t num = parts.size() - 1;
  BYTEORDER_FREE_STORE64(out, num);
  *nvalue -= 2;
  out += 2;

  uint64_t offset = DIV_ROUNDUP(num, 8);

  /* READY TO WRITE data */
  BitsWriter  wt1(out, offset);
  BitsWriter  wt2(out + offset, *nvalue - offset);

  for (uint64_t i = 0; i < num; i++) {
    /* COMPUTE MAX B in THE BLOCK */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    /* COMPUTE THE CODE for THE BLOCK LENGTH */
    uint32_t idx = 0;

    for (; idx < VSESIMPLE_LENS_LEN; idx++){
      if (parts[i + 1] - parts[i] == VSESIMPLE_LENS[idx])
        break;
    }

    /* WRITE inTEGERS */
    for (uint64_t j = parts[i]; j < parts[i + 1]; j++)
      wt2.write_bits(in[j], maxB);

    /* ALLIGN TO 32-BIT */
    wt2.flush_bits();

    /* WRITES THE VALUE OF B AND K */
    wt1.write_bits(VSESIMPLE_CODELOGS[maxB],
                   VSESIMPLE_LOGLOG);
    wt1.write_bits(idx, VSESIMPLE_LOGLEN);
  }

  wt1.flush_bits();
  *nvalue = 2 + wt1.size() + wt2.size();
}

void VSEncodingSimple::decodeArray(const uint32_t *in,
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

  static void *VSESIMPLE_UNPACK[VSESIMPLE_LEN] = {
    /* UNPACKER: 0 */
    &&VSESIMPLE_U0_1, &&VSESIMPLE_U0_2,
    &&VSESIMPLE_U0_3, &&VSESIMPLE_U0_4,
    &&VSESIMPLE_U0_5, &&VSESIMPLE_U0_6,
    &&VSESIMPLE_U0_7, &&VSESIMPLE_U0_8,
    &&VSESIMPLE_U0_9, &&VSESIMPLE_U0_10,
    &&VSESIMPLE_U0_11, &&VSESIMPLE_U0_12,
    &&VSESIMPLE_U0_14, &&VSESIMPLE_U0_16,
    &&VSESIMPLE_U0_32, &&VSESIMPLE_U0_64,

    /* UNPACKER: 1 */
    &&VSESIMPLE_U1_1, &&VSESIMPLE_U1_2,
    &&VSESIMPLE_U1_3, &&VSESIMPLE_U1_4,
    &&VSESIMPLE_U1_5, &&VSESIMPLE_U1_6,
    &&VSESIMPLE_U1_7, &&VSESIMPLE_U1_8,
    &&VSESIMPLE_U1_9, &&VSESIMPLE_U1_10,
    &&VSESIMPLE_U1_11, &&VSESIMPLE_U1_12,
    &&VSESIMPLE_U1_14, &&VSESIMPLE_U1_16,
    &&VSESIMPLE_U1_32, &&VSESIMPLE_U1_64,

    /* UNPACKER: 2 */
    &&VSESIMPLE_U2_1, &&VSESIMPLE_U2_2,
    &&VSESIMPLE_U2_3, &&VSESIMPLE_U2_4,
    &&VSESIMPLE_U2_5, &&VSESIMPLE_U2_6,
    &&VSESIMPLE_U2_7, &&VSESIMPLE_U2_8,
    &&VSESIMPLE_U2_9, &&VSESIMPLE_U2_10,
    &&VSESIMPLE_U2_11, &&VSESIMPLE_U2_12,
    &&VSESIMPLE_U2_14, &&VSESIMPLE_U2_16,
    &&VSESIMPLE_U2_32, &&VSESIMPLE_U2_64,

    /* UNPACKER: 3 */
    &&VSESIMPLE_U3_1, &&VSESIMPLE_U3_2,
    &&VSESIMPLE_U3_3, &&VSESIMPLE_U3_4,
    &&VSESIMPLE_U3_5, &&VSESIMPLE_U3_6,
    &&VSESIMPLE_U3_7, &&VSESIMPLE_U3_8,
    &&VSESIMPLE_U3_9, &&VSESIMPLE_U3_10,
    &&VSESIMPLE_U3_11, &&VSESIMPLE_U3_12,
    &&VSESIMPLE_U3_14, &&VSESIMPLE_U3_16,
    &&VSESIMPLE_U3_32, &&VSESIMPLE_U3_64,

    /* UNPACKER: 4 */
    &&VSESIMPLE_U4_1, &&VSESIMPLE_U4_2,
    &&VSESIMPLE_U4_3, &&VSESIMPLE_U4_4,
    &&VSESIMPLE_U4_5, &&VSESIMPLE_U4_6,
    &&VSESIMPLE_U4_7, &&VSESIMPLE_U4_8,
    &&VSESIMPLE_U4_9, &&VSESIMPLE_U4_10,
    &&VSESIMPLE_U4_11, &&VSESIMPLE_U4_12,
    &&VSESIMPLE_U4_14, &&VSESIMPLE_U4_16,
    &&VSESIMPLE_U4_32, &&VSESIMPLE_U4_64,

    /* UNPACKER: 5 */
    &&VSESIMPLE_U5_1, &&VSESIMPLE_U5_2,
    &&VSESIMPLE_U5_3, &&VSESIMPLE_U5_4,
    &&VSESIMPLE_U5_5, &&VSESIMPLE_U5_6,
    &&VSESIMPLE_U5_7, &&VSESIMPLE_U5_8,
    &&VSESIMPLE_U5_9, &&VSESIMPLE_U5_10,
    &&VSESIMPLE_U5_11, &&VSESIMPLE_U5_12,
    &&VSESIMPLE_U5_14, &&VSESIMPLE_U5_16,
    &&VSESIMPLE_U5_32, &&VSESIMPLE_U5_64,

    /* UNPACKER: 6 */
    &&VSESIMPLE_U6_1, &&VSESIMPLE_U6_2,
    &&VSESIMPLE_U6_3, &&VSESIMPLE_U6_4,
    &&VSESIMPLE_U6_5, &&VSESIMPLE_U6_6,
    &&VSESIMPLE_U6_7, &&VSESIMPLE_U6_8,
    &&VSESIMPLE_U6_9, &&VSESIMPLE_U6_10,
    &&VSESIMPLE_U6_11, &&VSESIMPLE_U6_12,
    &&VSESIMPLE_U6_14, &&VSESIMPLE_U6_16,
    &&VSESIMPLE_U6_32, &&VSESIMPLE_U6_64,

    /* UNPACKER: 7 */
    &&VSESIMPLE_U7_1, &&VSESIMPLE_U7_2,
    &&VSESIMPLE_U7_3, &&VSESIMPLE_U7_4,
    &&VSESIMPLE_U7_5, &&VSESIMPLE_U7_6,
    &&VSESIMPLE_U7_7, &&VSESIMPLE_U7_8,
    &&VSESIMPLE_U7_9, &&VSESIMPLE_U7_10,
    &&VSESIMPLE_U7_11, &&VSESIMPLE_U7_12,
    &&VSESIMPLE_U7_14, &&VSESIMPLE_U7_16,
    &&VSESIMPLE_U7_32, &&VSESIMPLE_U7_64,

    /* UNPACKER: 8 */
    &&VSESIMPLE_U8_1, &&VSESIMPLE_U8_2,
    &&VSESIMPLE_U8_3, &&VSESIMPLE_U8_4,
    &&VSESIMPLE_U8_5, &&VSESIMPLE_U8_6,
    &&VSESIMPLE_U8_7, &&VSESIMPLE_U8_8,
    &&VSESIMPLE_U8_9, &&VSESIMPLE_U8_10,
    &&VSESIMPLE_U8_11, &&VSESIMPLE_U8_12,
    &&VSESIMPLE_U8_14, &&VSESIMPLE_U8_16,
    &&VSESIMPLE_U8_32, &&VSESIMPLE_U8_64,

    /* UNPACKER: 9 */
    &&VSESIMPLE_U9_1, &&VSESIMPLE_U9_2,
    &&VSESIMPLE_U9_3, &&VSESIMPLE_U9_4,
    &&VSESIMPLE_U9_5, &&VSESIMPLE_U9_6,
    &&VSESIMPLE_U9_7, &&VSESIMPLE_U9_8,
    &&VSESIMPLE_U9_9, &&VSESIMPLE_U9_10,
    &&VSESIMPLE_U9_11, &&VSESIMPLE_U9_12,
    &&VSESIMPLE_U9_14, &&VSESIMPLE_U9_16,
    &&VSESIMPLE_U9_32, &&VSESIMPLE_U9_64,

    /* UNPACKER: 10 */
    &&VSESIMPLE_U10_1, &&VSESIMPLE_U10_2,
    &&VSESIMPLE_U10_3, &&VSESIMPLE_U10_4,
    &&VSESIMPLE_U10_5, &&VSESIMPLE_U10_6,
    &&VSESIMPLE_U10_7, &&VSESIMPLE_U10_8,
    &&VSESIMPLE_U10_9, &&VSESIMPLE_U10_10,
    &&VSESIMPLE_U10_11, &&VSESIMPLE_U10_12,
    &&VSESIMPLE_U10_14, &&VSESIMPLE_U10_16,
    &&VSESIMPLE_U10_32, &&VSESIMPLE_U10_64,

    /* UNPACKER: 11 */
    &&VSESIMPLE_U11_1, &&VSESIMPLE_U11_2,
    &&VSESIMPLE_U11_3, &&VSESIMPLE_U11_4,
    &&VSESIMPLE_U11_5, &&VSESIMPLE_U11_6,
    &&VSESIMPLE_U11_7, &&VSESIMPLE_U11_8,
    &&VSESIMPLE_U11_9, &&VSESIMPLE_U11_10,
    &&VSESIMPLE_U11_11, &&VSESIMPLE_U11_12,
    &&VSESIMPLE_U11_14, &&VSESIMPLE_U11_16,
    &&VSESIMPLE_U11_32, &&VSESIMPLE_U11_64,

    /* UNPACKER: 12 */
    &&VSESIMPLE_U12_1, &&VSESIMPLE_U12_2,
    &&VSESIMPLE_U12_3, &&VSESIMPLE_U12_4,
    &&VSESIMPLE_U12_5, &&VSESIMPLE_U12_6,
    &&VSESIMPLE_U12_7, &&VSESIMPLE_U12_8,
    &&VSESIMPLE_U12_9, &&VSESIMPLE_U12_10,
    &&VSESIMPLE_U12_11, &&VSESIMPLE_U12_12,
    &&VSESIMPLE_U12_14, &&VSESIMPLE_U12_16,
    &&VSESIMPLE_U12_32, &&VSESIMPLE_U12_64,

    /* UNPACKER: 16 */
    &&VSESIMPLE_U16_1, &&VSESIMPLE_U16_2,
    &&VSESIMPLE_U16_3, &&VSESIMPLE_U16_4,
    &&VSESIMPLE_U16_5, &&VSESIMPLE_U16_6,
    &&VSESIMPLE_U16_7, &&VSESIMPLE_U16_8,
    &&VSESIMPLE_U16_9, &&VSESIMPLE_U16_10,
    &&VSESIMPLE_U16_11, &&VSESIMPLE_U16_12,
    &&VSESIMPLE_U16_14, &&VSESIMPLE_U16_16,
    &&VSESIMPLE_U16_32, &&VSESIMPLE_U16_64,

    /* UNPACKER: 20 */
    &&VSESIMPLE_U20_1, &&VSESIMPLE_U20_2,
    &&VSESIMPLE_U20_3, &&VSESIMPLE_U20_4,
    &&VSESIMPLE_U20_5, &&VSESIMPLE_U20_6,
    &&VSESIMPLE_U20_7, &&VSESIMPLE_U20_8,
    &&VSESIMPLE_U20_9, &&VSESIMPLE_U20_10,
    &&VSESIMPLE_U20_11, &&VSESIMPLE_U20_12,
    &&VSESIMPLE_U20_14, &&VSESIMPLE_U20_16,
    &&VSESIMPLE_U20_32, &&VSESIMPLE_U20_64,

    /* UNPACKER: 32 */
    &&VSESIMPLE_U32_1, &&VSESIMPLE_U32_2,
    &&VSESIMPLE_U32_3, &&VSESIMPLE_U32_4,
    &&VSESIMPLE_U32_5, &&VSESIMPLE_U32_6,
    &&VSESIMPLE_U32_7, &&VSESIMPLE_U32_8,
    &&VSESIMPLE_U32_9, &&VSESIMPLE_U32_10,
    &&VSESIMPLE_U32_11, &&VSESIMPLE_U32_12,
    &&VSESIMPLE_U32_14, &&VSESIMPLE_U32_16,
    &&VSESIMPLE_U32_32, &&VSESIMPLE_U32_64,
  };

  const uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  uint64_t num = BYTEORDER_FREE_LOAD64(in);
  uint64_t offset =
      DIV_ROUNDUP(num, 32 / VSESIMPLE_LOGDESC);

  const uint32_t *data = in + offset + 2;
  in += 2;

  /* CREATE A DIPATCH TABLE */
  REGISTER_VECTOR_RAII(void *, jtable, num + 1);

  uint64_t numBlocks = num / 4;

  for (uint64_t i = 0; i < numBlocks; i++, in++) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    jtable[i * 4] =
        VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC * 3];
    jtable[i * 4 + 1] =
        VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC * 2];
    jtable[i * 4 + 2] =
        VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC * 1];
    jtable[i * 4 + 3] =
        VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC];
  }

  uint32_t rem = num % 4;

  if (rem != 0) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in);

    switch (rem) {
      case 3: {
        jtable[numBlocks + 2] =
            VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC * 2];
      }

      case 2: {
        jtable[numBlocks + 1] =
            VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC * 1];
      }

      case 1: {
        jtable[numBlocks] =
            VSESIMPLE_UNPACK[val >> VSESIMPLE_LOGDESC];
      }
    }
  }

  jtable[4 * numBlocks + rem] = &&VSESIMPLE_RET;

#define NEXT  \
  if (UNLIKELY(out < oterm && data < iterm))  \
    return;   \
  *jtable++

  /* Start point for decompression */
  NEXT;

/* UNAPCK 0 */
VSESIMPLE_U0_1:
  VSESIMPLE_UNPACK0_1(&out, &data); NEXT;
VSESIMPLE_U0_2:
  VSESIMPLE_UNPACK0_2(&out, &data); NEXT;
VSESIMPLE_U0_3:
  VSESIMPLE_UNPACK0_3(&out, &data); NEXT;
VSESIMPLE_U0_4:
  VSESIMPLE_UNPACK0_4(&out, &data); NEXT;
VSESIMPLE_U0_5:
  VSESIMPLE_UNPACK0_5(&out, &data); NEXT;
VSESIMPLE_U0_6:
  VSESIMPLE_UNPACK0_6(&out, &data); NEXT;
VSESIMPLE_U0_7:
  VSESIMPLE_UNPACK0_7(&out, &data); NEXT;
VSESIMPLE_U0_8:
  VSESIMPLE_UNPACK0_8(&out, &data); NEXT;
VSESIMPLE_U0_9:
  VSESIMPLE_UNPACK0_9(&out, &data); NEXT;
VSESIMPLE_U0_10:
  VSESIMPLE_UNPACK0_10(&out, &data); NEXT;
VSESIMPLE_U0_11:
  VSESIMPLE_UNPACK0_11(&out, &data); NEXT;
VSESIMPLE_U0_12:
  VSESIMPLE_UNPACK0_12(&out, &data); NEXT;
VSESIMPLE_U0_14:
  VSESIMPLE_UNPACK0_14(&out, &data); NEXT;
VSESIMPLE_U0_16:
  VSESIMPLE_UNPACK0_16(&out, &data); NEXT;
VSESIMPLE_U0_32:
  VSESIMPLE_UNPACK0_32(&out, &data); NEXT;
VSESIMPLE_U0_64:
  VSESIMPLE_UNPACK0_64(&out, &data); NEXT;

/* UNAPCK 1 */
VSESIMPLE_U1_1:
  VSESIMPLE_UNPACK1_1(&out, &data); NEXT;
VSESIMPLE_U1_2:
  VSESIMPLE_UNPACK1_2(&out, &data); NEXT;
VSESIMPLE_U1_3:
  VSESIMPLE_UNPACK1_3(&out, &data); NEXT;
VSESIMPLE_U1_4:
  VSESIMPLE_UNPACK1_4(&out, &data); NEXT;
VSESIMPLE_U1_5:
  VSESIMPLE_UNPACK1_5(&out, &data); NEXT;
VSESIMPLE_U1_6:
  VSESIMPLE_UNPACK1_6(&out, &data); NEXT;
VSESIMPLE_U1_7:
  VSESIMPLE_UNPACK1_7(&out, &data); NEXT;
VSESIMPLE_U1_8:
  VSESIMPLE_UNPACK1_8(&out, &data); NEXT;
VSESIMPLE_U1_9:
  VSESIMPLE_UNPACK1_9(&out, &data); NEXT;
VSESIMPLE_U1_10:
  VSESIMPLE_UNPACK1_10(&out, &data); NEXT;
VSESIMPLE_U1_11:
  VSESIMPLE_UNPACK1_11(&out, &data); NEXT;
VSESIMPLE_U1_12:
  VSESIMPLE_UNPACK1_12(&out, &data); NEXT;
VSESIMPLE_U1_14:
  VSESIMPLE_UNPACK1_14(&out, &data); NEXT;
VSESIMPLE_U1_16:
  VSESIMPLE_UNPACK1_16(&out, &data); NEXT;
VSESIMPLE_U1_32:
  VSESIMPLE_UNPACK1_32(&out, &data); NEXT;
VSESIMPLE_U1_64:
  VSESIMPLE_UNPACK1_64(&out, &data); NEXT;

/* UNAPCK 2 */
VSESIMPLE_U2_1:
  VSESIMPLE_UNPACK2_1(&out, &data); NEXT;
VSESIMPLE_U2_2:
  VSESIMPLE_UNPACK2_2(&out, &data); NEXT;
VSESIMPLE_U2_3:
  VSESIMPLE_UNPACK2_3(&out, &data); NEXT;
VSESIMPLE_U2_4:
  VSESIMPLE_UNPACK2_4(&out, &data); NEXT;
VSESIMPLE_U2_5:
  VSESIMPLE_UNPACK2_5(&out, &data); NEXT;
VSESIMPLE_U2_6:
  VSESIMPLE_UNPACK2_6(&out, &data); NEXT;
VSESIMPLE_U2_7:
  VSESIMPLE_UNPACK2_7(&out, &data); NEXT;
VSESIMPLE_U2_8:
  VSESIMPLE_UNPACK2_8(&out, &data); NEXT;
VSESIMPLE_U2_9:
  VSESIMPLE_UNPACK2_9(&out, &data); NEXT;
VSESIMPLE_U2_10:
  VSESIMPLE_UNPACK2_10(&out, &data); NEXT;
VSESIMPLE_U2_11:
  VSESIMPLE_UNPACK2_11(&out, &data); NEXT;
VSESIMPLE_U2_12:
  VSESIMPLE_UNPACK2_12(&out, &data); NEXT;
VSESIMPLE_U2_14:
  VSESIMPLE_UNPACK2_14(&out, &data); NEXT;
VSESIMPLE_U2_16:
  VSESIMPLE_UNPACK2_16(&out, &data); NEXT;
VSESIMPLE_U2_32:
  VSESIMPLE_UNPACK2_32(&out, &data); NEXT;
VSESIMPLE_U2_64:
  VSESIMPLE_UNPACK2_64(&out, &data); NEXT;

/* UNAPCK 3 */
VSESIMPLE_U3_1:
  VSESIMPLE_UNPACK3_1(&out, &data); NEXT;
VSESIMPLE_U3_2:
  VSESIMPLE_UNPACK3_2(&out, &data); NEXT;
VSESIMPLE_U3_3:
  VSESIMPLE_UNPACK3_3(&out, &data); NEXT;
VSESIMPLE_U3_4:
  VSESIMPLE_UNPACK3_4(&out, &data); NEXT;
VSESIMPLE_U3_5:
  VSESIMPLE_UNPACK3_5(&out, &data); NEXT;
VSESIMPLE_U3_6:
  VSESIMPLE_UNPACK3_6(&out, &data); NEXT;
VSESIMPLE_U3_7:
  VSESIMPLE_UNPACK3_7(&out, &data); NEXT;
VSESIMPLE_U3_8:
  VSESIMPLE_UNPACK3_8(&out, &data); NEXT;
VSESIMPLE_U3_9:
  VSESIMPLE_UNPACK3_9(&out, &data); NEXT;
VSESIMPLE_U3_10:
  VSESIMPLE_UNPACK3_10(&out, &data); NEXT;
VSESIMPLE_U3_11:
  VSESIMPLE_UNPACK3_11(&out, &data); NEXT;
VSESIMPLE_U3_12:
  VSESIMPLE_UNPACK3_12(&out, &data); NEXT;
VSESIMPLE_U3_14:
  VSESIMPLE_UNPACK3_14(&out, &data); NEXT;
VSESIMPLE_U3_16:
  VSESIMPLE_UNPACK3_16(&out, &data); NEXT;
VSESIMPLE_U3_32:
  VSESIMPLE_UNPACK3_32(&out, &data); NEXT;
VSESIMPLE_U3_64:
  VSESIMPLE_UNPACK3_64(&out, &data); NEXT;

/* UNAPCK 4 */
VSESIMPLE_U4_1:
  VSESIMPLE_UNPACK4_1(&out, &data); NEXT;
VSESIMPLE_U4_2:
  VSESIMPLE_UNPACK4_2(&out, &data); NEXT;
VSESIMPLE_U4_3:
  VSESIMPLE_UNPACK4_3(&out, &data); NEXT;
VSESIMPLE_U4_4:
  VSESIMPLE_UNPACK4_4(&out, &data); NEXT;
VSESIMPLE_U4_5:
  VSESIMPLE_UNPACK4_5(&out, &data); NEXT;
VSESIMPLE_U4_6:
  VSESIMPLE_UNPACK4_6(&out, &data); NEXT;
VSESIMPLE_U4_7:
  VSESIMPLE_UNPACK4_7(&out, &data); NEXT;
VSESIMPLE_U4_8:
  VSESIMPLE_UNPACK4_8(&out, &data); NEXT;
VSESIMPLE_U4_9:
  VSESIMPLE_UNPACK4_9(&out, &data); NEXT;
VSESIMPLE_U4_10:
  VSESIMPLE_UNPACK4_10(&out, &data); NEXT;
VSESIMPLE_U4_11:
  VSESIMPLE_UNPACK4_11(&out, &data); NEXT;
VSESIMPLE_U4_12:
  VSESIMPLE_UNPACK4_12(&out, &data); NEXT;
VSESIMPLE_U4_14:
  VSESIMPLE_UNPACK4_14(&out, &data); NEXT;
VSESIMPLE_U4_16:
  VSESIMPLE_UNPACK4_16(&out, &data); NEXT;
VSESIMPLE_U4_32:
  VSESIMPLE_UNPACK4_32(&out, &data); NEXT;
VSESIMPLE_U4_64:
  VSESIMPLE_UNPACK4_64(&out, &data); NEXT;

/* UNAPCK 5 */
VSESIMPLE_U5_1:
  VSESIMPLE_UNPACK5_1(&out, &data); NEXT;
VSESIMPLE_U5_2:
  VSESIMPLE_UNPACK5_2(&out, &data); NEXT;
VSESIMPLE_U5_3:
  VSESIMPLE_UNPACK5_3(&out, &data); NEXT;
VSESIMPLE_U5_4:
  VSESIMPLE_UNPACK5_4(&out, &data); NEXT;
VSESIMPLE_U5_5:
  VSESIMPLE_UNPACK5_5(&out, &data); NEXT;
VSESIMPLE_U5_6:
  VSESIMPLE_UNPACK5_6(&out, &data); NEXT;
VSESIMPLE_U5_7:
  VSESIMPLE_UNPACK5_7(&out, &data); NEXT;
VSESIMPLE_U5_8:
  VSESIMPLE_UNPACK5_8(&out, &data); NEXT;
VSESIMPLE_U5_9:
  VSESIMPLE_UNPACK5_9(&out, &data); NEXT;
VSESIMPLE_U5_10:
  VSESIMPLE_UNPACK5_10(&out, &data); NEXT;
VSESIMPLE_U5_11:
  VSESIMPLE_UNPACK5_11(&out, &data); NEXT;
VSESIMPLE_U5_12:
  VSESIMPLE_UNPACK5_12(&out, &data); NEXT;
VSESIMPLE_U5_14:
  VSESIMPLE_UNPACK5_14(&out, &data); NEXT;
VSESIMPLE_U5_16:
  VSESIMPLE_UNPACK5_16(&out, &data); NEXT;
VSESIMPLE_U5_32:
  VSESIMPLE_UNPACK5_32(&out, &data); NEXT;
VSESIMPLE_U5_64:
  VSESIMPLE_UNPACK5_64(&out, &data); NEXT;

/* UNAPCK 6 */
VSESIMPLE_U6_1:
  VSESIMPLE_UNPACK6_1(&out, &data); NEXT;
VSESIMPLE_U6_2:
  VSESIMPLE_UNPACK6_2(&out, &data); NEXT;
VSESIMPLE_U6_3:
  VSESIMPLE_UNPACK6_3(&out, &data); NEXT;
VSESIMPLE_U6_4:
  VSESIMPLE_UNPACK6_4(&out, &data); NEXT;
VSESIMPLE_U6_5:
  VSESIMPLE_UNPACK6_5(&out, &data); NEXT;
VSESIMPLE_U6_6:
  VSESIMPLE_UNPACK6_6(&out, &data); NEXT;
VSESIMPLE_U6_7:
  VSESIMPLE_UNPACK6_7(&out, &data); NEXT;
VSESIMPLE_U6_8:
  VSESIMPLE_UNPACK6_8(&out, &data); NEXT;
VSESIMPLE_U6_9:
  VSESIMPLE_UNPACK6_9(&out, &data); NEXT;
VSESIMPLE_U6_10:
  VSESIMPLE_UNPACK6_10(&out, &data); NEXT;
VSESIMPLE_U6_11:
  VSESIMPLE_UNPACK6_11(&out, &data); NEXT;
VSESIMPLE_U6_12:
  VSESIMPLE_UNPACK6_12(&out, &data); NEXT;
VSESIMPLE_U6_14:
  VSESIMPLE_UNPACK6_14(&out, &data); NEXT;
VSESIMPLE_U6_16:
  VSESIMPLE_UNPACK6_16(&out, &data); NEXT;
VSESIMPLE_U6_32:
  VSESIMPLE_UNPACK6_32(&out, &data); NEXT;
VSESIMPLE_U6_64:
  VSESIMPLE_UNPACK6_64(&out, &data); NEXT;

/* UNAPCK 7 */
VSESIMPLE_U7_1:
  VSESIMPLE_UNPACK7_1(&out, &data); NEXT;
VSESIMPLE_U7_2:
  VSESIMPLE_UNPACK7_2(&out, &data); NEXT;
VSESIMPLE_U7_3:
  VSESIMPLE_UNPACK7_3(&out, &data); NEXT;
VSESIMPLE_U7_4:
  VSESIMPLE_UNPACK7_4(&out, &data); NEXT;
VSESIMPLE_U7_5:
  VSESIMPLE_UNPACK7_5(&out, &data); NEXT;
VSESIMPLE_U7_6:
  VSESIMPLE_UNPACK7_6(&out, &data); NEXT;
VSESIMPLE_U7_7:
  VSESIMPLE_UNPACK7_7(&out, &data); NEXT;
VSESIMPLE_U7_8:
  VSESIMPLE_UNPACK7_8(&out, &data); NEXT;
VSESIMPLE_U7_9:
  VSESIMPLE_UNPACK7_9(&out, &data); NEXT;
VSESIMPLE_U7_10:
  VSESIMPLE_UNPACK7_10(&out, &data); NEXT;
VSESIMPLE_U7_11:
  VSESIMPLE_UNPACK7_11(&out, &data); NEXT;
VSESIMPLE_U7_12:
  VSESIMPLE_UNPACK7_12(&out, &data); NEXT;
VSESIMPLE_U7_14:
  VSESIMPLE_UNPACK7_14(&out, &data); NEXT;
VSESIMPLE_U7_16:
  VSESIMPLE_UNPACK7_16(&out, &data); NEXT;
VSESIMPLE_U7_32:
  VSESIMPLE_UNPACK7_32(&out, &data); NEXT;
VSESIMPLE_U7_64:
  VSESIMPLE_UNPACK7_64(&out, &data); NEXT;

/* UNAPCK 8 */
VSESIMPLE_U8_1:
  VSESIMPLE_UNPACK8_1(&out, &data); NEXT;
VSESIMPLE_U8_2:
  VSESIMPLE_UNPACK8_2(&out, &data); NEXT;
VSESIMPLE_U8_3:
  VSESIMPLE_UNPACK8_3(&out, &data); NEXT;
VSESIMPLE_U8_4:
  VSESIMPLE_UNPACK8_4(&out, &data); NEXT;
VSESIMPLE_U8_5:
  VSESIMPLE_UNPACK8_5(&out, &data); NEXT;
VSESIMPLE_U8_6:
  VSESIMPLE_UNPACK8_6(&out, &data); NEXT;
VSESIMPLE_U8_7:
  VSESIMPLE_UNPACK8_7(&out, &data); NEXT;
VSESIMPLE_U8_8:
  VSESIMPLE_UNPACK8_8(&out, &data); NEXT;
VSESIMPLE_U8_9:
  VSESIMPLE_UNPACK8_9(&out, &data); NEXT;
VSESIMPLE_U8_10:
  VSESIMPLE_UNPACK8_10(&out, &data); NEXT;
VSESIMPLE_U8_11:
  VSESIMPLE_UNPACK8_11(&out, &data); NEXT;
VSESIMPLE_U8_12:
  VSESIMPLE_UNPACK8_12(&out, &data); NEXT;
VSESIMPLE_U8_14:
  VSESIMPLE_UNPACK8_14(&out, &data); NEXT;
VSESIMPLE_U8_16:
  VSESIMPLE_UNPACK8_16(&out, &data); NEXT;
VSESIMPLE_U8_32:
  VSESIMPLE_UNPACK8_32(&out, &data); NEXT;
VSESIMPLE_U8_64:
  VSESIMPLE_UNPACK8_64(&out, &data); NEXT;

/* UNAPCK 9 */
VSESIMPLE_U9_1:
  VSESIMPLE_UNPACK9_1(&out, &data); NEXT;
VSESIMPLE_U9_2:
  VSESIMPLE_UNPACK9_2(&out, &data); NEXT;
VSESIMPLE_U9_3:
  VSESIMPLE_UNPACK9_3(&out, &data); NEXT;
VSESIMPLE_U9_4:
  VSESIMPLE_UNPACK9_4(&out, &data); NEXT;
VSESIMPLE_U9_5:
  VSESIMPLE_UNPACK9_5(&out, &data); NEXT;
VSESIMPLE_U9_6:
  VSESIMPLE_UNPACK9_6(&out, &data); NEXT;
VSESIMPLE_U9_7:
  VSESIMPLE_UNPACK9_7(&out, &data); NEXT;
VSESIMPLE_U9_8:
  VSESIMPLE_UNPACK9_8(&out, &data); NEXT;
VSESIMPLE_U9_9:
  VSESIMPLE_UNPACK9_9(&out, &data); NEXT;
VSESIMPLE_U9_10:
  VSESIMPLE_UNPACK9_10(&out, &data); NEXT;
VSESIMPLE_U9_11:
  VSESIMPLE_UNPACK9_11(&out, &data); NEXT;
VSESIMPLE_U9_12:
  VSESIMPLE_UNPACK9_12(&out, &data); NEXT;
VSESIMPLE_U9_14:
  VSESIMPLE_UNPACK9_14(&out, &data); NEXT;
VSESIMPLE_U9_16:
  VSESIMPLE_UNPACK9_16(&out, &data); NEXT;
VSESIMPLE_U9_32:
  VSESIMPLE_UNPACK9_32(&out, &data); NEXT;
VSESIMPLE_U9_64:
  VSESIMPLE_UNPACK9_64(&out, &data); NEXT;

/* UNAPCK 10 */
VSESIMPLE_U10_1:
  VSESIMPLE_UNPACK10_1(&out, &data); NEXT;
VSESIMPLE_U10_2:
  VSESIMPLE_UNPACK10_2(&out, &data); NEXT;
VSESIMPLE_U10_3:
  VSESIMPLE_UNPACK10_3(&out, &data); NEXT;
VSESIMPLE_U10_4:
  VSESIMPLE_UNPACK10_4(&out, &data); NEXT;
VSESIMPLE_U10_5:
  VSESIMPLE_UNPACK10_5(&out, &data); NEXT;
VSESIMPLE_U10_6:
  VSESIMPLE_UNPACK10_6(&out, &data); NEXT;
VSESIMPLE_U10_7:
  VSESIMPLE_UNPACK10_7(&out, &data); NEXT;
VSESIMPLE_U10_8:
  VSESIMPLE_UNPACK10_8(&out, &data); NEXT;
VSESIMPLE_U10_9:
  VSESIMPLE_UNPACK10_9(&out, &data); NEXT;
VSESIMPLE_U10_10:
  VSESIMPLE_UNPACK10_10(&out, &data); NEXT;
VSESIMPLE_U10_11:
  VSESIMPLE_UNPACK10_11(&out, &data); NEXT;
VSESIMPLE_U10_12:
  VSESIMPLE_UNPACK10_12(&out, &data); NEXT;
VSESIMPLE_U10_14:
  VSESIMPLE_UNPACK10_14(&out, &data); NEXT;
VSESIMPLE_U10_16:
  VSESIMPLE_UNPACK10_16(&out, &data); NEXT;
VSESIMPLE_U10_32:
  VSESIMPLE_UNPACK10_32(&out, &data); NEXT;
VSESIMPLE_U10_64:
  VSESIMPLE_UNPACK10_64(&out, &data); NEXT;

/* UNAPCK 11 */
VSESIMPLE_U11_1:
  VSESIMPLE_UNPACK11_1(&out, &data); NEXT;
VSESIMPLE_U11_2:
  VSESIMPLE_UNPACK11_2(&out, &data); NEXT;
VSESIMPLE_U11_3:
  VSESIMPLE_UNPACK11_3(&out, &data); NEXT;
VSESIMPLE_U11_4:
  VSESIMPLE_UNPACK11_4(&out, &data); NEXT;
VSESIMPLE_U11_5:
  VSESIMPLE_UNPACK11_5(&out, &data); NEXT;
VSESIMPLE_U11_6:
  VSESIMPLE_UNPACK11_6(&out, &data); NEXT;
VSESIMPLE_U11_7:
  VSESIMPLE_UNPACK11_7(&out, &data); NEXT;
VSESIMPLE_U11_8:
  VSESIMPLE_UNPACK11_8(&out, &data); NEXT;
VSESIMPLE_U11_9:
  VSESIMPLE_UNPACK11_9(&out, &data); NEXT;
VSESIMPLE_U11_10:
  VSESIMPLE_UNPACK11_10(&out, &data); NEXT;
VSESIMPLE_U11_11:
  VSESIMPLE_UNPACK11_11(&out, &data); NEXT;
VSESIMPLE_U11_12:
  VSESIMPLE_UNPACK11_12(&out, &data); NEXT;
VSESIMPLE_U11_14:
  VSESIMPLE_UNPACK11_14(&out, &data); NEXT;
VSESIMPLE_U11_16:
  VSESIMPLE_UNPACK11_16(&out, &data); NEXT;
VSESIMPLE_U11_32:
  VSESIMPLE_UNPACK11_32(&out, &data); NEXT;
VSESIMPLE_U11_64:
  VSESIMPLE_UNPACK11_64(&out, &data); NEXT;

/* UNAPCK 12 */
VSESIMPLE_U12_1:
  VSESIMPLE_UNPACK12_1(&out, &data); NEXT;
VSESIMPLE_U12_2:
  VSESIMPLE_UNPACK12_2(&out, &data); NEXT;
VSESIMPLE_U12_3:
  VSESIMPLE_UNPACK12_3(&out, &data); NEXT;
VSESIMPLE_U12_4:
  VSESIMPLE_UNPACK12_4(&out, &data); NEXT;
VSESIMPLE_U12_5:
  VSESIMPLE_UNPACK12_5(&out, &data); NEXT;
VSESIMPLE_U12_6:
  VSESIMPLE_UNPACK12_6(&out, &data); NEXT;
VSESIMPLE_U12_7:
  VSESIMPLE_UNPACK12_7(&out, &data); NEXT;
VSESIMPLE_U12_8:
  VSESIMPLE_UNPACK12_8(&out, &data); NEXT;
VSESIMPLE_U12_9:
  VSESIMPLE_UNPACK12_9(&out, &data); NEXT;
VSESIMPLE_U12_10:
  VSESIMPLE_UNPACK12_10(&out, &data); NEXT;
VSESIMPLE_U12_11:
  VSESIMPLE_UNPACK12_11(&out, &data); NEXT;
VSESIMPLE_U12_12:
  VSESIMPLE_UNPACK12_12(&out, &data); NEXT;
VSESIMPLE_U12_14:
  VSESIMPLE_UNPACK12_14(&out, &data); NEXT;
VSESIMPLE_U12_16:
  VSESIMPLE_UNPACK12_16(&out, &data); NEXT;
VSESIMPLE_U12_32:
  VSESIMPLE_UNPACK12_32(&out, &data); NEXT;
VSESIMPLE_U12_64:
  VSESIMPLE_UNPACK12_64(&out, &data); NEXT;

/* UNAPCK 16 */
VSESIMPLE_U16_1:
  VSESIMPLE_UNPACK16_1(&out, &data); NEXT;
VSESIMPLE_U16_2:
  VSESIMPLE_UNPACK16_2(&out, &data); NEXT;
VSESIMPLE_U16_3:
  VSESIMPLE_UNPACK16_3(&out, &data); NEXT;
VSESIMPLE_U16_4:
  VSESIMPLE_UNPACK16_4(&out, &data); NEXT;
VSESIMPLE_U16_5:
  VSESIMPLE_UNPACK16_5(&out, &data); NEXT;
VSESIMPLE_U16_6:
  VSESIMPLE_UNPACK16_6(&out, &data); NEXT;
VSESIMPLE_U16_7:
  VSESIMPLE_UNPACK16_7(&out, &data); NEXT;
VSESIMPLE_U16_8:
  VSESIMPLE_UNPACK16_8(&out, &data); NEXT;
VSESIMPLE_U16_9:
  VSESIMPLE_UNPACK16_9(&out, &data); NEXT;
VSESIMPLE_U16_10:
  VSESIMPLE_UNPACK16_10(&out, &data); NEXT;
VSESIMPLE_U16_11:
  VSESIMPLE_UNPACK16_11(&out, &data); NEXT;
VSESIMPLE_U16_12:
  VSESIMPLE_UNPACK16_12(&out, &data); NEXT;
VSESIMPLE_U16_14:
  VSESIMPLE_UNPACK16_14(&out, &data); NEXT;
VSESIMPLE_U16_16:
  VSESIMPLE_UNPACK16_16(&out, &data); NEXT;
VSESIMPLE_U16_32:
  VSESIMPLE_UNPACK16_32(&out, &data); NEXT;
VSESIMPLE_U16_64:
  VSESIMPLE_UNPACK16_64(&out, &data); NEXT;

/* UNAPCK 20 */
VSESIMPLE_U20_1:
  VSESIMPLE_UNPACK20_1(&out, &data); NEXT;
VSESIMPLE_U20_2:
  VSESIMPLE_UNPACK20_2(&out, &data); NEXT;
VSESIMPLE_U20_3:
  VSESIMPLE_UNPACK20_3(&out, &data); NEXT;
VSESIMPLE_U20_4:
  VSESIMPLE_UNPACK20_4(&out, &data); NEXT;
VSESIMPLE_U20_5:
  VSESIMPLE_UNPACK20_5(&out, &data); NEXT;
VSESIMPLE_U20_6:
  VSESIMPLE_UNPACK20_6(&out, &data); NEXT;
VSESIMPLE_U20_7:
  VSESIMPLE_UNPACK20_7(&out, &data); NEXT;
VSESIMPLE_U20_8:
  VSESIMPLE_UNPACK20_8(&out, &data); NEXT;
VSESIMPLE_U20_9:
  VSESIMPLE_UNPACK20_9(&out, &data); NEXT;
VSESIMPLE_U20_10:
  VSESIMPLE_UNPACK20_10(&out, &data); NEXT;
VSESIMPLE_U20_11:
  VSESIMPLE_UNPACK20_11(&out, &data); NEXT;
VSESIMPLE_U20_12:
  VSESIMPLE_UNPACK20_12(&out, &data); NEXT;
VSESIMPLE_U20_14:
  VSESIMPLE_UNPACK20_14(&out, &data); NEXT;
VSESIMPLE_U20_16:
  VSESIMPLE_UNPACK20_16(&out, &data); NEXT;
VSESIMPLE_U20_32:
  VSESIMPLE_UNPACK20_32(&out, &data); NEXT;
VSESIMPLE_U20_64:
  VSESIMPLE_UNPACK20_64(&out, &data); NEXT;

/* UNAPCK 32 */
VSESIMPLE_U32_1:
  VSESIMPLE_UNPACK32_1(&out, &data); NEXT;
VSESIMPLE_U32_2:
  VSESIMPLE_UNPACK32_2(&out, &data); NEXT;
VSESIMPLE_U32_3:
  VSESIMPLE_UNPACK32_3(&out, &data); NEXT;
VSESIMPLE_U32_4:
  VSESIMPLE_UNPACK32_4(&out, &data); NEXT;
VSESIMPLE_U32_5:
  VSESIMPLE_UNPACK32_5(&out, &data); NEXT;
VSESIMPLE_U32_6:
  VSESIMPLE_UNPACK32_6(&out, &data); NEXT;
VSESIMPLE_U32_7:
  VSESIMPLE_UNPACK32_7(&out, &data); NEXT;
VSESIMPLE_U32_8:
  VSESIMPLE_UNPACK32_8(&out, &data); NEXT;
VSESIMPLE_U32_9:
  VSESIMPLE_UNPACK32_9(&out, &data); NEXT;
VSESIMPLE_U32_10:
  VSESIMPLE_UNPACK32_10(&out, &data); NEXT;
VSESIMPLE_U32_11:
  VSESIMPLE_UNPACK32_11(&out, &data); NEXT;
VSESIMPLE_U32_12:
  VSESIMPLE_UNPACK32_12(&out, &data); NEXT;
VSESIMPLE_U32_14:
  VSESIMPLE_UNPACK32_14(&out, &data); NEXT;
VSESIMPLE_U32_16:
  VSESIMPLE_UNPACK32_16(&out, &data); NEXT;
VSESIMPLE_U32_32:
  VSESIMPLE_UNPACK32_32(&out, &data); NEXT;
VSESIMPLE_U32_64:
  VSESIMPLE_UNPACK32_64(&out, &data); NEXT;

/* Terminal point of threading */
VSESIMPLE_RET:
  return;
}

uint64_t VSEncodingSimple::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len + 5;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
