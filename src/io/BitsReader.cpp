/*-----------------------------------------------------------------------------
 *  BitsReader.cpp - A code to read compressed data for decoding
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

#include <io/BitsReader.hpp>

namespace integer_encoding {
namespace internals {

namespace {

#define BITSRD_BUFFILL(__cond__)  \
  ASSERT(__cond__ <= 32); \
  ASSERT(in_ != NULL);    \
  if (fill_ < __cond__) { \
    buffer_ = (buffer_ << 32) | BYTEORDER_FREE_LOAD32(in_); \
    in_++, fill_ += 32;         \
    if (UNLIKELY(in_ > term_))  \
      THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");  \
  }

const uint32_t F_MASK32 = 0xffff;

}; /* namespace: */

BitsReader::BitsReader(const uint32_t *in,
                       uint64_t len)
  : in_(in),
    term_(in + len),
    buffer_(0),
    fill_(0) {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(in, len);
}

BitsReader::~BitsReader() throw() {}

uint32_t BitsReader::read_bits(uint32_t num) {
  if (UNLIKELY(num == 0))
    return 0;
  ASSERT(num <= 32);
  BITSRD_BUFFILL(num);
  fill_ -= num;
  return (buffer_ >> fill_) & ((1ULL << num) - 1);
}

const uint32_t *BitsReader::pos() const {
  ASSERT(in_ != NULL);
  return in_ - 1;
}

uint32_t BitsReader::N_Unary() {
  uint32_t count = 0;
  while (read_bits(1) == 0)
    count++;
  return count;
}

uint32_t BitsReader::F_Unary() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decUnary[idx];

    ASSERT(dec <= 16);

    if (UNLIKELY(dec == 16)) {
      fill_ -= 16;
      return F_Unary() + dec;
    }

    fill_ -= dec + 1;
    return dec;
  }

  return N_Unary();
}

uint32_t BitsReader::N_Gamma() {
  uint32_t count = N_Unary();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

uint32_t BitsReader::F_Gamma() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decGamma[idx];

    if (UNLIKELY(dec == 0))
      return N_Gamma();

    fill_ -= (dec >> 16);
    return (dec & F_MASK32) - 1;
  }

  return N_Gamma();
}

uint32_t BitsReader::FU_Gamma() {
  uint32_t count = F_Unary();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

void BitsReader::N_GammaArray(uint32_t *out,
                              uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = N_Gamma();
}

void BitsReader::F_GammaArray(uint32_t *out,
                              uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = F_Gamma();
}

void BitsReader::FU_GammaArray(uint32_t *out,
                               uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = FU_Gamma();
}

uint32_t BitsReader::N_Delta() {
  uint32_t count = N_Gamma();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

uint32_t BitsReader::F_Delta() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decDelta[idx];

    if (UNLIKELY(dec == 0))
      return N_Delta();

    fill_ -= (dec >> 16);
    return (dec & ((1ULL << 16) - 1)) - 1;
  }

  return N_Delta();
}

uint32_t BitsReader::FU_Delta() {
  uint32_t count = F_Unary();
  ASSERT(count < 6);
  uint32_t log = ((1U << count) | read_bits(count)) - 1;
  ASSERT(log < 32);
  return ((1U << log) | read_bits(log)) - 1;
}

void BitsReader::N_DeltaArray(uint32_t *out,
                              uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = N_Delta();
}

void BitsReader::FU_DeltaArray(uint32_t *out,
                               uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = FU_Delta();
}

void BitsReader::FG_DeltaArray(uint32_t *out,
                               uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++) {
    uint32_t count = F_Gamma();
    ASSERT(count < 32);
    out[i] = ((1U << count) | read_bits(count)) - 1;
  }
}

void BitsReader::F_DeltaArray(uint32_t *out,
                              uint64_t nvalues) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (nvalues == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: nvalues");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT_ADDR(out, nvalues);

  for (uint64_t i = 0;
       i < nvalues && in_ <= term_; i++)
    out[i] = F_Delta();
}

uint32_t BitsReader::readMinimalBinary(uint32_t b) {
  ASSERT(1 <= b);
  uint32_t d = 31 - MSB32(b);
  uint32_t m = (1ULL << (d + 1)) - b;
  uint32_t x = read_bits(d);
  if (x < m)
    return x;
  return (x << 1) + read_bits(1) - m;
}

void BitsReader::InterpolativeArray(uint32_t *out,
                                    uint32_t nvalues,
                                    uint32_t offset,
                                    uint32_t lo,
                                    uint32_t hi) {
  if (UNLIKELY(nvalues == 0))
    return;

  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");
  if (lo > hi)
    THROW_ENCODING_EXCEPTION("Invalid equality: lo > hi");

  ASSERT_ADDR(out, nvalues);

  if (UNLIKELY(nvalues == 1)) {
    out[offset] = readMinimalBinary(hi - lo + 1) + lo;
    return;
  }

  uint32_t h = nvalues >> 1;
  uint32_t m = readMinimalBinary(
      hi - nvalues + h + 1 - (lo + h) + 1) + lo + h;

  out[offset + h] = m;
  InterpolativeArray(out, h, offset, lo, m - 1);
  InterpolativeArray(out, nvalues - h - 1,
  offset + h + 1, m + 1, hi);
}

} /* namespace: internals */
} /* namespace: integer_encoding */
