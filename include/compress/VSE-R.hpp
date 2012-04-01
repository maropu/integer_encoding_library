/*-----------------------------------------------------------------------------
 *  VSE-R.hpp - A encoder/decoder for a other version of VSEncoding
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

#ifndef __VSE_R_HPP__
#define __VSE_R_HPP__

#include "xxx_common.hpp"

#include "compress/Delta.hpp"
#include "compress/VSEncoding.hpp"
#include "compress/VSEncodingNaive.hpp"
#include "io/BitsReader.hpp"
#include "io/BitsWriter.hpp"

namespace opc {

class VSE_R {
public:
        static void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue);
        static void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue);
}; /* VSE_R */

}; /* namespace: opc */

#endif /* __VSE_R_HPP__ */
