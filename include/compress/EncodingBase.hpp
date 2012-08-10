/*-----------------------------------------------------------------------------
 *  EncodingBase.hpp - A base class for a series of decoders/encoders
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

#ifndef __ENCODINGBASE_HPP__
#define __ENCODINGBASE_HPP__

#include <cstdint>
#include <memory>

namespace integer_encoding {
namespace internals {

class EncodingBase {
 public:
  explicit EncodingBase(int id)
      : policy_(id) {}
  virtual ~EncodingBase() throw() {}

  virtual void encodeArray(const uint32_t *in,
                           uint64_t len,
                           uint32_t *out,
                           uint64_t *nvalue) const = 0;
  virtual void decodeArray(const uint32_t *in,
                           uint64_t len,
                           uint32_t *out,
                           uint64_t nvalue) const = 0;

  /*
   * NOTE: Get the maximum required size of memory.
   * Some decoders are intended to overrun the tail
   * of given memory for performance reasons.
   */
  virtual uint64_t inRequire(uint64_t len) const = 0;
  virtual uint64_t outRequire(uint64_t len) const = 0;

 private:
  int policy_;

  DISALLOW_COPY_AND_ASSIGN(EncodingBase);
};

} /* namespace: internals */

typedef std::shared_ptr<internals::EncodingBase> EncodingPtr;

} /* namespace: integer_encoding */

#endif /* __ENCODINGBASE_HPP__ */
