/*-----------------------------------------------------------------------------
 *  VSEncodingNaive.hpp - A naive implementation of VSEncoding
 *      This implementation is used by VSE-R.
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

#ifndef __VSENCODINGNAIVE_HPP__
#define __VSENCODINGNAIVE_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "io/BitsReader.hpp"
#include "io/BitsWriter.hpp"

#define VSENAIVE_LOGLEN         3
#define VSENAIVE_LOGLOG         3

#define VSENAIVE_LENS_LEN       (1 << VSENAIVE_LOGLEN)

namespace integer_coding {
namespace compressor {

const uint32_t __vsenaive_possLens[] = {
        1, 2, 4, 6, 8, 16, 32, 64
};

const uint32_t __vsenaive_possLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 20, 32
};

const uint32_t __vsenaive_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t __vsenaive_codeLens[] = {
        0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7
};

const uint32_t __vsenaive_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 13, 13, 13, 14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

class VSEncodingNaive : public CompressorBase {
private:
        std::shared_ptr<VSEncoding>     vdp;

public:
        VSEncodingNaive() : CompressorBase(C_INVALID),
                                vdp(new VSEncoding(&__vsenaive_possLens[0],
                                        NULL, VSENAIVE_LENS_LEN, false)) {}
        ~VSEncodingNaive() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingNaive */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODINGNAIVE_HPP__ */
