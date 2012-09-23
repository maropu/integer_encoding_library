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

  /* Decoders for gamma alternatives */
  void ngammaArray(uint32_t *out, uint64_t nvalues);
  void fgammaArray(uint32_t *out, uint64_t nvalues);
  void fugammaArray(uint32_t *out, uint64_t nvalues);

  /* Decoders for delta alternatives */
  void ndeltaArray(uint32_t *out, uint64_t nvalues);
  void fdeltaArray(uint32_t *out, uint64_t nvalues);
  void fudeltaArray(uint32_t *out, uint64_t nvalues);
  void fgdeltaArray(uint32_t *out, uint64_t nvalues);

  /* Decoders for binary interpolative */
  void intrpolatvArray(uint32_t *out,
                       uint32_t nvalues,
                       uint32_t offset,
                       uint32_t low, uint32_t high);

 private:
  friend class VSE_R;

  /* A single value decoder for unary */
  uint32_t read_unary();
  uint32_t read_funary();

  /* A single value decoder for gamma */
  uint32_t read_ngamma();
  uint32_t read_fgamma();
  uint32_t read_fugamma();

  /* A single value decoder for delta */
  uint32_t read_ndelta();
  uint32_t read_fdelta();
  uint32_t read_fudelta();

  /* A single value decoder for binary interpolative */
  uint32_t read_intrpolatv(uint32_t intvl);

  const uint32_t  *in_;
  const uint32_t  *term_;
  uint64_t  buffer_;
  uint32_t  fill_;

  DISALLOW_COPY_AND_ASSIGN(BitsReader);
}; /* BitsReader */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __BITSREADER_HPP__ */
