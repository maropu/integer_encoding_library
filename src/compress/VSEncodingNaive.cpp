/*-----------------------------------------------------------------------------
 *  VSEncodingNaive.hpp - A compact-oriented implementation of VSEncoding
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

#include <compress/policy/VSEncodingNaive.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSENAIVE_LOGLEN = 3;
const uint32_t VSENAIVE_LOGLOG = 3;

const uint32_t VSENAIVE_LENS_LEN = 1U << VSENAIVE_LOGLEN;

const uint32_t VSENAIVE_LENS[] = {
  1, 2, 4, 6, 8, 16, 32, 64
};

const uint32_t VSENAIVE_LOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 20, 32
};

const uint32_t VSENAIVE_REMAPLOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 16, 16, 16, 20, 20, 20, 20,
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t VSENAIVE_CODELENS[] = {
  0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7
};

const uint32_t VSENAIVE_CODELOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
  13, 13, 13, 13, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

} /* namespace: */

VSEncodingNaive::VSEncodingNaive()
    : EncodingBase(E_INVALID),
      vdp_(new VSEncodingDP(VSENAIVE_LENS,
                            NULL,
                            ARRAYSIZE(VSENAIVE_LENS), false)) {}

VSEncodingNaive::~VSEncodingNaive() throw() {}

void VSEncodingNaive::encodeArray(const uint32_t *in,
                                  uint64_t len,
                                  uint32_t *out,
                                  uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (*nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  /* Compute optimal partition */
  std::vector<uint32_t> logs;
  std::vector<uint32_t> parts;

  for (uint64_t i = 0; i < len; i++)
    logs.push_back(
        VSENAIVE_REMAPLOGS[32 - MSB32(in[i])]);

  ASSERT(logs.size() == len);
  ASSERT(parts.size() == 0);

  vdp_->computePartition(logs, &parts,
                         VSENAIVE_LOGLEN + VSENAIVE_LOGLOG);
  ASSERT(parts.size() > 1);

  /* Ready to write data */
  BitsWriter  wt(out, *nvalue);

  uint64_t num = parts.size() - 1;
  for (uint64_t i = 0; i < num; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    /* Write the value of B and K */
    wt.write_bits(VSENAIVE_CODELOGS[maxB],
                  VSENAIVE_LOGLOG);
    wt.write_bits(VSENAIVE_CODELENS[parts[i + 1] - parts[i]],
                  VSENAIVE_LOGLEN);

    /* Write integers */
    for (uint64_t j = parts[i];
            j < parts[i + 1]; j++)
      wt.write_bits(in[j], maxB);
  }

  wt.flush_bits();
  *nvalue = wt.size();
}

void VSEncodingNaive::decodeArray(const uint32_t *in,
                                  uint64_t len,
                                  uint32_t *out,
                                  uint64_t nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  BitsReader  rd(in, len);

  uint32_t *oterm = out + nvalue;

  while (LIKELY(out < oterm)) {
    uint32_t B = VSENAIVE_LOGS[rd.read_bits(VSENAIVE_LOGLOG)];
    uint32_t K = VSENAIVE_LENS[rd.read_bits(VSENAIVE_LOGLEN)];

    for (uint32_t i = 0; i < K; i++)
      out[i] = (B != 0)? rd.read_bits(B) : 0;
    out += K;
  }
}

uint64_t VSEncodingNaive::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
