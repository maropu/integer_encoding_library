/*-----------------------------------------------------------------------------
 *  vcompress.hpp - A header for vcompress.cpp
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

#ifndef __VCOMPRESS_HPP__
#define __VCOMPRESS_HPP__

#include <misc/encoding_internals.hpp>

namespace integer_encoding {

/* Configurable parameters */
const uint64_t MAXLEN = 100000000;
const uint64_t NSKIP = 32;

/*
 * Paramters and macros to load adn store
 * data in local filesystems.
 */
const uint32_t CMP_HEADER_SZ = 4;
const uint32_t POS_HEADER_SZ = 32;
const uint32_t POS_EACH_ENTRY_SZ = 16;

#define VC_LOAD32(__addr__) \
    ({                      \
      uint32_t d = BYTEORDER_FREE_LOAD32(__addr__); \
      __addr__ += 1, d;     \
    })

#define VC_LOAD64(__addr__) \
    ({                      \
      uint64_t d = BYTEORDER_FREE_LOAD64(__addr__); \
      __addr__ += 2, d;     \
    })

#define OUTPUT_AND_DIE(__x__) \
    ({fprintf(stderr, __x__); fprintf(stderr, "\n"); exit(1);})

uint32_t *OpenFile(const std::string& filename,
                   uint64_t *size) {
  void *addr = NULL;

  int fd = open(filename.c_str(), O_RDWR);
  if (fd == -1)
    goto OPEN_EXCEPTION;

  struct stat sb;
  if (fstat(fd, &sb) == -1 || sb.st_size == 0)
    goto OPEN_EXCEPTION;
  *size = sb.st_size;

  addr = mmap(NULL, *size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED)
    goto OPEN_EXCEPTION;

  close(fd);
  return reinterpret_cast<uint32_t *>(addr);

OPEN_EXCEPTION:
  OUTPUT_AND_DIE("Exception: can't open the file.");
}

void FastMemcpy(void *dest,
                void *src, uint64_t n) {
  if (n == 0) return;

  ASSERT(dest != NULL);
  ASSERT(dest != NULL);

  char *s = reinterpret_cast<char *>(src);
  char *d = reinterpret_cast<char *>(dest);
  uint64_t num = n >> 4;
  for (uint64_t i = 0; i < num; i++, s += 16, d += 16)
    MEMCPY128(s, d);

  memcpy(d, s, static_cast<size_t>(n - (num << 4)));
}

/* Activate FAST_MEMCPY */
#define MEMCPY  FastMemcpy
// #define MEMCPY  std::memcpy

class BenchmarkTimer {
 public:
  BenchmarkTimer()
    : base_(get_time()) {}
  ~BenchmarkTimer() throw() {}

  double elapsed() const {
    return get_time() - base_;
  }

  void reset() {
    base_ = get_time();
  }

 private:
  double  base_;

  static double get_time() {
#if 0
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    double utime = usage.ru_utime.tv_sec +
        (usage.ru_utime.tv_usec + 0.0) / 1000000.0;
    double stime = usage.ru_stime.tv_sec +
        (usage.ru_stime.tv_usec + 0.0) / 1000000.0;
    return (utime + stime);
#else
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + static_cast<double>(tv.tv_usec*1e-6);
#endif
  }

  DISALLOW_COPY_AND_ASSIGN(BenchmarkTimer);
};

} /* namespace: integer_encoding */

#endif /* __VCOMPRESS_HPP__ */
