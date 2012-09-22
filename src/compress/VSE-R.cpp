/*-----------------------------------------------------------------------------
 *  VSE-R.hpp - A alternative implementation of VSEncoding
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

#include <compress/policy/VSE-R.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSER_LOGS_LEN = 32;

/* FIXME: It comply with MAXLEN in vcompress.hpp */
const uint64_t MAXLEN = 100000000;

} /* namespace: */

VSE_R::VSE_R()
    : EncodingBase(E_VSER),
      wmem_(INITIALIZE_SPTR(uint32_t, MAXLEN)) {}

VSE_R::~VSE_R() throw() {}

void VSE_R::encodeArray(const uint32_t *in,
                        uint64_t len,
                        uint32_t *out,
                        uint64_t *nvalue) const {
  if (in == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: in");
  if (len == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: len");
  if (out == NULL)
    THROW_ENCODING_EXCEPTION("Invalid input: out");
  if (*nvalue < 5)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

}

void VSE_R::decodeArray(const uint32_t *in,
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

}

uint64_t VSE_R::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
