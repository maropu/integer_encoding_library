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
                magic = __next_read(addr, len);         \
                vmajor = __next_read(addr, len);        \
                vminor = __next_read(addr, len);        \
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
        uint32_t        i;
        uint32_t        j;
        uint32_t        *list;
        uint32_t        *cmp_addr;
        uint32_t        *toc_addr;
        uint32_t        sum_sizes;
        uint64_t        dints;
        uint64_t        cmpsz;
        uint64_t        tocsz;
        uint64_t        toclen;
        uint64_t        lenmax;
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
        if (decID != D_BINARYIPL)
                cmp_addr = int_utils::open_and_mmap_file(ifile, false, cmpsz);
        else
                cmp_addr = int_utils::open_and_mmap_file(ifile, true, cmpsz);

        strcat(ifile, TOCEXT);
        toc_addr = int_utils::open_and_mmap_file(ifile, false, tocsz);

        lenmax = tocsz >> 2;
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

        /* Counters initialized */
        dtime = 0.0;
        dints = 0;
        sum_sizes = 0;

        for (i = 0, ip = toclen; i < NLOOP; i++, toclen = ip) {
                uint32_t        num;
                uint32_t        prev_doc;
                uint32_t        cmp_pos;
                uint32_t        next_pos;
                double          tm;

                while (toclen < lenmax) {
                        /* Read the header of each list */
                        num = __next_read(toc_addr, toclen);

                        assert_debug(num < MAXLEN);

                        prev_doc = __next_read(toc_addr, toclen);
                        cmp_pos = __next_read(toc_addr, toclen);

                        next_pos = (toclen + NUM_EACH_HEADER_TOC - 1 < lenmax)?
                                __next_pos(toc_addr, toclen) : lenmax;

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

                                        for (j = 0; j < num - 1; j++) {
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

        cout << "Decoded ints: " << dints << endl;
        cout << "Time: " << dtime << " Secs" << endl;
        cout << "Performance: " << (dints + 0.0) / (dtime * 1000000) << " mis" << endl; 
        cout << "Size: " << ((sum_sizes * NLOOP * 4) / 1024) << " KiB" << endl;
        cout << "Size: " << ((sum_sizes * NLOOP) + 0.0) / (dints + 0.0) * 32 << " bpi" << endl;

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
