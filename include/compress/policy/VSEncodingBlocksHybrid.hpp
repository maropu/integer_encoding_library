/*-----------------------------------------------------------------------------
 *  VSEncodiingBlocksHybrid.hpp - A encoder/decoder for hybrid VSEncoding
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

#ifndef __VSENCODINGBLOCKSHYBRID_HPP__
#define __VSENCODINGBLOCKSHYBRID_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/policy/VSEncoding.hpp"
#include "compress/policy/VSEncodingBlocks.hpp"
#include "compress/policy/VSEncodingRest.hpp"

#define VSEHYBRID_THRES         4096

namespace integer_coding {
namespace compressor {

class VSEncodingBlocksHybrid : public VSEncodingBlocks {
public:
        VSEncodingBlocksHybrid() : VSEncodingBlocks(C_INVALID) {}
        explicit VSEncodingBlocksHybrid(int policy) : VSEncodingBlocks(policy) {}
        ~VSEncodingBlocksHybrid() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingBlockHybrid */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODINGBLOCKSHYBRID_HPP__ */
