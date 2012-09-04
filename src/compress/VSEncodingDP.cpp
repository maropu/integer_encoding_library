/*-----------------------------------------------------------------------------
 *  VSEncodingDP.cpp - To scan optimal partitions in a list
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

#include <compress/policy/VSEncodingDP.hpp>

namespace integer_encoding {
namespace internals {

VSEncodingDP::VSEncodingDP(const uint32_t *lens,
                           const uint32_t *zlens,
                           uint32_t size,
                           bool aligned)
    : aligned_(aligned),
      size_(size),
      mxblk_(lens[size - 1]),
      lens_(lens),
      zlens_(zlens) {
  if (lens == NULL)
    THROW_ENCODING_EXCEPTION("Invalid value: lens");
  if (size == 0)
    THROW_ENCODING_EXCEPTION("Invalid value: size");

  ASSERT_ADDR(lens, size);

  /* Set the max length of sequences */
  if (zlens != NULL && mxblk_ < zlens[size - 1])
    mxblk_ = zlens[size - 1];
}

VSEncodingDP::~VSEncodingDP() throw() {}

void VSEncodingDP::computePartition(const std::vector<uint32_t>& seq,
                                    std::vector<uint32_t> *parts,
                                    uint32_t cost) const {
  ASSERT(seq.size() != 0);
  ASSERT(parts != NULL);

  /*
   * costs[i] will contain the cost of
   * encoding up to i-th position.
   */
  std::vector<int32_t >   sssp;
  std::vector<uint32_t>   costs;

  for (uint64_t i = 0; i <= seq.size(); i++)
    sssp.push_back(-1);
  for (uint64_t i = 0; i <= seq.size(); i++)
    costs.push_back(0);

  ASSERT(sssp.size() == seq.size() + 1);
  ASSERT(costs.size() == seq.size() + 1);

  {
    /*
     * NOTE: This loop computes the cost of the optimal
     * partition. The computation of the max log in each
     * block is done by scanning. Probably we could
     * obtain a faster solution by using RMQ data structures.
     * We use this trivial solution since construction
     * time is not our main concern.
     */
    uint32_t  maxB;
    int64_t   j, g, l, mleft;
    uint64_t  ccost;

    for (uint64_t i = 1; i <= seq.size(); i++) {
      mleft = (i > mxblk_)? i - mxblk_ : 0;

      for (maxB = 0, l = 0, g = 0, j = i - 1;
              j >= mleft; j--) {
        ASSERT(l <= size_);
        ASSERT(g <= size_);

        if (maxB < seq[j])
          maxB = seq[j];

        if (zlens_ == NULL) {
          /*
           * FIXME: If the gaps of elements in lens_[]
           * are sparse, a process below is more efficient
           * to hop these gaps using the elements rather
           * than decrementing j.
           */
          if (i - j != lens_[l]) continue;
          else l++;
        } else {
          /*
           * Treat runs of 0 in a different way.
           * They could form larger blocks!
           */
          if (maxB != 0) {
            mleft = (i > mxblk_)? i - lens_[size_ - 1] : 0;
            if (i - j != lens_[l]) continue;
            else l++;
          } else {
            if (i - j == lens_[l]) l++;
            if (i - j != zlens_[g]) continue;
            else g++;
          }
        }

        /* Caluculate costs */
        if (aligned_)
          ccost = costs[j] + DIV_ROUNDUP((i - j) * maxB, 32) + cost;
        else
          ccost = costs[j] + (i - j) * maxB + cost;

        if (sssp[i] == -1)
          costs[i] = ccost + 1;

        /* If necessary, update the cost */
        if (ccost <= costs[i]) {
          costs[i] = ccost;
          sssp[i] = j;
        }
      }
    }
  }

  /* Compute number of nodes in the path */
  uint64_t idx = 0;
  uint64_t next = seq.size();
  while (next != 0) {next = sssp[next]; idx++;}

  /* Obtain the optimal partition */
  for (uint64_t i = 0; i <= idx; i++)
    parts->push_back(0);
  next = seq.size();
  while (next != 0) {(*parts)[idx--] = next; next = sssp[next];}
}

} /* namespace: internals */
} /* namespace: integer_encoding */
