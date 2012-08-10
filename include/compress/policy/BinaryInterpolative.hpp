/*-----------------------------------------------------------------------------
 *  BinaryInterpolative.hpp - A encoder/decoder for Binary Interpolative
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

#ifndef __BINARYINTERPOLATIVE_HPP__
#define __BINARYINTERPOLATIVE_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <io/BitsReader.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class BinaryInterpolative : public EncodingBase {
 public:
  BinaryInterpolative() : EncodingBase(E_BINARYIPL) {}
  ~BinaryInterpolative() throw() {}

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const {
    /* Write a maximum value in the head of out */
    out[0] = in[len - 1];

    /* Do actual binary interpolative code */
    BitsWriter  wt(out + 1, len - 1);
    wt.InterpolativeArray(in, len, 0, 0, in[len - 1]);
    wt.flush_bits();
    *nvalue = wt.size() + 1;
  }

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const {
    BitsReader  rd(in + 1, len - 1);
    rd.InterpolativeArray(out, nvalue, 0, 0, *in);
  }

  uint64_t inRequire(uint64_t len) const {
    return len;
  }

  /* FIXME: Fill correct required size */
  uint64_t outRequire(uint64_t len) const {
    return len;
  }
}; /* BinaryInterpolative */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __BINARY_INTERPOLATIVE_HPP__ */
