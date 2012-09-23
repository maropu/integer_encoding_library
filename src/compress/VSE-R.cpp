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

inline void VSER_UNPACK1(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK2(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK3(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK4(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK5(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK6(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK7(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK8(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK9(uint32_t * restrict out,
                         const uint32_t * restrict in,
                         uint32_t bs) {

}

inline void VSER_UNPACK10(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK11(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK12(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK13(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK14(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK15(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK16(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK17(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK18(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK19(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK20(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK21(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK22(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK23(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK24(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK25(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK26(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK27(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK28(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK29(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK30(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK31(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

inline void VSER_UNPACK32(uint32_t * restrict out,
                          const uint32_t * restrict in,
                          uint32_t bs) {

}

/* A interface of unpacking functions above */
typedef void (*vser_unpack_t)(uint32_t *out,
                              const uint32_t *in,
                              uint32_t bs);

vser_unpack_t VSER_UNPACK[] = {
  VSER_UNPACK1, VSER_UNPACK2,
  VSER_UNPACK3, VSER_UNPACK4,
  VSER_UNPACK5, VSER_UNPACK6,
  VSER_UNPACK7, VSER_UNPACK8,
  VSER_UNPACK9, VSER_UNPACK10,
  VSER_UNPACK11, VSER_UNPACK12,
  VSER_UNPACK13, VSER_UNPACK14,
  VSER_UNPACK15, VSER_UNPACK16,
  VSER_UNPACK17, VSER_UNPACK18,
  VSER_UNPACK19, VSER_UNPACK20,
  VSER_UNPACK21, VSER_UNPACK22,
  VSER_UNPACK23, VSER_UNPACK24,
  VSER_UNPACK25, VSER_UNPACK26,
  VSER_UNPACK27, VSER_UNPACK28,
  VSER_UNPACK29, VSER_UNPACK30,
  VSER_UNPACK31, VSER_UNPACK32
};

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
  if (*nvalue == 0)
    THROW_ENCODING_EXCEPTION("Invalid input: nvalue");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  uint64_t ntotal = 0;

  /* Compute logs of all numbers */
  REGISTER_VECTOR_RAII(uint32_t, logs, len);
  for (uint32_t i = 0; i < len; i++) {
    if (in[i] != 0)
      logs[i] = 32 - MSB32(in[i] + 1);
    else
      logs[i] = 0;
  }

  /* Compress a sequence of logs with VSEncodingNaive */
  uint64_t        csize;
  VSEncodingNaive vnav;
  vnav.encodeArray(logs, len, out + 2, &csize);

  /* Output the information of a 1st section */
  BYTEORDER_FREE_STORE64(out, csize);
  out += csize + 2;
  ntotal = csize + 2;
  ASSERT(ntotal < *nvalue);

  /*
   * hist[i] stores the number of occs of number whose
   * log is equal to i.
   */
  uint32_t  hist[VSER_LOGS_LEN + 1];

  for (uint32_t i = 0; i <= VSER_LOGS_LEN; i++)
    hist[i] = 0;

  /* Count the number of occs */
  uint32_t maxL = 0;

  for (uint32_t i = 0; i < len; i++) {
    if (logs[i] != 0)
      hist[logs[i]]++;
  }

  for (uint32_t i = 0; i <= VSER_LOGS_LEN; i++) {
    if (hist[i] != 0)
      maxL = i;
  }

  /* Write the number of occs resorting to Delta code */
  F_Delta fd;
  hist[0] = maxL;
  fd.encodeArray(hist, maxL + 1, out + 2, &csize);

  /* Output the information of a 2nd section */
  BYTEORDER_FREE_STORE64(out, csize);
  out += csize + 2;
  ntotal += csize + 2;
  ASSERT(ntotal < *nvalue);

  /* Ready to write each integer */
  BitsWriter  *wt[VSER_LOGS_LEN];

  for (uint32_t i = 1; i <= maxL; i++) {
    if (hist[i] != 0) {
      wt[i - 1] = new BitsWriter(out, *nvalue - ntotal);
      ntotal += DIV_ROUNDUP(i * hist[i], 32);
      out += DIV_ROUNDUP(i * hist[i], 32);
    }

    ASSERT(ntotal < *nvalue);
  }

  /* Write the number in blocks depending on their logs */
  for (uint32_t i = 0; i < len; i++) {
    if (logs[i] != 0)
      wt[logs[i] - 1]->write_bits(in[i] + 1, logs[i]);
  }

  for (uint32_t i = 0; i < maxL; i++) {
    if (hist[i + 1] != 0) {
      wt[i]->flush_bits();
      delete wt[i];
    }
  }

  *nvalue = ntotal;
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

  const uint32_t *iterm = in + len;

  VSEncodingNaive vnav;
  uint64_t n = BYTEORDER_FREE_LOAD64(in);
  vnav.decodeArray(in + 2, n, out, nvalue);
  in += n + 2;

  /* *in stores the length of the Delta encoded block */
  uint32_t  *blk[VSER_LOGS_LEN];

  n = BYTEORDER_FREE_LOAD64(in);
  in += 2;

  BitsReader rd(in, iterm - in);
  uint32_t maxL = rd.read_fdelta();
  in += n;

  uint32_t nlen = 0;
  uint32_t *outs = wmem_.get();

  for (uint32_t i = 1; i <= maxL; i++) {
    if (UNLIKELY(rd.pos() >= iterm))
      break;

    uint32_t n = rd.read_fdelta();

    if (n != 0) {
      blk[i] = &outs[nlen];
      (VSER_UNPACK[i - 1])(&outs[nlen], in, DIV_ROUNDUP(n * i, 32));
      in += DIV_ROUNDUP(n * i, 32);
      nlen +=  n;
    }
  }

  for (uint32_t i = 0; i < nvalue; i++)
    out[i] = (out[i] == 0)? 0 : *(blk[out[i] - 1])++ - 1;
}

uint64_t VSE_R::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
