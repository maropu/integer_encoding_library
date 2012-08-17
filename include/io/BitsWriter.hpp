/*-----------------------------------------------------------------------------
 *  BitsWriter.hpp - A write interface for a sequence of bits
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

#ifndef __BITSWRITER_HPP__
#define __BITSWRITER_HPP__

#include <misc/encoding_internals.hpp>

namespace integer_encoding {
namespace internals {

class BitsWriter {
 public:
  explicit BitsWriter(uint32_t *out, uint64_t len);
  ~BitsWriter() throw();

  void write_bits(uint32_t val, uint32_t num);
  void flush_bits();

  uint32_t *pos() const;
  uint64_t size() const;

  uint32_t gammaArray(const uint32_t *in,
                      uint64_t len);
  uint32_t deltaArray(const uint32_t *in,
                      uint64_t len);

  /* Binary Interpolative only supports 32-bit */
  void intrpolatvArray(const uint32_t *in,
                       uint32_t len,
                       uint32_t offset,
                       uint32_t low, uint32_t high);

 private:
  void write_unary(uint32_t val);
  void write_gamma(uint32_t val);
  void write_intrpolatv(uint32_t val, uint32_t intvl);

  uint32_t  *out_;
  uint32_t  *term_;
  uint64_t  buffer_;
  uint32_t  fill_;
  uint64_t  nwritten_;

  DISALLOW_COPY_AND_ASSIGN(BitsWriter);
}; /* BitsWriter */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __BITSWRITER_HPP__ */
