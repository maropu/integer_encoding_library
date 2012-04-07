/*-----------------------------------------------------------------------------
 *  xxx_common.hpp - A header for shared stuffs
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

#ifndef __XXX_COMMON_HPP__
#define __XXX_COMMON_HPP__

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <iomanip>

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "misc/err_utils.hpp"

/* Configurable parameters */
#define MAXLEN          200000000

/* For debugs */
#if !defined(NDEBUG) && defined(__linux__)
 #define MALLOC_CHECK   2
#endif

/* Keywords for compiler optimization */
#ifndef __NOCOMPILER_OPT__
 #define __no_aliases__         __restrict__
 #define __likely(x)            __builtin_expect(!!(x), 1)
 #define __unlikely(x)          __builtin_expect(!!(x), 0)
#else
 #define __no_aliases__
 #define __likely(x)            (x) 
 #define __unlikely(x)          (x) 
#endif /* __NOCOMPILER_OPT__ */

/* Utility inline functions below */
#define __log2_uint32(v)        \
        ({                      \
                uint32_t d;     \
                __asm__("bsr %1, %0;" :"=r"(d) :"r"(v));        \
                d;      \
         })

#define __array_size(x)         (sizeof(x) / sizeof(x[0]))

template <class T>
inline void
__init_vector(std::vector<T>& seq, uint64_t len, int iv = 0)
{
        seq.clear();
        seq.reserve(len);

        for (uint64_t i = 0; i < len; i++)
                seq.push_back(static_cast<T>(iv));

        __assert(seq.size() == len);
}

inline int
__get_msb(uint32_t v)
{
        return (v != 0)? __log2_uint32(v) : 0;
}

inline uint32_t
__div_roundup(uint32_t v, uint32_t div)
{
        return (v + (div - 1)) / div;
}

#endif /* __XXX_COMMON_HPP__ */

