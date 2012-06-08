/*-----------------------------------------------------------------------------
 *  VariableByte.hpp - A encoder/decoder for VariableByte
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

#ifndef __VARIABLEBYTE_HPP__
#define __VARIABLEBYTE_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

#define VARIABLEBYTE_DESC       0x80
#define VARIABLEBYTE_DATA       (VARIABLEBYTE_DESC - 1)

#define VARIABLEBYTE_EXT7BITS(value, num)         (value >> (7 * num)) & 0x7f

namespace integer_coding {
namespace compressor {

class VariableByte : public CompressorBase {
public:
        VariableByte() : CompressorBase(C_INVALID) {}
        VariableByte(int policy) : CompressorBase(policy) {}
        ~VariableByte() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VariableByte */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VARIABLEBYTE_HPP__ */
