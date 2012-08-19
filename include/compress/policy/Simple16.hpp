/*-----------------------------------------------------------------------------
 *  Simple16.hpp - A encoder/decoder for Simple16
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

#ifndef __SIMPLE16_HPP__
#define __SIMPLE16_HPP__

#include <compress/policy/Simple9.hpp>

namespace integer_encoding {
namespace internals {

class Simple16 : public Simple9 {
 public:
  Simple16();
  ~Simple16() throw();

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

 private:
  /* Check whether a word can pack values */
  static bool try_pack(const uint32_t *in,
                       uint32_t len,
                       uint32_t num1, uint32_t log1,
                       uint32_t num2, uint32_t log2);

  static bool try_pack(const uint32_t *in,
                       uint32_t len,
                       uint32_t num1, uint32_t log1,
                       uint32_t num2, uint32_t log2,
                       uint32_t num3, uint32_t log3);

  /* A series of integer unpackers */
  static void unpack7_2_14_1(uint32_t **out,
                             const uint32_t **in);
  static void unpack7_1_7_2_7_1(uint32_t **out,
                                const uint32_t **in);
  static void unpack14_1_7_2(uint32_t **out,
                             const uint32_t **in);
  static void unpack1_4_8_3(uint32_t **out,
                            const uint32_t **in);
  static void unpack1_3_4_4_3_3(uint32_t **out,
                                const uint32_t **in);
  static void unpack4_5_2_4(uint32_t **out,
                            const uint32_t **in);
  static void unpack2_4_4_5(uint32_t **out,
                            const uint32_t **in);
  static void unpack3_6_2_5(uint32_t **out,
                            const uint32_t **in);
  static void unpack2_5_3_6(uint32_t **out,
                            const uint32_t **in);
  static void unpack1_10_2_9(uint32_t **out,
                             const uint32_t **in);
}; /* Simple16 */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __SIMPLE16_HPP__ */
