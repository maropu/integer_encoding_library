/*-----------------------------------------------------------------------------
 *  BinaryInterpolative.hpp - A encoder/decoder for Binary Interpolative.
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

#ifndef BINARYINTERPOLATIVE_HPP
#define BINARYINTERPOLATIVE_HPP

#include "open_coders.hpp"
#include "io/BitsWriter.hpp"
#include "io/BitsReader.hpp"

class BinaryInterpolative {
        public:
                static void encodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t &nvalue) {
                        BitsWriter      *wt;

                        /* Preprocessing for Binary Interpolative */
                        wt = new BitsWriter(out + 1);

                        out[0] = in[len - 1];

                        wt->InterpolativeArray(in, len, 0, 0, in[len - 1]);
                        wt->bit_flush();
                        nvalue = wt->written + 1;

                        delete wt;
                }

                static void decodeArray(uint32_t *in, uint32_t len,
                                uint32_t *out, uint32_t nvalue) {
                        BitsReader      *rd;

                        rd = new BitsReader(in + 1);
                        rd->InterpolativeArray(out, nvalue, 0, 0, *in);

                        delete rd;
                }
};

#endif /* BINARY_INTERPOLATIVE_HPP */
