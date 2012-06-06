/*-----------------------------------------------------------------------------
 *  decbench.cpp - A benchmark for implemented coders.
 *      This benchmark uses a sequence of randomly generated integers as
 *      a test data set.
 *
 *  Coding-Style:
 *      emacs) Mode: C, tab-width: 8, c-basic-offset: 8, indent-tabs-mode: nil
 *      vi) tabstop: 8, expandtab
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *-----------------------------------------------------------------------------
 */

#include "integer_coding.hpp"
#include "xxx_common.hpp"

#include "misc/benchmarks.hpp"

#define BUFSIZE         1024

using namespace std;
using namespace integer_coding::compressor;

static void __usage(const char *msg, ...);

int
main(int argc, char **argv)
{
        char            *end;

        if (argc < 3)
                __usage(NULL);

        /* Recive input options */
        uint64_t        tsz;
        uint64_t        tlen;
        char            buf[BUFSIZE];

        /* Read CoderID */
        int codID = strtol(argv[1], &end, 10);
        if ((*end != '\0') || (codID < 0) ||
                        (codID >= NUMCODERS) ||(errno == ERANGE))
                __usage("CoderID '%s' invalid", argv[1]);

        strncpy(buf, argv[2], BUFSIZE);
        buf[BUFSIZE - 1] = '\0';

        uint32_t *tdata = __open_and_mmap_file(buf, tsz);

        tlen = (tsz >> 2) - 1;

        /* Allocate resources */
        shared_ptr<uint32_t> __list1(
                new uint32_t[tlen], default_delete<uint32_t[]>());

        uint32_t *list1 = __list1.get();

        shared_ptr<uint32_t> __list2(
                new uint32_t[OUTPUTMEM(tlen)], default_delete<uint32_t[]>());

        uint32_t *list2 = __list2.get();

        shared_ptr<uint32_t> __compressed(
                new uint32_t[tlen], default_delete<uint32_t[]>());

        uint32_t *compressed = __compressed.get();

        /* Re-format input data for some coders */
        for (uint32_t i = 0; i < tlen; i++) {
                if (tdata[i + 1] < tdata[i])
                        __usage("List ordering exception: list MUST be increasing");

                if (codID != C_BINARYIPL)
                        list1[i] = tdata[i + 1] - tdata[i] - 1;
                else
                        list1[i] = tdata[i + 1];
        }


        /* Do encoding */
        uint32_t        csize;

        CompressorPtr c = CompressorFactory::create(codID);
        c->encodeArray(list1, tlen, compressed, csize);

        /* Start benchmarking */
        double st = __get_time();
        c->decodeArray(compressed, csize, list2, tlen);
        double et = __get_time();

        /* Validation check */
        for (uint32_t i = 0; i < tlen; i++) {
                if (list1[i] != list2[i])
                        cerr << "Decoding Exception(" << i << "): "
                                << list1[i] << " != " << list2[i] << endl;
        }

        /* Show results */
        cout << "Performance: " << setprecision(5)
                << ((tlen + 0.0) / ((et - st) * 1000000)) << " mis" << endl; 
        cout << "Ratio: " << setprecision(3)
                << ((csize + 0.0) / tlen) * 100.0 << " %" << endl;

        return EXIT_SUCCESS;
}

/*--- Intra functions below ---*/

void
__usage(const char *msg, ...)
{
        cout << "Usage: decbench <CorderID> <TestData>" << endl;

        if (msg != NULL) {
                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stdout, msg, vargs);
                va_end(vargs);

                cout << endl;
        }

        exit(1);
}
