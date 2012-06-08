/*-----------------------------------------------------------------------------
 *  N_Gamma.hpp - A encoder/decoder for naive Gamma
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

#ifndef __N_GAMMA_HPP__
#define __N_GAMMA_HPP__

#include "xxx_common.hpp"

#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

#include "compress/CompressorBase.hpp"

namespace integer_coding {
namespace compressor {

class N_Gamma : public CompressorBase {
public:
        N_Gamma() : CompressorBase(C_INVALID) {}
        explicit N_Gamma(int policy) : CompressorBase(policy) {}
        ~N_Gamma() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const {
                utility::BitsWriter wt(out);
                nvalue = wt.N_GammaArray(in, len);
        }

        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const {
                utility::BitsReader rd(in);
                rd.N_GammaArray(out, nvalue);
        }
}; /* N_Gamma */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __N_GAMMA_HPP__ */
