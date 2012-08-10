/*-----------------------------------------------------------------------------
 *  BitsWriter.cpp - A code to write compressed data during encoding
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

#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

BitsWriter::BitsWriter(uint32_t *out,
                       uint64_t len)
  : out_(out),
    term_(out + len),
    buffer_(0),
    fill_(0),
    nwritten_(0) {
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: out");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(out, len);
}

BitsWriter::~BitsWriter() throw() {}

void BitsWriter::write_bits(uint32_t val,
                            uint32_t num) {
  ASSERT(out_ != NULL);
  ASSERT(out_ < term_);
  ASSERT(num <= 32);

  if (out_ >= term_ && num > 0) 
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  if (LIKELY(num > 0)) {
    buffer_ = (buffer_ << num) | (val & ((1ULL << num) - 1));
    fill_ += num;

    if (fill_ >= 32) {
      BYTEORDER_FREE_STORE32(
          out_, (buffer_ >> (fill_ - 32)) & ((1ULL << 32) - 1));
      out_++, nwritten_++, fill_ -= 32;
      if (out_ >= term_&& fill_ > 0)
        THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");
    }
  } 
}

void BitsWriter::flush_bits() {
  if (out_ >= term_ && fill_ > 0) 
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

  ASSERT(out_ != NULL);

  if (fill_ > 0) {
    BYTEORDER_FREE_STORE32(
      out_, buffer_ << (32 - fill_) & ((1ULL << 32) - 1));
    out_++, nwritten_++;
    buffer_ = 0, fill_ = 0;
  }
}

uint32_t *BitsWriter::pos() const {
  ASSERT(out_ != NULL);
  return out_;
}

uint64_t BitsWriter::size() const {
  return nwritten_;
}

void BitsWriter::N_Unary(uint32_t num) {
  write_bits(0, num);
  write_bits(1, 1);
}

void BitsWriter::N_Gamma(uint32_t val) {
  if (val == UINT32_MAX)
    THROW_ENCODING_EXCEPTION("Invalid value: val");

  uint32_t d = 31 - MSB32(val + 1);
  N_Unary(d);
  write_bits(val + 1, d);
}

uint32_t BitsWriter::N_GammaArray(const uint32_t *in,
                                  uint64_t len) {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(in, len);

  for (uint64_t i = 0;
       i < len && out_ < term_; i++) {
    uint32_t d = 31 - MSB32(in[i] + 1);
    N_Unary(d);
    write_bits(in[i] + 1, d);
  }

  flush_bits();
  return nwritten_;
}

uint32_t BitsWriter::N_DeltaArray(const uint32_t *in,
                                  uint64_t len) {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(in, len);

  for (uint64_t i = 0;
       i < len && out_ < term_; i++) {
    uint32_t d = 31 - MSB32(in[i] + 1);
    N_Gamma(d);
    write_bits(in[i] + 1, d);
  }

  flush_bits();
  return nwritten_;
}

void BitsWriter::writeMinimalBinary(uint32_t x,
                                    uint32_t b) {
  ASSERT(out_ != NULL);

  int d = 31 - MSB32(b);
  uint32_t m = (1ULL << (d + 1)) - b;

  if (x < m)
    write_bits(x, d);
  else
    write_bits(x + m, d + 1);
}

void BitsWriter::InterpolativeArray(const uint32_t *in,
                                    uint32_t len,
                                    uint32_t offset,
                                    uint32_t lo,
                                    uint32_t hi) {
  if (len == 0)
    return;

  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (out_ >= term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");
  if (lo > hi)
    THROW_ENCODING_EXCEPTION("Invalid equality: lo > hi");

  ASSERT_ADDR(in, len);

  if (len == 1) {
    writeMinimalBinary(in[offset] - lo, hi - lo + 1);
    return;
  }

  uint32_t h = len / 2;
  uint32_t m = in[offset + h];

  writeMinimalBinary(m - (lo + h),
                     hi - len + h + 1 - (lo + h) + 1);
  InterpolativeArray(in, h, offset, lo, m - 1);
  InterpolativeArray(in, len - h - 1,
                     offset + h + 1, m + 1, hi);
}

} /* namespace: internals */
} /* namespace: integer_encoding */
