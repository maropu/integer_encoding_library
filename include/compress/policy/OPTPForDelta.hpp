/*-----------------------------------------------------------------------------
 *  OPTPForDelta.cpp - A optimized implementation of PForDelta
 *      This implementation made by these authors based on a paper below:
 *       - http://dl.acm.org/citation.cfm?id=1526764
 *      And, some potions fo this code are optimized by means of a code given
 *      by Shuai Ding, who is of original authors proposing OPTPForDelta.
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

#ifndef __OPTPFORDELTA_HPP__
#define __OPTPFORDELTA_HPP__

#include <misc/encoding_internals.hpp>
#include <compress/policy/PForDelta.hpp>

namespace integer_encoding {
namespace internals {

class OPTPForDelta : public PForDelta {
 public:
  OPTPForDelta();
  ~OPTPForDelta() throw();

  uint64_t require(uint64_t len) const;

 private:
  /*
   * Two functions below are intended to
   * be overloaded in OPTPForDelta.
   */
  uint32_t tryB(uint32_t b,
                const uint32_t *in,
                uint64_t len) const;
  uint32_t findBestB(const uint32_t *in,
                     uint64_t len) const;
}; /* OPTPForDelta */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __OPTPFORDELTA_HPP__ */
