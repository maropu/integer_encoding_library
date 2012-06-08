/*-----------------------------------------------------------------------------
 *  VSEncodingSimpleV2.hpp - A encoder/decoder for optimized VSEncoding
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

#ifndef __VSENCODING_SIMPLE_V2_HPP__
#define __VSENCODING_SIMPLE_V2_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "io/BitsWriter.hpp"

#define VSESIMPLEV2_LOGLEN      8
#define VSESIMPLEV2_LOGLOG      4

#define VSESIMPLEV2_LENS_LEN    (1 << VSESIMPLEV2_LOGLEN)
#define VSESIMPLEV2_LOGS_LEN    (1 << VSESIMPLEV2_LOGLOG)

namespace integer_coding {
namespace compressor {

const uint32_t __vsesimplev2_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
        113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
        161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
        177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
        193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
        209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
        225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
        241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256
};

const uint32_t __vsesimplev2_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t __vsesimplev2_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

class VSEncodingSimpleV2 : public CompressorBase {
private:
        std::shared_ptr<VSEncoding>     vdp;

public:
        VSEncodingSimpleV2() : CompressorBase(C_INVALID),
                                vdp(new VSEncoding(&__vsesimplev2_possLens[0],
                                        NULL, VSESIMPLEV2_LENS_LEN, true)) {}
        VSEncodingSimpleV2(int policy) : CompressorBase(policy),
                                vdp(new VSEncoding(&__vsesimplev2_possLens[0],
                                        NULL, VSESIMPLEV2_LENS_LEN, true)) {}
        ~VSEncodingSimpleV2() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSEncodingSimpleV2 */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSENCODING_SIMPLE_V2_HPP__ */
