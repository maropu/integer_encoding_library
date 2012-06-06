/*-----------------------------------------------------------------------------
 *  VSE-R.hpp - A encoder/decoder for a other version of VSEncoding
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

#ifndef __VSE_R_HPP__
#define __VSE_R_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/policy/F_Delta.hpp"
#include "compress/policy/VSEncoding.hpp"
#include "compress/policy/VSEncodingNaive.hpp"
#include "io/BitsReader.hpp"
#include "io/BitsWriter.hpp"

#define VSER_LOGS_LEN   32

namespace integer_coding {
namespace compressor {

class VSE_R : public CompressorBase {
private:
        std::shared_ptr<uint32_t>    wmem_outs;

public:
        VSE_R() : CompressorBase(C_VSER),
                        wmem_outs(new uint32_t[MAXLEN + 128],
                                std::default_delete<uint32_t[]>()) {}
        ~VSE_R() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* VSE_R */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __VSE_R_HPP__ */
