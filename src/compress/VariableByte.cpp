/*-----------------------------------------------------------------------------
 *  VariableByte.cpp - A implementation of VariableByte
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

#include <compress/policy/VariableByte.hpp>

namespace integer_encoding {
namespace internals {

namespace {

#define VBYTE_EXT7BITS(val, num)  \
    ((val >> (7 * num)) & 0x7f)

const uint32_t VBYTE_DESC = 0x80;
const uint32_t VBYTE_DATA = VBYTE_DESC - 1;

} /* namespace: */

void VariableByte::encodeArray(const uint32_t *in,
                               uint64_t len,
                               uint32_t *out,
                               uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  BitsWriter  wt(out, *nvalue);

  for (uint32_t i = 0; i < len; i++) {
    uint32_t nwords = (32 - MSB32(in[i])) / 7;

    switch(nwords) {
      case 0: {
        wt.write_bits(1, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 0), 7);
        break;
      }

      case 1: {
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 0), 7);
        wt.write_bits(1, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 1), 7);
        break;
      }

      case 2: {
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 0), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 1), 7);
        wt.write_bits(1, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 2), 7);
        break;
      }

      case 3: {
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 0), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 1), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 2), 7);
        wt.write_bits(1, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 3), 7);
        break;
      }

      case 4: {
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 0), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 1), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 2), 7);
        wt.write_bits(0, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 3), 7);
        wt.write_bits(1, 1);
        wt.write_bits(VBYTE_EXT7BITS(in[i], 4), 7);
        break;
      }

      default: {
        THROW_ENCODING_EXCEPTION("Out Of Range Exception: nwords");
        break;
      }
    }
  }

  wt.flush_bits();
  *nvalue = wt.size();
}

void VariableByte::decodeArray(const uint32_t *in,
                               uint64_t len,
                               uint32_t *out,
                               uint64_t nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  BitsReader  rd(in, len);

  for (uint32_t i = 0; i < nvalue; i++, out++) {
    if (LIKELY(rd.pos() >= in + len))
      break;

    uint32_t d = rd.read_bits(8);
    *out = d & VBYTE_DATA;

    for (uint32_t j = 1; (d & VBYTE_DESC) == 0; j++) {
      ASSERT(j <= 5);
      d = rd.read_bits(8);
      *out |= (d & VBYTE_DATA) << (7 * j);
    }
  }
}

uint64_t VariableByte::require(uint64_t len) const {
  /* VariableByte needs 40-bit for UINT32_MAX */
  return (40 * len) >> 5;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
