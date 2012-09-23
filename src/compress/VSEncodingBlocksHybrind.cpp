/*-----------------------------------------------------------------------------
 *  VSEncodingBlocksHybrid.hpp - A hybrid implementation of VSEncoding
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

#include <compress/policy/VSEncodingBlocksHybrid.hpp>

namespace integer_encoding {
namespace internals {

VSEncodingBlocksHybrid::VSEncodingBlocksHybrid()
    : EncodingBase(E_VSEHYB) {}

VSEncodingBlocksHybrid::~VSEncodingBlocksHybrid() throw() {}

void VSEncodingBlocksHybrid::encodeArray(const uint32_t *in,
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

  uint64_t  csize = *nvalue;

  if (len <= VSEHYBRID_THRES) {
    VSEncodingRest  vser;
    vser.encodeArray(in, len, out + 1, &csize);
  } else {
    VSEncodingBlocks  vseblocks;
    vseblocks.encodeArray(in, len, out + 1, &csize);
  }

  BYTEORDER_FREE_STORE32(out, (len <= VSEHYBRID_THRES));
  *nvalue = csize + 1;
}

void VSEncodingBlocksHybrid::decodeArray(const uint32_t *in,
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

  uint32_t sw = BYTEORDER_FREE_LOAD32(in);
  if (sw) {
    VSEncodingRest  vser;
    vser.decodeArray(in + 1, len - 1, out, nvalue);
  } else {
    VSEncodingBlocks  vseblocks;
    vseblocks.decodeArray(in + 1, len - 1, out, nvalue);
  }
}

uint64_t VSEncodingBlocksHybrid::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
