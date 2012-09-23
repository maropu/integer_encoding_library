/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks.hpp - A original and simple implementation of VSEncoding
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

#ifndef __VSENCODINGBLOCKS_HPP__
#define __VSENCODINGBLOCKS_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <compress/policy/VSEncodingDP.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class VSEncodingBlocks : public EncodingBase {
 public:
  VSEncodingBlocks();
  ~VSEncodingBlocks() throw();

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
  void encodeVS(const uint32_t *in,
                uint32_t len,
                uint32_t *out,
                uint32_t *size) const;
  void decodeVS(const uint32_t *in,
                uint32_t len,
                uint32_t *out,
                uint32_t nvalue) const;

  std::shared_ptr<uint32_t>     wmem_;
  std::shared_ptr<VSEncodingDP> vdp_;
}; /* VSEncodingBlocks */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __VSENCODINGBLOCKS_HPP__ */
