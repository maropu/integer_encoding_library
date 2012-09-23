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

#include <integer_encoding.hpp>

namespace integer_encoding {

EncodingPtr EncodingFactory::create(const int policy) {
  switch (policy) {
    case E_N_GAMMA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::N_Gamma()));
      break;
    }

    case E_F_GAMMA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::F_Gamma()));
      break;
    }

    case E_FU_GAMMA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::FU_Gamma()));
      break;
    }

    case E_N_DELTA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::N_Delta()));
      break;
    }

    case E_F_DELTA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::F_Delta()));
      break;
    }

    case E_FU_DELTA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::FU_Delta()));
      break;
    }

    case E_FG_DELTA: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::FG_Delta()));
      break;
    }

    case E_VARIABLEBYTE: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VariableByte()));
      break;
    }

    case E_BINARYIPL: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::BinaryInterpolative()));
      break;
    }

    case E_SIMPLE9: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::Simple9()));
      break;
    }

    case E_SIMPLE16: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::Simple16()));
      break;
    }

    case E_P4D: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::PForDelta()));
      break;
    }

    case E_OPTP4D: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::OPTPForDelta()));
      break;
    }

    case E_VSEBLOCKS: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VSEncodingBlocks()));
      break;
    }

    case E_VSER: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VSE_R()));
      break;
    }

    case E_VSEREST: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VSEncodingRest()));
      break;
    }

    case E_VSEHYB: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VSEncodingBlocksHybrid()));
      break;
    }

    case E_VSESIMPLE: {
      return EncodingPtr(
          static_cast<internals::EncodingBase *>(
              new internals::VSEncodingSimple()));
      break;
    }
  }

  THROW_ENCODING_EXCEPTION("Invalid value: policy");
}

} /* namespace: integer_encoding */
