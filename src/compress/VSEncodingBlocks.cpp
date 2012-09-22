/*-----------------------------------------------------------------------------
 *  VSEncodingBlocks.cpp - A naive implementation of VSEncoding
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

#include <compress/policy/VSEncodingBlocks.hpp>

namespace integer_encoding {
namespace internals {

namespace {

const uint32_t VSEBLOCKS_LOGLEN = 4;
const uint32_t VSEBLOCKS_LOGLOG = 4;
const uint32_t VSEBLOCKS_LOGDESC =
    VSEBLOCKS_LOGLEN + VSEBLOCKS_LOGLOG;

const uint32_t VSEBLOCKS_LENS_LEN = 1U << VSEBLOCKS_LOGLEN;
const uint32_t VSEBLOCKS_LOGS_LEN = 1U << VSEBLOCKS_LOGLOG;
const uint32_t VSEBLOCKS_DESC_LEN = 1U << VSEBLOCKS_LOGDESC;

vsencoding_unpack_t VSEBLOCKS_UNPACK[] = {
  NULL,
  VSENCODING_UNPACK1,
  VSENCODING_UNPACK2,
  VSENCODING_UNPACK3,
  VSENCODING_UNPACK4,
  VSENCODING_UNPACK5,
  VSENCODING_UNPACK6,
  VSENCODING_UNPACK7,
  VSENCODING_UNPACK8,
  VSENCODING_UNPACK9,
  VSENCODING_UNPACK10,
  VSENCODING_UNPACK11,
  VSENCODING_UNPACK12,
  VSENCODING_UNPACK16,
  VSENCODING_UNPACK20,
  VSENCODING_UNPACK32
};

const uint32_t VSEBLOCKS_LENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 14, 15, 16
};

const uint32_t VSEBLOCKS_ZLENS[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 14, 16, 32
};

const uint32_t VSEBLOCKS_LOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 20, 32
};

const uint32_t VSEBLOCKS_REMAPLOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 16, 16, 16, 16, 20, 20, 20, 20,
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

const uint32_t VSEBLOCKS_CODELOGS[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
  11, 12, 13, 13, 13, 13, 14, 14, 14, 14,
  15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

} /* namespace: */

VSEncodingBlocks::VSEncodingBlocks()
    : EncodingBase(E_VSEBLOCKS),
      wmem_(INITIALIZE_SPTR(
              uint32_t, VSENCODING_BLOCKSZ * 2 + 128)),
      vdp_(new VSEncodingDP(VSEBLOCKS_LENS,
                            VSEBLOCKS_ZLENS,
                            VSEBLOCKS_LENS_LEN, false)){}

VSEncodingBlocks::~VSEncodingBlocks() throw() {}

void VSEncodingBlocks::encodeVS(const uint32_t *in,
                                uint32_t len,
                                uint32_t *out,
                                uint32_t *size) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);
  ASSERT(out != NULL);
  ASSERT(*size != 0);

  /* Compute optimal partition */
  std::vector<uint32_t> logs;
  std::vector<uint32_t> parts;

  for (uint32_t i = 0; i < len; i++) {
    uint32_t val = BYTEORDER_FREE_LOAD32(in + i);
    logs.push_back(VSEBLOCKS_REMAPLOGS[32 - MSB32(val)]);
  }

  ASSERT(logs.size() == len);
  ASSERT(parts.size() == 0);

  vdp_->computePartition(logs, &parts,
                         VSEBLOCKS_LOGLEN + VSEBLOCKS_LOGLOG);
  ASSERT(parts.size() > 1);

  uint32_t numBlocks = parts.size() - 1;

  /* countBlocksLogs[i] says how many blocks uses i bits */
  uint32_t  countBlocksLogs[VSEBLOCKS_LOGS_LEN];

  for (uint32_t i = 0; i < VSEBLOCKS_LOGS_LEN; i++)
    countBlocksLogs[i] = 0;

  /* Count number of occs of each log */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    countBlocksLogs[VSEBLOCKS_CODELOGS[maxB]] +=
        parts[i + 1] - parts[i];
  }

  uint32_t ntotal = 0;
  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0)
      ntotal++;
  }

  /* Write occs. zero is assumed to be present */
  BitsWriter wt(out, *size);
  wt.write_bits(ntotal, 32);

  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0) {
      wt.write_bits(countBlocksLogs[i], 28);
      wt.write_bits(i, 4);
    }
  }

  /* Prepare arrays to store groups of elements */
  std::vector<uint32_t> blocks[VSEBLOCKS_LOGS_LEN];

  for (uint32_t i = 1;
          i < VSEBLOCKS_LOGS_LEN; i++) {
    if (countBlocksLogs[i] > 0)
      blocks[i].reserve(countBlocksLogs[i]);
  }

  /* Permute the elements based on their values of B */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    if (!maxB)
      continue;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      /* Save current element in its bucket */
      uint32_t val = BYTEORDER_FREE_LOAD32(in + j);
      blocks[VSEBLOCKS_CODELOGS[maxB]].push_back(val);
    }
  }

  /* Write each bucket ... keeping byte alligment */
  for (uint32_t i = 1; i < VSEBLOCKS_LOGS_LEN; i++) {
    for (uint32_t j = 0; j < countBlocksLogs[i]; j++)
      wt.write_bits(blocks[i][j], VSEBLOCKS_LOGS[i]);

    wt.flush_bits();
  }

  /* write block codes... a byte each */
  for (uint32_t i = 0; i < numBlocks; i++) {
    /* Compute max B in the block */
    uint32_t maxB = 0;

    for (auto j = parts[i];
            j < parts[i + 1]; j++) {
      if (maxB < logs[j])
        maxB = logs[j];
    }

    uint32_t idx = 0;

    if (maxB) {
      /* Compute the code for the block length */
      for (; idx < VSEBLOCKS_LENS_LEN; idx++) {
        if (parts[i + 1] - parts[i] ==
                VSEBLOCKS_LENS[idx])
          break;
      }
    } else {
      /*
       * Treat runs of 0 in a different way.
       * Compute the code for the block length.
       */
      for (; idx < VSEBLOCKS_LENS_LEN; idx++) {
        if (parts[i + 1] - parts[i] ==
                VSEBLOCKS_ZLENS[idx])
          break;
      }
    }

    /* Writes the value of B and K */
    wt.write_bits(VSEBLOCKS_CODELOGS[maxB], VSEBLOCKS_LOGLOG);
    wt.write_bits(idx, VSEBLOCKS_LOGLEN);
  }

  wt.flush_bits();
  *size = wt.size();
}

namespace {

inline void CopySubLists(uint32_t offset,
                         uint32_t in,
                         uint32_t ** restrict out,
                         uint32_t ** restrict blk) {
  /* Permuting integers with a first 8-bit */
  uint32_t info = (in >> (VSEBLOCKS_LOGDESC * offset));
  info &= VSEBLOCKS_DESC_LEN - 1;

  uint32_t b = info >> VSEBLOCKS_LOGLEN;
  uint32_t k = info & (VSEBLOCKS_LENS_LEN - 1);

  if (LIKELY(b)) {
#if 0
    MEMCPY(*out, blk[b], VSEBLOCKS_LENS[k]);
#else
    if (LIKELY(k > (VSEBLOCKS_LENS_LEN >> 1) - 1)) {
      MEMCPY128(blk[b], *out);
      MEMCPY128(blk[b] + 4, *out + 4);
      MEMCPY128(blk[b] + 8, *out + 8);
      MEMCPY128(blk[b] + 12, *out + 12);
    } else {
      MEMCPY128(blk[b], *out);
      MEMCPY128(blk[b] + 4, *out + 4);
    }
#endif

    blk[b] += VSEBLOCKS_LENS[k];
    *out += VSEBLOCKS_LENS[k];
  } else {
#if 0
    ZMEMCPY(*out, VSEBLOCKS_ZLENS[k]);
#else
    if (LIKELY(k > (VSEBLOCKS_LENS_LEN >> 1) - 1)) {
      ZMEMCPY128(*out);
      ZMEMCPY128(*out + 4);
      ZMEMCPY128(*out + 8);
      ZMEMCPY128(*out + 12);
      ZMEMCPY128(*out + 16);
      ZMEMCPY128(*out + 20);
      ZMEMCPY128(*out + 24);
      ZMEMCPY128(*out + 28);
    } else {
      ZMEMCPY128(*out);
      ZMEMCPY128(*out + 4);
    }
#endif
    *out += VSEBLOCKS_ZLENS[k];
  }
}

} /* namespace: */

void VSEncodingBlocks::decodeVS(const uint32_t *in,
                                uint32_t len,
                                uint32_t *out,
                                uint32_t nvalue) const {
  ASSERT(in != NULL);
  ASSERT(len != 0);
  ASSERT(out != NULL);
  ASSERT(nvalue != 0);

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  uint32_t  *pblk[VSEBLOCKS_LOGS_LEN];

  const uint32_t *iterm = in + len;
  uint32_t *oterm = out + nvalue;

  /* All values unpacked in advance */
  int64_t ntotal = BYTEORDER_FREE_LOAD32(in);
  const uint32_t *data = ++in + ntotal;

  ASSERT(data < iterm);

  /* Get a working memory */
  uint32_t *aux = wmem_.get();

  while (LIKELY(ntotal-- > 0)) {
    uint32_t info = BYTEORDER_FREE_LOAD32(in);

    uint32_t b = info & (VSEBLOCKS_LOGS_LEN - 1);
    uint32_t nblk = info >> VSEBLOCKS_LOGLEN;

    /* Do unpacking */
    VSEBLOCKS_UNPACK[b](aux, data, nblk);
    pblk[b] = aux, aux += nblk;

    /* Move to next */
    in++;
    data += DIV_ROUNDUP(nblk * VSEBLOCKS_LOGS[b], 32);
  }

  while  (LIKELY(out < oterm && data < iterm)) {
    CopySubLists(3, *data, &out, pblk);
    CopySubLists(2, *data, &out, pblk);
    CopySubLists(1, *data, &out, pblk);
    CopySubLists(0, *data++, &out, pblk);
  }
}

void VSEncodingBlocks::encodeArray(const uint32_t *in,
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
  if (len > UINT32_MAX || *nvalue > UINT32_MAX)
    THROW_ENCODING_EXCEPTION(
        "VSEncodingBlocks only supports 32-bit length");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, *nvalue);

  uint32_t *oterm = out + *nvalue;

  uint64_t res = len;
  uint32_t csize = static_cast<uint32_t>(*nvalue);

  uint64_t ntotal = 0;
  while (LIKELY(res > VSENCODING_BLOCKSZ &&
                out < oterm)) {
    encodeVS(in, VSENCODING_BLOCKSZ, out + 1, &csize);
    in += VSENCODING_BLOCKSZ;

    BYTEORDER_FREE_STORE32(out, csize);
    out += csize + 1;

    /* Move to next */
    res -= VSENCODING_BLOCKSZ;
    ntotal += csize + 1;
    csize = static_cast<uint32_t>(*nvalue - ntotal);
  }

  /* If necessary, pack left values */
  if (LIKELY(res > 0 && out < oterm)) {
    encodeVS(in, res, out + 1, &csize);
    BYTEORDER_FREE_STORE32(
        out, static_cast<uint32_t>(csize));

    ntotal += csize + 1;
  }

  *nvalue = ntotal;
}

void VSEncodingBlocks::decodeArray(const uint32_t *in,
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
  if (len > UINT32_MAX || nvalue > UINT32_MAX)
    THROW_ENCODING_EXCEPTION(
        "VSEncodingBlocks only supports 32-bit length");

  ASSERT_ADDR(in, len);
  ASSERT_ADDR(out, nvalue);

  uint32_t res = static_cast<uint32_t>(nvalue);

  const uint32_t *iterm = in + len;

  while (LIKELY(res > VSENCODING_BLOCKSZ &&
                in < iterm)) {
    uint32_t sum = BYTEORDER_FREE_LOAD32(in);
    decodeVS(in + 1, sum, out, VSENCODING_BLOCKSZ);
    in += sum + 1;
    out += VSENCODING_BLOCKSZ;

    /* Move to next */
    res -= VSENCODING_BLOCKSZ;
  }

  if (LIKELY(res > 0 && in < iterm)) {
    uint32_t sum = BYTEORDER_FREE_LOAD32(in);
    decodeVS(in + 1, sum, out, res);
  }
}

uint64_t VSEncodingBlocks::require(uint64_t len) const {
  /* FIXME: Fill correct the required size */
  return len + 17;
}

} /* namespace: internals */
} /* namespace: integer_encoding */
