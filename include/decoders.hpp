/*-----------------------------------------------------------------------------
 *  decoders.hpp - A header for a variety of decoders
 *
 *  Coding-Style:
 *      emacs) Mode: C, tab-width: 8, c-basic-offset: 8, indent-tabs-mode: nil
 *      vi) tabstop: 8, expandtab
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *-----------------------------------------------------------------------------
 */

#ifndef __DECODERS_HPP__
#define __DECODERS_HPP__

/* Header files for a variety of compressions */
#include "compress/Gamma.hpp"
#include "compress/Delta.hpp"
#include "compress/VariableByte.hpp"
#include "compress/BinaryInterpolative.hpp"
#include "compress/Simple9.hpp"
#include "compress/Simple16.hpp"
#include "compress/PForDelta.hpp"
#include "compress/OPTPForDelta.hpp"
#include "compress/VSEncodingBlocks.hpp"
#include "compress/VSE-R.hpp"
#include "compress/VSEncodingRest.hpp"
#include "compress/VSEncodingBlocksHybrid.hpp"
#include "compress/VSEncodingSimpleV1.hpp"
#include "compress/VSEncodingSimpleV2.hpp"

#define NUMDECODERS     19

/* DecoderID */
#define D_GAMMA         0
#define D_FU_GAMMA      1
#define D_F_GAMMA       2
#define D_DELTA         3
#define D_FU_DELTA      4
#define D_FG_DELTA      5
#define D_F_DELTA       6
#define D_VARIABLEBYTE  7
#define D_BINARYIPL     8
#define D_SIMPLE9       9
#define D_SIMPLE16      10
#define D_P4D           11
#define D_OPTP4D        12
#define D_VSEBLOCKS     13
#define D_VSER          14
#define D_VSEREST       15
#define D_VSEHYB        16
#define D_VSESIMPLEV1   17
#define D_VSESIMPLEV2   18

using namespace opc;

typedef void (*pt2Dec)(uint32_t *, uint32_t, uint32_t *, uint32_t);

static pt2Dec decoders[NUMDECODERS] = {
        Gamma::decodeArray,
        Gamma::FU_decodeArray,
        Gamma::F_decodeArray,
        Delta::decodeArray,
        Delta::FU_decodeArray,
        Delta::FG_decodeArray,
        Delta::F_decodeArray,
        VariableByte::decodeArray,
        BinaryInterpolative::decodeArray,
        Simple9::decodeArray,
        Simple16::decodeArray,
        PForDelta::decodeArray,
        OPTPForDelta::decodeArray,
        VSEncodingBlocks::decodeArray,
        VSE_R::decodeArray,
        VSEncodingRest::decodeArray,
        VSEncodingBlocksHybrid::decodeArray,
        VSEncodingSimpleV1::decodeArray,
        VSEncodingSimpleV2::decodeArray
};

#endif /* __DECODERS_HPP__ */

