/*-----------------------------------------------------------------------------
 *  integer_coding.hpp - A header for global variables, or something
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

#ifndef __INTEGER_CODING_HPP__
#define __INTEGER_CODING_HPP__

#define __STDC_LIMIT_MACROS

#include <stdint.h>

#include "compress/CompressorFactory.hpp"

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

#define NUMCODERS       19

/* Coder Type ID */
#define C_INVALID       -1
#define C_N_GAMMA       0
#define C_FU_GAMMA      1
#define C_F_GAMMA       2
#define C_N_DELTA       3
#define C_FU_DELTA      4
#define C_FG_DELTA      5
#define C_F_DELTA       6
#define C_VARIABLEBYTE  7
#define C_BINARYIPL     8
#define C_SIMPLE9       9
#define C_SIMPLE16      10
#define C_P4D           11
#define C_OPTP4D        12
#define C_VSEBLOCKS     13
#define C_VSER          14
#define C_VSEREST       15
#define C_VSEHYB        16
#define C_VSESIMPLEV1   17
#define C_VSESIMPLEV2   18

#endif /* __INTEGER_CODING_HPP__ */
