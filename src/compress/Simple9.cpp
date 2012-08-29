/*-----------------------------------------------------------------------------
 *  Simple9.hpp - A encoder/decoder for Simple9
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

#include <compress/policy/Simple9.hpp>

namespace integer_encoding {
namespace internals {

Simple9::Simple9()
    : EncodingBase(E_SIMPLE9) {
  unpack_[0] = Simple9::unpack28_1;
  unpack_[1] = Simple9::unpack14_2;
  unpack_[2] = Simple9::unpack9_3;
  unpack_[3] = Simple9::unpack7_4;
  unpack_[4] = Simple9::unpack5_5;
  unpack_[5] = Simple9::unpack4_7;
  unpack_[6] = Simple9::unpack3_9;
  unpack_[7] = Simple9::unpack2_14;
  unpack_[8] = Simple9::unpack1_28;
}

Simple9::Simple9(int policy)
    : EncodingBase(policy) {}

Simple9::~Simple9() throw() {}

void Simple9::encodeArray(const uint32_t *in,
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

  BitsWriter  wt(out, *nvalue);

#define WRITE_SIMPLE9_ENTRY(__num__, __bit__) \
    ({  \
      uint32_t min = (len < __num__)? len : __num__;    \
      for (uint32_t i = 0; i < min; i++)  \
        wt.write_bits(*in++, __bit__);    \
      len -= min;   \
    })

  while (len > 0) {
    if (try_pack(in, len, 28, 1)) {
      wt.write_bits(0, 4);
      WRITE_SIMPLE9_ENTRY(28, 1);
    } else if (try_pack(in, len, 14, 2)) {
      wt.write_bits(1, 4);
      WRITE_SIMPLE9_ENTRY(14, 2);
    } else if (try_pack(in, len, 9, 3)) {
      wt.write_bits(2, 4);
      WRITE_SIMPLE9_ENTRY(9, 3);
    } else if (try_pack(in, len, 7, 4)) {
      wt.write_bits(3, 4);
      WRITE_SIMPLE9_ENTRY(7, 4);
    } else if (try_pack(in, len, 5, 5)) {
      wt.write_bits(4, 4);
      WRITE_SIMPLE9_ENTRY(5, 5);
    } else if (try_pack(in, len, 4, 7)) {
      wt.write_bits(5, 4);
      WRITE_SIMPLE9_ENTRY(4, 7);
    } else if (try_pack(in, len, 3, 9)) {
      wt.write_bits(6, 4);
      WRITE_SIMPLE9_ENTRY(3, 9);
    } else if (try_pack(in, len, 2, 14)) {
      wt.write_bits(7, 4);
      WRITE_SIMPLE9_ENTRY(2, 14);
    } else {
      if ((*in >> 28) > 0)
        THROW_ENCODING_EXCEPTION("Out of value range: *in");

      /* Write a value as it is */
      wt.write_bits(8, 4);
      wt.write_bits(*in++, 28);
      len--;
    }

    wt.flush_bits();
  }

  *nvalue = wt.size();
}

void Simple9::decodeArray(const uint32_t *in,
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

  ASSERT_ADDR(in, lne);
  ASSERT_ADDR(out, nvalue);

  const uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  while (1) {
    if (UNLIKELY(out >= oterm || in >= iterm))
      break;
    (unpack_[*in >> (32 - SIMPLE9_LOGDESC)])(&out, &in);
  }
}

uint64_t Simple9::require(uint64_t len) const {
  return len;
}

bool Simple9::try_pack(const uint32_t *in,
                       uint32_t len,
                       uint32_t num1, uint32_t log1) {
  uint32_t min = (len < num1)? len : num1;
  for (uint32_t i = 0; i < min; i++) {
    uint32_t d = 31 - MSB32(in[i]);
    if (d > log1 - 1)
      return false;
  }
  return true;
}

void Simple9::unpack28_1(uint32_t **out,
                         const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 27) & 0x01;
  pout[1] = (val >> 26) & 0x01;
  pout[2] = (val >> 25) & 0x01;
  pout[3] = (val >> 24) & 0x01;
  pout[4] = (val >> 23) & 0x01;
  pout[5] = (val >> 22) & 0x01;
  pout[6] = (val >> 21) & 0x01;
  pout[7] = (val >> 20) & 0x01;
  pout[8] = (val >> 19) & 0x01;
  pout[9] = (val >> 18) & 0x01;
  pout[10] = (val >> 17) & 0x01;
  pout[11] = (val >> 16) & 0x01;
  pout[12] = (val >> 15) & 0x01;
  pout[13] = (val >> 14) & 0x01;
  pout[14] = (val >> 13) & 0x01;
  pout[15] = (val >> 12) & 0x01;
  pout[16] = (val >> 11) & 0x01;
  pout[17] = (val >> 10) & 0x01;
  pout[18] = (val >> 9) & 0x01;
  pout[19] = (val >> 8) & 0x01;
  pout[20] = (val >> 7) & 0x01;
  pout[21] = (val >> 6) & 0x01;
  pout[22] = (val >> 5) & 0x01;
  pout[23] = (val >> 4) & 0x01;
  pout[24] = (val >> 3) & 0x01;
  pout[25] = (val >> 2) & 0x01;
  pout[26] = (val >> 1) & 0x01;
  pout[27] = val & 0x01;

  *in = pin + 1;
  *out = pout + 28;
}

void Simple9::unpack14_2(uint32_t **out,
                         const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 26) & 0x03;
  pout[1] = (val >> 24) & 0x03;
  pout[2] = (val >> 22) & 0x03;
  pout[3] = (val >> 20) & 0x03;
  pout[4] = (val >> 18) & 0x03;
  pout[5] = (val >> 16) & 0x03;
  pout[6] = (val >> 14) & 0x03;
  pout[7] = (val >> 12) & 0x03;
  pout[8] = (val >> 10) & 0x03;
  pout[9] = (val >> 8) & 0x03;
  pout[10] = (val >> 6) & 0x03;
  pout[11] = (val >> 4) & 0x03;
  pout[12] = (val >> 2) & 0x03;
  pout[13] = val & 0x03;

  *in = pin + 1;
  *out = pout + 14;
}

void Simple9::unpack9_3(uint32_t **out,
                        const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 25) & 0x07;
  pout[1] = (val >> 22) & 0x07;
  pout[2] = (val >> 19) & 0x07;
  pout[3] = (val >> 16) & 0x07;
  pout[4] = (val >> 13) & 0x07;
  pout[5] = (val >> 10) & 0x07;
  pout[6] = (val >> 7) & 0x07;
  pout[7] = (val >> 4) & 0x07;
  pout[8] = (val >> 1) & 0x07;

  *in = pin + 1;
  *out = pout + 9;
}

void Simple9::unpack7_4(uint32_t **out,
                        const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 24) & 0x0f;
  pout[1] = (val >> 20) & 0x0f;
  pout[2] = (val >> 16) & 0x0f;
  pout[3] = (val >> 12) & 0x0f;
  pout[4] = (val >> 8) & 0x0f;
  pout[5] = (val >> 4) & 0x0f;
  pout[6] = val & 0x0f;

  *in = pin + 1;
  *out = pout + 7;
}

void Simple9::unpack5_5(uint32_t **out,
                        const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 23) & 0x1f;
  pout[1] = (val >> 18) & 0x1f;
  pout[2] = (val >> 13) & 0x1f;
  pout[3] = (val >> 8) & 0x1f;
  pout[4] = (val >> 3) & 0x1f;

  *in = pin + 1;
  *out = pout + 5;
}

void Simple9::unpack4_7(uint32_t **out,
                        const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 21) & 0x7f;
  pout[1] = (val >> 14) & 0x7f;
  pout[2] = (val >> 7) & 0x7f;
  pout[3] = val & 0x7f;

  *in = pin + 1;
  *out = pout + 4;
}

void Simple9::unpack3_9(uint32_t **out,
                        const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 19) & 0x01ff;
  pout[1] = (val >> 10) & 0x01ff;
  pout[2] = (val >> 1) & 0x01ff;

  *in = pin + 1;
  *out = pout + 3;
}

void Simple9::unpack2_14(uint32_t **out,
                         const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = (val >> 14) & 0x3fff;
  pout[1] = val & 0x3fff;

  *in = pin + 1;
  *out = pout + 2;
}

void Simple9::unpack1_28(uint32_t **out,
                         const uint32_t **in) {
  uint32_t *pout = *out;
  const uint32_t *pin = *in;

  uint32_t val = BYTEORDER_FREE_LOAD32(pin);

  pout[0] = val & 0x0fffffff;

  *in = pin + 1;
  *out = pout + 1;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
