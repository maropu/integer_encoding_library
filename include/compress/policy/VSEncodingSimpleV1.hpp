/*-----------------------------------------------------------------------------
 *  VSEncodingSimpleV1.hpp - A encoder/decoder for optimized VSEncoding
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

#ifndef __VSENCODING_SIMPLE_V1_HPP__
#define __VSENCODING_SIMPLE_V1_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

#define VSESIMPLEV1_LOGLEN      4
#define VSESIMPLEV1_LOGLOG      4
#define VSESIMPLEV1_LOGDESC     (VSESIMPLEV1_LOGLEN + VSESIMPLEV1_LOGLOG)

#define VSESIMPLEV1_LENS_LEN    (1 << VSESIMPLEV1_LOGLEN)
#define VSESIMPLEV1_LOGS_LEN    (1 << VSESIMPLEV1_LOGLOG)
#define VSESIMPLEV1_LEN         (1 << VSESIMPLEV1_LOGDESC)

namespace integer_coding {
namespace compressor {

const uint32_t __vsesimplev1_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 32, 64
};

const uint32_t __vsesimplev1_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t __vsesimplev1_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

class VSEncodingSimpleV1 : public CompressorBase {
private:
        std::shared_ptr<VSEncoding>     vdp;

public:
        VSEncodingSimpleV1() : CompressorBase(C_VSEBLOCKS),
                                vdp(new VSEncoding(&__vsesimplev1_possLens[0],
                                        NULL, VSESIMPLEV1_LENS_LEN, true)) {}
        ~VSEncodingSimpleV1() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingSimpleV1 */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODING_SIMPLE_V1_HPP__ */
