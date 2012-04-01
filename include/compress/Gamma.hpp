/*-----------------------------------------------------------------------------
 *  Gamma.hpp - A encoder/decoder for Gamma
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

#ifndef __GAMMA_HPP__
#define __GAMMA_HPP__

#include "xxx_common.hpp"

#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

namespace opc {

class Gamma {
public:
        static void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) {
                BitsWriter wt(out);
                nvalue = wt.N_GammaArray(in, len);
        }

        static void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.N_GammaArray(out, nvalue);
        }

        static void FU_decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.FU_GammaArray(out, nvalue);
        }

        static void F_decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.F_GammaArray(out, nvalue);
        }
}; /* Gamma */

}; /* namespace: opc */

#endif /* __GAMMA_HPP__ */

