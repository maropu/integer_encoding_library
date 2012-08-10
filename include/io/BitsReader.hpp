/*-----------------------------------------------------------------------------
 *  BitsReader.hpp - A read interface for a sequence of bits
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

#ifndef __BITSREADER_HPP__
#define __BITSREADER_HPP__

#include <misc/encoding_internals.hpp>

/* A transformation table for fast decoding */
#include <compress/policy/decUnary.hpp>
#include <compress/policy/decGamma.hpp>
#include <compress/policy/decDelta.hpp>

namespace integer_encoding {
namespace internals {

class BitsReader {
 public:
  explicit BitsReader(const uint32_t *in,
                      uint64_t len);
  ~BitsReader() throw();
                
  uint32_t read_bits(uint32_t num);
  const uint32_t *pos() const;

  /* Unary code */
  uint32_t N_Unary();
  uint32_t F_Unary();
        
  /* Gamma code */
  void N_GammaArray(uint32_t *out, uint64_t nvalues);
  void F_GammaArray(uint32_t *out, uint64_t nvalues);
  void FU_GammaArray(uint32_t *out, uint64_t nvalues);

  uint32_t N_Gamma();
  uint32_t F_Gamma();
  uint32_t FU_Gamma();

  /* Delta code */
  void N_DeltaArray(uint32_t *out, uint64_t nvalues);
  void FU_DeltaArray(uint32_t *out, uint64_t nvalues);
  void FG_DeltaArray(uint32_t *out, uint64_t nvalues);
  void F_DeltaArray(uint32_t *out, uint64_t nvalues);

  uint32_t N_Delta();
  uint32_t F_Delta();
  uint32_t FU_Delta();

  /*
   * Binary Interpolative code
   * NOTE: This only supports 32-bit length.
   */
  void InterpolativeArray(uint32_t *out,
                          uint32_t nvalues,
                          uint32_t offset,
                          uint32_t lo, uint32_t hi);
  uint32_t readMinimalBinary(uint32_t b);

 private:
  const uint32_t  *in_;
  const uint32_t  *term_;
  uint64_t  buffer_;
  uint32_t  fill_; 

  DISALLOW_COPY_AND_ASSIGN(BitsReader);
}; /* BitsReader */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __BITSREADER_HPP__ */
