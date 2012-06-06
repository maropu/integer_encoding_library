/*-----------------------------------------------------------------------------
 *  CompressorBase.hpp - A base class for a series of decoders/encoders
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

#ifndef __COMPRESSORBASE_HPP__
#define __COMPRESSORBASE_HPP__

#include <cstdio>
#include <string>

#include <stdint.h>

namespace integer_coding {
namespace compressor {

#define THROW_COMPRESSOR_EXCEPTION(msg) \
        throw compressor_exception(msg, __FILE__, __func__, __LINE__)

class CompressorBase {
private:
        int     policy;

public:
        CompressorBase(const int id) : policy(id) {}
        virtual ~CompressorBase() throw() {}

        /*
         * FIXME: Is it better to vector<uint32_t> instead
         * of raw heap memory?
         */
        virtual void encodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t& nvalue) const = 0;
        virtual void decodeArray(uint32_t *in, uint32_t len,
                        uint32_t *out, uint32_t nvalue) const = 0;
};

class compressor_exception : public std::exception {
private:
        std::string      msg;

        /* Exception Info. */
        const char      *file;
        const char      *func;
        int             line;

public:
        compressor_exception(const std::string& msg) : msg(msg) {}
        compressor_exception(const std::string& msg, const char *file,
                        const char *func, int line) :
                msg(msg), file(file), func(func), line(line) {}
        ~compressor_exception() throw() {}
        const char *what() const throw() {return msg.c_str();}
};

} /* namespace: compressor */
} /* namespace: integer_coding */

#endif /* __COMPRESSORBASE_HPP__ */
