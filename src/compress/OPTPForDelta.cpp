/*-----------------------------------------------------------------------------
 *  OPTPForDelta.cpp - A optimized implementation of PForDelta
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

#include <compress/policy/OPTPForDelta.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t OPTPFORDELTA_LOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 20, 32
};

} /* namespace: */

OPTPForDelta::OPTPForDelta()
    : PForDelta(E_OPTP4D) {}

OPTPForDelta::~OPTPForDelta() throw() {}

uint32_t OPTPForDelta::tryB(uint32_t b,
                            const uint32_t *in,
                            uint64_t len) const {
  ASSERT(b <= 32);
  ASSERT(in != NULL);
  ASSERT(len != 0);

  ASSERT_ADDR(in, len);

  uint32_t size = len;

  /* Get working spaces */
  uint32_t *exceptionsPositions = exceptionsPositions_.get();
  uint32_t *exceptionsValues = exceptionsValues_.get();
  uint32_t *exceptions = exceptions_.get();
  uint32_t *encodedExceptions = encodedExceptions_.get();

  if (b < 32) {
    uint32_t curExcept = 0;

    size = DIV_ROUNDUP(len * b, 32);

    for (uint32_t i = 0; i < len; i++) {
      if (in[i] >= (1U << b)) {
        uint32_t e = in[i] >> b;
        exceptionsPositions[curExcept] = i;
        exceptionsValues[curExcept] = e;
        curExcept++;
      }
    }

    if (curExcept > 0) {
      for (uint32_t i = curExcept - 1; i > 0; i--) {
        uint32_t cur = exceptionsPositions[i];
        uint32_t prev = exceptionsPositions[i - 1];
        exceptionsPositions[i] = cur - prev;
      }

      for (uint32_t i = 0;  i < curExcept; i++) {
        uint32_t excPos = (i > 0)?
            exceptionsPositions[i] - 1 : exceptionsPositions[i];
        uint32_t excVal = exceptionsValues[i] - 1;

        exceptions[i] = excPos;
        exceptions[i + curExcept] = excVal;
      }

      /* Write down values in the exception area */
      uint64_t encodedExceptions_sz = s16_.require(len * 2);
      s16_.encodeArray(exceptions,
                      2 * curExcept,
                      encodedExceptions,
                      &encodedExceptions_sz);
      size += encodedExceptions_sz;
    }
  }

  return size;
}

uint32_t OPTPForDelta::findBestB(const uint32_t *in,
                                 uint64_t len) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);

  ASSERT_ADDR(in, len);

  uint32_t b = OPTPFORDELTA_LOGS[ARRAYSIZE(OPTPFORDELTA_LOGS) - 1];

  uint32_t bsize = len;
  for (uint32_t i = 0; i < ARRAYSIZE(OPTPFORDELTA_LOGS) - 1; i++) {
    uint32_t csize = tryB(OPTPFORDELTA_LOGS[i], in, len);
    if (csize <= bsize) {
      b = OPTPFORDELTA_LOGS[i];
      bsize = csize;
    }
  }

  return b;
}

uint64_t OPTPForDelta::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
