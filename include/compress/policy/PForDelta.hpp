/*-----------------------------------------------------------------------------
 *  PForDelta.hpp - A encoder/decoder for PForDelta
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

#ifndef __PFORDELTA_HPP__
#define __PFORDELTA_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <compress/policy/Simple16.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

/* FIXME: There is a bug with 128 of PFORDELTA_BLOCKSZ */
const size_t PFORDELTA_NBLOCK = 1;
const size_t PFORDELTA_BLOCKSZ = 32 * PFORDELTA_NBLOCK;

class PForDelta : public EncodingBase {
 public:
  PForDelta();
  explicit PForDelta(int policy);

  ~PForDelta() throw();

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  uint64_t require(uint64_t len) const;

 private:
  void encodeBlock(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

 protected:
  /*
   * Two functions below are intended to
   * be overloaded in OPTPForDelta.
   */
  virtual uint32_t tryB(uint32_t b,
                        const uint32_t *in,
                        uint64_t len) const;
  virtual uint32_t findBestB(const uint32_t *in,
                             uint64_t len) const;

  /* Compress overflowed values */
  Simple16  s16_;

  /* Used during compression phases */
  std::shared_ptr<uint32_t> codewords_;
  std::shared_ptr<uint32_t> exceptionsPositions_;
  std::shared_ptr<uint32_t> exceptionsValues_;
  std::shared_ptr<uint32_t> exceptions_;
  std::shared_ptr<uint32_t> encodedExceptions_;
}; /* PForDelta */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __PFORDELTA_HPP__ */
