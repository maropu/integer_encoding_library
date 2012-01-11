/*-----------------------------------------------------------------------------
 *  decoders.cpp - Decoders de-compressing correspinding encorded integers.
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

#include "decoders.hpp"

using namespace std;

#define NLOOP   1

#define __header_validate(addr, len)    \
        do {                            \
                uint32_t        magic;  \
                uint32_t        vmajor; \
                uint32_t        vminor; \
\
                magic = __next_read32(addr, len);       \
                vmajor = __next_read32(addr, len);      \
                vminor = __next_read32(addr, len);      \
\
                if (magic != MAGIC_NUM ||               \
                        vmajor != VMAJOR || vminor != VMINOR)   \
                        eoutput("Not support input format");    \
        } while (0);

static void __usage(const char *msg, ...);

int 
main(int argc, char **argv)
{
        int             decID;
        uint32_t        *list;
        uint32_t        *cmp_addr;
        uint32_t        *toc_addr;
        uint64_t        sum_sizes;
        uint64_t        dints;
        uint64_t        cmpsz;
        uint64_t        cmplenmax;
        uint64_t        tocsz;
        uint64_t        toclen;
        uint64_t        toclenmax;
        uint64_t        ip;
        char            *end;
        char            ifile[NFILENAME + NEXTNAME];
        char            ofile[NFILENAME + NEXTNAME];
        double          dtime;
        FILE            *dec;

        if (argc < 3)
                __usage(NULL);

        list = new uint32_t[MAXLEN + TAIL_MERGIN];

        if (list == NULL)
                eoutput("Can't allocate memory");

        decID = strtol(argv[1], &end, 10);
        if ((*end != '\0') || (decID < 0) ||
                        (decID >= NUMDECODERS) || (errno == ERANGE))
                __usage("DecoderID '%s' invalid", argv[1]);

        /* Read the file name, and open it */
        strncpy(ifile, argv[2], NFILENAME);
        ifile[NFILENAME - 1] = '\0';
        
        strcat(ifile, dec_ext[decID]);
        if (decID == D_VSEREST || decID == D_VSEHYB)
                cmp_addr = int_utils::open_and_mmap_file(ifile, true, cmpsz);
        else
                cmp_addr = int_utils::open_and_mmap_file(ifile, false, cmpsz);

        strcat(ifile, TOCEXT);
        toc_addr = int_utils::open_and_mmap_file(ifile, false, tocsz);

        /* Initialize each size */
        cmplenmax = cmpsz >> 2;
        toclenmax = tocsz >> 2;
        toclen = 0;

        __header_validate(toc_addr, toclen);

        /* If possible, setup a output file */
        dec = NULL;

        if (argc > 3) {
                strncpy(ofile, argv[3], NFILENAME);
                ofile[NFILENAME - 1] = '\0';

                strcat(ofile, DECEXT);
                dec = fopen(ofile, "w");

                if (dec == NULL)
                        eoutput("foepn(): Can't create a output file");

                setvbuf(dec, NULL, _IOFBF, BUFSIZ);
        }

        /*
         * FIXME: I think loops with mmap() is faster than that with
         * xxxread() on most linux platforms. True?
         */
        uint32_t        nloop;
        uint32_t        numHeaders;

        /* Counters initialized */
        dtime = 0.0;
        dints = 0;
        sum_sizes = 0;

        nloop = 0;
        numHeaders = toclenmax / EACH_HEADER_TOC_SZ;

        /* Store a initial position */
        ip = toclen;

        for (uint32_t i = 0; i < NLOOP; i++, toclen = ip) {
                uint32_t        num;
                uint32_t        prev_doc;
                uint64_t        cmp_pos;
                uint64_t        next_pos;
                double          tm;

                nloop++;

                for (uint32_t j = 0; j < numHeaders; j++) {
                        /* Read the header of each list */
                        num = __next_read32(toc_addr, toclen);

                        __assert(num < MAXLEN);

                        prev_doc = __next_read32(toc_addr, toclen);
                        cmp_pos = __next_read64(toc_addr, toclen);

                        if (__likely(j != numHeaders - 1))
                                next_pos = __next_pos64(toc_addr, toclen);
                        else
                                next_pos = cmplenmax;

                        __assert(cmp_pos <= next_pos);
                        __assert(next_pos - cmp_pos <= UINT32_MAX);

                        /* FIXME: Need to remove a code below in the future */
                        if (__unlikely(cmp_pos >= next_pos))
                                goto LOOP_END;

                        /* Do decoding */
                        tm = int_utils::get_time();
                        (decoders[decID])(cmp_addr + cmp_pos, next_pos - cmp_pos, list, num - 1);

                        /* Accumulate each count */
                        dtime += int_utils::get_time() - tm;
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
        }
LOOP_END:

        cout << "Decoded ints: " << dints << endl;
        cout << "Time: " << dtime << " Secs" << endl;
        cout << "Performance: " << (dints + 0.0) / (dtime * 1000000) << " mis" << endl; 
        cout << "Size: " << (sum_sizes * nloop / 1024) * 4 << " KiB" << endl;
        cout << "Size: " << ((sum_sizes * nloop + 0.0) / (dints + 0.0)) * 32 << " bpi" << endl;

        /* Finalization */
        int_utils::close_file(cmp_addr, cmpsz);
        int_utils::close_file(toc_addr, tocsz);

        if (dec != NULL)
                fclose(dec);

        delete[] list;

        return EXIT_SUCCESS;
}

/*--- Intra functions below ---*/

void
__usage(const char *msg, ...)
{
        cout << "Usage: decoders <DecoderID> <infilename> <outfilename>" << endl;

        if (msg != NULL) {
                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stderr, msg, vargs);
                va_end(vargs);

                cout << endl;
        }

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
        cout << "\t17\tVSEncodingSimple v1" << endl;
        cout << "\t18\tVSEncodingSimple v2" << endl << endl;

        exit(1);
}
