/*-----------------------------------------------------------------------------
 *  Simple16.hpp - A encoder/decoder for Simple16
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

#ifndef __SIMPLE16_HPP__
#define __SIMPLE16_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "io/BitsWriter.hpp"

#define SIMPLE16_LOGDESC        4
#define SIMPLE16_LEN            (1 << SIMPLE16_LOGDESC)

namespace integer_coding {
namespace compressor {

class Simple16 : public CompressorBase {
public:
        Simple16() : CompressorBase(C_INVALID) {}
        Simple16(int policy) : CompressorBase(policy) {}
        ~Simple16() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* Simple16 */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __SIMPLE16_HPP__ */
