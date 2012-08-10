/*-----------------------------------------------------------------------------
 *  FU_Gamma.hpp - A encoder/decoder for Gamma alternatives
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

#ifndef __FU_GAMMA_HPP__
#define __FU_GAMMA_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <io/BitsReader.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class FU_Gamma : public EncodingBase {
 public:
  FU_Gamma() : EncodingBase(E_FU_GAMMA) {}
  ~FU_Gamma() throw() {}

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const {
    BitsWriter wt(out, *nvalue);
    *nvalue = wt.N_GammaArray(in, len);
  }

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const {
    BitsReader rd(in, len);
    rd.FU_GammaArray(out, nvalue);
  }

  uint64_t inRequire(uint64_t len) const {
    return len;
  }

  /*
   * NOTE: Gamma codes need 64-bit for
   * UINT32_MAX, so it is (64 * len / 32).
   */
  uint64_t outRequire(uint64_t len) const {
    return (64 * len) >> 5;
  }
}; /* FU_Gamma */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __FU_GAMMA_HPP__ */
