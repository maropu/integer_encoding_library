/*-----------------------------------------------------------------------------
 *  VSEncodingRest.cpp - A optimized implementation of VSEncoding.
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

#include "compress/VSEncodingRest.hpp"

#define VSEREST_LOGLEN          4
#define VSEREST_LOGLOG          4
#define VSEREST_LOGDESC         (VSEREST_LOGLEN + VSEREST_LOGLOG)

#define VSEREST_LENS_LEN        (1 << VSEREST_LOGLEN)
#define VSEREST_LOGS_LEN        (1 << VSEREST_LOGLOG)
#define VSEREST_LEN             (1 << VSEREST_LOGDESC)

/* A set of unpacking functions */

/* --- UNPACK 0 --- */
static inline void __vserest_unpack0_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack0_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 1 --- */
static inline void __vserest_unpack1_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack1_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 2 --- */
static inline void __vserest_unpack2_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack2_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 3 --- */
static inline void __vserest_unpack3_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack3_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 4 --- */
static inline void __vserest_unpack4_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack4_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 5 --- */
static inline void __vserest_unpack5_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack5_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 6 --- */
static inline void __vserest_unpack6_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack6_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 7 --- */
static inline void __vserest_unpack7_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack7_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 8 --- */
static inline void __vserest_unpack8_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack8_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 9 --- */
static inline void __vserest_unpack9_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack9_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 10 --- */
static inline void __vserest_unpack10_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack10_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 11 --- */
static inline void __vserest_unpack11_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack11_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 12 --- */
static inline void __vserest_unpack12_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack12_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 16 --- */
static inline void __vserest_unpack16_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack16_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 20 --- */
static inline void __vserest_unpack20_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack20_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));

/* --- UNPACK 32 --- */
static inline void __vserest_unpack32_1(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_2(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_3(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_4(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_5(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_6(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_7(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_8(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_9(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_10(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_11(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_12(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_14(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_16(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_32(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));
static inline void __vserest_unpack32_64(uint32_t **out, uint32_t **in,
                uint32_t &Fill, uint64_t &buffer) __attribute__((always_inline));


/* A interface of unpacking functions above */
typedef void (*__vserest_unpacker)(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer);

static __vserest_unpacker       __vserest_unpack[VSEREST_LEN] = {
        /* UNPACKER: 0 */
        __vserest_unpack0_1, __vserest_unpack0_2,
        __vserest_unpack0_3, __vserest_unpack0_4,
        __vserest_unpack0_5, __vserest_unpack0_6,
        __vserest_unpack0_7, __vserest_unpack0_8,
        __vserest_unpack0_9, __vserest_unpack0_10,
        __vserest_unpack0_11, __vserest_unpack0_12,
        __vserest_unpack0_14, __vserest_unpack0_16,
        __vserest_unpack0_32, __vserest_unpack0_64,
        /* UNPACKER: 1 */
        __vserest_unpack1_1, __vserest_unpack1_2,
        __vserest_unpack1_3, __vserest_unpack1_4,
        __vserest_unpack1_5, __vserest_unpack1_6,
        __vserest_unpack1_7, __vserest_unpack1_8,
        __vserest_unpack1_9, __vserest_unpack1_10,
        __vserest_unpack1_11, __vserest_unpack1_12,
        __vserest_unpack1_14, __vserest_unpack1_16,
        __vserest_unpack1_32, __vserest_unpack1_64,
        /* UNPACKER: 2 */
        __vserest_unpack2_1, __vserest_unpack2_2,
        __vserest_unpack2_3, __vserest_unpack2_4,
        __vserest_unpack2_5, __vserest_unpack2_6,
        __vserest_unpack2_7, __vserest_unpack2_8,
        __vserest_unpack2_9, __vserest_unpack2_10,
        __vserest_unpack2_11, __vserest_unpack2_12,
        __vserest_unpack2_14, __vserest_unpack2_16,
        __vserest_unpack2_32, __vserest_unpack2_64,
        /* UNPACKER: 3 */
        __vserest_unpack3_1, __vserest_unpack3_2,
        __vserest_unpack3_3, __vserest_unpack3_4,
        __vserest_unpack3_5, __vserest_unpack3_6,
        __vserest_unpack3_7, __vserest_unpack3_8,
        __vserest_unpack3_9, __vserest_unpack3_10,
        __vserest_unpack3_11, __vserest_unpack3_12,
        __vserest_unpack3_14, __vserest_unpack3_16,
        __vserest_unpack3_32, __vserest_unpack3_64,
        /* UNPACKER: 4 */
        __vserest_unpack4_1, __vserest_unpack4_2,
        __vserest_unpack4_3, __vserest_unpack4_4,
        __vserest_unpack4_5, __vserest_unpack4_6,
        __vserest_unpack4_7, __vserest_unpack4_8,
        __vserest_unpack4_9, __vserest_unpack4_10,
        __vserest_unpack4_11, __vserest_unpack4_12,
        __vserest_unpack4_14, __vserest_unpack4_16,
        __vserest_unpack4_32, __vserest_unpack4_64,
        /* UNPACKER: 5 */
        __vserest_unpack5_1, __vserest_unpack5_2,
        __vserest_unpack5_3, __vserest_unpack5_4,
        __vserest_unpack5_5, __vserest_unpack5_6,
        __vserest_unpack5_7, __vserest_unpack5_8,
        __vserest_unpack5_9, __vserest_unpack5_10,
        __vserest_unpack5_11, __vserest_unpack5_12,
        __vserest_unpack5_14, __vserest_unpack5_16,
        __vserest_unpack5_32, __vserest_unpack5_64,
        /* UNPACKER: 6 */
        __vserest_unpack6_1, __vserest_unpack6_2,
        __vserest_unpack6_3, __vserest_unpack6_4,
        __vserest_unpack6_5, __vserest_unpack6_6,
        __vserest_unpack6_7, __vserest_unpack6_8,
        __vserest_unpack6_9, __vserest_unpack6_10,
        __vserest_unpack6_11, __vserest_unpack6_12,
        __vserest_unpack6_14, __vserest_unpack6_16,
        __vserest_unpack6_32, __vserest_unpack6_64,
        /* UNPACKER: 7 */
        __vserest_unpack7_1, __vserest_unpack7_2,
        __vserest_unpack7_3, __vserest_unpack7_4,
        __vserest_unpack7_5, __vserest_unpack7_6,
        __vserest_unpack7_7, __vserest_unpack7_8,
        __vserest_unpack7_9, __vserest_unpack7_10,
        __vserest_unpack7_11, __vserest_unpack7_12,
        __vserest_unpack7_14, __vserest_unpack7_16,
        __vserest_unpack7_32, __vserest_unpack7_64,
        /* UNPACKER: 8 */
        __vserest_unpack8_1, __vserest_unpack8_2,
        __vserest_unpack8_3, __vserest_unpack8_4,
        __vserest_unpack8_5, __vserest_unpack8_6,
        __vserest_unpack8_7, __vserest_unpack8_8,
        __vserest_unpack8_9, __vserest_unpack8_10,
        __vserest_unpack8_11, __vserest_unpack8_12,
        __vserest_unpack8_14, __vserest_unpack8_16,
        __vserest_unpack8_32, __vserest_unpack8_64,
        /* UNPACKER: 9 */
        __vserest_unpack9_1, __vserest_unpack9_2,
        __vserest_unpack9_3, __vserest_unpack9_4,
        __vserest_unpack9_5, __vserest_unpack9_6,
        __vserest_unpack9_7, __vserest_unpack9_8,
        __vserest_unpack9_9, __vserest_unpack9_10,
        __vserest_unpack9_11, __vserest_unpack9_12,
        __vserest_unpack9_14, __vserest_unpack9_16,
        __vserest_unpack9_32, __vserest_unpack9_64,
        /* UNPACKER: 10 */
        __vserest_unpack10_1, __vserest_unpack10_2,
        __vserest_unpack10_3, __vserest_unpack10_4,
        __vserest_unpack10_5, __vserest_unpack10_6,
        __vserest_unpack10_7, __vserest_unpack10_8,
        __vserest_unpack10_9, __vserest_unpack10_10,
        __vserest_unpack10_11, __vserest_unpack10_12,
        __vserest_unpack10_14, __vserest_unpack10_16,
        __vserest_unpack10_32, __vserest_unpack10_64,
        /* UNPACKER: 11 */
        __vserest_unpack11_1, __vserest_unpack11_2,
        __vserest_unpack11_3, __vserest_unpack11_4,
        __vserest_unpack11_5, __vserest_unpack11_6,
        __vserest_unpack11_7, __vserest_unpack11_8,
        __vserest_unpack11_9, __vserest_unpack11_10,
        __vserest_unpack11_11, __vserest_unpack11_12,
        __vserest_unpack11_14, __vserest_unpack11_16,
        __vserest_unpack11_32, __vserest_unpack11_64,
        /* UNPACKER: 12 */
        __vserest_unpack12_1, __vserest_unpack12_2,
        __vserest_unpack12_3, __vserest_unpack12_4,
        __vserest_unpack12_5, __vserest_unpack12_6,
        __vserest_unpack12_7, __vserest_unpack12_8,
        __vserest_unpack12_9, __vserest_unpack12_10,
        __vserest_unpack12_11, __vserest_unpack12_12,
        __vserest_unpack12_14, __vserest_unpack12_16,
        __vserest_unpack12_32, __vserest_unpack12_64,
        /* UNPACKER: 16 */
        __vserest_unpack16_1, __vserest_unpack16_2,
        __vserest_unpack16_3, __vserest_unpack16_4,
        __vserest_unpack16_5, __vserest_unpack16_6,
        __vserest_unpack16_7, __vserest_unpack16_8,
        __vserest_unpack16_9, __vserest_unpack16_10,
        __vserest_unpack16_11, __vserest_unpack16_12,
        __vserest_unpack16_14, __vserest_unpack16_16,
        __vserest_unpack16_32, __vserest_unpack16_64,
        /* UNPACKER: 20 */
        __vserest_unpack20_1, __vserest_unpack20_2,
        __vserest_unpack20_3, __vserest_unpack20_4,
        __vserest_unpack20_5, __vserest_unpack20_6,
        __vserest_unpack20_7, __vserest_unpack20_8,
        __vserest_unpack20_9, __vserest_unpack20_10,
        __vserest_unpack20_11, __vserest_unpack20_12,
        __vserest_unpack20_14, __vserest_unpack20_16,
        __vserest_unpack20_32, __vserest_unpack20_64,
        /* UNPACKER: 32 */
        __vserest_unpack32_1, __vserest_unpack32_2,
        __vserest_unpack32_3, __vserest_unpack32_4,
        __vserest_unpack32_5, __vserest_unpack32_6,
        __vserest_unpack32_7, __vserest_unpack32_8,
        __vserest_unpack32_9, __vserest_unpack32_10,
        __vserest_unpack32_11, __vserest_unpack32_12,
        __vserest_unpack32_14, __vserest_unpack32_16,
        __vserest_unpack32_32, __vserest_unpack32_64,
};

static uint32_t __vserest_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 32, 64
};

static uint32_t __vserest_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

static uint32_t __vserest_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

/* A difinition to harness left padding areas */
static struct {
        int     nPad;
        int     head;
        int     tail;

        struct {
                uint32_t        *pos;
                uint32_t        nleft;
                uint32_t        shift;
        } ent[32];
} __pad_st;

static void __vserest_init_pad(void);
static void __vserest_fill_pad(uint32_t *base,
                uint32_t *len, uint32_t maxB, BitsWriter *wt);
static void __vserest_push_pad(uint32_t nleft, BitsWriter *wt);

#ifdef USE_BOOST_SHAREDPTR
static VSEncodingPtr __vserest =
                VSEncodingPtr(new VSEncoding(&__vserest_possLens[0],
                NULL, VSEREST_LENS_LEN, false));
#else
static VSEncoding *__vserest =
                new VSEncoding(&__vserest_possLens[0],
                NULL, VSEREST_LENS_LEN, false);
#endif /* USE_BOOST_SHAREDPTR */

void
VSEncodingRest::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue)
{
        uint32_t        i;
        uint32_t        j;
        uint32_t        k;
        uint32_t        numBlocks;
        uint32_t        pos;
        uint32_t        maxB;
        uint32_t        *logs;
        uint32_t        *part;
        BitsWriter      *ds_wt;
        BitsWriter      *cd_wt;

        logs = new uint32_t[len];
        if (logs == NULL)
                eoutput("Can't allocate memory");

        /* Initialize the ring buffer */
        __vserest_init_pad();

        /* Compute logs of all numbers */
        for (i = 0; i < len; i++)
                logs[i] = __vserest_remapLogs[1 + int_utils::get_msb(in[i])];

        /* Compute optimal partition */
        part = __vserest->compute_OptPartition(logs, len,
                        VSEREST_LOGLEN + VSEREST_LOGLOG, numBlocks);

    	/* Ready to write descripters for compressed integers */ 
        ds_wt = new BitsWriter(out);
        if (ds_wt == NULL)
                eoutput("Can't initialize a class");

     	/* Write the initial position of compressed integers */
        pos = int_utils::div_roundup(numBlocks, 32 / VSEREST_LOGDESC);
        ds_wt->bit_writer(pos, 32);

    	/* Ready to write actual compressed integers */ 
        cd_wt = new BitsWriter(out + pos + 1);
        if (cd_wt == NULL)
                eoutput("Can't initialize a class");

        /* Write descripters & integers */
        for (i = 0; i < numBlocks; i++) {
                /* Compute max B in the block */
                for (j = part[i], maxB = 0; j < part[i + 1]; j++) {
                        if (maxB < logs[j])
                                maxB = logs[j];
                }

                /* Compute the code for the block length */
                for (k = 0; k < VSEREST_LENS_LEN; k++) {
                        if (part[i + 1] - part[i] == __vserest_possLens[k])
                                break;
                }

                /* A code for a buffering technique to exploit padding areas */
                {
                        uint32_t        offset;

                        offset = part[i + 1] - part[i];

                        /* Fill the buffer */
                        __vserest_fill_pad(&in[part[i]], &offset, maxB, cd_wt);

                        if (part[i] + offset < part[i + 1]) {
                                /* Write integers */
                                for (j = part[i] + offset; j < part[i + 1]; j++)
                                        cd_wt->bit_writer(in[j], maxB);

                                /* Remember the position of padding areas */
                                __vserest_push_pad(
                                        32 - ((part[i + 1] - part[i]) * maxB) % 32, cd_wt);
                        }
                }

                /* Allign to 32-bit */
                cd_wt->bit_flush(); 

                /* Writes the value of B and K */
                ds_wt->bit_writer(__vserest_codeLogs[maxB], VSEREST_LOGLOG);
                ds_wt->bit_writer(k, VSEREST_LOGLEN);
        }

        /* Allign to 32-bit */
        ds_wt->bit_flush(); 

        nvalue = ds_wt->written + cd_wt->written;

        delete ds_wt;
        delete cd_wt;
        delete[] logs;
}

void
__vserest_init_pad(void)
{
        __pad_st.nPad = 0;
        __pad_st.head = 0;
        __pad_st.tail = 0;
}

#define CAN_FILL_PADDING()      (__pad_st.nPad >= 32)
#define CAN_USE_CURBUF(wb)      (wb < __pad_st.ent[__pad_st.head].nleft)
#define USE_CURBUF(wb, wv)      \
        ({                      \
                *(__pad_st.ent[__pad_st.head].pos) |=                   \
                        (wv << __pad_st.ent[__pad_st.head].shift)       \
                        << (__pad_st.ent[__pad_st.head].nleft - wb);    \
                        __pad_st.ent[__pad_st.head].nleft -= wb;        \
\
                __pad_st.nPad -= wb;    \
\
                wb = 0;                 \
         })

#define USE_CURBUF_ROTATE(wb, wv)       \
        ({                              \
                *(__pad_st.ent[__pad_st.head].pos) |=                           \
                        (wv >> (wb - __pad_st.ent[__pad_st.head].nleft))        \
                        << __pad_st.ent[__pad_st.head].shift;                   \
\
                __pad_st.nPad -= __pad_st.ent[__pad_st.head].nleft;             \
\
                wv &= (1ULL << (wb - __pad_st.ent[__pad_st.head].nleft)) - 1;   \
                wb -= __pad_st.ent[__pad_st.head].nleft;                        \
\
                __pad_st.head = (__pad_st.head + 1) % 32;                       \
         })

#define RECYCLE_CURBUF(nleft)   \
        ({                      \
                __pad_st.ent[__pad_st.head].nleft -= nleft;     \
\
                __pad_st.ent[__pad_st.tail].pos =               \
                        __pad_st.ent[__pad_st.head].pos;        \
                __pad_st.ent[__pad_st.tail].nleft = nleft;      \
                __pad_st.ent[__pad_st.tail].shift =             \
                         __pad_st.ent[__pad_st.head].nleft;     \
\
                __pad_st.tail = (__pad_st.tail + 1) % 32;       \
                nleft = 0;      \
         })

#define RECYCLE_CURBUF_ROTATE(nleft)    \
        ({                              \
                __pad_st.ent[__pad_st.tail].pos =               \
                        __pad_st.ent[__pad_st.head].pos;        \
                __pad_st.ent[__pad_st.tail].nleft =             \
                        __pad_st.ent[__pad_st.head].nleft;      \
                __pad_st.ent[__pad_st.tail].shift = 0;          \
                __pad_st.tail = (__pad_st.tail + 1) % 32;       \
\
                nleft -= __pad_st.ent[__pad_st.head].nleft;     \
                __pad_st.head = (__pad_st.head + 1) % 32;       \
         })

void
__vserest_fill_pad(uint32_t *base, uint32_t *len,
                uint32_t maxB, BitsWriter *wt)
{
        uint32_t        length;

        __assert(*len != 0);

        length = *len;
        *len = 0;

        if (CAN_FILL_PADDING()) {
                uint32_t        pos;
                uint32_t        wb;
                uint32_t        wv;

                for (pos = 1; pos <= (32 + maxB - 1) / maxB; pos++)  {
                        wb = (maxB * pos <= 32)? maxB : 32 % maxB;

                        if (pos <= length) {
                                wv = base[pos - 1] >> (maxB - wb);

                                while (wb > 0) {
                                        if (CAN_USE_CURBUF(wb))
                                                USE_CURBUF(wb, wv);
                                        else
                                                USE_CURBUF_ROTATE(wb, wv);
                                 }
                        } else {
                                uint32_t        nleft;

                                nleft = 32 - maxB * (pos - 1);
                                __assert(nleft < 32);

                                while (nleft > 0) {
                                        if (CAN_USE_CURBUF(nleft))
                                                RECYCLE_CURBUF(nleft);
                                        else
                                                RECYCLE_CURBUF_ROTATE(nleft);
                                }

                                goto LOOP_END;
                        }
                }

                if (32 % maxB > 0) {
                        wt->bit_writer(base[(pos - 1) - 1] &
                                ((1ULL << (maxB - 32 % maxB)) - 1),
                                maxB - 32 % maxB);

                        if (pos - 1 == length)
                                __vserest_push_pad(
                                        32 - (length * maxB) % 32, wt);
                }
LOOP_END:
                *len = pos - 1;
        }
}

void
__vserest_push_pad(uint32_t nleft, BitsWriter *wt)
{
        __assert(nleft <= 32);

        if (nleft != 32) {
                __pad_st.nPad += nleft;
                __pad_st.ent[__pad_st.tail].pos = wt->ret_pos();
                __pad_st.ent[__pad_st.tail].nleft = nleft;
                __pad_st.ent[__pad_st.tail].shift = 0;
                __pad_st.tail = (__pad_st.tail + 1) % 32;
        }
}

#define __vserest_bufunfill(in, Fill, buffer)           \
        do {                                            \
                (Fill >= 32)? *(--in) =                 \
                buffer >> (Fill -= 32) : 0;             \
        } while (0)

void
VSEncodingRest::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue)
{
        uint32_t        d;
        uint32_t        *bin;
        uint32_t        *data;
        uint32_t        *end;
        /* To harness the padding areas of each partition */
        uint32_t        Fill;
        uint64_t        buffer;

        Fill = 0;
        buffer = 0;

        bin = in;

        end = bin + len;
        data = bin + *bin + 1;

        do {
                /* Read B and K */
                d = *++bin;

                /* Unpacking integers with a first 8-bit */
                (__vserest_unpack[d >> VSEREST_LOGDESC * 3])(&out, &data, Fill, buffer);

                if (end >= data)
                        __vserest_bufunfill(data, Fill, buffer);
                else
                        break;

                /* Unpacking integers with a second 8-bit */
                (__vserest_unpack[(d >> VSEREST_LOGDESC * 2) &
                         (VSEREST_LEN - 1)])(&out, &data, Fill, buffer);

                if (end >= data)
                        __vserest_bufunfill(data, Fill, buffer);
                else
                        break;

                /* Unpacking integers with a third 8-bit */
                (__vserest_unpack[(d >> VSEREST_LOGDESC * 1) &
                         (VSEREST_LEN - 1)])(&out, &data, Fill, buffer);

                if (end >= data)
                        __vserest_bufunfill(data, Fill, buffer);
                else
                        break;

                /* Unpacking integers with a fourth 8-bit */
                (__vserest_unpack[d & (VSEREST_LEN - 1)])(&out, &data, Fill, buffer);

                if (end >= data)
                        __vserest_bufunfill(data, Fill, buffer);
                else
                        break;
        } while (1);
}

/* --- Intra functions below --- */

/* --- UNPACK 0 --- */
void
__vserest_unpack0_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        (*out)[0] = 0;
        *out += 1;
}

void
__vserest_unpack0_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                ::"memory", "%xmm0");

        *out += 2;
}

void
__vserest_unpack0_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                ::"memory", "%xmm0");

        *out += 3;
}

void
__vserest_unpack0_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                ::"memory", "%xmm0");

        *out += 4;
}

void
__vserest_unpack0_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                ::"memory", "%xmm0");

        *out += 5;
}

void
__vserest_unpack0_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                ::"memory", "%xmm0");

        *out += 6;
}

void
__vserest_unpack0_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                ::"memory", "%xmm0");

        *out += 7;
}

void
__vserest_unpack0_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                ::"memory", "%xmm0");

        *out += 8;
}

void
__vserest_unpack0_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                ::"memory", "%xmm0");

        *out += 9;
}

void
__vserest_unpack0_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                ::"memory", "%xmm0");

        *out += 10;
}

void
__vserest_unpack0_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                ::"memory", "%xmm0");

        *out += 11;
}

void
__vserest_unpack0_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                ::"memory", "%xmm0");

        *out += 12;
}

void
__vserest_unpack0_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                "movdqu %%xmm0, %3\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12])
                ::"memory", "%xmm0");

        *out += 14;
}

void
__vserest_unpack0_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                "movdqu %%xmm0, %3\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12])
                ::"memory", "%xmm0");

        *out += 16;
}

void
__vserest_unpack0_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                "movdqu %%xmm0, %3\n\t"
                "movdqu %%xmm0, %4\n\t"
                "movdqu %%xmm0, %5\n\t"
                "movdqu %%xmm0, %6\n\t"
                "movdqu %%xmm0, %7\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12]),
                        "=m" ((*out)[16]), "=m" ((*out)[20]), "=m" ((*out)[24]), "=m" ((*out)[28])
                ::"memory", "%xmm0");

        *out += 32;
}

void
__vserest_unpack0_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "pxor   %%xmm0, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm0, %1\n\t"
                "movdqu %%xmm0, %2\n\t"
                "movdqu %%xmm0, %3\n\t"
                "movdqu %%xmm0, %4\n\t"
                "movdqu %%xmm0, %5\n\t"
                "movdqu %%xmm0, %6\n\t"
                "movdqu %%xmm0, %7\n\t"
                "movdqu %%xmm0, %8\n\t"
                "movdqu %%xmm0, %9\n\t"
                "movdqu %%xmm0, %10\n\t"
                "movdqu %%xmm0, %11\n\t"
                "movdqu %%xmm0, %12\n\t"
                "movdqu %%xmm0, %13\n\t"
                "movdqu %%xmm0, %14\n\t"
                "movdqu %%xmm0, %15\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12]) ,
                        "=m" ((*out)[16]), "=m" ((*out)[20]), "=m" ((*out)[24]), "=m" ((*out)[28]),
                        "=m" ((*out)[32]), "=m" ((*out)[36]), "=m" ((*out)[40]), "=m" ((*out)[44]),
                        "=m" ((*out)[48]), "=m" ((*out)[52]), "=m" ((*out)[56]), "=m" ((*out)[60])
                ::"memory", "%xmm0");

        *out += 64;
}

/* --- UNPACK 1 --- */

#define __vserest_bufupdate(val, pad, Fill, buffer)     \
        ({                                              \
                buffer = (buffer << pad) | (val & ((1ULL << pad) - 1)); \
                Fill += pad;    \
         })

void
__vserest_unpack1_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;

        __vserest_bufupdate(pin[0], 31, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack1_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;

        __vserest_bufupdate(pin[0], 30, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack1_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;

        __vserest_bufupdate(pin[0], 29, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack1_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;

        __vserest_bufupdate(pin[0], 28, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack1_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;

        __vserest_bufupdate(pin[0], 27, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack1_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;

        __vserest_bufupdate(pin[0], 26, Fill, buffer);

        *in = pin + 1;
        *out = pout + 6;
}

void
__vserest_unpack1_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;

        __vserest_bufupdate(pin[0], 25, Fill, buffer);

        *in = pin + 1;
        *out = pout + 7;
}

void
__vserest_unpack1_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;

        __vserest_bufupdate(pin[0], 24, Fill, buffer);

        *in = pin + 1;
        *out = pout + 8;
}

void
__vserest_unpack1_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;

        __vserest_bufupdate(pin[0], 23, Fill, buffer);

        *in = pin + 1;
        *out = pout + 9;
}

void
__vserest_unpack1_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;

        __vserest_bufupdate(pin[0], 22, Fill, buffer);

        *in = pin + 1;
        *out = pout + 10;
}

void
__vserest_unpack1_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;

        __vserest_bufupdate(pin[0], 21, Fill, buffer);

        *in = pin + 1;
        *out = pout + 11;
}

void
__vserest_unpack1_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;
        pout[11] = (pin[0] >> 20) & 0x01;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 12;
}

void
__vserest_unpack1_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;
        pout[11] = (pin[0] >> 20) & 0x01;
        pout[12] = (pin[0] >> 19) & 0x01;
        pout[13] = (pin[0] >> 18) & 0x01;

        __vserest_bufupdate(pin[0], 18, Fill, buffer);

        *in = pin + 1;
        *out = pout + 14;
}

void
__vserest_unpack1_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;
        pout[11] = (pin[0] >> 20) & 0x01;
        pout[12] = (pin[0] >> 19) & 0x01;
        pout[13] = (pin[0] >> 18) & 0x01;
        pout[14] = (pin[0] >> 17) & 0x01;
        pout[15] = (pin[0] >> 16) & 0x01;

        __vserest_bufupdate(pin[0], 16, Fill, buffer);

        *in = pin + 1;
        *out = pout + 16;
}

void
__vserest_unpack1_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;
        pout[11] = (pin[0] >> 20) & 0x01;
        pout[12] = (pin[0] >> 19) & 0x01;
        pout[13] = (pin[0] >> 18) & 0x01;
        pout[14] = (pin[0] >> 17) & 0x01;
        pout[15] = (pin[0] >> 16) & 0x01;
        pout[16] = (pin[0] >> 15) & 0x01;
        pout[17] = (pin[0] >> 14) & 0x01;
        pout[18] = (pin[0] >> 13) & 0x01;
        pout[19] = (pin[0] >> 12) & 0x01;
        pout[20] = (pin[0] >> 11) & 0x01;
        pout[21] = (pin[0] >> 10) & 0x01;
        pout[22] = (pin[0] >> 9) & 0x01;
        pout[23] = (pin[0] >> 8) & 0x01;
        pout[24] = (pin[0] >> 7) & 0x01;
        pout[25] = (pin[0] >> 6) & 0x01;
        pout[26] = (pin[0] >> 5) & 0x01;
        pout[27] = (pin[0] >> 4) & 0x01;
        pout[28] = (pin[0] >> 3) & 0x01;
        pout[29] = (pin[0] >> 2) & 0x01;
        pout[30] = (pin[0] >> 1) & 0x01;
        pout[31] = pin[0] & 0x01;

        *in = pin + 1;
        *out = pout + 32;
}

void
__vserest_unpack1_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 31;
        pout[1] = (pin[0] >> 30) & 0x01;
        pout[2] = (pin[0] >> 29) & 0x01;
        pout[3] = (pin[0] >> 28) & 0x01;
        pout[4] = (pin[0] >> 27) & 0x01;
        pout[5] = (pin[0] >> 26) & 0x01;
        pout[6] = (pin[0] >> 25) & 0x01;
        pout[7] = (pin[0] >> 24) & 0x01;
        pout[8] = (pin[0] >> 23) & 0x01;
        pout[9] = (pin[0] >> 22) & 0x01;
        pout[10] = (pin[0] >> 21) & 0x01;
        pout[11] = (pin[0] >> 20) & 0x01;
        pout[12] = (pin[0] >> 19) & 0x01;
        pout[13] = (pin[0] >> 18) & 0x01;
        pout[14] = (pin[0] >> 17) & 0x01;
        pout[15] = (pin[0] >> 16) & 0x01;
        pout[16] = (pin[0] >> 15) & 0x01;
        pout[17] = (pin[0] >> 14) & 0x01;
        pout[18] = (pin[0] >> 13) & 0x01;
        pout[19] = (pin[0] >> 12) & 0x01;
        pout[20] = (pin[0] >> 11) & 0x01;
        pout[21] = (pin[0] >> 10) & 0x01;
        pout[22] = (pin[0] >> 9) & 0x01;
        pout[23] = (pin[0] >> 8) & 0x01;
        pout[24] = (pin[0] >> 7) & 0x01;
        pout[25] = (pin[0] >> 6) & 0x01;
        pout[26] = (pin[0] >> 5) & 0x01;
        pout[27] = (pin[0] >> 4) & 0x01;
        pout[28] = (pin[0] >> 3) & 0x01;
        pout[29] = (pin[0] >> 2) & 0x01;
        pout[30] = (pin[0] >> 1) & 0x01;
        pout[31] = pin[0] & 0x01;
        pout[32] = pin[1] >> 31;
        pout[33] = (pin[1] >> 30) & 0x01;
        pout[34] = (pin[1] >> 29) & 0x01;
        pout[35] = (pin[1] >> 28) & 0x01;
        pout[36] = (pin[1] >> 27) & 0x01;
        pout[37] = (pin[1] >> 26) & 0x01;
        pout[38] = (pin[1] >> 25) & 0x01;
        pout[39] = (pin[1] >> 24) & 0x01;
        pout[40] = (pin[1] >> 23) & 0x01;
        pout[41] = (pin[1] >> 22) & 0x01;
        pout[42] = (pin[1] >> 21) & 0x01;
        pout[43] = (pin[1] >> 20) & 0x01;
        pout[44] = (pin[1] >> 19) & 0x01;
        pout[45] = (pin[1] >> 18) & 0x01;
        pout[46] = (pin[1] >> 17) & 0x01;
        pout[47] = (pin[1] >> 16) & 0x01;
        pout[48] = (pin[1] >> 15) & 0x01;
        pout[49] = (pin[1] >> 14) & 0x01;
        pout[50] = (pin[1] >> 13) & 0x01;
        pout[51] = (pin[1] >> 12) & 0x01;
        pout[52] = (pin[1] >> 11) & 0x01;
        pout[53] = (pin[1] >> 10) & 0x01;
        pout[54] = (pin[1] >> 9) & 0x01;
        pout[55] = (pin[1] >> 8) & 0x01;
        pout[56] = (pin[1] >> 7) & 0x01;
        pout[57] = (pin[1] >> 6) & 0x01;
        pout[58] = (pin[1] >> 5) & 0x01;
        pout[59] = (pin[1] >> 4) & 0x01;
        pout[60] = (pin[1] >> 3) & 0x01;
        pout[61] = (pin[1] >> 2) & 0x01;
        pout[62] = (pin[1] >> 1) & 0x01;
        pout[63] = pin[1] & 0x01;

        *in = pin + 2;
        *out = pout + 64;
}

/* --- UNPACK 2 --- */
void
__vserest_unpack2_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;

        __vserest_bufupdate(pin[0], 30, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack2_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;

        __vserest_bufupdate(pin[0], 28, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack2_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;

        __vserest_bufupdate(pin[0], 26, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack2_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;

        __vserest_bufupdate(pin[0], 24, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack2_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;

        __vserest_bufupdate(pin[0], 22, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack2_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 6;
}

void
__vserest_unpack2_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;

        __vserest_bufupdate(pin[0], 18, Fill, buffer);

        *in = pin + 1;
        *out = pout + 7;
}

void
__vserest_unpack2_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;

        __vserest_bufupdate(pin[0], 16, Fill, buffer);

        *in = pin + 1;
        *out = pout + 8;
}

void
__vserest_unpack2_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;

        __vserest_bufupdate(pin[0], 14, Fill, buffer);

        *in = pin + 1;
        *out = pout + 9;
}

void
__vserest_unpack2_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;

        __vserest_bufupdate(pin[0], 12, Fill, buffer);

        *in = pin + 1;
        *out = pout + 10;
}

void
__vserest_unpack2_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;

        __vserest_bufupdate(pin[0], 10, Fill, buffer);

        *in = pin + 1;
        *out = pout + 11;
}

void
__vserest_unpack2_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;
        pout[11] = (pin[0] >> 8) & 0x03;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 12;
}

void
__vserest_unpack2_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;
        pout[11] = (pin[0] >> 8) & 0x03;
        pout[12] = (pin[0] >> 6) & 0x03;
        pout[13] = (pin[0] >> 4) & 0x03;

        __vserest_bufupdate(pin[0], 4, Fill, buffer);

        *in = pin + 1;
        *out = pout + 14;
}

void
__vserest_unpack2_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;
        pout[11] = (pin[0] >> 8) & 0x03;
        pout[12] = (pin[0] >> 6) & 0x03;
        pout[13] = (pin[0] >> 4) & 0x03;
        pout[14] = (pin[0] >> 2) & 0x03;
        pout[15] = pin[0] & 0x03;

        *in = pin + 1;
        *out = pout + 16;
}

void
__vserest_unpack2_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;
        pout[11] = (pin[0] >> 8) & 0x03;
        pout[12] = (pin[0] >> 6) & 0x03;
        pout[13] = (pin[0] >> 4) & 0x03;
        pout[14] = (pin[0] >> 2) & 0x03;
        pout[15] = pin[0] & 0x03;
        pout[16] = pin[1] >> 30;
        pout[17] = (pin[1] >> 28) & 0x03;
        pout[18] = (pin[1] >> 26) & 0x03;
        pout[19] = (pin[1] >> 24) & 0x03;
        pout[20] = (pin[1] >> 22) & 0x03;
        pout[21] = (pin[1] >> 20) & 0x03;
        pout[22] = (pin[1] >> 18) & 0x03;
        pout[23] = (pin[1] >> 16) & 0x03;
        pout[24] = (pin[1] >> 14) & 0x03;
        pout[25] = (pin[1] >> 12) & 0x03;
        pout[26] = (pin[1] >> 10) & 0x03;
        pout[27] = (pin[1] >> 8) & 0x03;
        pout[28] = (pin[1] >> 6) & 0x03;
        pout[29] = (pin[1] >> 4) & 0x03;
        pout[30] = (pin[1] >> 2) & 0x03;
        pout[31] = pin[1] & 0x03;

        *in = pin + 2;
        *out = pout + 32;
}

void
__vserest_unpack2_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 30;
        pout[1] = (pin[0] >> 28) & 0x03;
        pout[2] = (pin[0] >> 26) & 0x03;
        pout[3] = (pin[0] >> 24) & 0x03;
        pout[4] = (pin[0] >> 22) & 0x03;
        pout[5] = (pin[0] >> 20) & 0x03;
        pout[6] = (pin[0] >> 18) & 0x03;
        pout[7] = (pin[0] >> 16) & 0x03;
        pout[8] = (pin[0] >> 14) & 0x03;
        pout[9] = (pin[0] >> 12) & 0x03;
        pout[10] = (pin[0] >> 10) & 0x03;
        pout[11] = (pin[0] >> 8) & 0x03;
        pout[12] = (pin[0] >> 6) & 0x03;
        pout[13] = (pin[0] >> 4) & 0x03;
        pout[14] = (pin[0] >> 2) & 0x03;
        pout[15] = pin[0] & 0x03;
        pout[16] = pin[1] >> 30;
        pout[17] = (pin[1] >> 28) & 0x03;
        pout[18] = (pin[1] >> 26) & 0x03;
        pout[19] = (pin[1] >> 24) & 0x03;
        pout[20] = (pin[1] >> 22) & 0x03;
        pout[21] = (pin[1] >> 20) & 0x03;
        pout[22] = (pin[1] >> 18) & 0x03;
        pout[23] = (pin[1] >> 16) & 0x03;
        pout[24] = (pin[1] >> 14) & 0x03;
        pout[25] = (pin[1] >> 12) & 0x03;
        pout[26] = (pin[1] >> 10) & 0x03;
        pout[27] = (pin[1] >> 8) & 0x03;
        pout[28] = (pin[1] >> 6) & 0x03;
        pout[29] = (pin[1] >> 4) & 0x03;
        pout[30] = (pin[1] >> 2) & 0x03;
        pout[31] = pin[1] & 0x03;
        pout[32] = pin[2] >> 30;
        pout[33] = (pin[2] >> 28) & 0x03;
        pout[34] = (pin[2] >> 26) & 0x03;
        pout[35] = (pin[2] >> 24) & 0x03;
        pout[36] = (pin[2] >> 22) & 0x03;
        pout[37] = (pin[2] >> 20) & 0x03;
        pout[38] = (pin[2] >> 18) & 0x03;
        pout[39] = (pin[2] >> 16) & 0x03;
        pout[40] = (pin[2] >> 14) & 0x03;
        pout[41] = (pin[2] >> 12) & 0x03;
        pout[42] = (pin[2] >> 10) & 0x03;
        pout[43] = (pin[2] >> 8) & 0x03;
        pout[44] = (pin[2] >> 6) & 0x03;
        pout[45] = (pin[2] >> 4) & 0x03;
        pout[46] = (pin[2] >> 2) & 0x03;
        pout[47] = pin[2] & 0x03;
        pout[48] = pin[3] >> 30;
        pout[49] = (pin[3] >> 28) & 0x03;
        pout[50] = (pin[3] >> 26) & 0x03;
        pout[51] = (pin[3] >> 24) & 0x03;
        pout[52] = (pin[3] >> 22) & 0x03;
        pout[53] = (pin[3] >> 20) & 0x03;
        pout[54] = (pin[3] >> 18) & 0x03;
        pout[55] = (pin[3] >> 16) & 0x03;
        pout[56] = (pin[3] >> 14) & 0x03;
        pout[57] = (pin[3] >> 12) & 0x03;
        pout[58] = (pin[3] >> 10) & 0x03;
        pout[59] = (pin[3] >> 8) & 0x03;
        pout[60] = (pin[3] >> 6) & 0x03;
        pout[61] = (pin[3] >> 4) & 0x03;
        pout[62] = (pin[3] >> 2) & 0x03;
        pout[63] = pin[3] & 0x03;

        *in = pin + 4;
        *out = pout + 64;
}

/* --- UNPACK 3 --- */
void
__vserest_unpack3_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;

        __vserest_bufupdate(pin[0], 29, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack3_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;

        __vserest_bufupdate(pin[0], 26, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack3_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;

        __vserest_bufupdate(pin[0], 23, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack3_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack3_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;

        __vserest_bufupdate(pin[0], 17, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack3_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;

        __vserest_bufupdate(pin[0], 14, Fill, buffer);

        *in = pin + 1;
        *out = pout + 6;
}

void
__vserest_unpack3_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;

        __vserest_bufupdate(pin[0], 11, Fill, buffer);

        *in = pin + 1;
        *out = pout + 7;
}

void
__vserest_unpack3_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 8;
}

void
__vserest_unpack3_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;

        __vserest_bufupdate(pin[0], 5, Fill, buffer);

        *in = pin + 1;
        *out = pout + 9;
}

void
__vserest_unpack3_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;

        __vserest_bufupdate(pin[0], 2, Fill, buffer);

        *in = pin + 1;
        *out = pout + 10;
}

void
__vserest_unpack3_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;

        __vserest_bufupdate(pin[1], 31, Fill, buffer);

        *in = pin + 2;
        *out = pout + 11;
}

void
__vserest_unpack3_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;
        pout[11] = (pin[1] >> 28) & 0x07;

        __vserest_bufupdate(pin[1], 28, Fill, buffer);

        *in = pin + 2;
        *out = pout + 12;
}

void
__vserest_unpack3_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;
        pout[11] = (pin[1] >> 28) & 0x07;
        pout[12] = (pin[1] >> 25) & 0x07;
        pout[13] = (pin[1] >> 22) & 0x07;

        __vserest_bufupdate(pin[1], 22, Fill, buffer);

        *in = pin + 2;
        *out = pout + 14;
}

void
__vserest_unpack3_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;
        pout[11] = (pin[1] >> 28) & 0x07;
        pout[12] = (pin[1] >> 25) & 0x07;
        pout[13] = (pin[1] >> 22) & 0x07;
        pout[14] = (pin[1] >> 19) & 0x07;
        pout[15] = (pin[1] >> 16) & 0x07;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 16;
}

void
__vserest_unpack3_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;
        pout[11] = (pin[1] >> 28) & 0x07;
        pout[12] = (pin[1] >> 25) & 0x07;
        pout[13] = (pin[1] >> 22) & 0x07;
        pout[14] = (pin[1] >> 19) & 0x07;
        pout[15] = (pin[1] >> 16) & 0x07;
        pout[16] = (pin[1] >> 13) & 0x07;
        pout[17] = (pin[1] >> 10) & 0x07;
        pout[18] = (pin[1] >> 7) & 0x07;
        pout[19] = (pin[1] >> 4) & 0x07;
        pout[20] = (pin[1] >> 1) & 0x07;
        pout[21] = (pin[1] << 2) & 0x07;
        pout[21] |= pin[2] >> 30;
        pout[22] = (pin[2] >> 27) & 0x07;
        pout[23] = (pin[2] >> 24) & 0x07;
        pout[24] = (pin[2] >> 21) & 0x07;
        pout[25] = (pin[2] >> 18) & 0x07;
        pout[26] = (pin[2] >> 15) & 0x07;
        pout[27] = (pin[2] >> 12) & 0x07;
        pout[28] = (pin[2] >> 9) & 0x07;
        pout[29] = (pin[2] >> 6) & 0x07;
        pout[30] = (pin[2] >> 3) & 0x07;
        pout[31] = pin[2] & 0x07;

        *in = pin + 3;
        *out = pout + 32;
}

void
__vserest_unpack3_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 29;
        pout[1] = (pin[0] >> 26) & 0x07;
        pout[2] = (pin[0] >> 23) & 0x07;
        pout[3] = (pin[0] >> 20) & 0x07;
        pout[4] = (pin[0] >> 17) & 0x07;
        pout[5] = (pin[0] >> 14) & 0x07;
        pout[6] = (pin[0] >> 11) & 0x07;
        pout[7] = (pin[0] >> 8) & 0x07;
        pout[8] = (pin[0] >> 5) & 0x07;
        pout[9] = (pin[0] >> 2) & 0x07;
        pout[10] = (pin[0] << 1) & 0x07;
        pout[10] |= pin[1] >> 31;
        pout[11] = (pin[1] >> 28) & 0x07;
        pout[12] = (pin[1] >> 25) & 0x07;
        pout[13] = (pin[1] >> 22) & 0x07;
        pout[14] = (pin[1] >> 19) & 0x07;
        pout[15] = (pin[1] >> 16) & 0x07;
        pout[16] = (pin[1] >> 13) & 0x07;
        pout[17] = (pin[1] >> 10) & 0x07;
        pout[18] = (pin[1] >> 7) & 0x07;
        pout[19] = (pin[1] >> 4) & 0x07;
        pout[20] = (pin[1] >> 1) & 0x07;
        pout[21] = (pin[1] << 2) & 0x07;
        pout[21] |= pin[2] >> 30;
        pout[22] = (pin[2] >> 27) & 0x07;
        pout[23] = (pin[2] >> 24) & 0x07;
        pout[24] = (pin[2] >> 21) & 0x07;
        pout[25] = (pin[2] >> 18) & 0x07;
        pout[26] = (pin[2] >> 15) & 0x07;
        pout[27] = (pin[2] >> 12) & 0x07;
        pout[28] = (pin[2] >> 9) & 0x07;
        pout[29] = (pin[2] >> 6) & 0x07;
        pout[30] = (pin[2] >> 3) & 0x07;
        pout[31] = pin[2] & 0x07;
        pout[32] = pin[3] >> 29;
        pout[33] = (pin[3] >> 26) & 0x07;
        pout[34] = (pin[3] >> 23) & 0x07;
        pout[35] = (pin[3] >> 20) & 0x07;
        pout[36] = (pin[3] >> 17) & 0x07;
        pout[37] = (pin[3] >> 14) & 0x07;
        pout[38] = (pin[3] >> 11) & 0x07;
        pout[39] = (pin[3] >> 8) & 0x07;
        pout[40] = (pin[3] >> 5) & 0x07;
        pout[41] = (pin[3] >> 2) & 0x07;
        pout[42] = (pin[3] << 1) & 0x07;
        pout[42] |= pin[4] >> 31;
        pout[43] = (pin[4] >> 28) & 0x07;
        pout[44] = (pin[4] >> 25) & 0x07;
        pout[45] = (pin[4] >> 22) & 0x07;
        pout[46] = (pin[4] >> 19) & 0x07;
        pout[47] = (pin[4] >> 16) & 0x07;
        pout[48] = (pin[4] >> 13) & 0x07;
        pout[49] = (pin[4] >> 10) & 0x07;
        pout[50] = (pin[4] >> 7) & 0x07;
        pout[51] = (pin[4] >> 4) & 0x07;
        pout[52] = (pin[4] >> 1) & 0x07;
        pout[53] = (pin[4] << 2) & 0x07;
        pout[53] |= pin[5] >> 30;
        pout[54] = (pin[5] >> 27) & 0x07;
        pout[55] = (pin[5] >> 24) & 0x07;
        pout[56] = (pin[5] >> 21) & 0x07;
        pout[57] = (pin[5] >> 18) & 0x07;
        pout[58] = (pin[5] >> 15) & 0x07;
        pout[59] = (pin[5] >> 12) & 0x07;
        pout[60] = (pin[5] >> 9) & 0x07;
        pout[61] = (pin[5] >> 6) & 0x07;
        pout[62] = (pin[5] >> 3) & 0x07;
        pout[63] = pin[5] & 0x07;

        *in = pin + 6;
        *out = pout + 64;
}

/* --- UNPACK 4 --- */
void
__vserest_unpack4_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;

        __vserest_bufupdate(pin[0], 28, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack4_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;

        __vserest_bufupdate(pin[0], 24, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack4_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack4_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;

        __vserest_bufupdate(pin[0], 16, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack4_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;

        __vserest_bufupdate(pin[0], 12, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack4_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 6;
}

void
__vserest_unpack4_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;

        __vserest_bufupdate(pin[0], 4, Fill, buffer);

        *in = pin + 1;
        *out = pout + 7;
}

void
__vserest_unpack4_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;

        *in = pin + 1;
        *out = pout + 8;
}

void
__vserest_unpack4_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;

        __vserest_bufupdate(pin[1], 28, Fill, buffer);

        *in = pin + 2;
        *out = pout + 9;
}

void
__vserest_unpack4_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;

        __vserest_bufupdate(pin[1], 24, Fill, buffer);

        *in = pin + 2;
        *out = pout + 10;
}

void
__vserest_unpack4_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;

        __vserest_bufupdate(pin[1], 20, Fill, buffer);

        *in = pin + 2;
        *out = pout + 11;
}

void
__vserest_unpack4_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;
        pout[11] = (pin[1] >> 16) & 0x0f;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 12;
}

void
__vserest_unpack4_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;
        pout[11] = (pin[1] >> 16) & 0x0f;
        pout[12] = (pin[1] >> 12) & 0x0f;
        pout[13] = (pin[1] >> 8) & 0x0f;

        __vserest_bufupdate(pin[1], 8, Fill, buffer);

        *in = pin + 2;
        *out = pout + 14;
}

void
__vserest_unpack4_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;
        pout[11] = (pin[1] >> 16) & 0x0f;
        pout[12] = (pin[1] >> 12) & 0x0f;
        pout[13] = (pin[1] >> 8) & 0x0f;
        pout[14] = (pin[1] >> 4) & 0x0f;
        pout[15] = pin[1] & 0x0f;

        *in = pin + 2;
        *out = pout + 16;
}

void
__vserest_unpack4_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;
        pout[11] = (pin[1] >> 16) & 0x0f;
        pout[12] = (pin[1] >> 12) & 0x0f;
        pout[13] = (pin[1] >> 8) & 0x0f;
        pout[14] = (pin[1] >> 4) & 0x0f;
        pout[15] = pin[1] & 0x0f;
        pout[16] = pin[2] >> 28;
        pout[17] = (pin[2] >> 24) & 0x0f;
        pout[18] = (pin[2] >> 20) & 0x0f;
        pout[19] = (pin[2] >> 16) & 0x0f;
        pout[20] = (pin[2] >> 12) & 0x0f;
        pout[21] = (pin[2] >> 8) & 0x0f;
        pout[22] = (pin[2] >> 4) & 0x0f;
        pout[23] = pin[2]  & 0x0f;
        pout[24] = pin[3] >> 28;
        pout[25] = (pin[3] >> 24) & 0x0f;
        pout[26] = (pin[3] >> 20) & 0x0f;
        pout[27] = (pin[3] >> 16) & 0x0f;
        pout[28] = (pin[3] >> 12) & 0x0f;
        pout[29] = (pin[3] >> 8) & 0x0f;
        pout[30] = (pin[3] >> 4) & 0x0f;
        pout[31] = pin[3] & 0x0f;

        *in = pin + 4;
        *out = pout + 32;
}

void
__vserest_unpack4_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 28;
        pout[1] = (pin[0] >> 24) & 0x0f;
        pout[2] = (pin[0] >> 20) & 0x0f;
        pout[3] = (pin[0] >> 16) & 0x0f;
        pout[4] = (pin[0] >> 12) & 0x0f;
        pout[5] = (pin[0] >> 8) & 0x0f;
        pout[6] = (pin[0] >> 4) & 0x0f;
        pout[7] = pin[0]  & 0x0f;
        pout[8] = pin[1] >> 28;
        pout[9] = (pin[1] >> 24) & 0x0f;
        pout[10] = (pin[1] >> 20) & 0x0f;
        pout[11] = (pin[1] >> 16) & 0x0f;
        pout[12] = (pin[1] >> 12) & 0x0f;
        pout[13] = (pin[1] >> 8) & 0x0f;
        pout[14] = (pin[1] >> 4) & 0x0f;
        pout[15] = pin[1] & 0x0f;
        pout[16] = pin[2] >> 28;
        pout[17] = (pin[2] >> 24) & 0x0f;
        pout[18] = (pin[2] >> 20) & 0x0f;
        pout[19] = (pin[2] >> 16) & 0x0f;
        pout[20] = (pin[2] >> 12) & 0x0f;
        pout[21] = (pin[2] >> 8) & 0x0f;
        pout[22] = (pin[2] >> 4) & 0x0f;
        pout[23] = pin[2]  & 0x0f;
        pout[24] = pin[3] >> 28;
        pout[25] = (pin[3] >> 24) & 0x0f;
        pout[26] = (pin[3] >> 20) & 0x0f;
        pout[27] = (pin[3] >> 16) & 0x0f;
        pout[28] = (pin[3] >> 12) & 0x0f;
        pout[29] = (pin[3] >> 8) & 0x0f;
        pout[30] = (pin[3] >> 4) & 0x0f;
        pout[31] = pin[3] & 0x0f;
        pout[32] = pin[4] >> 28;
        pout[33] = (pin[4] >> 24) & 0x0f;
        pout[34] = (pin[4] >> 20) & 0x0f;
        pout[35] = (pin[4] >> 16) & 0x0f;
        pout[36] = (pin[4] >> 12) & 0x0f;
        pout[37] = (pin[4] >> 8) & 0x0f;
        pout[38] = (pin[4] >> 4) & 0x0f;
        pout[39] = pin[4]  & 0x0f;
        pout[40] = pin[5] >> 28;
        pout[41] = (pin[5] >> 24) & 0x0f;
        pout[42] = (pin[5] >> 20) & 0x0f;
        pout[43] = (pin[5] >> 16) & 0x0f;
        pout[44] = (pin[5] >> 12) & 0x0f;
        pout[45] = (pin[5] >> 8) & 0x0f;
        pout[46] = (pin[5] >> 4) & 0x0f;
        pout[47] = pin[5] & 0x0f;
        pout[48] = pin[6] >> 28;
        pout[49] = (pin[6] >> 24) & 0x0f;
        pout[50] = (pin[6] >> 20) & 0x0f;
        pout[51] = (pin[6] >> 16) & 0x0f;
        pout[52] = (pin[6] >> 12) & 0x0f;
        pout[53] = (pin[6] >> 8) & 0x0f;
        pout[54] = (pin[6] >> 4) & 0x0f;
        pout[55] = pin[6]  & 0x0f;
        pout[56] = pin[7] >> 28;
        pout[57] = (pin[7] >> 24) & 0x0f;
        pout[58] = (pin[7] >> 20) & 0x0f;
        pout[59] = (pin[7] >> 16) & 0x0f;
        pout[60] = (pin[7] >> 12) & 0x0f;
        pout[61] = (pin[7] >> 8) & 0x0f;
        pout[62] = (pin[7] >> 4) & 0x0f;
        pout[63] = pin[7] & 0x0f;

        *in = pin + 8;
        *out = pout + 64;
}

/* --- UNPACK 5 --- */
void
__vserest_unpack5_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;

        __vserest_bufupdate(pin[0], 27, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack5_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;

        __vserest_bufupdate(pin[0], 22, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack5_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;

        __vserest_bufupdate(pin[0], 17, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack5_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;

        __vserest_bufupdate(pin[0], 12, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack5_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;

        __vserest_bufupdate(pin[0], 7, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack5_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;

        __vserest_bufupdate(pin[0], 2, Fill, buffer);
        
        *in = pin + 1;
        *out = pout + 6;
}

void
__vserest_unpack5_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;

        __vserest_bufupdate(pin[1], 29, Fill, buffer);

        *in = pin + 2;
        *out = pout + 7;
}

void
__vserest_unpack5_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;

        __vserest_bufupdate(pin[1], 24, Fill, buffer);

        *in = pin + 2;
        *out = pout + 8;
}

void
__vserest_unpack5_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;

        __vserest_bufupdate(pin[1], 19, Fill, buffer);

        *in = pin + 2;
        *out = pout + 9;
}

void
__vserest_unpack5_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;

        __vserest_bufupdate(pin[1], 14, Fill, buffer);

        *in = pin + 2;
        *out = pout + 10;
}

void
__vserest_unpack5_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;

        __vserest_bufupdate(pin[1], 9, Fill, buffer);

        *in = pin + 2;
        *out = pout + 11;
}

void
__vserest_unpack5_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;
        pout[11] = (pin[1] >> 4) & 0x1f;

        __vserest_bufupdate(pin[1], 4, Fill, buffer);

        *in = pin + 2;
        *out = pout + 12;
}

void
__vserest_unpack5_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;
        pout[11] = (pin[1] >> 4) & 0x1f;
        pout[12] = (pin[1] << 1) & 0x1f;
        pout[12] |= pin[2] >> 31;
        pout[13] = (pin[2] >> 26) & 0x1f;

        __vserest_bufupdate(pin[2], 26, Fill, buffer);

        *in = pin + 3;
        *out = pout + 14;
}

void
__vserest_unpack5_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;
        pout[11] = (pin[1] >> 4) & 0x1f;
        pout[12] = (pin[1] << 1) & 0x1f;
        pout[12] |= pin[2] >> 31;
        pout[13] = (pin[2] >> 26) & 0x1f;
        pout[14] = (pin[2] >> 21) & 0x1f;
        pout[15] = (pin[2] >> 16) & 0x1f;

        __vserest_bufupdate(pin[2], 16, Fill, buffer);

        *in = pin + 3;
        *out = pout + 16;
}

void
__vserest_unpack5_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;
        pout[11] = (pin[1] >> 4) & 0x1f;
        pout[12] = (pin[1] << 1) & 0x1f;
        pout[12] |= pin[2] >> 31;
        pout[13] = (pin[2] >> 26) & 0x1f;
        pout[14] = (pin[2] >> 21) & 0x1f;
        pout[15] = (pin[2] >> 16) & 0x1f;
        pout[16] = (pin[2] >> 11) & 0x1f;
        pout[17] = (pin[2] >> 6) & 0x1f;
        pout[18] = (pin[2] >> 1) & 0x1f;
        pout[19] = (pin[2] << 4) & 0x1f;
        pout[19] |= pin[3] >> 28;
        pout[20] = (pin[3] >> 23) & 0x1f;
        pout[21] = (pin[3] >> 18) & 0x1f;
        pout[22] = (pin[3] >> 13) & 0x1f;
        pout[23] = (pin[3] >> 8) & 0x1f;
        pout[24] = (pin[3] >> 3) & 0x1f;
        pout[25] = (pin[3] << 2) & 0x1f;
        pout[25] |= pin[4] >> 30;
        pout[26] = (pin[4] >> 25) & 0x1f;
        pout[27] = (pin[4] >> 20) & 0x1f;
        pout[28] = (pin[4] >> 15) & 0x1f;
        pout[29] = (pin[4] >> 10) & 0x1f;
        pout[30] = (pin[4] >> 5) & 0x1f;
        pout[31] = pin[4] & 0x1f;

        *in = pin + 5;
        *out = pout + 32;
}

void
__vserest_unpack5_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 27;
        pout[1] = (pin[0] >> 22) & 0x1f;
        pout[2] = (pin[0] >> 17) & 0x1f;
        pout[3] = (pin[0] >> 12) & 0x1f;
        pout[4] = (pin[0] >> 7) & 0x1f;
        pout[5] = (pin[0] >> 2) & 0x1f;
        pout[6] = (pin[0] << 3) & 0x1f;
        pout[6] |= pin[1] >> 29;
        pout[7] = (pin[1] >> 24) & 0x1f;
        pout[8] = (pin[1] >> 19) & 0x1f;
        pout[9] = (pin[1] >> 14) & 0x1f;
        pout[10] = (pin[1] >> 9) & 0x1f;
        pout[11] = (pin[1] >> 4) & 0x1f;
        pout[12] = (pin[1] << 1) & 0x1f;
        pout[12] |= pin[2] >> 31;
        pout[13] = (pin[2] >> 26) & 0x1f;
        pout[14] = (pin[2] >> 21) & 0x1f;
        pout[15] = (pin[2] >> 16) & 0x1f;
        pout[16] = (pin[2] >> 11) & 0x1f;
        pout[17] = (pin[2] >> 6) & 0x1f;
        pout[18] = (pin[2] >> 1) & 0x1f;
        pout[19] = (pin[2] << 4) & 0x1f;
        pout[19] |= pin[3] >> 28;
        pout[20] = (pin[3] >> 23) & 0x1f;
        pout[21] = (pin[3] >> 18) & 0x1f;
        pout[22] = (pin[3] >> 13) & 0x1f;
        pout[23] = (pin[3] >> 8) & 0x1f;
        pout[24] = (pin[3] >> 3) & 0x1f;
        pout[25] = (pin[3] << 2) & 0x1f;
        pout[25] |= pin[4] >> 30;
        pout[26] = (pin[4] >> 25) & 0x1f;
        pout[27] = (pin[4] >> 20) & 0x1f;
        pout[28] = (pin[4] >> 15) & 0x1f;
        pout[29] = (pin[4] >> 10) & 0x1f;
        pout[30] = (pin[4] >> 5) & 0x1f;
        pout[31] = pin[4] & 0x1f;
        pout[32] = pin[5] >> 27;
        pout[33] = (pin[5] >> 22) & 0x1f;
        pout[34] = (pin[5] >> 17) & 0x1f;
        pout[35] = (pin[5] >> 12) & 0x1f;
        pout[36] = (pin[5] >> 7) & 0x1f;
        pout[37] = (pin[5] >> 2) & 0x1f;
        pout[38] = (pin[5] << 3) & 0x1f;
        pout[38] |= pin[6] >> 29;
        pout[39] = (pin[6] >> 24) & 0x1f;
        pout[40] = (pin[6] >> 19) & 0x1f;
        pout[41] = (pin[6] >> 14) & 0x1f;
        pout[42] = (pin[6] >> 9) & 0x1f;
        pout[43] = (pin[6] >> 4) & 0x1f;
        pout[44] = (pin[6] << 1) & 0x1f;
        pout[44] |= pin[7] >> 31;
        pout[45] = (pin[7] >> 26) & 0x1f;
        pout[46] = (pin[7] >> 21) & 0x1f;
        pout[47] = (pin[7] >> 16) & 0x1f;
        pout[48] = (pin[7] >> 11) & 0x1f;
        pout[49] = (pin[7] >> 6) & 0x1f;
        pout[50] = (pin[7] >> 1) & 0x1f;
        pout[51] = (pin[7] << 4) & 0x1f;
        pout[51] |= pin[8] >> 28;
        pout[52] = (pin[8] >> 23) & 0x1f;
        pout[53] = (pin[8] >> 18) & 0x1f;
        pout[54] = (pin[8] >> 13) & 0x1f;
        pout[55] = (pin[8] >> 8) & 0x1f;
        pout[56] = (pin[8] >> 3) & 0x1f;
        pout[57] = (pin[8] << 2) & 0x1f;
        pout[57] |= pin[9] >> 30;
        pout[58] = (pin[9] >> 25) & 0x1f;
        pout[59] = (pin[9] >> 20) & 0x1f;
        pout[60] = (pin[9] >> 15) & 0x1f;
        pout[61] = (pin[9] >> 10) & 0x1f;
        pout[62] = (pin[9] >> 5) & 0x1f;
        pout[63] = pin[9] & 0x1f;

        *in = pin + 10;
        *out = pout + 64;
}

/* --- UNPACK 6 --- */
void
__vserest_unpack6_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;

        __vserest_bufupdate(pin[0], 26, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack6_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack6_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;

        __vserest_bufupdate(pin[0], 14, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack6_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack6_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;

        __vserest_bufupdate(pin[0], 2, Fill, buffer);

        *in = pin + 1;
        *out = pout + 5;
}

void
__vserest_unpack6_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;

        __vserest_bufupdate(pin[1], 28, Fill, buffer);

        *in = pin + 2;
        *out = pout + 6;
}

void
__vserest_unpack6_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;

        __vserest_bufupdate(pin[1], 22, Fill, buffer);

        *in = pin + 2;
        *out = pout + 7;
}

void
__vserest_unpack6_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 8;
}

void
__vserest_unpack6_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;

        __vserest_bufupdate(pin[1], 10, Fill, buffer);

        *in = pin + 2;
        *out = pout + 9;
}

void
__vserest_unpack6_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;

        __vserest_bufupdate(pin[1], 4, Fill, buffer);

        *in = pin + 2;
        *out = pout + 10;
}

void
__vserest_unpack6_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;

        __vserest_bufupdate(pin[2], 30, Fill, buffer);

        *in = pin + 3;
        *out = pout + 11;
}

void
__vserest_unpack6_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;
        pout[11] = (pin[2] >> 24) & 0x3f;

        __vserest_bufupdate(pin[2], 24, Fill, buffer);

        *in = pin + 3;
        *out = pout + 12;
}

void
__vserest_unpack6_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;
        pout[11] = (pin[2] >> 24) & 0x3f;
        pout[12] = (pin[2] >> 18) & 0x3f;
        pout[13] = (pin[2] >> 12) & 0x3f;

        __vserest_bufupdate(pin[2], 12, Fill, buffer);

        *in = pin + 3;
        *out = pout + 14;
}

void
__vserest_unpack6_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;
        pout[11] = (pin[2] >> 24) & 0x3f;
        pout[12] = (pin[2] >> 18) & 0x3f;
        pout[13] = (pin[2] >> 12) & 0x3f;
        pout[14] = (pin[2] >> 6) & 0x3f;
        pout[15] = pin[2] & 0x3f;

        *in = pin + 3;
        *out = pout + 16;
}

void
__vserest_unpack6_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;
        pout[11] = (pin[2] >> 24) & 0x3f;
        pout[12] = (pin[2] >> 18) & 0x3f;
        pout[13] = (pin[2] >> 12) & 0x3f;
        pout[14] = (pin[2] >> 6) & 0x3f;
        pout[15] = pin[2] & 0x3f;
        pout[16] = pin[3] >> 26;
        pout[17] = (pin[3] >> 20) & 0x3f;
        pout[18] = (pin[3] >> 14) & 0x3f;
        pout[19] = (pin[3] >> 8) & 0x3f;
        pout[20] = (pin[3] >> 2) & 0x3f;
        pout[21] = (pin[3] << 4) & 0x3f;
        pout[21] |= pin[4] >> 28;
        pout[22] = (pin[4] >> 22) & 0x3f;
        pout[23] = (pin[4] >> 16) & 0x3f;
        pout[24] = (pin[4] >> 10) & 0x3f;
        pout[25] = (pin[4] >> 4) & 0x3f;
        pout[26] = (pin[4] << 2) & 0x3f;
        pout[26] |= pin[5] >> 30;
        pout[27] = (pin[5] >> 24) & 0x3f;
        pout[28] = (pin[5] >> 18) & 0x3f;
        pout[29] = (pin[5] >> 12) & 0x3f;
        pout[30] = (pin[5] >> 6) & 0x3f;
        pout[31] = pin[5] & 0x3f;

        *in = pin + 6;
        *out = pout + 32;
}

void
__vserest_unpack6_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 26;
        pout[1] = (pin[0] >> 20) & 0x3f;
        pout[2] = (pin[0] >> 14) & 0x3f;
        pout[3] = (pin[0] >> 8) & 0x3f;
        pout[4] = (pin[0] >> 2) & 0x3f;
        pout[5] = (pin[0] << 4) & 0x3f;
        pout[5] |= pin[1] >> 28;
        pout[6] = (pin[1] >> 22) & 0x3f;
        pout[7] = (pin[1] >> 16) & 0x3f;
        pout[8] = (pin[1] >> 10) & 0x3f;
        pout[9] = (pin[1] >> 4) & 0x3f;
        pout[10] = (pin[1] << 2) & 0x3f;
        pout[10] |= pin[2] >> 30;
        pout[11] = (pin[2] >> 24) & 0x3f;
        pout[12] = (pin[2] >> 18) & 0x3f;
        pout[13] = (pin[2] >> 12) & 0x3f;
        pout[14] = (pin[2] >> 6) & 0x3f;
        pout[15] = pin[2] & 0x3f;
        pout[16] = pin[3] >> 26;
        pout[17] = (pin[3] >> 20) & 0x3f;
        pout[18] = (pin[3] >> 14) & 0x3f;
        pout[19] = (pin[3] >> 8) & 0x3f;
        pout[20] = (pin[3] >> 2) & 0x3f;
        pout[21] = (pin[3] << 4) & 0x3f;
        pout[21] |= pin[4] >> 28;
        pout[22] = (pin[4] >> 22) & 0x3f;
        pout[23] = (pin[4] >> 16) & 0x3f;
        pout[24] = (pin[4] >> 10) & 0x3f;
        pout[25] = (pin[4] >> 4) & 0x3f;
        pout[26] = (pin[4] << 2) & 0x3f;
        pout[26] |= pin[5] >> 30;
        pout[27] = (pin[5] >> 24) & 0x3f;
        pout[28] = (pin[5] >> 18) & 0x3f;
        pout[29] = (pin[5] >> 12) & 0x3f;
        pout[30] = (pin[5] >> 6) & 0x3f;
        pout[31] = pin[5] & 0x3f;
        pout[32] = pin[6] >> 26;
        pout[33] = (pin[6] >> 20) & 0x3f;
        pout[34] = (pin[6] >> 14) & 0x3f;
        pout[35] = (pin[6] >> 8) & 0x3f;
        pout[36] = (pin[6] >> 2) & 0x3f;
        pout[37] = (pin[6] << 4) & 0x3f;
        pout[37] |= pin[7] >> 28;
        pout[38] = (pin[7] >> 22) & 0x3f;
        pout[39] = (pin[7] >> 16) & 0x3f;
        pout[40] = (pin[7] >> 10) & 0x3f;
        pout[41] = (pin[7] >> 4) & 0x3f;
        pout[42] = (pin[7] << 2) & 0x3f;
        pout[42] |= pin[8] >> 30;
        pout[43] = (pin[8] >> 24) & 0x3f;
        pout[44] = (pin[8] >> 18) & 0x3f;
        pout[45] = (pin[8] >> 12) & 0x3f;
        pout[46] = (pin[8] >> 6) & 0x3f;
        pout[47] = pin[8] & 0x3f;
        pout[48] = pin[9] >> 26;
        pout[49] = (pin[9] >> 20) & 0x3f;
        pout[50] = (pin[9] >> 14) & 0x3f;
        pout[51] = (pin[9] >> 8) & 0x3f;
        pout[52] = (pin[9] >> 2) & 0x3f;
        pout[53] = (pin[9] << 4) & 0x3f;
        pout[53] |= pin[10] >> 28;
        pout[54] = (pin[10] >> 22) & 0x3f;
        pout[55] = (pin[10] >> 16) & 0x3f;
        pout[56] = (pin[10] >> 10) & 0x3f;
        pout[57] = (pin[10] >> 4) & 0x3f;
        pout[58] = (pin[10] << 2) & 0x3f;
        pout[58] |= pin[11] >> 30;
        pout[59] = (pin[11] >> 24) & 0x3f;
        pout[60] = (pin[11] >> 18) & 0x3f;
        pout[61] = (pin[11] >> 12) & 0x3f;
        pout[62] = (pin[11] >> 6) & 0x3f;
        pout[63] = pin[11] & 0x3f;

        *in = pin + 12;
        *out = pout + 64;
}

/* --- UNPACK 7 --- */
void
__vserest_unpack7_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;

        __vserest_bufupdate(pin[0], 25, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack7_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;

        __vserest_bufupdate(pin[0], 18, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack7_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;

        __vserest_bufupdate(pin[0], 11, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack7_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;

        __vserest_bufupdate(pin[0], 4, Fill, buffer);

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack7_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;

        __vserest_bufupdate(pin[1], 29, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack7_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;

        __vserest_bufupdate(pin[1], 22, Fill, buffer);

        *in = pin + 2;
        *out = pout + 6;
}

void
__vserest_unpack7_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;

        __vserest_bufupdate(pin[1], 15, Fill, buffer);

        *in = pin + 2;
        *out = pout + 7;
}

void
__vserest_unpack7_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;

        __vserest_bufupdate(pin[1], 8, Fill, buffer);

        *in = pin + 2;
        *out = pout + 8;
}

void
__vserest_unpack7_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;

        __vserest_bufupdate(pin[1], 1, Fill, buffer);

        *in = pin + 2;
        *out = pout + 9;
}

void
__vserest_unpack7_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;

        __vserest_bufupdate(pin[2], 26, Fill, buffer);

        *in = pin + 3;
        *out = pout + 10;
}

void
__vserest_unpack7_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;

        __vserest_bufupdate(pin[2], 19, Fill, buffer);

        *in = pin + 3;
        *out = pout + 11;
}

void
__vserest_unpack7_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;
        pout[11] = (pin[2] >> 12) & 0x7f;

        __vserest_bufupdate(pin[2], 12, Fill, buffer);

        *in = pin + 3;
        *out = pout + 12;
}

void
__vserest_unpack7_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;
        pout[11] = (pin[2] >> 12) & 0x7f;
        pout[12] = (pin[2] >> 5) & 0x7f;
        pout[13] = (pin[2] << 2) & 0x7f;
        pout[13] |= pin[3] >> 30;

        __vserest_bufupdate(pin[3], 30, Fill, buffer);

        *in = pin + 4;
        *out = pout + 14;
}

void
__vserest_unpack7_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;
        pout[11] = (pin[2] >> 12) & 0x7f;
        pout[12] = (pin[2] >> 5) & 0x7f;
        pout[13] = (pin[2] << 2) & 0x7f;
        pout[13] |= pin[3] >> 30;
        pout[14] = (pin[3] >> 23) & 0x7f;
        pout[15] = (pin[3] >> 16) & 0x7f;

        __vserest_bufupdate(pin[3], 16, Fill, buffer);

        *in = pin + 4;
        *out = pout + 16;
}

void
__vserest_unpack7_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;
        pout[11] = (pin[2] >> 12) & 0x7f;
        pout[12] = (pin[2] >> 5) & 0x7f;
        pout[13] = (pin[2] << 2) & 0x7f;
        pout[13] |= pin[3] >> 30;
        pout[14] = (pin[3] >> 23) & 0x7f;
        pout[15] = (pin[3] >> 16) & 0x7f;
        pout[16] = (pin[3] >> 9) & 0x7f;
        pout[17] = (pin[3] >> 2) & 0x7f;
        pout[18] = (pin[3] << 5) & 0x7f;
        pout[18] |= pin[4] >> 27;
        pout[19] = (pin[4] >> 20) & 0x7f;
        pout[20] = (pin[4] >> 13) & 0x7f;
        pout[21] = (pin[4] >> 6) & 0x7f;
        pout[22] = (pin[4] << 1) & 0x7f;
        pout[22] |= pin[5] >> 31;
        pout[23] = (pin[5] >> 24) & 0x7f;
        pout[24] = (pin[5] >> 17) & 0x7f;
        pout[25] = (pin[5] >> 10) & 0x7f;
        pout[26] = (pin[5] >> 3) & 0x7f;
        pout[27] = (pin[5] << 4) & 0x7f;
        pout[27] |= pin[6] >> 28;
        pout[28] = (pin[6] >> 21) & 0x7f;
        pout[29] = (pin[6] >> 14) & 0x7f;
        pout[30] = (pin[6] >> 7) & 0x7f;
        pout[31] = pin[6] & 0x7f;

        *in = pin + 7;
        *out = pout + 32;
}

void
__vserest_unpack7_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 25;
        pout[1] = (pin[0] >> 18) & 0x7f;
        pout[2] = (pin[0] >> 11) & 0x7f;
        pout[3] = (pin[0] >> 4) & 0x7f;
        pout[4] = (pin[0] << 3) & 0x7f;
        pout[4] |= pin[1] >> 29;
        pout[5] = (pin[1] >> 22) & 0x7f;
        pout[6] = (pin[1] >> 15) & 0x7f;
        pout[7] = (pin[1] >> 8) & 0x7f;
        pout[8] = (pin[1] >> 1) & 0x7f;
        pout[9] = (pin[1] << 6) & 0x7f;
        pout[9] |= pin[2] >> 26;
        pout[10] = (pin[2] >> 19) & 0x7f;
        pout[11] = (pin[2] >> 12) & 0x7f;
        pout[12] = (pin[2] >> 5) & 0x7f;
        pout[13] = (pin[2] << 2) & 0x7f;
        pout[13] |= pin[3] >> 30;
        pout[14] = (pin[3] >> 23) & 0x7f;
        pout[15] = (pin[3] >> 16) & 0x7f;
        pout[16] = (pin[3] >> 9) & 0x7f;
        pout[17] = (pin[3] >> 2) & 0x7f;
        pout[18] = (pin[3] << 5) & 0x7f;
        pout[18] |= pin[4] >> 27;
        pout[19] = (pin[4] >> 20) & 0x7f;
        pout[20] = (pin[4] >> 13) & 0x7f;
        pout[21] = (pin[4] >> 6) & 0x7f;
        pout[22] = (pin[4] << 1) & 0x7f;
        pout[22] |= pin[5] >> 31;
        pout[23] = (pin[5] >> 24) & 0x7f;
        pout[24] = (pin[5] >> 17) & 0x7f;
        pout[25] = (pin[5] >> 10) & 0x7f;
        pout[26] = (pin[5] >> 3) & 0x7f;
        pout[27] = (pin[5] << 4) & 0x7f;
        pout[27] |= pin[6] >> 28;
        pout[28] = (pin[6] >> 21) & 0x7f;
        pout[29] = (pin[6] >> 14) & 0x7f;
        pout[30] = (pin[6] >> 7) & 0x7f;
        pout[31] = pin[6] & 0x7f;
        pout[32] = pin[7] >> 25;
        pout[33] = (pin[7] >> 18) & 0x7f;
        pout[34] = (pin[7] >> 11) & 0x7f;
        pout[35] = (pin[7] >> 4) & 0x7f;
        pout[36] = (pin[7] << 3) & 0x7f;
        pout[36] |= pin[8] >> 29;
        pout[37] = (pin[8] >> 22) & 0x7f;
        pout[38] = (pin[8] >> 15) & 0x7f;
        pout[39] = (pin[8] >> 8) & 0x7f;
        pout[40] = (pin[8] >> 1) & 0x7f;
        pout[41] = (pin[8] << 6) & 0x7f;
        pout[41] |= pin[9] >> 26;
        pout[42] = (pin[9] >> 19) & 0x7f;
        pout[43] = (pin[9] >> 12) & 0x7f;
        pout[44] = (pin[9] >> 5) & 0x7f;
        pout[45] = (pin[9] << 2) & 0x7f;
        pout[45] |= pin[10] >> 30;
        pout[46] = (pin[10] >> 23) & 0x7f;
        pout[47] = (pin[10] >> 16) & 0x7f;
        pout[48] = (pin[10] >> 9) & 0x7f;
        pout[49] = (pin[10] >> 2) & 0x7f;
        pout[50] = (pin[10] << 5) & 0x7f;
        pout[50] |= pin[11] >> 27;
        pout[51] = (pin[11] >> 20) & 0x7f;
        pout[52] = (pin[11] >> 13) & 0x7f;
        pout[53] = (pin[11] >> 6) & 0x7f;
        pout[54] = (pin[11] << 1) & 0x7f;
        pout[54] |= pin[12] >> 31;
        pout[55] = (pin[12] >> 24) & 0x7f;
        pout[56] = (pin[12] >> 17) & 0x7f;
        pout[57] = (pin[12] >> 10) & 0x7f;
        pout[58] = (pin[12] >> 3) & 0x7f;
        pout[59] = (pin[12] << 4) & 0x7f;
        pout[59] |= pin[13] >> 28;
        pout[60] = (pin[13] >> 21) & 0x7f;
        pout[61] = (pin[13] >> 14) & 0x7f;
        pout[62] = (pin[13] >> 7) & 0x7f;
        pout[63] = pin[13] & 0x7f;

        *in = pin + 14;
        *out = pout + 64;
}

/* --- UNPACK 8 --- */
void
__vserest_unpack8_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;

        __vserest_bufupdate(pin[0], 24, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack8_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;

        __vserest_bufupdate(pin[0], 16, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack8_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack8_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;

        *in = pin + 1;
        *out = pout + 4;
}

void
__vserest_unpack8_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;

        __vserest_bufupdate(pin[1], 24, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack8_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 6;
}

void
__vserest_unpack8_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;

        __vserest_bufupdate(pin[1], 8, Fill, buffer);

        *in = pin + 2;
        *out = pout + 7;
}

void
__vserest_unpack8_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;

        *in = pin + 2;
        *out = pout + 8;
}

void
__vserest_unpack8_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;

        __vserest_bufupdate(pin[2], 24, Fill, buffer);

        *in = pin + 3;
        *out = pout + 9;
}

void
__vserest_unpack8_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;

        __vserest_bufupdate(pin[2], 16, Fill, buffer);

        *in = pin + 3;
        *out = pout + 10;
}

void
__vserest_unpack8_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;

        __vserest_bufupdate(pin[2], 8, Fill, buffer);

        *in = pin + 3;
        *out = pout + 11;
}

void
__vserest_unpack8_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;
        pout[11] = pin[2] & 0xff;

        *in = pin + 3;
        *out = pout + 12;
}

void
__vserest_unpack8_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;
        pout[11] = pin[2] & 0xff;
        pout[12] = pin[3] >> 24;
        pout[13] = (pin[3] >> 16) & 0xff;

        __vserest_bufupdate(pin[3], 16, Fill, buffer);

        *in = pin + 4;
        *out = pout + 14;
}

void
__vserest_unpack8_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;
        pout[11] = pin[2] & 0xff;
        pout[12] = pin[3] >> 24;
        pout[13] = (pin[3] >> 16) & 0xff;
        pout[14] = (pin[3] >> 8) & 0xff;
        pout[15] = pin[3] & 0xff;

        *in = pin + 4;
        *out = pout + 16;
}

void
__vserest_unpack8_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;
        pout[11] = pin[2] & 0xff;
        pout[12] = pin[3] >> 24;
        pout[13] = (pin[3] >> 16) & 0xff;
        pout[14] = (pin[3] >> 8) & 0xff;
        pout[15] = pin[3] & 0xff;
        pout[16] = pin[4] >> 24;
        pout[17] = (pin[4] >> 16) & 0xff;
        pout[18] = (pin[4] >> 8) & 0xff;
        pout[19] = pin[4] & 0xff;
        pout[20] = pin[5] >> 24;
        pout[21] = (pin[5] >> 16) & 0xff;
        pout[22] = (pin[5] >> 8) & 0xff;
        pout[23] = pin[5] & 0xff;
        pout[24] = pin[6] >> 24;
        pout[25] = (pin[6] >> 16) & 0xff;
        pout[26] = (pin[6] >> 8) & 0xff;
        pout[27] = pin[6] & 0xff;
        pout[28] = pin[7] >> 24;
        pout[29] = (pin[7] >> 16) & 0xff;
        pout[30] = (pin[7] >> 8) & 0xff;
        pout[31] = pin[7] & 0xff;

        *in = pin + 8;
        *out = pout + 32;
}

void
__vserest_unpack8_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 24;
        pout[1] = (pin[0] >> 16) & 0xff;
        pout[2] = (pin[0] >> 8) & 0xff;
        pout[3] = pin[0] & 0xff;
        pout[4] = pin[1] >> 24;
        pout[5] = (pin[1] >> 16) & 0xff;
        pout[6] = (pin[1] >> 8) & 0xff;
        pout[7] = pin[1] & 0xff;
        pout[8] = pin[2] >> 24;
        pout[9] = (pin[2] >> 16) & 0xff;
        pout[10] = (pin[2] >> 8) & 0xff;
        pout[11] = pin[2] & 0xff;
        pout[12] = pin[3] >> 24;
        pout[13] = (pin[3] >> 16) & 0xff;
        pout[14] = (pin[3] >> 8) & 0xff;
        pout[15] = pin[3] & 0xff;
        pout[16] = pin[4] >> 24;
        pout[17] = (pin[4] >> 16) & 0xff;
        pout[18] = (pin[4] >> 8) & 0xff;
        pout[19] = pin[4] & 0xff;
        pout[20] = pin[5] >> 24;
        pout[21] = (pin[5] >> 16) & 0xff;
        pout[22] = (pin[5] >> 8) & 0xff;
        pout[23] = pin[5] & 0xff;
        pout[24] = pin[6] >> 24;
        pout[25] = (pin[6] >> 16) & 0xff;
        pout[26] = (pin[6] >> 8) & 0xff;
        pout[27] = pin[6] & 0xff;
        pout[28] = pin[7] >> 24;
        pout[29] = (pin[7] >> 16) & 0xff;
        pout[30] = (pin[7] >> 8) & 0xff;
        pout[31] = pin[7] & 0xff;
        pout[32] = pin[8] >> 24;
        pout[33] = (pin[8] >> 16) & 0xff;
        pout[34] = (pin[8] >> 8) & 0xff;
        pout[35] = pin[8] & 0xff;
        pout[36] = pin[9] >> 24;
        pout[37] = (pin[9] >> 16) & 0xff;
        pout[38] = (pin[9] >> 8) & 0xff;
        pout[39] = pin[9] & 0xff;
        pout[40] = pin[10] >> 24;
        pout[41] = (pin[10] >> 16) & 0xff;
        pout[42] = (pin[10] >> 8) & 0xff;
        pout[43] = pin[10] & 0xff;
        pout[44] = pin[11] >> 24;
        pout[45] = (pin[11] >> 16) & 0xff;
        pout[46] = (pin[11] >> 8) & 0xff;
        pout[47] = pin[11] & 0xff;
        pout[48] = pin[12] >> 24;
        pout[49] = (pin[12] >> 16) & 0xff;
        pout[50] = (pin[12] >> 8) & 0xff;
        pout[51] = pin[12] & 0xff;
        pout[52] = pin[13] >> 24;
        pout[53] = (pin[13] >> 16) & 0xff;
        pout[54] = (pin[13] >> 8) & 0xff;
        pout[55] = pin[13] & 0xff;
        pout[56] = pin[14] >> 24;
        pout[57] = (pin[14] >> 16) & 0xff;
        pout[58] = (pin[14] >> 8) & 0xff;
        pout[59] = pin[14] & 0xff;
        pout[60] = pin[15] >> 24;
        pout[61] = (pin[15] >> 16) & 0xff;
        pout[62] = (pin[15] >> 8) & 0xff;
        pout[63] = pin[15] & 0xff;

        *in = pin + 16;
        *out = pout + 64;
}

/* --- UNPACK 9 --- */
void
__vserest_unpack9_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;

        __vserest_bufupdate(pin[0], 23, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack9_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;

        __vserest_bufupdate(pin[0], 14, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack9_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;

        __vserest_bufupdate(pin[0], 5, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack9_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;

        __vserest_bufupdate(pin[1], 28, Fill, buffer);

        *in = pin + 2;
        *out = pout + 4;
}

void
__vserest_unpack9_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;

        __vserest_bufupdate(pin[1], 19, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack9_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;

        __vserest_bufupdate(pin[1], 10, Fill, buffer);

        *in = pin + 2;
        *out = pout + 6;
}

void
__vserest_unpack9_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;
        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;

        __vserest_bufupdate(pin[1], 1, Fill, buffer);

        *in = pin + 2;
        *out = pout + 7;
}

void
__vserest_unpack9_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;

        __vserest_bufupdate(pin[2], 24, Fill, buffer);

        *in = pin + 3;
        *out = pout + 8;
}

void
__vserest_unpack9_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;

        __vserest_bufupdate(pin[2], 15, Fill, buffer);

        *in = pin + 3;
        *out = pout + 9;
}

void
__vserest_unpack9_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;

        __vserest_bufupdate(pin[2], 6, Fill, buffer);

        *in = pin + 3;
        *out = pout + 10;
}

void
__vserest_unpack9_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;

        __vserest_bufupdate(pin[3], 29, Fill, buffer);

        *in = pin + 4;
        *out = pout + 11;
}

void
__vserest_unpack9_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;
        pout[11] = (pin[3] >> 20) & 0x01ff;

        __vserest_bufupdate(pin[3], 20, Fill, buffer);

        *in = pin + 4;
        *out = pout + 12;
}

void
__vserest_unpack9_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;
        pout[11] = (pin[3] >> 20) & 0x01ff;
        pout[12] = (pin[3] >> 11) & 0x01ff;
        pout[13] = (pin[3] >> 2) & 0x01ff;

        __vserest_bufupdate(pin[3], 2, Fill, buffer);

        *in = pin + 4;
        *out = pout + 14;
}

void
__vserest_unpack9_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;
        pout[11] = (pin[3] >> 20) & 0x01ff;
        pout[12] = (pin[3] >> 11) & 0x01ff;
        pout[13] = (pin[3] >> 2) & 0x01ff;
        pout[14] = (pin[3] << 7) & 0x01ff;
        pout[14] |= pin[4] >> 25;
        pout[15] = (pin[4] >> 16) & 0x01ff;

        __vserest_bufupdate(pin[4], 16, Fill, buffer);

        *in = pin + 5;
        *out = pout + 16;
}

void
__vserest_unpack9_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;
        pout[11] = (pin[3] >> 20) & 0x01ff;
        pout[12] = (pin[3] >> 11) & 0x01ff;
        pout[13] = (pin[3] >> 2) & 0x01ff;
        pout[14] = (pin[3] << 7) & 0x01ff;
        pout[14] |= pin[4] >> 25;
        pout[15] = (pin[4] >> 16) & 0x01ff;
        pout[16] = (pin[4] >> 7) & 0x01ff;
        pout[17] = (pin[4] << 2) & 0x01ff;
        pout[17] |= pin[5] >> 30;
        pout[18] = (pin[5] >> 21) & 0x01ff;
        pout[19] = (pin[5] >> 12) & 0x01ff;
        pout[20] = (pin[5] >> 3) & 0x01ff;
        pout[21] = (pin[5] << 6) & 0x01ff;
        pout[21] |= pin[6] >> 26;
        pout[22] = (pin[6] >> 17) & 0x01ff;
        pout[23] = (pin[6] >> 8) & 0x01ff;
        pout[24] = (pin[6] << 1) & 0x01ff;
        pout[24] |= pin[7] >> 31;
        pout[25] = (pin[7] >> 22) & 0x01ff;
        pout[26] = (pin[7] >> 13) & 0x01ff;
        pout[27] = (pin[7] >> 4) & 0x01ff;
        pout[28] = (pin[7] << 5) & 0x01ff;
        pout[28] |= pin[8] >> 27;
        pout[29] = (pin[8] >> 18) & 0x01ff;
        pout[30] = (pin[8] >> 9) & 0x01ff;
        pout[31] = pin[8] & 0x01ff;

        *in = pin + 9;
        *out = pout + 32;
}

void
__vserest_unpack9_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in; 

        pout[0] = pin[0] >> 23;
        pout[1] = (pin[0] >> 14) & 0x01ff;
        pout[2] = (pin[0] >> 5) & 0x01ff;
        pout[3] = (pin[0] << 4) & 0x01ff;
        pout[3] |= pin[1] >> 28;
        pout[4] = (pin[1] >> 19) & 0x01ff;
        pout[5] = (pin[1] >> 10) & 0x01ff;
        pout[6] = (pin[1] >> 1) & 0x01ff;
        pout[7] = (pin[1] << 8) & 0x01ff;
        pout[7] |= pin[2] >> 24;
        pout[8] = (pin[2] >> 15) & 0x01ff;
        pout[9] = (pin[2] >> 6) & 0x01ff;
        pout[10] = (pin[2] << 3) & 0x01ff;
        pout[10] |= pin[3] >> 29;
        pout[11] = (pin[3] >> 20) & 0x01ff;
        pout[12] = (pin[3] >> 11) & 0x01ff;
        pout[13] = (pin[3] >> 2) & 0x01ff;
        pout[14] = (pin[3] << 7) & 0x01ff;
        pout[14] |= pin[4] >> 25;
        pout[15] = (pin[4] >> 16) & 0x01ff;
        pout[16] = (pin[4] >> 7) & 0x01ff;
        pout[17] = (pin[4] << 2) & 0x01ff;
        pout[17] |= pin[5] >> 30;
        pout[18] = (pin[5] >> 21) & 0x01ff;
        pout[19] = (pin[5] >> 12) & 0x01ff;
        pout[20] = (pin[5] >> 3) & 0x01ff;
        pout[21] = (pin[5] << 6) & 0x01ff;
        pout[21] |= pin[6] >> 26;
        pout[22] = (pin[6] >> 17) & 0x01ff;
        pout[23] = (pin[6] >> 8) & 0x01ff;
        pout[24] = (pin[6] << 1) & 0x01ff;
        pout[24] |= pin[7] >> 31;
        pout[25] = (pin[7] >> 22) & 0x01ff;
        pout[26] = (pin[7] >> 13) & 0x01ff;
        pout[27] = (pin[7] >> 4) & 0x01ff;
        pout[28] = (pin[7] << 5) & 0x01ff;
        pout[28] |= pin[8] >> 27;
        pout[29] = (pin[8] >> 18) & 0x01ff;
        pout[30] = (pin[8] >> 9) & 0x01ff;
        pout[31] = pin[8] & 0x01ff;
        pout[32] = pin[9] >> 23;
        pout[33] = (pin[9] >> 14) & 0x01ff;
        pout[34] = (pin[9] >> 5) & 0x01ff;
        pout[35] = (pin[9] << 4) & 0x01ff;
        pout[35] |= pin[10] >> 28;
        pout[36] = (pin[10] >> 19) & 0x01ff;
        pout[37] = (pin[10] >> 10) & 0x01ff;
        pout[38] = (pin[10] >> 1) & 0x01ff;
        pout[39] = (pin[10] << 8) & 0x01ff;
        pout[39] |= pin[11] >> 24;
        pout[40] = (pin[11] >> 15) & 0x01ff;
        pout[41] = (pin[11] >> 6) & 0x01ff;
        pout[42] = (pin[11] << 3) & 0x01ff;
        pout[42] |= pin[12] >> 29;
        pout[43] = (pin[12] >> 20) & 0x01ff;
        pout[44] = (pin[12] >> 11) & 0x01ff;
        pout[45] = (pin[12] >> 2) & 0x01ff;
        pout[46] = (pin[12] << 7) & 0x01ff;
        pout[46] |= pin[13] >> 25;
        pout[47] = (pin[13] >> 16) & 0x01ff;
        pout[48] = (pin[13] >> 7) & 0x01ff;
        pout[49] = (pin[13] << 2) & 0x01ff;
        pout[49] |= pin[14] >> 30;
        pout[50] = (pin[14] >> 21) & 0x01ff;
        pout[51] = (pin[14] >> 12) & 0x01ff;
        pout[52] = (pin[14] >> 3) & 0x01ff;
        pout[53] = (pin[14] << 6) & 0x01ff;
        pout[53] |= pin[15] >> 26;
        pout[54] = (pin[15] >> 17) & 0x01ff;
        pout[55] = (pin[15] >> 8) & 0x01ff;
        pout[56] = (pin[15] << 1) & 0x01ff;
        pout[56] |= pin[16] >> 31;
        pout[57] = (pin[16] >> 22) & 0x01ff;
        pout[58] = (pin[16] >> 13) & 0x01ff;
        pout[59] = (pin[16] >> 4) & 0x01ff;
        pout[60] = (pin[16] << 5) & 0x01ff;
        pout[60] |= pin[17] >> 27;
        pout[61] = (pin[17] >> 18) & 0x01ff;
        pout[62] = (pin[17] >> 9) & 0x01ff;
        pout[63] = pin[17] & 0x01ff;

        *in = pin + 18;
        *out = pout + 64;
}

/* --- UNPACK 10 --- */
void
__vserest_unpack10_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;

        __vserest_bufupdate(pin[0], 22, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack10_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;

        __vserest_bufupdate(pin[0], 12, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack10_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;

        __vserest_bufupdate(pin[0], 2, Fill, buffer);

        *in = pin + 1;
        *out = pout + 3;
}

void
__vserest_unpack10_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;

        __vserest_bufupdate(pin[1], 24, Fill, buffer);

        *in = pin + 2;
        *out = pout + 4;
}

void
__vserest_unpack10_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;

        __vserest_bufupdate(pin[1], 14, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack10_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;

        __vserest_bufupdate(pin[1], 4, Fill, buffer);

        *in = pin + 2;
        *out = pout + 6;
}

void
__vserest_unpack10_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;

        __vserest_bufupdate(pin[2], 26, Fill, buffer);

        *in = pin + 3;
        *out = pout + 7;
}

void
__vserest_unpack10_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;

        __vserest_bufupdate(pin[2], 16, Fill, buffer);

        *in = pin + 3;
        *out = pout + 8;
}

void
__vserest_unpack10_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;

        __vserest_bufupdate(pin[2], 6, Fill, buffer);

        *in = pin + 3;
        *out = pout + 9;
}

void
__vserest_unpack10_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;

        __vserest_bufupdate(pin[3], 28, Fill, buffer);

        *in = pin + 4;
        *out = pout + 10;
}

void
__vserest_unpack10_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;

        __vserest_bufupdate(pin[3], 18, Fill, buffer);

        *in = pin + 4;
        *out = pout + 11;
}

void
__vserest_unpack10_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;
        pout[11] = (pin[3] >> 8) & 0x03ff;

        __vserest_bufupdate(pin[3], 8, Fill, buffer);

        *in = pin + 4;
        *out = pout + 12;
}

void
__vserest_unpack10_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;
        pout[11] = (pin[3] >> 8) & 0x03ff;
        pout[12] = (pin[3] << 2) & 0x03ff;
        pout[12] |= pin[4] >> 30;
        pout[13] = (pin[4] >> 20) & 0x03ff;

        __vserest_bufupdate(pin[4], 20, Fill, buffer);

        *in = pin + 5;
        *out = pout + 14;
}

void
__vserest_unpack10_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;
        pout[11] = (pin[3] >> 8) & 0x03ff;
        pout[12] = (pin[3] << 2) & 0x03ff;
        pout[12] |= pin[4] >> 30;
        pout[13] = (pin[4] >> 20) & 0x03ff;
        pout[14] = (pin[4] >> 10) & 0x03ff;
        pout[15] = pin[4] & 0x03ff;

        *in = pin + 5;
        *out = pout + 16;
}

void
__vserest_unpack10_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;
        pout[11] = (pin[3] >> 8) & 0x03ff;
        pout[12] = (pin[3] << 2) & 0x03ff;
        pout[12] |= pin[4] >> 30;
        pout[13] = (pin[4] >> 20) & 0x03ff;
        pout[14] = (pin[4] >> 10) & 0x03ff;
        pout[15] = pin[4] & 0x03ff;
        pout[16] = pin[5] >> 22;
        pout[17] = (pin[5] >> 12) & 0x03ff;
        pout[18] = (pin[5] >> 2) & 0x03ff;
        pout[19] = (pin[5] << 8) & 0x03ff;
        pout[19] |= pin[6] >> 24;
        pout[20] = (pin[6] >> 14) & 0x03ff;
        pout[21] = (pin[6] >> 4) & 0x03ff;
        pout[22] = (pin[6] << 6) & 0x03ff;
        pout[22] |= pin[7] >> 26;
        pout[23] = (pin[7] >> 16) & 0x03ff;
        pout[24] = (pin[7] >> 6) & 0x03ff;
        pout[25] = (pin[7] << 4) & 0x03ff;
        pout[25] |= pin[8] >> 28;
        pout[26] = (pin[8] >> 18) & 0x03ff;
        pout[27] = (pin[8] >> 8) & 0x03ff;
        pout[28] = (pin[8] << 2) & 0x03ff;
        pout[28] |= pin[9] >> 30;
        pout[29] = (pin[9] >> 20) & 0x03ff;
        pout[30] = (pin[9] >> 10) & 0x03ff;
        pout[31] = pin[9] & 0x03ff;

        *in = pin + 10;
        *out = pout + 32;
}

void
__vserest_unpack10_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 22;
        pout[1] = (pin[0] >> 12) & 0x03ff;
        pout[2] = (pin[0] >> 2) & 0x03ff;
        pout[3] = (pin[0] << 8) & 0x03ff;
        pout[3] |= pin[1] >> 24;
        pout[4] = (pin[1] >> 14) & 0x03ff;
        pout[5] = (pin[1] >> 4) & 0x03ff;
        pout[6] = (pin[1] << 6) & 0x03ff;
        pout[6] |= pin[2] >> 26;
        pout[7] = (pin[2] >> 16) & 0x03ff;
        pout[8] = (pin[2] >> 6) & 0x03ff;
        pout[9] = (pin[2] << 4) & 0x03ff;
        pout[9] |= pin[3] >> 28;
        pout[10] = (pin[3] >> 18) & 0x03ff;
        pout[11] = (pin[3] >> 8) & 0x03ff;
        pout[12] = (pin[3] << 2) & 0x03ff;
        pout[12] |= pin[4] >> 30;
        pout[13] = (pin[4] >> 20) & 0x03ff;
        pout[14] = (pin[4] >> 10) & 0x03ff;
        pout[15] = pin[4] & 0x03ff;
        pout[16] = pin[5] >> 22;
        pout[17] = (pin[5] >> 12) & 0x03ff;
        pout[18] = (pin[5] >> 2) & 0x03ff;
        pout[19] = (pin[5] << 8) & 0x03ff;
        pout[19] |= pin[6] >> 24;
        pout[20] = (pin[6] >> 14) & 0x03ff;
        pout[21] = (pin[6] >> 4) & 0x03ff;
        pout[22] = (pin[6] << 6) & 0x03ff;
        pout[22] |= pin[7] >> 26;
        pout[23] = (pin[7] >> 16) & 0x03ff;
        pout[24] = (pin[7] >> 6) & 0x03ff;
        pout[25] = (pin[7] << 4) & 0x03ff;
        pout[25] |= pin[8] >> 28;
        pout[26] = (pin[8] >> 18) & 0x03ff;
        pout[27] = (pin[8] >> 8) & 0x03ff;
        pout[28] = (pin[8] << 2) & 0x03ff;
        pout[28] |= pin[9] >> 30;
        pout[29] = (pin[9] >> 20) & 0x03ff;
        pout[30] = (pin[9] >> 10) & 0x03ff;
        pout[31] = pin[9] & 0x03ff;
        pout[32] = pin[10] >> 22;
        pout[33] = (pin[10] >> 12) & 0x03ff;
        pout[34] = (pin[10] >> 2) & 0x03ff;
        pout[35] = (pin[10] << 8) & 0x03ff;
        pout[35] |= pin[11] >> 24;
        pout[36] = (pin[11] >> 14) & 0x03ff;
        pout[37] = (pin[11] >> 4) & 0x03ff;
        pout[38] = (pin[11] << 6) & 0x03ff;
        pout[38] |= pin[12] >> 26;
        pout[39] = (pin[12] >> 16) & 0x03ff;
        pout[40] = (pin[12] >> 6) & 0x03ff;
        pout[41] = (pin[12] << 4) & 0x03ff;
        pout[41] |= pin[13] >> 28;
        pout[42] = (pin[13] >> 18) & 0x03ff;
        pout[43] = (pin[13] >> 8) & 0x03ff;
        pout[44] = (pin[13] << 2) & 0x03ff;
        pout[44] |= pin[14] >> 30;
        pout[45] = (pin[14] >> 20) & 0x03ff;
        pout[46] = (pin[14] >> 10) & 0x03ff;
        pout[47] = pin[14] & 0x03ff;
        pout[48] = pin[15] >> 22;
        pout[49] = (pin[15] >> 12) & 0x03ff;
        pout[50] = (pin[15] >> 2) & 0x03ff;
        pout[51] = (pin[15] << 8) & 0x03ff;
        pout[51] |= pin[16] >> 24;
        pout[52] = (pin[16] >> 14) & 0x03ff;
        pout[53] = (pin[16] >> 4) & 0x03ff;
        pout[54] = (pin[16] << 6) & 0x03ff;
        pout[54] |= pin[17] >> 26;
        pout[55] = (pin[17] >> 16) & 0x03ff;
        pout[56] = (pin[17] >> 6) & 0x03ff;
        pout[57] = (pin[17] << 4) & 0x03ff;
        pout[57] |= pin[18] >> 28;
        pout[58] = (pin[18] >> 18) & 0x03ff;
        pout[59] = (pin[18] >> 8) & 0x03ff;
        pout[60] = (pin[18] << 2) & 0x03ff;
        pout[60] |= pin[19] >> 30;
        pout[61] = (pin[19] >> 20) & 0x03ff;
        pout[62] = (pin[19] >> 10) & 0x03ff;
        pout[63] = pin[19] & 0x03ff;

        *in = pin + 20;
        *out = pout + 64;
}

/* --- UNPACK 11 --- */
void
__vserest_unpack11_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;

        __vserest_bufupdate(pin[0], 21, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack11_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;

        __vserest_bufupdate(pin[0], 10, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack11_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;

        __vserest_bufupdate(pin[1], 31, Fill, buffer);

        *in = pin + 2;
        *out = pout + 3;
}

void
__vserest_unpack11_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;

        __vserest_bufupdate(pin[1], 20, Fill, buffer);

        *in = pin + 2;
        *out = pout + 4;
}

void
__vserest_unpack11_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;

        __vserest_bufupdate(pin[1], 9, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack11_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;

        __vserest_bufupdate(pin[2], 30, Fill, buffer);

        *in = pin + 3;
        *out = pout + 6;
}

void
__vserest_unpack11_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;

        __vserest_bufupdate(pin[2], 19, Fill, buffer);

        *in = pin + 3;
        *out = pout + 7;
}
void
__vserest_unpack11_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;

        __vserest_bufupdate(pin[2], 8, Fill, buffer);

        *in = pin + 3;
        *out = pout + 8;
}

void
__vserest_unpack11_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;

        __vserest_bufupdate(pin[3], 29, Fill, buffer);

        *in = pin + 4;
        *out = pout + 9;
}

void
__vserest_unpack11_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;

        __vserest_bufupdate(pin[3], 18, Fill, buffer);

        *in = pin + 4;
        *out = pout + 10;
}

void
__vserest_unpack11_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;

        __vserest_bufupdate(pin[3], 7, Fill, buffer);

        *in = pin + 4;
        *out = pout + 11;
}

void
__vserest_unpack11_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;
        pout[11] = (pin[3] << 4) & 0x07ff;
        pout[11] |= pin[4] >> 28;

        __vserest_bufupdate(pin[4], 28, Fill, buffer);

        *in = pin + 5;
        *out = pout + 12;
}

void
__vserest_unpack11_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;
        pout[11] = (pin[3] << 4) & 0x07ff;
        pout[11] |= pin[4] >> 28;
        pout[12] = (pin[4] >> 17) & 0x07ff;
        pout[13] = (pin[4] >> 6) & 0x07ff;

        __vserest_bufupdate(pin[4], 6, Fill, buffer);

        *in = pin + 5;
        *out = pout + 14;
}

void
__vserest_unpack11_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;
        pout[11] = (pin[3] << 4) & 0x07ff;
        pout[11] |= pin[4] >> 28;
        pout[12] = (pin[4] >> 17) & 0x07ff;
        pout[13] = (pin[4] >> 6) & 0x07ff;
        pout[14] = (pin[4] << 5) & 0x07ff;
        pout[14] |= pin[5] >> 27;
        pout[15] = (pin[5] >> 16) & 0x07ff;

        __vserest_bufupdate(pin[5], 16, Fill, buffer);

        *in = pin + 6;
        *out = pout + 16;
}

void
__vserest_unpack11_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;
        pout[11] = (pin[3] << 4) & 0x07ff;
        pout[11] |= pin[4] >> 28;
        pout[12] = (pin[4] >> 17) & 0x07ff;
        pout[13] = (pin[4] >> 6) & 0x07ff;
        pout[14] = (pin[4] << 5) & 0x07ff;
        pout[14] |= pin[5] >> 27;
        pout[15] = (pin[5] >> 16) & 0x07ff;
        pout[16] = (pin[5] >> 5) & 0x07ff;
        pout[17] = (pin[5] << 6) & 0x07ff;
        pout[17] |= pin[6] >> 26;
        pout[18] = (pin[6] >> 15) & 0x07ff;
        pout[19] = (pin[6] >> 4) & 0x07ff;
        pout[20] = (pin[6] << 7) & 0x07ff;
        pout[20] |= pin[7] >> 25;
        pout[21] = (pin[7] >> 14) & 0x07ff;
        pout[22] = (pin[7] >> 3) & 0x07ff;
        pout[23] = (pin[7] << 8) & 0x07ff;
        pout[23] |= pin[8] >> 24;
        pout[24] = (pin[8] >> 13) & 0x07ff;
        pout[25] = (pin[8] >> 2) & 0x07ff;
        pout[26] = (pin[8] << 9) & 0x07ff;
        pout[26] |= pin[9] >> 23;
        pout[27] = (pin[9] >> 12) & 0x07ff;
        pout[28] = (pin[9] >> 1) & 0x07ff;
        pout[29] = (pin[9] << 10) & 0x07ff;
        pout[29] |= pin[10] >> 22;
        pout[30] = (pin[10] >> 11) & 0x07ff;
        pout[31] = pin[10] & 0x07ff;

        *in = pin + 11;
        *out = pout + 32;
}

void
__vserest_unpack11_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 21;
        pout[1] = (pin[0] >> 10) & 0x07ff;
        pout[2] = (pin[0] << 1) & 0x07ff;
        pout[2] |= pin[1] >> 31;
        pout[3] = (pin[1] >> 20) & 0x07ff;
        pout[4] = (pin[1] >> 9) & 0x07ff;
        pout[5] = (pin[1] << 2) & 0x07ff;
        pout[5] |= pin[2] >> 30;
        pout[6] = (pin[2] >> 19) & 0x07ff;
        pout[7] = (pin[2] >> 8) & 0x07ff;
        pout[8] = (pin[2] << 3) & 0x07ff;
        pout[8] |= pin[3] >> 29;
        pout[9] = (pin[3] >> 18) & 0x07ff;
        pout[10] = (pin[3] >> 7) & 0x07ff;
        pout[11] = (pin[3] << 4) & 0x07ff;
        pout[11] |= pin[4] >> 28;
        pout[12] = (pin[4] >> 17) & 0x07ff;
        pout[13] = (pin[4] >> 6) & 0x07ff;
        pout[14] = (pin[4] << 5) & 0x07ff;
        pout[14] |= pin[5] >> 27;
        pout[15] = (pin[5] >> 16) & 0x07ff;
        pout[16] = (pin[5] >> 5) & 0x07ff;
        pout[17] = (pin[5] << 6) & 0x07ff;
        pout[17] |= pin[6] >> 26;
        pout[18] = (pin[6] >> 15) & 0x07ff;
        pout[19] = (pin[6] >> 4) & 0x07ff;
        pout[20] = (pin[6] << 7) & 0x07ff;
        pout[20] |= pin[7] >> 25;
        pout[21] = (pin[7] >> 14) & 0x07ff;
        pout[22] = (pin[7] >> 3) & 0x07ff;
        pout[23] = (pin[7] << 8) & 0x07ff;
        pout[23] |= pin[8] >> 24;
        pout[24] = (pin[8] >> 13) & 0x07ff;
        pout[25] = (pin[8] >> 2) & 0x07ff;
        pout[26] = (pin[8] << 9) & 0x07ff;
        pout[26] |= pin[9] >> 23;
        pout[27] = (pin[9] >> 12) & 0x07ff;
        pout[28] = (pin[9] >> 1) & 0x07ff;
        pout[29] = (pin[9] << 10) & 0x07ff;
        pout[29] |= pin[10] >> 22;
        pout[30] = (pin[10] >> 11) & 0x07ff;
        pout[31] = pin[10] & 0x07ff;
        pout[32] = pin[11] >> 21;
        pout[33] = (pin[11] >> 10) & 0x07ff;
        pout[34] = (pin[11] << 1) & 0x07ff;
        pout[34] |= pin[12] >> 31;
        pout[35] = (pin[12] >> 20) & 0x07ff;
        pout[36] = (pin[12] >> 9) & 0x07ff;
        pout[37] = (pin[12] << 2) & 0x07ff;
        pout[37] |= pin[13] >> 30;
        pout[38] = (pin[13] >> 19) & 0x07ff;
        pout[39] = (pin[13] >> 8) & 0x07ff;
        pout[40] = (pin[13] << 3) & 0x07ff;
        pout[40] |= pin[14] >> 29;
        pout[41] = (pin[14] >> 18) & 0x07ff;
        pout[42] = (pin[14] >> 7) & 0x07ff;
        pout[43] = (pin[14] << 4) & 0x07ff;
        pout[43] |= pin[15] >> 28;
        pout[44] = (pin[15] >> 17) & 0x07ff;
        pout[45] = (pin[15] >> 6) & 0x07ff;
        pout[46] = (pin[15] << 5) & 0x07ff;
        pout[46] |= pin[16] >> 27;
        pout[47] = (pin[16] >> 16) & 0x07ff;
        pout[48] = (pin[16] >> 5) & 0x07ff;
        pout[49] = (pin[16] << 6) & 0x07ff;
        pout[49] |= pin[17] >> 26;
        pout[50] = (pin[17] >> 15) & 0x07ff;
        pout[51] = (pin[17] >> 4) & 0x07ff;
        pout[52] = (pin[17] << 7) & 0x07ff;
        pout[52] |= pin[18] >> 25;
        pout[53] = (pin[18] >> 14) & 0x07ff;
        pout[54] = (pin[18] >> 3) & 0x07ff;
        pout[55] = (pin[18] << 8) & 0x07ff;
        pout[55] |= pin[19] >> 24;
        pout[56] = (pin[19] >> 13) & 0x07ff;
        pout[57] = (pin[19] >> 2) & 0x07ff;
        pout[58] = (pin[19] << 9) & 0x07ff;
        pout[58] |= pin[20] >> 23;
        pout[59] = (pin[20] >> 12) & 0x07ff;
        pout[60] = (pin[20] >> 1) & 0x07ff;
        pout[61] = (pin[20] << 10) & 0x07ff;
        pout[61] |= pin[21] >> 22;
        pout[62] = (pin[21] >> 11) & 0x07ff;
        pout[63] = pin[21] & 0x07ff;

        *in = pin + 22;
        *out = pout + 64;
}

/* --- UNPACK 12 --- */
void
__vserest_unpack12_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;

        __vserest_bufupdate(pin[0], 20, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack12_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;

        __vserest_bufupdate(pin[0], 8, Fill, buffer);

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack12_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;

        __vserest_bufupdate(pin[1], 28, Fill, buffer);

        *in = pin + 2;
        *out = pout + 3;
}

void
__vserest_unpack12_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 4;
}

void
__vserest_unpack12_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;

        __vserest_bufupdate(pin[1], 4, Fill, buffer);

        *in = pin + 2;
        *out = pout + 5;
}

void
__vserest_unpack12_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;

        __vserest_bufupdate(pin[2], 24, Fill, buffer);

        *in = pin + 3;
        *out = pout + 6;
}

void
__vserest_unpack12_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;

        __vserest_bufupdate(pin[2], 12, Fill, buffer);

        *in = pin + 3;
        *out = pout + 7;
}

void
__vserest_unpack12_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;

        *in = pin + 3;
        *out = pout + 8;
}

void
__vserest_unpack12_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;

        __vserest_bufupdate(pin[3], 20, Fill, buffer);

        *in = pin + 4;
        *out = pout + 9;
}

void
__vserest_unpack12_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;

        __vserest_bufupdate(pin[3], 8, Fill, buffer);

        *in = pin + 4;
        *out = pout + 10;
}

void
__vserest_unpack12_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;

        __vserest_bufupdate(pin[4], 28, Fill, buffer);

        *in = pin + 5;
        *out = pout + 11;
}

void
__vserest_unpack12_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;
        pout[11] = (pin[4] >> 16) & 0x0fff;

        __vserest_bufupdate(pin[4], 16, Fill, buffer);

        *in = pin + 5;
        *out = pout + 12;
}

void
__vserest_unpack12_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;
        pout[11] = (pin[4] >> 16) & 0x0fff;
        pout[12] = (pin[4] >> 4) & 0x0fff;
        pout[13] = (pin[4] << 8) & 0x0fff;
        pout[13] |= pin[5] >> 24;

        __vserest_bufupdate(pin[5], 24, Fill, buffer);

        *in = pin + 6;
        *out = pout + 14;
}

void
__vserest_unpack12_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;
        pout[11] = (pin[4] >> 16) & 0x0fff;
        pout[12] = (pin[4] >> 4) & 0x0fff;
        pout[13] = (pin[4] << 8) & 0x0fff;
        pout[13] |= pin[5] >> 24;
        pout[14] = (pin[5] >> 12) & 0x0fff;
        pout[15] = pin[5] & 0x0fff;

        *in = pin + 6;
        *out = pout + 16;
}

void
__vserest_unpack12_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;
        pout[11] = (pin[4] >> 16) & 0x0fff;
        pout[12] = (pin[4] >> 4) & 0x0fff;
        pout[13] = (pin[4] << 8) & 0x0fff;
        pout[13] |= pin[5] >> 24;
        pout[14] = (pin[5] >> 12) & 0x0fff;
        pout[15] = pin[5] & 0x0fff;
        pout[16] = pin[6] >> 20;
        pout[17] = (pin[6] >> 8) & 0x0fff;
        pout[18] = (pin[6] << 4) & 0x0fff;
        pout[18] |= pin[7] >> 28;
        pout[19] = (pin[7] >> 16) & 0x0fff;
        pout[20] = (pin[7] >> 4) & 0x0fff;
        pout[21] = (pin[7] << 8) & 0x0fff;
        pout[21] |= pin[8] >> 24;
        pout[22] = (pin[8] >> 12) & 0x0fff;
        pout[23] = pin[8] & 0x0fff;
        pout[24] = pin[9] >> 20;
        pout[25] = (pin[9] >> 8) & 0x0fff;
        pout[26] = (pin[9] << 4) & 0x0fff;
        pout[26] |= pin[10] >> 28;
        pout[27] = (pin[10] >> 16) & 0x0fff;
        pout[28] = (pin[10] >> 4) & 0x0fff;
        pout[29] = (pin[10] << 8) & 0x0fff;
        pout[29] |= pin[11] >> 24;
        pout[30] = (pin[11] >> 12) & 0x0fff;
        pout[31] = pin[11] & 0x0fff;

        *in = pin + 12;
        *out = pout + 32;
}

void
__vserest_unpack12_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 20;
        pout[1] = (pin[0] >> 8) & 0x0fff;
        pout[2] = (pin[0] << 4) & 0x0fff;
        pout[2] |= pin[1] >> 28;
        pout[3] = (pin[1] >> 16) & 0x0fff;
        pout[4] = (pin[1] >> 4) & 0x0fff;
        pout[5] = (pin[1] << 8) & 0x0fff;
        pout[5] |= pin[2] >> 24;
        pout[6] = (pin[2] >> 12) & 0x0fff;
        pout[7] = pin[2] & 0x0fff;
        pout[8] = pin[3] >> 20;
        pout[9] = (pin[3] >> 8) & 0x0fff;
        pout[10] = (pin[3] << 4) & 0x0fff;
        pout[10] |= pin[4] >> 28;
        pout[11] = (pin[4] >> 16) & 0x0fff;
        pout[12] = (pin[4] >> 4) & 0x0fff;
        pout[13] = (pin[4] << 8) & 0x0fff;
        pout[13] |= pin[5] >> 24;
        pout[14] = (pin[5] >> 12) & 0x0fff;
        pout[15] = pin[5] & 0x0fff;
        pout[16] = pin[6] >> 20;
        pout[17] = (pin[6] >> 8) & 0x0fff;
        pout[18] = (pin[6] << 4) & 0x0fff;
        pout[18] |= pin[7] >> 28;
        pout[19] = (pin[7] >> 16) & 0x0fff;
        pout[20] = (pin[7] >> 4) & 0x0fff;
        pout[21] = (pin[7] << 8) & 0x0fff;
        pout[21] |= pin[8] >> 24;
        pout[22] = (pin[8] >> 12) & 0x0fff;
        pout[23] = pin[8] & 0x0fff;
        pout[24] = pin[9] >> 20;
        pout[25] = (pin[9] >> 8) & 0x0fff;
        pout[26] = (pin[9] << 4) & 0x0fff;
        pout[26] |= pin[10] >> 28;
        pout[27] = (pin[10] >> 16) & 0x0fff;
        pout[28] = (pin[10] >> 4) & 0x0fff;
        pout[29] = (pin[10] << 8) & 0x0fff;
        pout[29] |= pin[11] >> 24;
        pout[30] = (pin[11] >> 12) & 0x0fff;
        pout[31] = pin[11] & 0x0fff;
        pout[32] = pin[12] >> 20;
        pout[33] = (pin[12] >> 8) & 0x0fff;
        pout[34] = (pin[12] << 4) & 0x0fff;
        pout[34] |= pin[13] >> 28;
        pout[35] = (pin[13] >> 16) & 0x0fff;
        pout[36] = (pin[13] >> 4) & 0x0fff;
        pout[37] = (pin[13] << 8) & 0x0fff;
        pout[37] |= pin[14] >> 24;
        pout[38] = (pin[14] >> 12) & 0x0fff;
        pout[39] = pin[14] & 0x0fff;
        pout[40] = pin[15] >> 20;
        pout[41] = (pin[15] >> 8) & 0x0fff;
        pout[42] = (pin[15] << 4) & 0x0fff;
        pout[42] |= pin[16] >> 28;
        pout[43] = (pin[16] >> 16) & 0x0fff;
        pout[44] = (pin[16] >> 4) & 0x0fff;
        pout[45] = (pin[16] << 8) & 0x0fff;
        pout[45] |= pin[17] >> 24;
        pout[46] = (pin[17] >> 12) & 0x0fff;
        pout[47] = pin[17] & 0x0fff;
        pout[48] = pin[18] >> 20;
        pout[49] = (pin[18] >> 8) & 0x0fff;
        pout[50] = (pin[18] << 4) & 0x0fff;
        pout[50] |= pin[19] >> 28;
        pout[51] = (pin[19] >> 16) & 0x0fff;
        pout[52] = (pin[19] >> 4) & 0x0fff;
        pout[53] = (pin[19] << 8) & 0x0fff;
        pout[53] |= pin[20] >> 24;
        pout[54] = (pin[20] >> 12) & 0x0fff;
        pout[55] = pin[20] & 0x0fff;
        pout[56] = pin[21] >> 20;
        pout[57] = (pin[21] >> 8) & 0x0fff;
        pout[58] = (pin[21] << 4) & 0x0fff;
        pout[58] |= pin[22] >> 28;
        pout[59] = (pin[22] >> 16) & 0x0fff;
        pout[60] = (pin[22] >> 4) & 0x0fff;
        pout[61] = (pin[22] << 8) & 0x0fff;
        pout[61] |= pin[23] >> 24;
        pout[62] = (pin[23] >> 12) & 0x0fff;
        pout[63] = pin[23] & 0x0fff;

        *in = pin + 24;
        *out = pout + 64;
}

/* --- UNPACK 16 --- */
void
__vserest_unpack16_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;

        __vserest_bufupdate(pin[0], 16, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack16_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;

        *in = pin + 1;
        *out = pout + 2;
}

void
__vserest_unpack16_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;

        __vserest_bufupdate(pin[1], 16, Fill, buffer);

        *in = pin + 2;
        *out = pout + 3;
}

void
__vserest_unpack16_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;

        *in = pin + 2;
        *out = pout + 4;
}

void
__vserest_unpack16_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;

        __vserest_bufupdate(pin[2], 16, Fill, buffer);

        *in = pin + 3;
        *out = pout + 5;
}

void
__vserest_unpack16_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;

        *in = pin + 3;
        *out = pout + 6;
}

void
__vserest_unpack16_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;

        __vserest_bufupdate(pin[3], 16, Fill, buffer);

        *in = pin + 4;
        *out = pout + 7;
}

void
__vserest_unpack16_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;

        *in = pin + 4;
        *out = pout + 8;
}

void
__vserest_unpack16_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;

        __vserest_bufupdate(pin[4], 16, Fill, buffer);

        *in = pin + 5;
        *out = pout + 9;
}

void
__vserest_unpack16_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;

        *in = pin + 5;
        *out = pout + 10;
}

void
__vserest_unpack16_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;

        __vserest_bufupdate(pin[5], 16, Fill, buffer);

        *in = pin + 6;
        *out = pout + 11;
}

void
__vserest_unpack16_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;
        pout[11] = pin[5] & 0xffff;

        *in = pin + 6;
        *out = pout + 12;
}

void
__vserest_unpack16_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;
        pout[11] = pin[5] & 0xffff;
        pout[12] = pin[6] >> 16;
        pout[13] = pin[6] & 0xffff;

        *in = pin + 7;
        *out = pout + 14;
}

void
__vserest_unpack16_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;
        pout[11] = pin[5] & 0xffff;
        pout[12] = pin[6] >> 16;
        pout[13] = pin[6] & 0xffff;
        pout[14] = pin[7] >> 16;
        pout[15] = pin[7] & 0xffff;

        *in = pin + 8;
        *out = pout + 16;
}

void
__vserest_unpack16_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;
        pout[11] = pin[5] & 0xffff;
        pout[12] = pin[6] >> 16;
        pout[13] = pin[6] & 0xffff;
        pout[14] = pin[7] >> 16;
        pout[15] = pin[7] & 0xffff;
        pout[16] = pin[8] >> 16;
        pout[17] = pin[8] & 0xffff;
        pout[18] = pin[9] >> 16;
        pout[19] = pin[9] & 0xffff;
        pout[20] = pin[10] >> 16;
        pout[21] = pin[10] & 0xffff;
        pout[22] = pin[11] >> 16;
        pout[23] = pin[11] & 0xffff;
        pout[24] = pin[12] >> 16;
        pout[25] = pin[12] & 0xffff;
        pout[26] = pin[13] >> 16;
        pout[27] = pin[13] & 0xffff;
        pout[28] = pin[14] >> 16;
        pout[29] = pin[14] & 0xffff;
        pout[30] = pin[15] >> 16;
        pout[31] = pin[15] & 0xffff;

        *in = pin + 16;
        *out = pout + 32;
}

void
__vserest_unpack16_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 16;
        pout[1] = pin[0] & 0xffff;
        pout[2] = pin[1] >> 16;
        pout[3] = pin[1] & 0xffff;
        pout[4] = pin[2] >> 16;
        pout[5] = pin[2] & 0xffff;
        pout[6] = pin[3] >> 16;
        pout[7] = pin[3] & 0xffff;
        pout[8] = pin[4] >> 16;
        pout[9] = pin[4] & 0xffff;
        pout[10] = pin[5] >> 16;
        pout[11] = pin[5] & 0xffff;
        pout[12] = pin[6] >> 16;
        pout[13] = pin[6] & 0xffff;
        pout[14] = pin[7] >> 16;
        pout[15] = pin[7] & 0xffff;
        pout[16] = pin[8] >> 16;
        pout[17] = pin[8] & 0xffff;
        pout[18] = pin[9] >> 16;
        pout[19] = pin[9] & 0xffff;
        pout[20] = pin[10] >> 16;
        pout[21] = pin[10] & 0xffff;
        pout[22] = pin[11] >> 16;
        pout[23] = pin[11] & 0xffff;
        pout[24] = pin[12] >> 16;
        pout[25] = pin[12] & 0xffff;
        pout[26] = pin[13] >> 16;
        pout[27] = pin[13] & 0xffff;
        pout[28] = pin[14] >> 16;
        pout[29] = pin[14] & 0xffff;
        pout[30] = pin[15] >> 16;
        pout[31] = pin[15] & 0xffff;
        pout[32] = pin[16] >> 16;
        pout[33] = pin[16] & 0xffff;
        pout[34] = pin[17] >> 16;
        pout[35] = pin[17] & 0xffff;
        pout[36] = pin[18] >> 16;
        pout[37] = pin[18] & 0xffff;
        pout[38] = pin[19] >> 16;
        pout[39] = pin[19] & 0xffff;
        pout[40] = pin[20] >> 16;
        pout[41] = pin[20] & 0xffff;
        pout[42] = pin[21] >> 16;
        pout[43] = pin[21] & 0xffff;
        pout[44] = pin[22] >> 16;
        pout[45] = pin[22] & 0xffff;
        pout[46] = pin[23] >> 16;
        pout[47] = pin[23] & 0xffff;
        pout[48] = pin[24] >> 16;
        pout[49] = pin[24] & 0xffff;
        pout[50] = pin[25] >> 16;
        pout[51] = pin[25] & 0xffff;
        pout[52] = pin[26] >> 16;
        pout[53] = pin[26] & 0xffff;
        pout[54] = pin[27] >> 16;
        pout[55] = pin[27] & 0xffff;
        pout[56] = pin[28] >> 16;
        pout[57] = pin[28] & 0xffff;
        pout[58] = pin[29] >> 16;
        pout[59] = pin[29] & 0xffff;
        pout[60] = pin[30] >> 16;
        pout[61] = pin[30] & 0xffff;
        pout[62] = pin[31] >> 16;
        pout[63] = pin[31] & 0xffff;

        *in = pin + 32;
        *out = pout + 64;
}

/* --- UNPACK 20 --- */
void
__vserest_unpack20_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;

        __vserest_bufupdate(pin[0], 12, Fill, buffer);

        *in = pin + 1;
        *out = pout + 1;
}

void
__vserest_unpack20_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;

        __vserest_bufupdate(pin[1], 24, Fill, buffer);

        *in = pin + 2;
        *out = pout + 2;
}

void
__vserest_unpack20_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;

        __vserest_bufupdate(pin[1], 4, Fill, buffer);

        *in = pin + 2;
        *out = pout + 3;
}

void
__vserest_unpack20_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;

        __vserest_bufupdate(pin[2], 16, Fill, buffer);

        *in = pin + 3;
        *out = pout + 4;
}

void
__vserest_unpack20_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;

        __vserest_bufupdate(pin[3], 28, Fill, buffer);

        *in = pin + 4;
        *out = pout + 5;
}

void
__vserest_unpack20_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;

        __vserest_bufupdate(pin[3], 8, Fill, buffer);

        *in = pin + 4;
        *out = pout + 6;
}

void
__vserest_unpack20_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;

        __vserest_bufupdate(pin[4], 20, Fill, buffer);

        *in = pin + 5;
        *out = pout + 7;
}

void
__vserest_unpack20_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;

        *in = pin + 5;
        *out = pout + 8;
}

void
__vserest_unpack20_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;

        __vserest_bufupdate(pin[5], 12, Fill, buffer);

        *in = pin + 6;
        *out = pout + 9;
}

void
__vserest_unpack20_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;

        __vserest_bufupdate(pin[6], 24, Fill, buffer);

        *in = pin + 7;
        *out = pout + 10;
}

void
__vserest_unpack20_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;

        __vserest_bufupdate(pin[6], 4, Fill, buffer);

        *in = pin + 7;
        *out = pout + 11;
}

void
__vserest_unpack20_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;
        pout[11] = (pin[6] << 16) & 0xfffff;
        pout[11] |= pin[7] >> 16;

        __vserest_bufupdate(pin[7], 16, Fill, buffer);
        *in = pin + 8;
        *out = pout + 12;
}

void
__vserest_unpack20_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;
        pout[11] = (pin[6] << 16) & 0xfffff;
        pout[11] |= pin[7] >> 16;
        pout[12] = (pin[7] << 4) & 0xfffff;
        pout[12] |= pin[8] >> 28;
        pout[13] = (pin[8] >> 8) & 0xfffff;

        __vserest_bufupdate(pin[8], 8, Fill, buffer);

        *in = pin + 9;
        *out = pout + 14;
}

void
__vserest_unpack20_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;
        pout[11] = (pin[6] << 16) & 0xfffff;
        pout[11] |= pin[7] >> 16;
        pout[12] = (pin[7] << 4) & 0xfffff;
        pout[12] |= pin[8] >> 28;
        pout[13] = (pin[8] >> 8) & 0xfffff;
        pout[14] = (pin[8] << 12) & 0xfffff;
        pout[14] |= pin[9] >> 20;
        pout[15] = pin[9] & 0xfffff;

        *in = pin + 10;
        *out = pout + 16;
}

void
__vserest_unpack20_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;
        pout[11] = (pin[6] << 16) & 0xfffff;
        pout[11] |= pin[7] >> 16;
        pout[12] = (pin[7] << 4) & 0xfffff;
        pout[12] |= pin[8] >> 28;
        pout[13] = (pin[8] >> 8) & 0xfffff;
        pout[14] = (pin[8] << 12) & 0xfffff;
        pout[14] |= pin[9] >> 20;
        pout[15] = pin[9] & 0xfffff;
        pout[16] = pin[10] >> 12;
        pout[17] = (pin[10] << 8) & 0x0fffff;
        pout[17] |= pin[11] >> 24;
        pout[18] = (pin[11] >> 4) & 0xfffff;
        pout[19] = (pin[11] << 16) & 0xfffff;
        pout[19] |= pin[12] >> 16;
        pout[20] = (pin[12] << 4) & 0xfffff;
        pout[20] |= pin[13] >> 28;
        pout[21] = (pin[13] >> 8) & 0xfffff;
        pout[22] = (pin[13] << 12) & 0xfffff;
        pout[22] |= pin[14] >> 20;
        pout[23] = pin[14] & 0xfffff;
        pout[24] = pin[15] >> 12;
        pout[25] = (pin[15] << 8) & 0x0fffff;
        pout[25] |= pin[16] >> 24;
        pout[26] = (pin[16] >> 4) & 0xfffff;
        pout[27] = (pin[16] << 16) & 0xfffff;
        pout[27] |= pin[17] >> 16;
        pout[28] = (pin[17] << 4) & 0xfffff;
        pout[28] |= pin[18] >> 28;
        pout[29] = (pin[18] >> 8) & 0xfffff;
        pout[30] = (pin[18] << 12) & 0xfffff;
        pout[30] |= pin[19] >> 20;
        pout[31] = pin[19] & 0xfffff;

        *in = pin + 20;
        *out = pout + 32;
}

void
__vserest_unpack20_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] >> 12;
        pout[1] = (pin[0] << 8) & 0x0fffff;
        pout[1] |= pin[1] >> 24;
        pout[2] = (pin[1] >> 4) & 0xfffff;
        pout[3] = (pin[1] << 16) & 0xfffff;
        pout[3] |= pin[2] >> 16;
        pout[4] = (pin[2] << 4) & 0xfffff;
        pout[4] |= pin[3] >> 28;
        pout[5] = (pin[3] >> 8) & 0xfffff;
        pout[6] = (pin[3] << 12) & 0xfffff;
        pout[6] |= pin[4] >> 20;
        pout[7] = pin[4] & 0xfffff;
        pout[8] = pin[5] >> 12;
        pout[9] = (pin[5] << 8) & 0x0fffff;
        pout[9] |= pin[6] >> 24;
        pout[10] = (pin[6] >> 4) & 0xfffff;
        pout[11] = (pin[6] << 16) & 0xfffff;
        pout[11] |= pin[7] >> 16;
        pout[12] = (pin[7] << 4) & 0xfffff;
        pout[12] |= pin[8] >> 28;
        pout[13] = (pin[8] >> 8) & 0xfffff;
        pout[14] = (pin[8] << 12) & 0xfffff;
        pout[14] |= pin[9] >> 20;
        pout[15] = pin[9] & 0xfffff;
        pout[16] = pin[10] >> 12;
        pout[17] = (pin[10] << 8) & 0x0fffff;
        pout[17] |= pin[11] >> 24;
        pout[18] = (pin[11] >> 4) & 0xfffff;
        pout[19] = (pin[11] << 16) & 0xfffff;
        pout[19] |= pin[12] >> 16;
        pout[20] = (pin[12] << 4) & 0xfffff;
        pout[20] |= pin[13] >> 28;
        pout[21] = (pin[13] >> 8) & 0xfffff;
        pout[22] = (pin[13] << 12) & 0xfffff;
        pout[22] |= pin[14] >> 20;
        pout[23] = pin[14] & 0xfffff;
        pout[24] = pin[15] >> 12;
        pout[25] = (pin[15] << 8) & 0x0fffff;
        pout[25] |= pin[16] >> 24;
        pout[26] = (pin[16] >> 4) & 0xfffff;
        pout[27] = (pin[16] << 16) & 0xfffff;
        pout[27] |= pin[17] >> 16;
        pout[28] = (pin[17] << 4) & 0xfffff;
        pout[28] |= pin[18] >> 28;
        pout[29] = (pin[18] >> 8) & 0xfffff;
        pout[30] = (pin[18] << 12) & 0xfffff;
        pout[30] |= pin[19] >> 20;
        pout[31] = pin[19] & 0xfffff;
        pout[32] = pin[20] >> 12;
        pout[33] = (pin[20] << 8) & 0x0fffff;
        pout[33] |= pin[21] >> 24;
        pout[34] = (pin[21] >> 4) & 0xfffff;
        pout[35] = (pin[21] << 16) & 0xfffff;
        pout[35] |= pin[22] >> 16;
        pout[36] = (pin[22] << 4) & 0xfffff;
        pout[36] |= pin[23] >> 28;
        pout[37] = (pin[23] >> 8) & 0xfffff;
        pout[38] = (pin[23] << 12) & 0xfffff;
        pout[38] |= pin[24] >> 20;
        pout[39] = pin[24] & 0xfffff;
        pout[40] = pin[25] >> 12;
        pout[41] = (pin[25] << 8) & 0x0fffff;
        pout[41] |= pin[26] >> 24;
        pout[42] = (pin[26] >> 4) & 0xfffff;
        pout[43] = (pin[26] << 16) & 0xfffff;
        pout[43] |= pin[27] >> 16;
        pout[44] = (pin[27] << 4) & 0xfffff;
        pout[44] |= pin[28] >> 28;
        pout[45] = (pin[28] >> 8) & 0xfffff;
        pout[46] = (pin[28] << 12) & 0xfffff;
        pout[46] |= pin[29] >> 20;
        pout[47] = pin[29] & 0xfffff;
        pout[48] = pin[30] >> 12;
        pout[49] = (pin[30] << 8) & 0x0fffff;
        pout[49] |= pin[31] >> 24;
        pout[50] = (pin[31] >> 4) & 0xfffff;
        pout[51] = (pin[31] << 16) & 0xfffff;
        pout[51] |= pin[32] >> 16;
        pout[52] = (pin[32] << 4) & 0xfffff;
        pout[52] |= pin[33] >> 28;
        pout[53] = (pin[33] >> 8) & 0xfffff;
        pout[54] = (pin[33] << 12) & 0xfffff;
        pout[54] |= pin[34] >> 20;
        pout[55] = pin[34] & 0xfffff;
        pout[56] = pin[35] >> 12;
        pout[57] = (pin[35] << 8) & 0x0fffff;
        pout[57] |= pin[36] >> 24;
        pout[58] = (pin[36] >> 4) & 0xfffff;
        pout[59] = (pin[36] << 16) & 0xfffff;
        pout[59] |= pin[37] >> 16;
        pout[60] = (pin[37] << 4) & 0xfffff;
        pout[60] |= pin[38] >> 28;
        pout[61] = (pin[38] >> 8) & 0xfffff;
        pout[62] = (pin[38] << 12) & 0xfffff;
        pout[62] |= pin[39] >> 20;
        pout[63] = pin[39] & 0xfffff;

        *in = pin + 40;
        *out = pout + 64;
}

/* --- UNPACK 32 --- */
void
__vserest_unpack32_1(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        (*out)[0] = (*in)[0];

        *in += 1;
        *out += 1;
}

void
__vserest_unpack32_2(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %1, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                :"m" ((*in)[0])
                :"memory", "%xmm0");

        *in += 2;
        *out += 2;
}

void
__vserest_unpack32_3(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %1, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                :"m" ((*in)[0])
                :"memory", "%xmm0");

        *in += 3;
        *out += 3;
}

void
__vserest_unpack32_4(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %1, %%xmm0\n\t"
                "movdqu %%xmm0, %0\n\t"
                :"=m" ((*out)[0])
                :"m" ((*in)[0])
                :"memory", "%xmm0");

        *in += 4;
        *out += 4;
}

void
__vserest_unpack32_5(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %2, %%xmm0\n\t"
                "movdqu %3, %%xmm1\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                :"m" ((*in)[0]), "m" ((*in)[4])
                :"memory", "%xmm0", "%xmm1");

        *in += 5;
        *out += 5;
}

void
__vserest_unpack32_6(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %2, %%xmm0\n\t"
                "movdqu %3, %%xmm1\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                :"m" ((*in)[0]), "m" ((*in)[4])
                :"memory", "%xmm0", "%xmm1");

        *in += 6;
        *out += 6;
}

void
__vserest_unpack32_7(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %2, %%xmm0\n\t"
                "movdqu %3, %%xmm1\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                :"m" ((*in)[0]), "m" ((*in)[4])
                :"memory", "%xmm0", "%xmm1");

        *in += 7;
        *out += 7;
}

void
__vserest_unpack32_8(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %2, %%xmm0\n\t"
                "movdqu %3, %%xmm1\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4])
                :"m" ((*in)[0]), "m" ((*in)[4])
                :"memory", "%xmm0", "%xmm1");

        *in += 8;
        *out += 8;
}

void
__vserest_unpack32_9(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %3, %%xmm0\n\t"
                "movdqu %4, %%xmm1\n\t"
                "movdqu %5, %%xmm2\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8])
                :"memory", "%xmm0", "%xmm1", "%xmm2");

        *in += 9;
        *out += 9;
}

void
__vserest_unpack32_10(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %3, %%xmm0\n\t"
                "movdqu %4, %%xmm1\n\t"
                "movdqu %5, %%xmm2\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8])
                :"memory", "%xmm0", "%xmm1", "%xmm2");

        *in += 10;
        *out += 10;

}

void
__vserest_unpack32_11(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %3, %%xmm0\n\t"
                "movdqu %4, %%xmm1\n\t"
                "movdqu %5, %%xmm2\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8])
                :"memory", "%xmm0", "%xmm1", "%xmm2");

        *in += 11;
        *out += 11;

}

void
__vserest_unpack32_12(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %3, %%xmm0\n\t"
                "movdqu %4, %%xmm1\n\t"
                "movdqu %5, %%xmm2\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8])
                :"memory", "%xmm0", "%xmm1", "%xmm2");

        *in += 12;
        *out += 12;
}

void
__vserest_unpack32_14(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %4, %%xmm0\n\t"
                "movdqu %5, %%xmm1\n\t"
                "movdqu %6, %%xmm2\n\t"
                "movdqu %7, %%xmm3\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                "movdqu %%xmm3, %3\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8]), "m" ((*in)[12])
                :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");

        *in += 14;
        *out += 14;
}

void
__vserest_unpack32_16(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %4, %%xmm0\n\t"
                "movdqu %5, %%xmm1\n\t"
                "movdqu %6, %%xmm2\n\t"
                "movdqu %7, %%xmm3\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                "movdqu %%xmm3, %3\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8]), "m" ((*in)[12])
                :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");

        *in += 16;
        *out += 16;
}

void
__vserest_unpack32_32(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %8, %%xmm0\n\t"
                "movdqu %9, %%xmm1\n\t"
                "movdqu %10, %%xmm2\n\t"
                "movdqu %11, %%xmm3\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                "movdqu %%xmm3, %3\n\t"
                "movdqu %12, %%xmm0\n\t"
                "movdqu %13, %%xmm1\n\t"
                "movdqu %14, %%xmm2\n\t"
                "movdqu %15, %%xmm3\n\t"
                "movdqu %%xmm0, %4\n\t"
                "movdqu %%xmm1, %5\n\t"
                "movdqu %%xmm2, %6\n\t"
                "movdqu %%xmm3, %7\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12]),
                        "=m" ((*out)[16]), "=m" ((*out)[20]), "=m" ((*out)[24]), "=m" ((*out)[28])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8]), "m" ((*in)[12]),
                        "m" ((*in)[16]), "m" ((*in)[20]), "m" ((*in)[24]), "m" ((*in)[28])
                :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");

        *in += 32;
        *out += 32;
}

void
__vserest_unpack32_64(uint32_t **out, uint32_t **in, uint32_t &Fill, uint64_t &buffer)
{
        __asm__ __volatile__(
                "movdqu %8, %%xmm0\n\t"
                "movdqu %9, %%xmm1\n\t"
                "movdqu %10, %%xmm2\n\t"
                "movdqu %11, %%xmm3\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                "movdqu %%xmm3, %3\n\t"
                "movdqu %12, %%xmm0\n\t"
                "movdqu %13, %%xmm1\n\t"
                "movdqu %14, %%xmm2\n\t"
                "movdqu %15, %%xmm3\n\t"
                "movdqu %%xmm0, %4\n\t"
                "movdqu %%xmm1, %5\n\t"
                "movdqu %%xmm2, %6\n\t"
                "movdqu %%xmm3, %7\n\t"
                :"=m" ((*out)[0]), "=m" ((*out)[4]), "=m" ((*out)[8]), "=m" ((*out)[12]),
                        "=m" ((*out)[16]), "=m" ((*out)[20]), "=m" ((*out)[24]), "=m" ((*out)[28])
                :"m" ((*in)[0]), "m" ((*in)[4]), "m" ((*in)[8]), "m" ((*in)[12]),
                        "m" ((*in)[16]), "m" ((*in)[20]), "m" ((*in)[24]), "m" ((*in)[28])
                :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");

        __asm__ __volatile__(
                "movdqu %8, %%xmm0\n\t"
                "movdqu %9, %%xmm1\n\t"
                "movdqu %10, %%xmm2\n\t"
                "movdqu %11, %%xmm3\n\t"
                "movdqu %%xmm0, %0\n\t"
                "movdqu %%xmm1, %1\n\t"
                "movdqu %%xmm2, %2\n\t"
                "movdqu %%xmm3, %3\n\t"
                "movdqu %12, %%xmm0\n\t"
                "movdqu %13, %%xmm1\n\t"
                "movdqu %14, %%xmm2\n\t"
                "movdqu %15, %%xmm3\n\t"
                "movdqu %%xmm0, %4\n\t"
                "movdqu %%xmm1, %5\n\t"
                "movdqu %%xmm2, %6\n\t"
                "movdqu %%xmm3, %7\n\t"
                :"=m" ((*out)[32]), "=m" ((*out)[36]), "=m" ((*out)[40]), "=m" ((*out)[44]),
                        "=m" ((*out)[48]), "=m" ((*out)[52]), "=m" ((*out)[56]), "=m" ((*out)[60])
                :"m" ((*in)[32]), "m" ((*in)[36]), "m" ((*in)[40]), "m" ((*in)[44]),
                        "m" ((*in)[48]), "m" ((*in)[52]), "m" ((*in)[56]), "m" ((*in)[60])
                :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");

        *in += 64;
        *out += 64;
}
