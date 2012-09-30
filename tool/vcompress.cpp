/*-----------------------------------------------------------------------------
 *  vcompress.cpp - A demo code for integer encoders/decoders
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

using namespace integer_encoding;
using namespace integer_encoding::internals;

namespace {

/* Current version embeded in a file header */
const uint32_t VC_MAGIC = 0x0f823cb4;
const uint32_t VC_MAJOR = 0;
const uint32_t VC_MINOR = 3;
const uint32_t VC_PATCHLEVEL = 0;
const uint32_t VC_VERSION =
    ((VC_MAJOR << 16) | (VC_MINOR << 8) | VC_PATCHLEVEL);

/* Valid options */
bool decompress_enabled =  false;
bool verbose_enabled =  false;
bool squeeze_enabled = false;
int encoder_id = -1;
uint64_t num_compressed = 0;
std::string input;
std::string output;

/* Extensions for encoders */
const std::string encoder_suffix[] = {
  ".gamma",   /* N Gamma */
  ".gamma",   /* FU Gamma */
  ".gamma",   /* F Gamma */
  ".delta",   /* N Delta */
  ".delta",   /* FU Delta */
  ".delta",   /* FG Delta */
  ".delta",   /* F Delta */
  ".vb",      /* Variable Byte */
  ".bip",     /* Binary Interpolative */
  ".s9",      /* Simple 9 */
  ".s16",     /* Simple 16 */
  ".p4d",     /* PForDelta */
  ".op4d",    /* OPTPForDelta */
  ".vse",     /* VSEncodingBlocks */
  ".vser",    /* VSE-R */
  ".vsert",   /* VSencodingRest */
  ".vseh",    /* VSEncodingBlocksHybrid */
  ".vses",    /* VSEncodingSimple */
};

/* For position of data */
const std::string pos_suffix = ".vc";

void show_usage() {
  fprintf(stderr, "Usage: vcompress [OPTIONS]... [ID] [FILE] [OUT]\n");
  fprintf(stderr, "Compress or uncompress FILE ");
  fprintf(stderr, "(by default, compress FILE).\n");
  fprintf(stderr, "-d, decompress\n");
  fprintf(stderr, "-l, ID list\n");
  fprintf(stderr, "-n XXX, number to decompress\n");
  fprintf(stderr, "-v, verbose mode\n\n");
  fprintf(stderr, "Report bugs to <integerencoding_at_isti.cnr.it>\n\n");

  exit(1);
}

void show_ids() {
  fprintf(stderr, "The library uses following IDs:\n");
  fprintf(stderr, "ID\tName\n");
  fprintf(stderr, "---\n");
  fprintf(stderr, "0\tN Gamma\n");
  fprintf(stderr, "1\tFU Gamma\n");
  fprintf(stderr, "2\tF Gamma\n");
  fprintf(stderr, "3\tN Delta\n");
  fprintf(stderr, "4\tFU Delta\n");
  fprintf(stderr, "5\tFG Delta\n");
  fprintf(stderr, "6\tF Delta\n");
  fprintf(stderr, "7\tVariable Byte\n");
  fprintf(stderr, "8\tBinary Interpolative\n");
  fprintf(stderr, "9\tSimple 9\n");
  fprintf(stderr, "10\tSimple 16\n");
  fprintf(stderr, "11\tPForDelta\n");
  fprintf(stderr, "12\tOPTPForDelta\n");
  fprintf(stderr, "13\tVSEncodingBlocks\n");
  fprintf(stderr, "14\tVSE-R\n");
  fprintf(stderr, "15\tVSEncodingRest\n");
  fprintf(stderr, "16\tVSEncodingBlocksHybrid\n");
  fprintf(stderr, "17\tVSEncodingSimple\n");
  fprintf(stderr, "\n");

  exit(1);
}

int parse_command(int argc, char **argv) {
  int   result;
  char  *end;

  /* Read input options */
  while ((result = getopt(argc, argv, "dlvhn:")) != -1) {
    switch (result) {
      case 'd': {decompress_enabled = true; break;}
      case 'v': {verbose_enabled = true; break;}
      case 'n': {
        squeeze_enabled = true;
        num_compressed = strtol(optarg, &end, 10);
        break;
      }
      case 'l': {show_ids(); break;}
      case 'h': {show_usage(); break;}
      case '?': {show_usage(); break;}
    }
  }

  if (squeeze_enabled &&
          (num_compressed <= NSKIP ||
              num_compressed >= MAXLEN))
    return 1;

  if (decompress_enabled) {
    /* Left arguments MUST be >= 1 */
    if (argc <= optind)
      return 1;

    input = argv[optind++];
    if (argc > optind)
      output = argv[optind];

    return 0;
  }

  /* Left arguments MUST be >= 2 */
  if (argc < optind + 2)
    return 1;

  /* Get a encoder ID */
  encoder_id = strtol(argv[optind++], &end, 10);
  if ((errno == ERANGE) || (*end != '\0') || (encoder_id < 0) ||
      (encoder_id >= NUMCODERS)) {
    fprintf(stderr, "Invalid EncoderID: %d\n\n", encoder_id);
    show_ids();
  }

  input = argv[optind++];

  return 0;
}

void skip_headerinfo(FILE *cmp, FILE *pos) {
  ASSERT(cmp != NULL);
  ASSERT(pos != NULL);
  fseeko(cmp, CMP_HEADER_SZ, SEEK_SET);
  fseeko(pos, POS_HEADER_SZ, SEEK_SET);
}

void write_headerinfo(FILE *cmp, FILE *pos) {
  ASSERT(cmp != NULL);
  ASSERT(pos != NULL);

  char  buf[32];

  /* Generate a random-generated magic number */
  uint32_t rmagic = xor128();

  /* Get file size */
  uint64_t cmplen = ftello(cmp);
  uint64_t poslen = ftello(pos);

  /* Rewind the file descriptors */
  fseeko(cmp, 0, SEEK_SET);
  fseeko(pos, 0, SEEK_SET);

  /* Write down in cmp */
  BYTEORDER_FREE_STORE32(buf, rmagic);
  fwrite(buf, 4, 1, cmp);
  fsync(fileno(cmp));

  /* Write down in pos */
  BYTEORDER_FREE_STORE32(buf, encoder_id);
  BYTEORDER_FREE_STORE32(buf + 4, VC_VERSION);
  BYTEORDER_FREE_STORE32(buf + 8, VC_MAGIC);
  BYTEORDER_FREE_STORE32(buf + 12, rmagic);
  BYTEORDER_FREE_STORE64(buf + 16, cmplen);
  BYTEORDER_FREE_STORE64(buf + 24, poslen);
  fwrite(buf, 32, 1, pos);
  fsync(fileno(pos));
}

void write_pos_entry(uint32_t num,
                     uint32_t prev,
                     uint64_t pos, FILE *out) {
  ASSERT(out != NULL);
  char buf[16];
  BYTEORDER_FREE_STORE64(buf, pos);
  BYTEORDER_FREE_STORE32(buf + 8, num);
  BYTEORDER_FREE_STORE32(buf + 12, prev);
  fwrite(buf, 16, 1, out);
}

void write_pos_entry(uint64_t pos, FILE *out) {
  ASSERT(out != NULL);
  char buf[8];
  BYTEORDER_FREE_STORE64(buf, pos);
  fwrite(buf, 8, 1, out);
}

void validate_encoder_id(uint32_t **pos) {
  encoder_id = VC_LOAD32(*pos);
  if ((encoder_id < 0) || (encoder_id >= NUMCODERS))
    OUTPUT_AND_DIE("File format exception: encoder ID");
}

void validate_headerinfo(uint32_t **cmp, uint64_t cmplen,
                         uint32_t **pos, uint64_t poslen) {
  /* Check VC_VERSION and VC_MAGIC */
  uint32_t version = VC_LOAD32(*pos);
  uint32_t magic = VC_LOAD32(*pos);

  if (magic != VC_MAGIC || version != VC_VERSION)
    OUTPUT_AND_DIE("File format exception: version");

  /* Check a correct pair of compressed data */
  uint32_t rmagic = VC_LOAD32(*pos);
  uint32_t cmp_rmagic = VC_LOAD32(*cmp);

  if (rmagic != cmp_rmagic)
    OUTPUT_AND_DIE("File format exception: file");

  /* Check a length of input files */
  uint64_t cmpvlen = VC_LOAD64(*pos);
  uint64_t posvlen = VC_LOAD64(*pos);

  if (cmplen != cmpvlen || poslen != posvlen)
    OUTPUT_AND_DIE("File format exception: file length");
}

void do_compress(const std::string& input, int id) {
  /* Open a input file */
  uint64_t len = 0;
  uint32_t *addr = OpenFile(input, &len);

  /* Open output files */
  FILE *cmp = fopen((input + encoder_suffix[id]).c_str(), "w");
  FILE *pos = fopen((input + pos_suffix).c_str(), "w");
  if (cmp == NULL || pos == NULL)
    OUTPUT_AND_DIE("Exception: can't open output files");

  /* Allocate the pre-defined size of memory */
  REGISTER_VECTOR_RAII(uint32_t, list, MAXLEN);
  REGISTER_VECTOR_RAII(uint32_t, cmp_array, MAXLEN);

  EncodingPtr c = EncodingFactory::create(id);

  /* Skip a header, and fill it finally  */
  skip_headerinfo(cmp, pos);

  /* Do actual compression */
  uint64_t cmp_pos = 0;
  uint32_t *term = addr + (len >> 2);

  while (LIKELY(addr < term)) {
    /* Read the numer of integers in a list */
    uint32_t num = VC_LOAD32(addr);
    if (UNLIKELY(addr + num > term))
      goto LOOP_END;

    uint32_t prev = VC_LOAD32(addr);
    uint32_t base = prev;

    if (UNLIKELY(num > NSKIP && num < MAXLEN)) {
      for (uint32_t i = 0; i < num - 1; i++) {
        uint32_t d = VC_LOAD32(addr);
        if (UNLIKELY(d < prev))
          fprintf(stderr, "List Order Exception: Lists MUST be increasing\n");

        if (id != E_BINARYIPL)
          list[i] = d - prev - 1;
        else
          list[i] = d;

        prev = d;
      }

      if (squeeze_enabled) {
        if (num < num_compressed)
          continue;

        /* Chop lists to compress for performance tests */
        num = num_compressed;
      }

      write_pos_entry(num, base, cmp_pos, pos);

      uint64_t cmp_size = MAXLEN;
      c->encodeArray(list, num - 1, cmp_array, &cmp_size);

      /* NOTE: the data in cmp_array are byte-order free */
      fwrite(cmp_array, 4, cmp_size, cmp);
      cmp_pos += cmp_size;
    } else {
      /* Skip a needless list */
      addr += num - 1;
    }
  }

 LOOP_END:
  /* Write the terminal position for decoding */
  write_pos_entry(cmp_pos, pos);

  /* Fill the header */
  write_headerinfo(cmp, pos);

  fclose(cmp);
  fclose(pos);
}

void do_decompress(const std::string& input,
                   const std::string& output) {
  /* Open a file for position */
  uint64_t poslen = 0;
  uint32_t *pos = OpenFile(input, &poslen);

  /* Get a encoder id from the header */
  validate_encoder_id(&pos);

  /* Open a file for position */
  uint64_t cmplen = 0;
  uint32_t *cmp = OpenFile(
      input.substr(0, input.length() - pos_suffix.length()) +
      encoder_suffix[encoder_id], &cmplen);

  /* Open a output file */
  FILE *out = NULL;
  if (output.length() != 0) {
    out = fopen(output.c_str(), "w");
    if (out == NULL)
      OUTPUT_AND_DIE("Exception: can't open a output file");
  }

  /* Validate input files with header infomation */
  validate_headerinfo(&cmp, cmplen, &pos, poslen);

  REGISTER_VECTOR_RAII(uint32_t,
                       list,
                       DECODE_REQUIRE_MEM(MAXLEN + 128));

  EncodingPtr c = EncodingFactory::create(encoder_id);

  /* Summary information */
  uint64_t dnum = 0;
  double elapsed = 0;

  /* Do actual decompression */
  uint32_t numHeaders =
      (poslen - POS_HEADER_SZ) / POS_EACH_ENTRY_SZ;

  uint64_t cmp_pos = VC_LOAD64(pos);
  for (uint64_t i = 0; i < numHeaders; i++) {
    uint32_t num = VC_LOAD32(pos);
    uint32_t prev = VC_LOAD32(pos);
    uint64_t next_pos = VC_LOAD64(pos);

    ASSERT(num < MAXLEN);

    /* Do decoding */
    uint32_t *ptr = reinterpret_cast<uint32_t *>(cmp) + cmp_pos;

    BenchmarkTimer  t;
    c->decodeArray(ptr, next_pos - cmp_pos, list, num - 1);
    elapsed += t.elapsed();
    dnum += num - 1;

    /* Write in the output file */
    if (out != NULL) {
      char buf[8];
      BYTEORDER_FREE_STORE32(buf, num);
      BYTEORDER_FREE_STORE32(buf + 4, prev);

      fwrite(buf, 8, 1, out);

      if (encoder_id != E_BINARYIPL) {
        for (uint32_t j = 0; j < num - 1; j++) {
          prev += list[j] + 1;
          BYTEORDER_FREE_STORE32(buf, prev);
          fwrite(buf, 4, 1, out);
        }
      } else {
        for (uint32_t j = 0; j < num - 1; j++) {
          BYTEORDER_FREE_STORE32(buf, list[j]);
          fwrite(buf, 4, 1, out);
        }
      }
    }

    /* Move to next */
    cmp_pos = next_pos;
  }

  /* Show performance results */
  fprintf(stdout, "Performance Results(ID:%d):\n", encoder_id);
  fprintf(stdout, "  Total Num Decoded: %llu\n",
          static_cast<unsigned long long>(dnum));
  fprintf(stdout, "  Elapsed: %.2lf\n", elapsed);
  fprintf(stdout, "  Performance: %.2lfmis\n", (dnum + 0.0) / (elapsed * 1000000));
  fprintf(stdout, "  Throughput: %.2lfGiB/s\n",
          dnum * 4.0 / (elapsed * 1024 * 1024 * 1024));
  fprintf(stdout, "  Size: %.2lfbpi\n", ((cmp_pos + 0.0) / dnum) * 32);
}

}; /* namespace: */

int main(int argc, char **argv) {
  if (parse_command(argc, argv)) {
    fprintf(stderr, "vcompress: compressed data not written to a terminal.\n");
    fprintf(stderr, "For help, type: vcompress -h\n");
    exit(1);
  }

  if (decompress_enabled)
    do_decompress(input, output);
  else
    do_compress(input, encoder_id);

  return 0;
}
