/*-----------------------------------------------------------------------------
 *  Simple9.hpp - A encoder/decoder for Simple9
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

#ifndef __SIMPLE9_HPP__
#define __SIMPLE9_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "io/BitsWriter.hpp"

#define SIMPLE9_LOGDESC         4
#define SIMPLE9_LEN             (1 << SIMPLE9_LOGDESC)

namespace integer_coding {
namespace compressor {

class Simple9 : public CompressorBase {
public:
        Simple9() : CompressorBase(C_INVALID) {}
        Simple9(int policy) : CompressorBase(policy) {}
        ~Simple9() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* Simple9 */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __SIMPLE9_HPP__ */
