/*-----------------------------------------------------------------------------
 *  VSEncodingRest.hpp - A implementation of optimized VSEncoding
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

#ifndef __VSENCODINGREST_HPP__
#define __VSENCODINGREST_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <compress/policy/VSEncodingDP.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class VSEncodingRest : public EncodingBase {
 public:
  VSEncodingRest();
  explicit VSEncodingRest(int policy);

  ~VSEncodingRest() throw();

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  /* FIXME: VSEncodingRest rewrites its own input integers */
  void decodeArray(uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  uint64_t require(uint64_t len) const;

 private:
  std::shared_ptr<VSEncodingDP> vdp_;
}; /* VSEncodingRest */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __VSENCODINGREST_HPP__ */
