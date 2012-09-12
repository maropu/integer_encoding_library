/*-----------------------------------------------------------------------------
 *  encoding_internals.hpp - Common utility stuffs
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

#ifndef __ENCODING_INTERNALS_HPP__
#define __ENCODING_INTERNALS_HPP__

#ifndef __STDC_LIMIT_MACROS
# define __STDC_LIMIT_MACROS
#endif

#include <misc/encoding_port_internals.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <ctime>
#include <cassert>

#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <exception>
#include <string>
#include <limits>
#include <map>
#include <vector>
#include <memory>

namespace integer_encoding {

/*
 * NOTE: Get the maximum required size of memory when
 * decoding. Some are intended to overrun the tail of
 * given memory for performance reasons.
 */
#define DECODE_REQUIRE_MEM(x)   ((x) + 128)

/* Smart pointer stuffs */
#define INITIALIZE_SPTR(__type__, __size__)  \
    std::shared_ptr<__type__>(  \
        new __type__[__size__], \
        std::default_delete<__type__[]>())

#define REGISTER_VECTOR_RAII(__type__, __name__, __size__)  \
    std::shared_ptr<__type__>   \
        __##__name__(new __type__[__size__],  \
                     std::default_delete<__type__[]>());    \
    __type__ *__name__ = __##__name__.get()

/* Assertion macros */
#ifndef NDEBUG
# define ASSERT(__x__)                  assert(__x__)
# define ASSERT_ADDR(__addr__, __n__)   // Not defined yet ...
#else
# define ASSERT(__x__)
# define ASSERT_ADDR(__addr__, __n__)
#endif /* NDEBUG */

#define DIV_ROUNDUP(__x__, __y__) \
    ((__x__ + __y__ - 1) / __y__)

/*
 * NOTE: Fast memory copy stuffs, these functions
 * are intended to overrun given memory spaces
 * for performance reasons. A caller needs to make
 * sure that the overruning causes no crashes.
 */
inline void MEMCPY(void *dest,
                   void *src, uint64_t n) {
  ASSERT(dest != NULL);
  ASSERT(src != NULL);

  char *s = reinterpret_cast<char *>(src);
  char *d = reinterpret_cast<char *>(dest);

  uint64_t num = DIV_ROUNDUP(n, 4);
  for (uint64_t i = 0;
          i < num; i++, s += 16, d += 16)
    MEMCPY128(s, d);
}

inline void ZMEMCPY(void *dest, uint64_t n) {
  ASSERT(dest != NULL);

  char *d = reinterpret_cast<char *>(dest);

  uint64_t num = DIV_ROUNDUP(n, 4);
  for (uint64_t i = 0;
          i < num; i++, d += 16)
    ZMEMCPY128(d);
}

#define DISALLOW_COPY_AND_ASSIGN(__Type__)  \
    __Type__(const __Type__&);              \
    void operator= (const __Type__&)

/* Num of coders */
const int NUMCODERS = 18;

/* Encoder ID for policy */
const int E_INVALID       = -1;
const int E_N_GAMMA       = 0;
const int E_FU_GAMMA      = 1;
const int E_F_GAMMA       = 2;
const int E_N_DELTA       = 3;
const int E_FU_DELTA      = 4;
const int E_FG_DELTA      = 5;
const int E_F_DELTA       = 6;
const int E_VARIABLEBYTE  = 7;
const int E_BINARYIPL     = 8;
const int E_SIMPLE9       = 9;
const int E_SIMPLE16      = 10;
const int E_P4D           = 11;
const int E_OPTP4D        = 12;
const int E_VSEBLOCKS     = 13;
const int E_VSER          = 14;
const int E_VSEREST       = 15;
const int E_VSEHYB        = 16;
const int E_VSESIMPLE     = 17;

#define THROW_ENCODING_EXCEPTION(msg) \
    throw encoding_exception(msg, __FILE__, __func__, __LINE__)

class encoding_exception : public std::exception {
 public:
  explicit encoding_exception(const std::string& msg)
      : msg_(msg),
        file_(NULL),
        func_(NULL),
        line_(0) {}

  explicit encoding_exception(const std::string& msg,
                            const char *file,
                            const char *func,
                            int line)
      : msg_(msg),
        file_(file),
        func_(func),
        line_(line) {
    char buf[256];
    int n = snprintf(buf, 256, "(src:%s func:%s line:%d)",
                     file_.c_str(), func_.c_str(), line_);
    msg_ += std::string(buf, n);
  }

  ~encoding_exception() throw() {}

  const char *what() const throw() {return msg_.c_str();}

 private:
  std::string msg_;

  /* Exception Info. */
  std::string file_;
  std::string func_;
  int line_;
};

namespace internals {

/* Generate a randomized value */
inline uint32_t xor128() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;

  uint32_t t = (x ^ (x << 11));
  x = y, y = z, z = w;

  return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __ENCODING_INTERNALS_HPP__ */
