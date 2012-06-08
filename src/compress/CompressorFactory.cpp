/*-----------------------------------------------------------------------------
 *  CompressorFactory.cpp - A factory class for a series of decoders/encoders
 *
 *  Coding-Style
 *      emacs) Mode: C, tab-width: 8, c-basic-offset: 8, indent-tabs-mode: nil
 *      vi) tabstop: 8, expandtab
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *-----------------------------------------------------------------------------
 */

#include "integer_coding.hpp"

#include "compress/CompressorFactory.hpp"
#include "compress/policy/N_Gamma.hpp"
#include "compress/policy/FU_Gamma.hpp"
#include "compress/policy/F_Gamma.hpp"
#include "compress/policy/N_Delta.hpp"
#include "compress/policy/FU_Delta.hpp"
#include "compress/policy/FG_Delta.hpp"
#include "compress/policy/F_Delta.hpp"
#include "compress/policy/VariableByte.hpp"
#include "compress/policy/BinaryInterpolative.hpp"
#include "compress/policy/Simple9.hpp"
#include "compress/policy/Simple16.hpp"
#include "compress/policy/PForDelta.hpp"
#include "compress/policy/OPTPForDelta.hpp"
#include "compress/policy/VSEncodingBlocks.hpp"
#include "compress/policy/VSE-R.hpp"
#include "compress/policy/VSEncodingRest.hpp"
#include "compress/policy/VSEncodingBlocksHybrid.hpp"
#include "compress/policy/VSEncodingSimpleV1.hpp"
#include "compress/policy/VSEncodingSimpleV2.hpp"

namespace integer_coding {
namespace compressor {

CompressorPtr
CompressorFactory::create(const int policy)
{
        switch (policy) {
        case C_N_GAMMA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new N_Gamma(C_N_GAMMA)));
                break;

        case C_FU_GAMMA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new FU_Gamma(C_FU_GAMMA)));
                break;

        case C_F_GAMMA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new F_Gamma(C_F_GAMMA)));
                break;

        case C_N_DELTA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new N_Delta(C_N_DELTA)));
                break;

        case C_FU_DELTA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new FU_Delta(C_FU_DELTA)));
                break;

        case C_FG_DELTA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new FG_Delta(C_FG_DELTA)));
                break;

        case C_F_DELTA:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new F_Delta(C_F_DELTA)));
                break;

        case C_VARIABLEBYTE:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VariableByte(C_VARIABLEBYTE)));
                break;

        case C_BINARYIPL:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new BinaryInterpolative(C_BINARYIPL)));
                break;

        case C_SIMPLE9:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new Simple9(C_SIMPLE9)));
                break;

        case C_SIMPLE16:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new Simple16(C_SIMPLE16)));
                break;

        case C_P4D:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new PForDelta(C_P4D)));
                break;

        case C_OPTP4D:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new OPTPForDelta(C_OPTP4D)));
                break;

        case C_VSEBLOCKS:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSEncodingBlocks(C_VSEBLOCKS)));
                break;

        case C_VSER:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSE_R(C_VSER)));
                break;

        case C_VSEREST:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSEncodingRest(C_VSEREST)));
                break;

        case C_VSEHYB:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSEncodingBlocksHybrid(C_VSEHYB)));
                break;

        case C_VSESIMPLEV1:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSEncodingSimpleV1(C_VSESIMPLEV1)));
                break;

        case C_VSESIMPLEV2:
                return CompressorPtr(
                                static_cast<CompressorBase *>(
                                        new VSEncodingSimpleV2(C_VSESIMPLEV2)));
                break;

        default:
                break;

        }

        THROW_COMPRESSOR_EXCEPTION("Irregal control path");
};

} /* namespace: compressor */
} /* namespace: integer_coding */
