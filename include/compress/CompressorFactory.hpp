/*-----------------------------------------------------------------------------
 *  CompressorFactory.hpp - A factory class for a series of decoders/encoders
 *
 *  Coding-Style
 *      emacs) Mode: C, tab-width: 8, c-basic-offset: 8, indent-tabs-mode: nil
 *      vi) tabstop: 8, expandtab
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *-----------------------------------------------------------------------------
 */

#ifndef __COMPRESSORFACTORY_HPP__
#define __COMPRESSORFACTORY_HPP__

#include <memory>

#include "compress/CompressorBase.hpp"

namespace integer_coding {
namespace compressor {

typedef std::shared_ptr<CompressorBase> CompressorPtr;

class CompressorFactory {
public:
        static CompressorPtr create(const int policy);
};

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __COMPRESSORFACTORY_HPP__ */
