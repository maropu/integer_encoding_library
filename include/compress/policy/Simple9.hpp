/*-----------------------------------------------------------------------------
 *  Simple9.hpp - A encoder/decoder for Simple9
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

#ifndef __SIMPLE9_HPP__
#define __SIMPLE9_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class Simple9 : public EncodingBase {
 public:
  Simple9() : EncodingBase(E_SIMPLE9) {}
  ~Simple9() throw() {}

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  uint64_t require(uint64_t len) const;
}; /* Simple9 */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __SIMPLE9_HPP__ */
