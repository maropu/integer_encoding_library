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
  if (num > 32)
    THROW_ENCODING_EXCEPTION("Out of range exception: num");

  ASSERT(out_ != NULL);

  if (LIKELY(num > 0)) {
    if (out_ >= term_)
      THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");

    buffer_ = (buffer_ << num) |
        (val & ((uint64_t(1) << num) - 1));
    fill_ += num;

    if (fill_ >= 32) {
      BYTEORDER_FREE_STORE32(
          out_, (buffer_ >> (fill_ - 32)) &
                    ((uint64_t(1) << 32) - 1));
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
  ASSERT(fill_ < 32);

  if (fill_ > 0) {
    BYTEORDER_FREE_STORE32(
      out_, buffer_ << (32 - fill_) &
                ((uint64_t(1) << 32) - 1));
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

void BitsWriter::write_unary(uint32_t val) {
  ASSERT(val < 32);
  write_bits(0, val);
  write_bits(1, 1);
}

void BitsWriter::write_gamma(uint32_t val) {
  uint32_t d = 31 - MSB32(val + 1);
  ASSERT(d < 32);
  write_unary(d);
  write_bits(val + 1, d);
}

uint32_t BitsWriter::gammaArray(const uint32_t *in,
                                uint64_t len) {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(in, len);

  for (uint64_t i = 0;
          i < len && out_ < term_; i++)
    write_gamma(in[i]);

  flush_bits();
  return nwritten_;
}

uint32_t BitsWriter::deltaArray(const uint32_t *in,
                                uint64_t len) {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: len");

  ASSERT_ADDR(in, len);

  for (uint64_t i = 0;
           i < len && out_ < term_; i++) {
    uint32_t d = 31 - MSB32(in[i] + 1);
    ASSERT(d < 32);
    write_gamma(d);
    write_bits(in[i] + 1, d);
  }

  flush_bits();
  return nwritten_;
}

void BitsWriter::write_intrpolatv(uint32_t val,
                                  uint32_t intvl) {
  ASSERT(out_ != NULL);

  uint32_t d = 31 - MSB32(intvl);
  uint32_t m = (uint64_t(1) << (d + 1)) - intvl;

  if (val < m)
    write_bits(val, d);
  else
    write_bits(val + m, d + 1);
}

void BitsWriter::intrpolatvArray(const uint32_t *in,
                                 uint32_t len,
                                 uint32_t offset,
                                 uint32_t low,
                                 uint32_t high) {
  if (len == 0)
    return;

  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: in");
  if (out_ >= term_)
    THROW_ENCODING_EXCEPTION("Buffer-overflowed exception");
  if (low > high)
    THROW_ENCODING_EXCEPTION("Invalid equality: low > high");

  ASSERT_ADDR(in, len);

  if (UNLIKELY(len == 1)) {
    write_intrpolatv(in[offset] - low, high - low + 1);
    return;
  }

  uint32_t h = len / 2;
  uint32_t m = in[offset + h];

  write_intrpolatv(m - (low + h),
                   high - len + h + 1 - (low + h) + 1);
  intrpolatvArray(in, h, offset, low, m - 1);
  intrpolatvArray(in, len - h - 1,
                  offset + h + 1, m + 1, high);
}

} /* namespace: internals */
} /* namespace: integer_encoding */
