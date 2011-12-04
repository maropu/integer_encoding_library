/*-----------------------------------------------------------------------------
 *  open_coders.hpp - A header for global variables, or something.
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

#ifndef INTEGER_CODERS_HPP
#define INTEGER_CODERS_HPP

#define __STDC_LIMIT_MACROS

#include <cstdio>
#include <string>
#include <cstring>
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
#include <boost/shared_ptr.hpp>

#include "utils/err_utils.hpp"
#include "utils/int_utils.hpp"

/* Configure parameters */
#define MAXLEN          200000000
#define SKIP            32

/* Magic numbers */
#define MAGIC_NUM       0x0f823cb3
#define VMAJOR          0
#define VMINOR          1

/* A extension for a location file */
#define TOCEXT          ".TOC"
#define DECEXT          ".DEC"
#define NFILENAME       256
#define NEXTNAME        32

/*
 * FIXME: Some encoders might overrun the length of given
 * memory. This makes a code simple but unobvious, so we
 * need to remove it.
 */
#define TAIL_MERGIN     128

/*
 * Macros for reading files. A header for each compressed list
 * is composed of three etnries: the total of integers, a first
 * integer, and the next posision of a list.
 */
#define NUM_EACH_HEADER_TOC     3
#define __next_read(addr, len)  addr[len++]
#define __next_pos(addr, len)   addr[len + NUM_EACH_HEADER_TOC - 1]

#if HAVE_DECL_POSIX_FADVISE && defined(HAVE_POSIX_FADVISE)
 #define __fadvise_sequential(fd, len)   \
        posix_fadvise(fd, 0, len, POSIX_FADV_SEQUENTIAL)
#else
 #define __fadvise_sequential(fd, len)
#endif

/* For debugs */
#if defined(DEBUG) && defined(__linux__)
 #define MALLOC_CHECK   2
#endif

/* Keywords for compiler optimization */
#define __compiler_opt__

#ifdef __compiler_opt__
 #define __no_aliases__         __restrict__
 #define __likely(x)            __builtin_expect(!!(x), 1)
 #define __unlikely(x)          __builtin_expect(!!(x), 0)
#else
 #define __no_aliases__
 #define __likely(x)            (x) 
 #define __unlikely(x)          (x) 
#endif /* __compiler_opt__ */

#endif /* INTEGER_CODERS_HPP */
