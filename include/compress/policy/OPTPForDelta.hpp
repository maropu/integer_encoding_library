/*-----------------------------------------------------------------------------
 *  OPTPForDelta.cpp - A optimized implementation of PForDelta
 *      This implementation made by these authors based on a paper below:
 *       - http://dl.acm.org/citation.cfm?id=1526764
 *      And, some potions fo this code are optimized by means of a code given
 *      by Shuai Ding, who is of original authors proposing OPTPForDelta.
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

#ifndef __OPTPFORDELTAV1_HPP__
#define __OPTPFORDELTAV1_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/Simple16.hpp"
#include "compress/policy/PForDelta.hpp"
#include "io/BitsWriter.hpp"

namespace integer_coding {
namespace compressor {

const uint32_t __optp4delta_possLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 20, 32
};

class OPTPForDelta : public PForDelta {
protected:
        uint32_t tryB(uint32_t b, uint32_t *in,
                        uint32_t len) const;
        uint32_t findBestB(uint32_t *in, uint32_t len) const;

public:
        OPTPForDelta() : PForDelta(C_INVALID) {}
        OPTPForDelta(int policy) : PForDelta(policy) {}
        ~OPTPForDelta() throw() {}

        void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* OPTPForDelta */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __OPTPFORDELTAV1_HPP__ */
