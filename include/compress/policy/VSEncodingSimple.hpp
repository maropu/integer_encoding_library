/*-----------------------------------------------------------------------------
 *  VSEncodingSimple.hpp - A speed-oriented implementation of VSEncoding
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

#ifndef __VSENCODINGSIMPLE_HPP__
#define __VSENCODINGSIMPLE_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <compress/policy/VSEncodingDP.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

/*
 * NOTE: This has two following improved things
 * as compared th other alternative:
 *
 * 1. each partition determined by the dynamic
 * programming is layouted with 32-bit alignments
 * for performance reasons. It has the advantage of
 * less coping stuffs caused by VSEncodingBlocks,
 * but increases wasteful padding areas exploited
 * by VSEncodingRest.
 *
 * 2. a direct threading technique known in VM
 * domins is employed to dispacth unpacking
 * functions correspoinding to compressed
 * partitions, and it cound reduce the penalty
 * of indirect jumps.
 */
class VSEncodingSimple : public EncodingBase {
 public:
  VSEncodingSimple();
  ~VSEncodingSimple() throw();

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const;

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const;

  uint64_t require(uint64_t len) const;

 private:
  /*
   * FIXME: It is wasteful to allocate memory
   * in advance, so decodeArray needs to be
   * modified in a similar way of VSEncodingBlocks,
   * that is, it splits the constant chunk and
   * compress each chunk.
   */
  std::shared_ptr<void *>       jtable_;
  std::shared_ptr<VSEncodingDP> vdp_;
}; /* VSEncodingSimple */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __VSENCODINGSIMPLE_HPP__ */
