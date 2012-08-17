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
    ASSERT(__cond__ <= 32);       \
    ASSERT(in_ != NULL);          \
    if (fill_ < __cond__) {       \
      buffer_ = (buffer_ << 32) | BYTEORDER_FREE_LOAD32(in_);     \
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
  return (buffer_ >> fill_) &
      ((uint64_t(1) << num) - 1);
}

const uint32_t *BitsReader::pos() const {
  ASSERT(in_ != NULL);
  return in_ - 1;
}

uint32_t BitsReader::read_unary() {
  uint32_t count = 0;
  while (read_bits(1) == 0)
    count++;
  return count;
}

uint32_t BitsReader::read_funary() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decUnary[idx];

    ASSERT(dec <= 16);

    if (UNLIKELY(dec == 16)) {
      fill_ -= 16;
      return read_funary() + dec;
    }

    fill_ -= dec + 1;
    return dec;
  }

  return read_unary();
}

uint32_t BitsReader::read_ngamma() {
  uint32_t count = read_unary();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

uint32_t BitsReader::read_fgamma() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decGamma[idx];

    if (UNLIKELY(dec == 0))
      return read_ngamma();

    fill_ -= (dec >> 16);
    return (dec & F_MASK32) - 1;
  }

  return read_ngamma();
}

uint32_t BitsReader::read_fugamma() {
  uint32_t count = read_funary();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

void BitsReader::ngammaArray(uint32_t *out,
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
    out[i] = read_ngamma();
}

void BitsReader::fgammaArray(uint32_t *out,
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
    out[i] = read_fgamma();
}

void BitsReader::fugammaArray(uint32_t *out,
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
    out[i] = read_fugamma();
}

uint32_t BitsReader::read_ndelta() {
  uint32_t count = read_ngamma();
  ASSERT(count < 32);
  return ((1U << count) | read_bits(count)) - 1;
}

uint32_t BitsReader::read_fdelta() {
  if (LIKELY(in_ != term_)) {
    BITSRD_BUFFILL(16);
    uint32_t idx = (buffer_ >> (fill_ - 16)) & F_MASK32;
    uint32_t dec = decDelta[idx];

    if (UNLIKELY(dec == 0))
      return read_ndelta();

    fill_ -= (dec >> 16);
    return (dec & ((uint64_t(1) << 16) - 1)) - 1;
  }

  return read_ndelta();
}

uint32_t BitsReader::read_fudelta() {
  uint32_t count = read_funary();
  ASSERT(count < 6);
  uint32_t log = ((1U << count) | read_bits(count)) - 1;
  ASSERT(log < 32);
  return ((1U << log) | read_bits(log)) - 1;
}

void BitsReader::ndeltaArray(uint32_t *out,
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
    out[i] = read_ndelta();
}

void BitsReader::fudeltaArray(uint32_t *out,
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
    out[i] = read_fudelta();
}

void BitsReader::fgdeltaArray(uint32_t *out,
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
    uint32_t count = read_fgamma();
    ASSERT(count < 32);
    out[i] = ((1U << count) | read_bits(count)) - 1;
  }
}

void BitsReader::fdeltaArray(uint32_t *out,
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
    out[i] = read_fdelta();
}

uint32_t BitsReader::read_intrpolatv(uint32_t intvl) {
  ASSERT(1 <= intvl);

  uint32_t d = 31 - MSB32(intvl);
  ASSERT(d < 32);

  uint32_t m = (uint64_t(1) << (d + 1)) - intvl;
  uint32_t x = read_bits(d);

  if (x < m)
    return x;
  return (x << 1) + read_bits(1) - m;
}

void BitsReader::intrpolatvArray(uint32_t *out,
                                 uint32_t nvalues,
                                 uint32_t offset,
                                 uint32_t low,
                                 uint32_t high) {
  if (UNLIKELY(nvalues == 0))
    return;

  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (in_ > term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");
  if (low > high)
    THROW_ENCODING_EXCEPTION("Invalid equality: low > high");

  ASSERT_ADDR(out, nvalues);

  if (UNLIKELY(nvalues == 1)) {
    out[offset] = read_intrpolatv(high - low + 1) + low;
    return;
  }

  uint32_t h = nvalues >> 1;
  uint32_t m = read_intrpolatv(
      high - nvalues + h + 1 - (low + h) + 1) + low + h;

  out[offset + h] = m;
  intrpolatvArray(out, h, offset, low, m - 1);
  intrpolatvArray(out, nvalues - h - 1,
                  offset + h + 1, m + 1, high);
}

} /* namespace: internals */
} /* namespace: integer_encoding */
