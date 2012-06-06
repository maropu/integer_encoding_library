/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks.hpp - A original and simple implementation of VSEncoding
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

#ifndef __VSENCODINGBLOCKS_HPP__
#define __VSENCODINGBLOCKS_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

#define VSEBLOCKS_LOGLEN        4
#define VSEBLOCKS_LOGLOG        4
#define VSEBLOCKS_LOGDESC       (VSEBLOCKS_LOGLEN + VSEBLOCKS_LOGLOG)

#define VSEBLOCKS_LENS_LEN      (1 << VSEBLOCKS_LOGLEN)
#define VSEBLOCKS_LOGS_LEN      (1 << VSEBLOCKS_LOGLOG)

namespace integer_coding {
namespace compressor {

/*
 * There is asymmetry between possible lenghts ofblocks
 * if they are formed by zeros or larger numbers. 
 */
const uint32_t __vseblocks_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

const uint32_t __vseblocks_posszLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 32
};

const uint32_t __vseblocks_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t __vseblocks_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

const uint32_t __vseblocks_possLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 20, 32
};

class VSEncodingBlocks : public CompressorBase {
private:
        std::shared_ptr<VSEncoding>     vdp;

protected:
        std::shared_ptr<uint32_t>       wmem_aux;

        void encodeVS(uint32_t len, uint32_t *in,
                        uint32_t &size, uint32_t *out) const;

        void decodeVS(uint32_t len, uint32_t *in,
                        uint32_t *out, uint32_t *aux) const;

public:
        VSEncodingBlocks() : CompressorBase(C_VSEBLOCKS),
                        vdp(new VSEncoding(&__vseblocks_possLens[0],
                                &__vseblocks_posszLens[0],
                                VSEBLOCKS_LENS_LEN, false)),
                        wmem_aux(new uint32_t[VSENCODING_BLOCKSZ * 2 + 128],
                                std::default_delete<uint32_t[]>()) {}
        VSEncodingBlocks(int policy) : CompressorBase(policy),
                        vdp(new VSEncoding(&__vseblocks_possLens[0],
                                &__vseblocks_posszLens[0],
                                VSEBLOCKS_LENS_LEN, false)),
                        wmem_aux(new uint32_t[VSENCODING_BLOCKSZ * 2 + 128],
                                std::default_delete<uint32_t[]>()) {}
        ~VSEncodingBlocks() throw() {}

        /*
         * It assumes that values start form 0.
         *  - *in: points to the first d-gap to be encoded
         *  - *out: points to the first int that will countain the compress
         * It returns the compress size in number of int   
         *
         * Note: *out must be large enough to contain the compress.
         */
        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;

        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingBlocks */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODINGBLOCKS_HPP__ */
