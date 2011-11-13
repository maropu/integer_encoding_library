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

#include "encoders.hpp"
#include "decoders.hpp"

using namespace std;

#define NCTYPENAME      64

#define MAX_N           1000000000
#define MIN_N           10
#define MAX_RAVG        1000000
#define MIN_RAVG        2

#define __array_size(x) (sizeof(x) / sizeof(x[0]))

static void __usage(const char *msg, ...);
static uint32_t __get_random(int d);

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

static int32_t _init_rand;

int
main(int argc, char **argv)
{
        char            buf[NCTYPENAME];
        char            *end;
        int             nlist;
        uint32_t        i;
        uint32_t        N;
        uint32_t        L;
        uint32_t        *list1;
        uint32_t        *list2;
        uint32_t        *cmp_array;
        uint32_t        cmp_size;
        double          st;
        double          et;

        if (argc < 4)
                __usage(NULL);

        strncpy(buf, argv[1], NCTYPENAME);
        buf[NCTYPENAME - 1] = '\0';

        for (i = 0, nlist = -1; i < __array_size(__clist); i++)
                if (!strcmp(buf, __clist[i].name))
                        nlist = i;

        if (nlist == -1)
                __usage("Invalid coder-type: %s\n", buf);

        N = strtol(argv[2], &end, 10);

        if (N >= MAX_N || N <= MIN_N)
                __usage("Invalid N: %d\n", N);

        L = strtol(argv[3], &end, 10);

        if (L >= MAX_RAVG || L <= MIN_RAVG)
                __usage("Invalid Lambda: %d\n", L);

        /* Generate test data sets */
        list1 = new uint32_t[N + TAIL_MERGIN];
        list2 = new uint32_t[N + TAIL_MERGIN];
        cmp_array = new uint32_t[MAXLEN + TAIL_MERGIN];

        if (list1 == NULL || list2 == NULL || cmp_array == NULL)
                eoutput("Can't allocate memory");

        if (__clist[nlist].encID != E_BINARYIPL) {
                for (i = 0; i < N; i++)
                        list1[i] = __get_random(L);
        } else {
                uint32_t        r;

                for (i = 1, list1[0] = 0; i < N; i++) {
                        r = __get_random(L) + 1;

                        if (UINT32_MAX - list1[i - 1] < r)
                                eoutput("Overflow Exception");

                        list1[i] = list1[i - 1] + r;
                }
        }

        /* Do encoding */
        (encoders[__clist[nlist].encID])(list1, N, cmp_array, cmp_size);

        /* Start benchmarking */
        st = int_utils::get_time();
        (decoders[__clist[nlist].decID])(cmp_array, N, list2, N);
        et = int_utils::get_time();

        /* Validation check */
        for (i = 0; i < N; i++) {
                if (list1[i] != list2[i])
                        cerr << "Decoding Exception(" << i << "): "
                                <<list1[i] << " != " << list2[i] << endl;
        }

        /* Show results */
        cout << "Performance: " << setprecision(5)
                << ((N + 0.0) / ((et - st) * 1000000)) << " mis" << endl; 
        cout << "Ratio: " << setprecision(3)
                << ((cmp_size + 0.0) / N) * 100.0 << " %" << endl;

        delete[] list1;
        delete[] list2;
        delete[] cmp_array;

        return EXIT_SUCCESS;
}

/*--- Intra functions below ---*/

uint32_t
__get_random(int d)
{
        if  (!_init_rand++)
                srand(0);

        return (uint32_t)(d * ((double)rand() / UINT_MAX));
}

void
__usage(const char *msg, ...)
{
        cout << "Usage: encoders <coder-types> <N> <Maximum>" << endl;

        if (msg != NULL) {
                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stdout, msg, vargs);
                va_end(vargs);

                cout << endl;
        }

        exit(1);
}
