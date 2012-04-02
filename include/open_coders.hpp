/*-----------------------------------------------------------------------------
 *  open_coders.hpp - A header for global variables, or something
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

#ifndef __INTEGER_CODERS_HPP__
#define __INTEGER_CODERS_HPP__

#define __STDC_LIMIT_MACROS

#include <stdint.h>

#include "encoders.hpp"
#include "decoders.hpp"

/* Support for over 4GiB files on 32-bit platform */
//#define MAP_HUGETLB             1

#if __i386__
 #define LARGEFILE64_SOURCE     1
 #define FILE_OFFSET_BITS       64
#endif

/*
 * NOTE: Some decoders are intended to overrun
 * these tails of given memory for performance reasons.
 */
#define OUTPUTMEM(len)          ((len) + 128)

#endif /* __INTEGER_CODERS_HPP__ */
