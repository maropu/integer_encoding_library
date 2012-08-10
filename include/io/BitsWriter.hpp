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

  /* For Unary codes */
  void N_Unary(uint32_t num);

  /* For Delta codes */
  void N_Gamma(uint32_t val);
  uint32_t N_GammaArray(const uint32_t *in,
                        uint64_t len);

  /* For Delta codes */
  uint32_t N_DeltaArray(const uint32_t *in,
                        uint64_t len);

  /*
   * Binary Interpolative code
   * NOTE: This only supports 32-bit length.
   */
  void writeMinimalBinary(uint32_t x, uint32_t b);
  void InterpolativeArray(const uint32_t *in,
                          uint32_t len,
                          uint32_t offset,
                          uint32_t lo, uint32_t hi);

 private:
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
