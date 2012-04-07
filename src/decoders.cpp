/*-----------------------------------------------------------------------------
 *  decoders.cpp - Decoders de-compressing correspinding encorded integers
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

#include "xxx_common.hpp"
#include "misc/benchmarks.hpp"

using namespace std;
using namespace opc;

static void __usage(const char *msg, ...);

int 
main(int argc, char **argv)
{
        char            *end;

        if (argc < 3)
                __usage(NULL);

        int decID = strtol(argv[1], &end, 10);
        if ((*end != '\0') || (decID < 0) ||
                        (decID >= NUMDECODERS) || (errno == ERANGE))
                __usage("DecoderID '%s' invalid", argv[1]);

        shared_ptr<uint32_t> __list(
                new uint32_t[OUTPUTMEM(MAXLEN)], default_delete<uint32_t[]>());

        uint32_t *list = __list.get();

        /*
         * FIXME: VSEncodingRest self-modifies a compressed
         * list during decoding, so it must copy data to
         * sbuf[] with memcpy. 
         */
        uint32_t *sbuf = NULL;

        shared_ptr<uint32_t> __sbuf(
                static_cast<uint32_t *>(0), default_delete<uint32_t[]>());

        if (decID == D_VSEREST ||
                        decID == D_VSEHYB) {
                shared_ptr<uint32_t> __temp(
                        new uint32_t[OUTPUTMEM(MAXLEN)],
                        default_delete<uint32_t[]>());

                sbuf = (__sbuf = __temp).get();
        }

        /* Read the file name, and open it */
        uint64_t        cmpsz;
        uint64_t        tocsz;
        char            ifile[NFILENAME + NEXTNAME];
        char            ofile[NFILENAME + NEXTNAME];

        strncpy(ifile, argv[2], NFILENAME);
        ifile[NFILENAME - 1] = '\0';
        
        strcat(ifile, dec_ext[decID]);
        uint32_t *cmp_addr = __open_and_mmap_file(ifile, cmpsz);

        strcat(ifile, TOCEXT);
        uint32_t *toc_addr = __open_and_mmap_file(ifile, tocsz);

        /* Initialize each size */
        uint64_t toclen = 0;
        uint64_t cmplenmax = cmpsz >> 2;
        uint64_t toclenmax = (tocsz - HEADERSZ * sizeof(uint32_t)) >> 2;

        __header_validate(toc_addr, toclen);

        /* If possible, setup a output file */
        FILE *dec = NULL;
        shared_ptr<FILE> __dec(static_cast<FILE *>(0), __deleter_fclose);

        if (argc > 3) {
                strncpy(ofile, argv[3], NFILENAME);
                ofile[NFILENAME - 1] = '\0';
                strcat(ofile, DECEXT);

                shared_ptr<FILE> __temp(
                        fopen(ofile, "w"), __deleter_fclose);
                dec = (__dec = __temp, __dec).get();

                setvbuf(dec, NULL, _IOFBF, BUFSIZ);
        }

        /*
         * FIXME: I think loops with mmap() is faster than that with
         * xxxread() on most linux platforms. True?
         */
        uint32_t numHeaders = toclenmax / EACH_HEADER_TOC_SZ;

        uint64_t dints = 0;
        uint64_t sum_sizes = 0;
        double dtime = 0.0;

        /* Start decoding */
        for (uint32_t j = 0; j < numHeaders; j++) {
                uint64_t        next_pos;

                /* Read the header of each list */
                uint32_t num = __next_read32(toc_addr, toclen);

                __assert(num < MAXLEN);

                uint32_t prev_doc = __next_read32(toc_addr, toclen);
                uint32_t cmp_pos = __next_read64(toc_addr, toclen);

                if (__likely(j != numHeaders - 1))
                        next_pos = __next_pos64(toc_addr, toclen);
                else
                        next_pos = cmplenmax;

                __assert(cmp_pos <= next_pos);
                __assert(next_pos - cmp_pos <= UINT32_MAX);

                /* FIXME: Need to remove a code below in the future */
                if (__unlikely(cmp_pos >= next_pos))
                        goto DECODING_END;

                uint32_t *ptr = cmp_addr + cmp_pos;

                if (decID == D_VSEREST ||
                                decID == D_VSEHYB) {
                        memcpy(sbuf, ptr, sizeof(uint32_t) *
                                        (next_pos - cmp_pos));
                        ptr = sbuf;
                }

                /* Do decoding */
                double tm = __get_time();
                (decoders[decID])(ptr, next_pos - cmp_pos, list, num - 1);
                dtime += __get_time() - tm;

                /* Accumulate each count */
                dints += num - 1;
                sum_sizes = cmp_pos;

                /* Write on the output file */
                if (dec != NULL) {
                        if (decID != D_BINARYIPL) {
                                fwrite(&num, 1, sizeof(uint32_t), dec);
                                fwrite(&prev_doc, 1, sizeof(uint32_t), dec);

                                for (uint32_t j = 0; j < num - 1; j++) {
                                        prev_doc += list[j] + 1;
                                        fwrite(&prev_doc, 1, sizeof(uint32_t), dec);
                                }
                        } else {
                                fwrite(&num, 1, sizeof(uint32_t), dec);
                                fwrite(&prev_doc, 1, sizeof(uint32_t), dec);
                                fwrite(&list, num - 1, sizeof(uint32_t), dec);
                        }
                }
        }
DECODING_END:

        cout << "Decoded ints: " << dints << endl;
        cout << "Time: " << dtime << " Secs" << endl;
        cout << "Performance: " << (dints + 0.0) / (dtime * 1000000) << " mis" << endl; 
        cout << "Size: " << (sum_sizes / 1024) * 4 << " KiB" << endl;
        cout << "Size: " << ((sum_sizes + 0.0) / (dints + 0.0)) * 32 << " bpi" << endl;

        return EXIT_SUCCESS;
}

/*--- Intra functions below ---*/

void
__usage(const char *msg, ...)
{
        if (msg != NULL) {
                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stderr, msg, vargs);
                va_end(vargs);

                cout << endl;
        }

        cout << "Usage: decoders <DecoderID> <infilename> <outfilename>" << endl;

        cout << endl << "DecoderID\tDecoderName" << endl;
        cout << "---" << endl;

        cout << "\t0\tN Gamma" << endl;
        cout << "\t1\tFU Gamma" << endl;
        cout << "\t2\tF Gamma" << endl;
        cout << "\t3\tN Delta" << endl;
        cout << "\t4\tFU Delta" << endl;
        cout << "\t5\tFG Delta" << endl;
        cout << "\t6\tF Delta" << endl;
        cout << "\t7\tVariable Byte" << endl;
        cout << "\t8\tBinary Interpolative" << endl;
        cout << "\t9\tSimple 9" << endl;
        cout << "\t10\tSimple 16" << endl;
        cout << "\t11\tPForDelta" << endl; 
        cout << "\t12\tOPTPForDelta" << endl; 
        cout << "\t13\tVSEncodingBlocks" << endl;
        cout << "\t14\tVSE-R" << endl;
        cout << "\t15\tVSEncodingRest" << endl;
        cout << "\t16\tVSEncodingBlocksHybrid" << endl;
        cout << "\t17\tVSEncodingSimple V1" << endl;
        cout << "\t18\tVSEncodingSimple V2" << endl << endl;

        exit(1);
}

