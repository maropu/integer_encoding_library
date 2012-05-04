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

#include "open_coders.hpp"
#include "misc/benchmarks.hpp"

#define BUFSIZE         1024

using namespace std;

#define __array_size(x) (sizeof(x) / sizeof(x[0]))

static void __usage(const char *msg, ...);

struct __coders_list {
        const char      *name;
        int             encID;
        int             decID;
};

/* A coder list to test */
static __coders_list __clist[] = {
        {"n-gamma", E_GAMMA, D_GAMMA},
        {"fu-gamma", E_GAMMA, D_FU_GAMMA},
        {"f-gamma", E_GAMMA, D_F_GAMMA},
        {"n-delta", E_DELTA, D_DELTA},
        {"fu-delta", E_DELTA, D_FU_DELTA},
        {"fg-delta", E_DELTA, D_FG_DELTA},
        {"f-delta", E_DELTA, D_F_DELTA},
        {"varbyte", E_VARIABLEBYTE, D_VARIABLEBYTE},
        {"biny-intpltv", E_BINARYIPL, D_BINARYIPL},
        {"simple9", E_SIMPLE9, D_SIMPLE9},
        {"simple16", E_SIMPLE16, D_SIMPLE16},
        {"p4delta", E_P4D, D_P4D},
        {"optp4delta", E_OPTP4D, D_OPTP4D},
        {"vseblocks", E_VSEBLOCKS, D_VSEBLOCKS},
        {"vse-r", E_VSER, D_VSER},
        {"vserest", E_VSEREST, D_VSEREST},
        {"vsehybrid", E_VSEHYB, D_VSEHYB},
        {"vsesimple-v1", E_VSESIMPLEV1, D_VSESIMPLEV1},
        {"vsesimple-v2", E_VSESIMPLEV2, D_VSESIMPLEV2}
};

int
main(int argc, char **argv)
{
        if (argc < 3)
                __usage(NULL);

        /* Recive input options */
        uint64_t        tsz;
        uint64_t        tlen;
        char            buf[BUFSIZE];

        strncpy(buf, argv[1], BUFSIZE);
        buf[BUFSIZE - 1] = '\0';

        int nlist = -1;
        for (uint32_t i = 0; i < __array_size(__clist); i++) {
                if (!strcmp(buf, __clist[i].name))
                        nlist = i;
        }

        if (nlist == -1)
                __usage("Invalid coder-type: %s\n", buf);

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

                if (__clist[nlist].encID != E_BINARYIPL)
                        list1[i] = tdata[i + 1] - tdata[i] - 1;
                else
                        list1[i] = tdata[i + 1];
        }

        /* Do encoding */
        uint32_t        csize;

        (encoders[__clist[nlist].encID])(list1, tlen, compressed, csize);

        /* Start benchmarking */
        double st = __get_time();
        (decoders[__clist[nlist].decID])(compressed, csize, list2, tlen);
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
        cout << "Usage: decbench <coder-types> <test-data>" << endl;

        if (msg != NULL) {
                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stdout, msg, vargs);
                va_end(vargs);

                cout << endl;
        }

        exit(1);
}
