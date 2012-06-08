/*-----------------------------------------------------------------------------
 *  PForDelta.hpp - A encoder/decoder for PForDelta
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

#ifndef __PFORDELTA_HPP__
#define __PFORDELTA_HPP__

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "compress/CompressorBase.hpp"
#include "compress/policy/Simple16.hpp"
#include "io/BitsWriter.hpp"

/* FIXME: There is a bug with 128 of PFORDELTA_BLOCKSZ */
#define PFORDELTA_NBLOCK        1
#define PFORDELTA_BLOCKSZ       (32 * PFORDELTA_NBLOCK)

#define PFORDELTA_RATIO         0.1

/*
 * Lemme resume the block's format here.
 *
 *      |--------------------------------------------------|
 *      |       b | nExceptions | s16encodedExceptionSize  |
 *      |  6 bits |   10 bits   |         16 bits          |
 *      |--------------------------------------------------|
 *      |              fixed_b(codewords)                  |
 *      |--------------------------------------------------|
 *      |                s16(exceptions)                   |
 *      |--------------------------------------------------|
 *
 */
#define PFORDELTA_B             6
#define PFORDELTA_NEXCEPT       10
#define PFORDELTA_EXCEPTSZ      16

namespace integer_coding {
namespace compressor {

class PForDelta : public CompressorBase {
protected:
        virtual uint32_t tryB(uint32_t b, uint32_t *in,
                        uint32_t len) const;
        virtual uint32_t findBestB(uint32_t *in, uint32_t len) const;

        void encodeBlock(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;

public:
        PForDelta() : CompressorBase(C_INVALID) {}
        PForDelta(int policy) : CompressorBase(policy) {}
        virtual ~PForDelta() throw() {}

        virtual void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t &nvalue) const;
        virtual void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const;
}; /* PForDelta */

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __PFORDELTA_HPP__ */
