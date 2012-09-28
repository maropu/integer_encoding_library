/*-----------------------------------------------------------------------------
 *  encoding_unitest.cpp - Unit tests for integer_encoding.cpp
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

#include <integer_encoding.hpp>
#include <vcompress.hpp>

#include <gtest/gtest.h>

using namespace integer_encoding;
using namespace integer_encoding::internals;

TEST(IntegerEncodingInternals, FactoryTests) {
  {
    /* Encoder ID: E_N_GAMMA  */
    EncodingPtr c = EncodingFactory::create(E_N_GAMMA);
    EXPECT_EQ(typeid(N_Gamma), typeid(*c));
  }

  {
    /* Encoder ID: E_F_GAMMA */
    EncodingPtr c = EncodingFactory::create(E_F_GAMMA);
    EXPECT_EQ(typeid(F_Gamma), typeid(*c));
  }

  {
    /* Encoder ID: E_FU_GAMMA */
    EncodingPtr c = EncodingFactory::create(E_FU_GAMMA);
    EXPECT_EQ(typeid(FU_Gamma), typeid(*c));
  }

  {
    /* Encoder ID: E_N_DELTA */
    EncodingPtr c = EncodingFactory::create(E_N_DELTA);
    EXPECT_EQ(typeid(N_Delta), typeid(*c));
  }

  {
    /* Encoder ID: E_F_DELTA */
    EncodingPtr c = EncodingFactory::create(E_F_DELTA);
    EXPECT_EQ(typeid(F_Delta), typeid(*c));
  }

  {
    /* Encoder ID: E_FU_DELTA */
    EncodingPtr c = EncodingFactory::create(E_FU_DELTA);
    EXPECT_EQ(typeid(FU_Delta), typeid(*c));
  }

  {
    /* Encoder ID: E_FG_DELTA */
    EncodingPtr c = EncodingFactory::create(E_FG_DELTA);
    EXPECT_EQ(typeid(FG_Delta), typeid(*c));
  }

  {
    /* Encoder ID: E_VARIABLEBYTE */
    EncodingPtr c = EncodingFactory::create(E_VARIABLEBYTE);
    EXPECT_EQ(typeid(VariableByte), typeid(*c));
  }

  {
    /* Encoder ID: E_BINARYIPL */
    EncodingPtr c = EncodingFactory::create(E_BINARYIPL);
    EXPECT_EQ(typeid(BinaryInterpolative), typeid(*c));
  }

  {
    /* Encoder ID: E_SIMPLE9 */
    EncodingPtr c = EncodingFactory::create(E_SIMPLE9);
    EXPECT_EQ(typeid(Simple9), typeid(*c));
  }

  {
    /* Encoder ID: E_SIMPLE16 */
    EncodingPtr c = EncodingFactory::create(E_SIMPLE16);
    EXPECT_EQ(typeid(Simple16), typeid(*c));
  }

  {
    /* Encoder ID: E_P4D */
    EncodingPtr c = EncodingFactory::create(E_P4D);
    EXPECT_EQ(typeid(PForDelta), typeid(*c));
  }

  {
    /* Encoder ID: E_OPTP4D */
    EncodingPtr c = EncodingFactory::create(E_OPTP4D);
    EXPECT_EQ(typeid(OPTPForDelta), typeid(*c));
  }

  {
    /* Encoder ID: E_VSEBLOCKS */
    EncodingPtr c = EncodingFactory::create(E_VSEBLOCKS);
    EXPECT_EQ(typeid(VSEncodingBlocks), typeid(*c));
  }

  {
    /* Encoder ID: E_VSER */
    EncodingPtr c = EncodingFactory::create(E_VSER);
    EXPECT_EQ(typeid(VSE_R), typeid(*c));
  }

  {
    /* Encoder ID: E_VSEREST */
    EncodingPtr c = EncodingFactory::create(E_VSEREST);
    EXPECT_EQ(typeid(VSEncodingRest), typeid(*c));
  }

  {
    /* Encoder ID: E_VSEHYB */
    EncodingPtr c = EncodingFactory::create(E_VSEHYB);
    EXPECT_EQ(typeid(VSEncodingBlocksHybrid), typeid(*c));
  }

  {
    /* Encoder ID: E_VSESIMPLE */
    EncodingPtr c = EncodingFactory::create(E_VSESIMPLE);
    EXPECT_EQ(typeid(VSEncodingSimple), typeid(*c));
  }

  EXPECT_THROW(EncodingFactory::create(E_INVALID),
               encoding_exception);
}

TEST(IntegerEncodingInternals, BitsRWTests) {
  uint32_t  out[2];

  BitsWriter wt(out, 2);

  EXPECT_EQ(0, wt.size());
  EXPECT_EQ(&out[0], wt.pos());

  EXPECT_NO_THROW(wt.write_bits(4, 3));
  EXPECT_NO_THROW(wt.write_bits(8, 4));
  EXPECT_NO_THROW(wt.write_bits(23, 5));
  EXPECT_NO_THROW(wt.write_bits(62, 6));
  EXPECT_NO_THROW(wt.write_bits(91, 7));
  EXPECT_NO_THROW(wt.write_bits(149, 8));
  EXPECT_NO_THROW(wt.write_bits(190, 8));
  EXPECT_NO_THROW(wt.write_bits(217, 8));
  EXPECT_NO_THROW(wt.write_bits(255, 8));
  EXPECT_NO_THROW(wt.flush_bits());

  EXPECT_EQ(2, wt.size());
  EXPECT_EQ(&out[2], wt.pos());

  EXPECT_THROW(wt.write_bits(329, 9), encoding_exception);

  BitsReader rd(out, 2);
  EXPECT_EQ(4, rd.read_bits(3));
  EXPECT_EQ(8, rd.read_bits(4));
  EXPECT_EQ(23, rd.read_bits(5));
  EXPECT_EQ(62, rd.read_bits(6));
  EXPECT_EQ(91, rd.read_bits(7));
  EXPECT_EQ(149, rd.read_bits(8));
  EXPECT_EQ(190, rd.read_bits(8));
  EXPECT_EQ(217, rd.read_bits(8));
  EXPECT_EQ(255, rd.read_bits(8));

  EXPECT_THROW(rd.read_bits(9), encoding_exception);
}

namespace {

class SkewedRandom {
 public:
  SkewedRandom() {}
  ~SkewedRandom() throw() {}
  uint32_t next(int log) {
    ASSERT(log > 0 && log < 32);
    const uint32_t base = (xor128() - 1) % log;
    return (xor128() - 1) & ((1U << base) - 1);
  }
};

const int RANDOM_TEST_LEN = 1000000;
const int RANDOM_TEST_LOG = 23;

} /* nemespace: */

class IntegerEncoding : public ::testing::TestWithParam<int> {
 public:
  virtual void SetUp() {
    /* test data sets: 1 */
    data = OpenFile(".testdata/gov2.dat", &len);
    len >>= 2;

    /* test data sets: 2 */
    SkewedRandom  rnd;
    rlen = RANDOM_TEST_LEN;
    rdata = new uint32_t[rlen];
    for (int i = 0; i < rlen; i++)
      rdata[i] = rnd.next(RANDOM_TEST_LOG);
  }

  virtual void TearDown() {delete[] rdata;}

  /* test data sets: 1 */
  uint32_t  *data;
  uint64_t  len;

  /* test data sets: 2 */
  uint32_t  *rdata;
  uint64_t  rlen;
};

TEST_P(IntegerEncoding, EncoderTests) {
  /* Generate encoders */
  int policy = GetParam();
  EncodingPtr c = EncodingFactory::create(policy);

  {
    /* Simple Tests */
    uint64_t nvalue = c->require(16);
    uint32_t out[nvalue];
    uint32_t dec[DECODE_REQUIRE_MEM(16)];

    uint32_t data[16] = {
        3, 9, 2, 0, 1, 9, 13, 2, 9, 6, 2, 20, 1, 3, 4, 9
    };

    if (policy == E_BINARYIPL) {
      for (int i = 1; i < 16; i++)
        data[i] += data[i - 1] + 1;
    }

    EXPECT_NO_THROW(c->encodeArray(data, 16, out, &nvalue));
    EXPECT_NO_THROW(c->decodeArray(out, nvalue, dec, 16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(data[i], dec[i]);
  }

  {
    /* Simple Tests */
    /* Long Sequence Tests */
    uint64_t nvalue = c->require(len);
    REGISTER_VECTOR_RAII(uint32_t, out, nvalue);
    REGISTER_VECTOR_RAII(uint32_t, dec, DECODE_REQUIRE_MEM(len));

    if (policy == E_BINARYIPL) {
      REGISTER_VECTOR_RAII(uint32_t, sdata, len);

      for (uint64_t i = 0; i < len; i++)
        sdata[i] = data[i] + ((i > 0)? sdata[i - 1] + 1 : 0);

      EXPECT_NO_THROW(c->encodeArray(sdata, len, out, &nvalue));
      EXPECT_NO_THROW(c->decodeArray(out, nvalue, dec, len));
      for (uint64_t i = 0; i < len; i++)
        EXPECT_EQ(sdata[i], dec[i]);
    } else {
      EXPECT_NO_THROW(c->encodeArray(data, len, out, &nvalue));
      EXPECT_NO_THROW(c->decodeArray(out, nvalue, dec, len));
      for (uint64_t i = 0; i < len; i++)
        EXPECT_EQ(data[i], dec[i]);
    }
  }

  {
    /* Skewed Random Sequence Tests */
    uint64_t nvalue = c->require(rlen);
    REGISTER_VECTOR_RAII(uint32_t, out, nvalue);
    REGISTER_VECTOR_RAII(uint32_t, dec, DECODE_REQUIRE_MEM(rlen));

    if (policy != E_BINARYIPL) {
      EXPECT_NO_THROW(c->encodeArray(rdata, rlen, out, &nvalue));
      EXPECT_NO_THROW(c->decodeArray(out, nvalue, dec, rlen));
      for (uint64_t i = 0; i < rlen; i++)
        EXPECT_EQ(rdata[i], dec[i]);
    }
  }
}

INSTANTIATE_TEST_CASE_P(
    IntegerEncodingInstance,
    IntegerEncoding,
    testing::Values(E_N_GAMMA, E_F_GAMMA, E_FU_GAMMA,
                    E_N_DELTA, E_F_DELTA, E_FU_DELTA, E_FG_DELTA,
                    E_VARIABLEBYTE, E_BINARYIPL,
                    E_SIMPLE9, E_SIMPLE16,
                    E_P4D, E_OPTP4D,
                    E_VSEBLOCKS, E_VSER, E_VSEREST, E_VSEHYB, E_VSESIMPLE));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
