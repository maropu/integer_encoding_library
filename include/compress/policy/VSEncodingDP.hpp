/*-----------------------------------------------------------------------------
 *  VSEncodingDP.hpp - To scan optimal partitions in a list
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

#ifndef __VSENCODINGDP_HPP__
#define __VSENCODINGDP_HPP__

#include <misc/encoding_internals.hpp>

/*
 * If a list is larger that this value, then
 * it is split into subblocks that are
 * compressed separatelly. Compression is
 * slightly worse, but the decompression is
 * more cache-friendly.
 */
const uint32_t VSENCODING_BLOCKSZ = 65536;

namespace integer_encoding {
namespace internals {

class VSEncodingDP {
 public:
  explicit VSEncodingDP(const uint32_t *lens,
                        const uint32_t *zlens,
                        uint32_t size,
                        bool aligned);

  ~VSEncodingDP() throw();

  /*
   * computePartition
   *   Compute optimal sub-lists from input a list
   *     seq    : input list
   *     parts  : calculated optimal sub-lists
   *     cost   : fix cost in bits that we pay for each block
   */
  void computePartition(const std::vector<uint32_t>& seq,
                        std::vector<uint32_t> *parts,
                        uint32_t cost) const;

 private:
  bool            aligned_;
  uint32_t        size_;
  uint32_t        mxblk_;
  const uint32_t  *lens_;
  const uint32_t  *zlens_;

  DISALLOW_COPY_AND_ASSIGN(VSEncodingDP);
}; /* VSEncodingDP */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __VSENCODINGDP_HPP__ */
