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

#define __USE_GTEST__

#ifdef __USE_GTEST__
# include <gtest/gtest.h>
# define INIT_GTEST(argc, argv) \
    ::testing::InitGoogleTest(&argc, argv)
#else
# define TEST(test_case, test_subcase)  \
    void Test_##test_case##_##test_subcase()
# define INIT_GTEST(argc, argv)

# define EXPECT_EQ            CHECK_EQ
# define EXPECT_NE            CHECK_NE
# define EXPECT_FALSE(cond)   CHECK(!(cond))
# define EXPECT_STREQ         CHECK_STREQ
#endif /* __USE_GTEST__ */

namespace {

#ifndef __USE_GTEST__

void Test_IntegerEncoding_FactoryTests();
void Test_IntegerEncoding_BitsRWTests();
void Test_IntegerEncoding_GammaTests();
void Test_IntegerEncoding_DeltaTests();
void Test_IntegerEncoding_BinaryInterpolativeTests();

inline int RUN_ALL_TESTS() {
  fprintf(stderr, "Running the sets of unit-tests...\n");
  Test_IntegerEncoding_FactoryTests();
  Test_IntegerEncoding_BitsRWTests();
  Test_IntegerEncoding_GammaTests();
  Test_IntegerEncoding_DeltaTests();
  Test_IntegerEncoding_BinaryInterpolativeTests();
  fprintf(stderr, "All tests passed.\n");

  return 0;
}

#endif /* __USE_GTEST__ */

#define LOG(level)  LogMessage()
#define VLOG(level) (true)? (void)0 : \
    lze::LogMessageVoidify() & lze::LogMessage()

class LogMessage {
 public:
  LogMessage() {}
  ~LogMessage() {std::cerr << std::endl;}
  LogMessage& operator<< (const std::string& msg) {
    std::cerr << msg;
    return *this;
  }
};

#define ABORT_IF(cond)        \
    LIKELY(!cond)? (void)0 :  \
    lze::LogMessageVoidify() & lze::LogMessageCrash()

class LogMessageCrash : public LogMessage {
 public:
  LogMessageCrash() {}
  ~LogMessageCrash() {
    std::cerr << std::endl;
    abort();
  }
};

class LogMessageVoidify {
 public:
  LogMessageVoidify() {}
  void operator& (const LogMessage&) {}
};

#define CHECK(cond)         ABORT_IF(!(cond))
#define CHECK_EQ(a, b)      ABORT_IF((a) != (b))
#define CHECK_NE(a, b)      ABORT_IF((a) == (b))
#define CHECK_STREQ(a, b)   ABORT_IF(strcmp(a, b))

}; /* namespace: */

using namespace integer_encoding;
using namespace integer_encoding::internals;

/*
 * A series of unit tests for LZEnd++ below
 */
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
    /* Encoder ID: E_BINARYIPL */
    EncodingPtr c = EncodingFactory::create(E_BINARYIPL);
    EXPECT_EQ(typeid(BinaryInterpolative), typeid(*c));
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

class IntegerEncoding : public ::testing::Test {
 public:
  virtual void SetUp() {
    data = OpenFile(".testdata/gov2.dat", &len);
    len >>= 2;
  }

  virtual void TearDown() {}
  uint32_t  *data;
  uint64_t  len;
};

TEST_F(IntegerEncoding, GammaTests) {
  /* Generate encoders */
  EncodingPtr c0 = EncodingFactory::create(E_N_GAMMA);
  EncodingPtr c1 = EncodingFactory::create(E_F_GAMMA);
  EncodingPtr c2 = EncodingFactory::create(E_FU_GAMMA);

  {
    /* Simple Tests */
    const uint32_t in[16] = {
      3, 9, 2, 0, 1, 9, 13, 2, 9, 6, 2, 20, 1, 3, 4, 9
    };

    uint32_t out[c0->outRequire(16)];
    uint32_t dec[c0->inRequire(16)];

    uint64_t nvalue = c0->outRequire(16);
    c0->encodeArray(in, 16, out, &nvalue);

    /* Tests for N_Gamma */
    c0->decodeArray(out, nvalue, dec, c0->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);

    /* Tests for F_Gamma */
    c1->decodeArray(out, nvalue, dec, c1->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);

    /* Tests for FU_Gamma */
    c2->decodeArray(out, nvalue, dec, c2->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);
  }

  {
    /* Long Sequence Tests */
    REGISTER_VECTOR_RAII(uint32_t, out, c0->outRequire(len));
    REGISTER_VECTOR_RAII(uint32_t, dec, c0->inRequire(len));

    uint64_t nvalue = c0->outRequire(len);
    c0->encodeArray(data, len, out, &nvalue);

    /* Tests for N_Gamma */
    c0->decodeArray(out, nvalue, dec, c0->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);

    /* Tests for F_Gamma */
    c1->decodeArray(out, nvalue, dec, c1->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);

    /* Tests for FU_Gamma */
    c2->decodeArray(out, nvalue, dec, c2->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);
  }
}

TEST_F(IntegerEncoding, DeltaTests) {
  /* Generate encoders */
  EncodingPtr c0 = EncodingFactory::create(E_N_DELTA);
  EncodingPtr c1 = EncodingFactory::create(E_F_DELTA);
  EncodingPtr c2 = EncodingFactory::create(E_FU_DELTA);
  EncodingPtr c3 = EncodingFactory::create(E_FG_DELTA);

  {
    /* Simple Tests */
    const uint32_t in[16] = {
      3, 9, 2, 0, 1, 9, 13, 2, 9, 6, 2, 20, 1, 3, 4, 9
    };

    uint32_t out[c0->outRequire(16)];
    uint32_t dec[c0->inRequire(16)];

    uint64_t nvalue = c0->outRequire(16);
    c0->encodeArray(in, 16, out, &nvalue);

    /* Tests for N_Delta */
    c0->decodeArray(out, nvalue, dec, c0->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);

    /* Tests for F_Delta */
    c1->decodeArray(out, nvalue, dec, c1->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);

    /* Tests for FU_Delta */
    c2->decodeArray(out, nvalue, dec, c2->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);

    /* Tests for FG_Delta */
    c3->decodeArray(out, nvalue, dec, c3->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);
  }

  {
    /* Long Sequence Tests */
    REGISTER_VECTOR_RAII(uint32_t, out, c0->outRequire(len));
    REGISTER_VECTOR_RAII(uint32_t, dec, c0->inRequire(len));

    uint64_t nvalue = c0->outRequire(len);
    c0->encodeArray(data, len, out, &nvalue);

    /* Tests for N_Delta */
    c0->decodeArray(out, nvalue, dec, c0->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);

    /* Tests for F_Delta */
    c1->decodeArray(out, nvalue, dec, c1->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);

    /* Tests for FU_Delta */
    c2->decodeArray(out, nvalue, dec, c2->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);

    /* Tests for FG_Delta */
    c3->decodeArray(out, nvalue, dec, c3->inRequire(len));
    for (uint64_t i = 0; i < len; i++)
      EXPECT_EQ(data[i], dec[i]);
  }
}

TEST_F(IntegerEncoding, BinaryInterpolativeTests) {
  /* Generate encoders */
  EncodingPtr c = EncodingFactory::create(E_BINARYIPL);

  {
    /* Simple Tests */
    const uint32_t in[16] = {
      3, 9, 13, 14, 19, 21, 25, 31, 34, 39, 44, 48, 52, 55, 59, 60
    };

    uint32_t out[c->outRequire(16)];
    uint32_t dec[c->inRequire(16)];

    uint64_t nvalue = c->outRequire(16);
    c->encodeArray(in, 16, out, &nvalue);

    /* Tests for BinaryInterpolative */
    c->decodeArray(out, nvalue, dec, c->inRequire(16));
    for (int i = 0; i < 16; i++)
      EXPECT_EQ(in[i], dec[i]);
  }

  /* Long Sequence Tests */

}

int main(int argc, char **argv) {
  INIT_GTEST(argc, argv);
  return RUN_ALL_TESTS();
}
