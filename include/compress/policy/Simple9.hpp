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

const size_t SIMPLE9_LOGDESC = 4;
const size_t SIMPLE9_LEN = (1U << SIMPLE9_LOGDESC);

/* A interface of unpacking functions above */
typedef void (*simple9_unpacker_t)(uint32_t **out,
                                   const uint32_t **in);

class Simple9 : public EncodingBase {
 public:
  Simple9();
  explicit Simple9(int policy);

  ~Simple9() throw();

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  uint64_t require(uint64_t len) const;

 protected:
  /* Check whether a word can pack values */
  static bool try_pack(const uint32_t *in,
                       uint32_t len,
                       uint32_t num1, uint32_t log1);

  /* A series of integer unpackers */
  static void unpack28_1(uint32_t **out,
                         const uint32_t **in);
  static void unpack14_2(uint32_t **out,
                         const uint32_t **in);
  static void unpack9_3(uint32_t **out,
                        const uint32_t **in);
  static void unpack7_4(uint32_t **out,
                        const uint32_t **in);
  static void unpack5_5(uint32_t **out,
                        const uint32_t **in);
  static void unpack4_7(uint32_t **out,
                        const uint32_t **in);
  static void unpack3_9(uint32_t **out,
                        const uint32_t **in);
  static void unpack2_14(uint32_t **out,
                         const uint32_t **in);
  static void unpack1_28(uint32_t **out,
                         const uint32_t **in);

 protected:
  simple9_unpacker_t unpack_[SIMPLE9_LEN];
}; /* Simple9 */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __SIMPLE9_HPP__ */
