/*-----------------------------------------------------------------------------
 *  integer_encoding.hpp - A header for encoder/decoder collections
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

#ifndef __INTEGER_ENCODING_HPP__
#define __INTEGER_ENCODING_HPP__

#include <misc/encoding_internals.hpp>

/* Implemented encoders/decoders */
#include <compress/EncodingBase.hpp>
#include <compress/policy/N_Gamma.hpp>
#include <compress/policy/FU_Gamma.hpp>
#include <compress/policy/F_Gamma.hpp>
#include <compress/policy/N_Delta.hpp>
#include <compress/policy/FU_Delta.hpp>
#include <compress/policy/FG_Delta.hpp>
#include <compress/policy/F_Delta.hpp>
#include <compress/policy/VariableByte.hpp>
#include <compress/policy/BinaryInterpolative.hpp>
#include <compress/policy/Simple9.hpp>
#include <compress/policy/Simple16.hpp>
#include <compress/policy/PForDelta.hpp>
#include <compress/policy/OPTPForDelta.hpp>
#include <compress/policy/VSEncodingBlocks.hpp>
#include <compress/policy/VSE-R.hpp>
#include <compress/policy/VSEncodingRest.hpp>
#include <compress/policy/VSEncodingBlocksHybrid.hpp>
#include <compress/policy/VSEncodingSimple.hpp>

namespace integer_encoding {

class EncodingFactory {
 public:
  static EncodingPtr create(const int policy);
};

} /* namespace: integer_encoding */

#endif /* __INTEGER_ENCODING_HPP__ */
