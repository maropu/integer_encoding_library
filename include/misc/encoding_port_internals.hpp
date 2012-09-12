/*-----------------------------------------------------------------------------
 *  encoding_port_internals.hpp - Utility stuffs for portablitiy
 *
 *  Coding-Style: google-styleguide
 *      https://code.google.com/p/google-styleguide/
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *
 *  Copyright 2012 Integer Encoding Library <integerencoding_at_isti.cnr.it>
 *      http://integerencoding.ist.cnr.it/
 *-----------------------------------------------------------------------------
 */

#ifndef __ENCODING_PORT_INTERNALS_HPP__
#define __ENCODING_PORT_INTERNALS_HPP__

#include <cstdint>

/* gcc version */
#define GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)

/* 64-bit/32-bit detection */
#if (defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) ||  \
     defined(__amd64) || defined(__ppc64__) || defined(_WIN64) ||       \
     defined(__LP64__) || defined(_LP64))
# define LZE_ARCH64
#endif

/* Byte-order detection */
#if (defined(__BIG_ENDIAN__) || defined(__BIG_ENDIAN) ||  \
     defined(_BIG_ENDIAN) || defined(_ARCH_PPC) || defined(__PPC__) ||  \
     defined(__PPC) || defined(PPC) || defined(__powerpc__) ||          \
     defined(__powerpc) || defined(powerpc) ||                          \
     ((defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))))
# define LZE_BIGENDIAN
#endif

// #define LZE_BIGENDIAN_FORCE_RW

/* Processor Optimization for gcc */
#if ((GCC_VERSION >= 302) || (__INTEL_COMPILER >= 800) || defined(__clang__))
# define LIKELY(__x__)   __builtin_expect(!!(__x__), 1)
# define UNLIKELY(__x__) __builtin_expect(!!(__x__), 0)
#else
# define LIKELY(__x__)
# define UNLIKELY(__x__)
#endif

/* C99 standard option */
#if __STDC_VERSION__ < 199901L
# define restrict
#endif

/* Some cpus do not support unaligned accesses */
// #define LZE_ENABLE_UNALIGNED_RW

#if !defined(LZE_ENABLE_UNALIGNED_RW)

# pragma pack(push, 1)

typedef struct {uint32_t  v;} U32_S;
typedef struct {uint64_t  v;} U64_S;

# pragma pack(pop)

/* Not display some warnings in gcc */
# if defined(__GNUC__) && (GCC_VERSION >= 406)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wstrict-aliasing"
# endif

# define LOAD32(__x__)  (((U32_S *)(__x__))->v)
# define LOAD64(__x__)  (((U64_S *)(__x__))->v)

# define STORE32(__x__, __y__)  ((((U32_S *)(__x__))->v) = __y__)
# define STORE64(__x__, __y__)  ((((U64_S *)(__x__))->v) = __y__)

# if defined(__GNUC__) && (GCC_VERSION >= 406)
#   pragma GCC diagnostic pop
# endif

#else

# define LOAD32(__x__)  ({uint32_t  v; memcpy(&v, __x__, 4); v;})
# define LOAD64(__x__)  ({uint64_t  v; memcpy(&v, __x__, 8); v;})

# define STORE32(__x__, __y__)  \
  ({uint32_t v = __y__; memcpy(&v, __x__, 4);})
# define STORE64(__x__, __y__)  \
  ({uint64_t v = __y__; memcpy(&v, __x__, 8);})

#endif

/* Byte-swap detection */
#if defined(__GNUC__) && (GCC_VERSION >= 403)

# define BSWAP32(__x__) __builtin_bswap32(__x__)
# define BSWAP64(__x__) __builtin_bswap64(__x__)

#else

inline uint32_t BSWAP32(uint32_t x) {
  x = ((x & 0xff00ff00UL) >> 8) | ((x & 0x00ff00ffUL) << 8);
  return (x >> 16) | (x << 16);
}

inline uint64_t BSWAP64(uint64_t x) {
  x = ((x & 0xff00ff00ff00ff00ULL) >> 8) |
        ((x & 0x00ff00ff00ff00ffULL) << 8);
  x = ((x & 0xffff0000ffff0000ULL) >> 16) |
        ((x & 0x0000ffff0000ffffULL) << 16);
  return (x >> 32) | (x << 32);
}

#endif

#if defined(LZE_BIGENDIAN) && !defined(LZE_BIGENDIAN_FORCE_RW)

# define BYTEORDER_FREE_LOAD32(__x__) \
  {uint32_t v = LOAD32(__x__); v = BSWAP32(v); v;}
# define BYTEORDER_FREE_LOAD64(__x__) \
  {uint64_t v = LOAD64(__x__); v = BSWAP64(v); v;}

# define BYTEORDER_FREE_STORE32(__x__, __y__) \
  {uint32_t v = BSWAP32(__y__); STORE32(__x__, v);}
# define BYTEORDER_FREE_STORE64(__x__, __y__) \
  {uint64_t v = BSWAP64(__y__); STORE64(__x__, v);}

#else

# define BYTEORDER_FREE_LOAD32(__x__) LOAD32(__x__)
# define BYTEORDER_FREE_LOAD64(__x__) LOAD64(__x__)

# define BYTEORDER_FREE_STORE32(__x__, __y__) STORE32(__x__, __y__)
# define BYTEORDER_FREE_STORE64(__x__, __y__) STORE64(__x__, __y__)

#endif

/* Hardware bit-count detection */
#if defined(__GNUC__) && (GCC_VERSION >= 304)
# define MSB32(__x__)   ((__x__ != 0)? __builtin_clz(__x__) : 32)
#else

inline uint32_t MSB32(uint32_t x) {
  uint32_t pos = 32;
  uint32_t temp = x >> 16;
  if (temp != 0) {pos -= 16; x = temp;}
  temp = x >> 8;
  if (temp != 0) {pos -= 8; x = temp;}
  temp = x >> 4;
  if (temp != 0) {pos -= 4; x = temp;}
  temp = x >> 2;
  if (temp != 0) {pos -= 2; x = temp;}
  temp = x >> 1;
  if (temp != 0) {return pos - 2;}
  return pos - x;
}

#endif

#if (defined(__x86_64__) || defined(__x86_64))

inline void MEMCPY128(const void *src, void *dest) {
  const uint32_t *s =
          reinterpret_cast<const uint32_t *>(src);
  uint32_t *d = reinterpret_cast<uint32_t *>(dest);

  __asm__ (
    "movdqu %1, %%xmm0\n\t"
    "movdqu %%xmm0, %0\n\t"
    :"=m" (d[0]) :"m" (s[0])
    :"memory", "%xmm0", "%xmm1", "%xmm2", "%xmm3");
}

inline void MEMCPYA128(const void *src, void *dest) {
  const uint32_t *s =
          reinterpret_cast<const uint32_t *>(src);
  uint32_t *d = reinterpret_cast<uint32_t *>(dest);

  __asm__ (
    "movdqa  %1, %%xmm0\n\t"
    "movntdq %%xmm0, %0\n\t"
    :"=m" (d[0]) :"m" (s[0]) :"memory", "%xmm0");
}

inline void ZMEMCPY128(void *dest) {
  uint32_t *d = reinterpret_cast<uint32_t *>(dest);

  __asm__ (
    "pxor   %%xmm0, %%xmm0\n\t"
    "movdqu %%xmm0, %0\n\t"
    :"=m" (d[0]) ::"memory", "%xmm0");
}

inline void ZMEMCPYA128(void *dest) {
  uint32_t *d = reinterpret_cast<uint32_t *>(dest);
  __asm__ (
    "pxor     %%xmm0, %%xmm0\n\t"
    "movntdq  %%xmm0, %0\n\t"
    :"=m" (d[0]) ::"memory", "%xmm0");
}

#else

inline void MEMCPY128(const void *src, void *dest) {
  const char *s = reinterpret_cast<const char *>(src);
  char *d = reinterpret_cast<char *>(dest);
# if defined(LZE_ARCH64)
  STORE64(d, LOAD64(s));
  STORE64(d + 8, LOAD64(s + 8));
# else
  STORE32(d, LOAD32(s));
  STORE32(d + 4, LOAD32(s + 4));
  STORE32(d + 8, LOAD32(s + 8));
  STORE32(d + 12, LOAD32(s + 12));
# endif
}

inline void ZMEMCPY128(void *dest) {
  char *d = reinterpret_cast<char *>(dest);
# if defined(LZE_ARCH64)
  STORE64(d, 0);
  STORE64(d + 8, 0);
# else
  STORE32(d, 0);
  STORE32(d + 4, 0);
  STORE32(d + 8, 0);
  STORE32(d + 12, 0);
# endif
}

/* Just replace these with non-alignment copys */
#define MEMCPYA128    MEMCPY128
#define ZMEMCPYA128   ZMEMCPYA128

#endif

// #define __AVX__

#if defined(__AVX__) && \
    (defined(__x86_64__) || defined(__x86_64))

inline void ZMEMCPY256(void *dest) {
  uint32_t *d = reinterpret_cast<uint32_t *>(dest);

  __asm__ (
    "vpxor   %%xmm0, %%xmm0, %%xmm0\n\t"
    "vmovdqu %%ymm0, %0\n\t"
    :"=m" (d[0]) ::"memory", "%xmm0");
}

#endif

/* Support 64bit files even on 32bit platfroms */
#if defined(__GNUC__) && (GCC_VERSION >= 202)
# ifndef _LARGEFILE_SOURCE
#   define _LARGEFILE_SOURCE
# endif
# define _FILE_OFFSET_BITS  64
#else
  /* Not defined yet */
#endif

/*
 * Some compilers already have a definition, so
 * it is undefined first and defined again.
 */
#ifdef ARRAYSIZE
# undef ARRAYSIZE
#endif

#define ARRAYSIZE(__x__)  \
    (sizeof(__x__) / sizeof(*(__x__)))

#endif /* __ENCODING_PORT_INTERNALS_HPP__ */
