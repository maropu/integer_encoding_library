/*-----------------------------------------------------------------------------
 *  Delta.hpp - A encoder/decoder for Delta
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

#ifndef __DELTA_HPP__
#define __DELTA_HPP__

#include "xxx_common.hpp"

#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

namespace opc {

class Delta {
public:
        static void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) {
                BitsWriter wt(out);
                nvalue = wt.N_DeltaArray(in, len);
        }

        static void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.N_DeltaArray(out, nvalue);
        }

        static void FU_decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.FU_DeltaArray(out, nvalue);
        }

        static void FG_decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.FG_DeltaArray(out, nvalue);
        }

        static void F_decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) {
                BitsReader rd(in);
                rd.F_DeltaArray(out, nvalue);
        }
}; /* Delta */

}; /* namespace: opc */

#endif /* __DELTA_HPP__ */

