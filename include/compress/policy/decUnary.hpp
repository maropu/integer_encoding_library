/*-----------------------------------------------------------------------------
 *  decUnary.hpp - A transformation table for Unary codes
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

#ifndef __DECUNARY_HPP__
#define __DECUNARY_HPP__

#include <stdint.h>

namespace integer_encoding {
namespace internals {
extern uint16_t decUnary[1 << 16];
} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __DECUNARY_HPP__ */
