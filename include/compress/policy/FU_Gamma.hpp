/*-----------------------------------------------------------------------------
 *  FU_Gamma.hpp - A encoder/decoder for improved Gamma
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

#ifndef __FU_GAMMA_HPP__
#define __FU_GAMMA_HPP__

#include "xxx_common.hpp"

#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

namespace integer_coding {
namespace compressor {

class FU_Gamma : public CompressorBase {
public:
        FU_Gamma() : CompressorBase(C_FU_GAMMA) {}
        ~FU_Gamma() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const {
                utility::BitsWriter wt(out);
                nvalue = wt.N_GammaArray(in, len);
        }

        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const {
                utility::BitsReader rd(in);
                rd.FU_GammaArray(out, nvalue);
        }
}; /* FU_Gamma */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __FU_GAMMA_HPP__ */
