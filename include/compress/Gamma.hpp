/*-----------------------------------------------------------------------------
 *  Gamma.hpp - A encoder/decoder for Gamma.
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

#ifndef GAMMA_HPP
#define GAMMA_HPP

#include "open_coders.hpp"
#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

class Gamma {
        public:
                static void encodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t &nvalue) {
                        BitsWriter *wt = new BitsWriter(out);
                        nvalue = wt->N_GammaArray(in, len);
                        delete wt;
                }

                static void decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue) {
                        BitsReader *rd = new BitsReader(in);
                        rd->N_GammaArray(out, nvalue);
                        delete rd;
                }

                static void FU_decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue) {
                        BitsReader *rd = new BitsReader(in);
                        rd->FU_GammaArray(out, nvalue);
                        delete rd;
                }

                static void F_decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue) {
                        BitsReader *rd = new BitsReader(in);
                        rd->F_GammaArray(out, nvalue);
                        delete rd;
                }
};

#endif /* GAMMA_HPP */
