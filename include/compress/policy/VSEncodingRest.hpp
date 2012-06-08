/*-----------------------------------------------------------------------------
 *  VSEncodingRest.hpp - A encoder/decoder for optimized VSEncoding
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

#ifndef __VSENCODING_REST_HPP__
#define __VSENCODING_REST_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

#define VSEREST_LOGLEN          4
#define VSEREST_LOGLOG          4
#define VSEREST_LOGDESC         (VSEREST_LOGLEN + VSEREST_LOGLOG)

#define VSEREST_LENS_LEN        (1 << VSEREST_LOGLEN)
#define VSEREST_LOGS_LEN        (1 << VSEREST_LOGLOG)
#define VSEREST_LEN             (1 << VSEREST_LOGDESC)

namespace integer_coding {
namespace compressor {

const uint32_t __vserest_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 32, 64
};

const uint32_t __vserest_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t __vserest_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

class VSEncodingRest : public CompressorBase {
private:
        std::shared_ptr<VSEncoding>     vdp;

public:
        VSEncodingRest() : CompressorBase(C_INVALID),
                                vdp(new VSEncoding(&__vserest_possLens[0],
                                        NULL, VSEREST_LENS_LEN, false)) {}
        explicit VSEncodingRest(int policy) : CompressorBase(policy),
                                vdp(new VSEncoding(&__vserest_possLens[0],
                                        NULL, VSEREST_LENS_LEN, false)) {}
        ~VSEncodingRest() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingRest */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODING_REST_HPP__ */
