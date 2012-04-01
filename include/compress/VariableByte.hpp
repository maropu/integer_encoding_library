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

#include "xxx_common.hpp"

#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

namespace opc {

class VariableByte {
public:
        static void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue);
        static void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue);
}; /* VariableByte */

}; /* namespace: opc */

#endif /* __VARIABLEBYTE_HPP__ */
