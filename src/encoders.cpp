/*-----------------------------------------------------------------------------
 *  encoders.cpp - Encoders implementing many types of copression algorithms
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

/* A macro for header stuffs */
#define __header_written(out)   \
        do {                    \
                uint32_t        magic;  \
                uint32_t        vmajor; \
                uint32_t        vminor; \
                uint32_t        rs_num; \
                uint32_t        rs_pos; \
                uint64_t        rs_len; \
                uint64_t        rs_lenmax;      \
\
                magic = MAGIC_NUM;      \
                vmajor = VMAJOR;        \
                vminor = VMINOR;        \
\
                rs_num = 0;     \
                rs_pos = 0;     \
                rs_len = 0;     \
                rs_lenmax = UINT64_MAX; \
\
                fwrite(&magic, sizeof(uint32_t), 1, out);       \
                fwrite(&vmajor, sizeof(uint32_t), 1, out);      \
                fwrite(&vminor, sizeof(uint32_t), 1, out);      \
\
                fwrite(&rs_num, sizeof(uint32_t), 1, out);      \
                fwrite(&rs_pos, sizeof(uint32_t), 1, out);      \
                fwrite(&rs_len, sizeof(uint64_t), 1, out);      \
                fwrite(&rs_lenmax, sizeof(uint64_t), 1, out);   \
\
                fsync(fileno(out));     \
        } while (0)

/* Macros for resume stuffs */
#define RESUME_INFO_BASE        3
#define CHECKPOINT_INTVL        1000000       

#define __get_resume_num(addr)          __do_read32(addr, RESUME_INFO_BASE)
#define __get_resume_pos(addr)          __do_read32(addr, RESUME_INFO_BASE + 1)
#define __get_resume_len(addr)          __do_read64(addr, RESUME_INFO_BASE + 2)
#define __get_resume_lenmax(addr)       __do_read64(addr, RESUME_INFO_BASE + 4)

#define __set_resume_info(num, pos, len, lenmax, fp)    \
        ({                              \
                fpos_t  old;            \
\
                fgetpos(fp, &old);      \
\
                fseek(fp, RESUME_INFO_BASE *                    \
                        sizeof(uint32_t), SEEK_SET);            \
                fwrite(&num, sizeof(uint32_t), 1, fp);          \
                fwrite(&pos, sizeof(uint32_t), 1, fp);          \
                fwrite(&len, sizeof(uint64_t), 1, fp);          \
                fwrite(&lenmax, sizeof(uint64_t), 1, fp);       \
\
                fsetpos(fp, &old);      \
         })

#define __periodical_checkpoint(it, toc, cmp_pos, cmp, len, lenmax)     \
        ({      \
                if (it % CHECKPOINT_INTVL == 0) {       \
                        __set_resume_info(it, cmp_pos, len, lenmax, toc);       \
                        fsync(fileno(cmp));     \
                        fsync(fileno(toc));     \
                }       \
         })

/* A macro for a progress indicator */
#define PROG_PER_COUNT  1000000

static double   __progress_start_time;
static int      __init_progress;

#define __show_progress(str, it, c, n)  \
        ({                      \
                double  pg;     \
                double  left;   \
\
                if (!__init_progress++)         \
                        __progress_start_time = __get_time();   \
\
                if ((c) != 0 && (it) % ((n) / PROG_PER_COUNT) == 0) {   \
                        pg = static_cast<double>(c) / (n);              \
                        left = ((1.0 - pg) / pg) *                      \
                                (__get_time() - __progress_start_time); \
\
                        fprintf(stderr,                         \
                                "%s: %.3lf done, %.1lfs left    \
                                                        \r",    \
                                str, pg, left);                 \
                }       \
         })

static void __usage(const char *msg, ...);

int 
main(int argc, char **argv)
{
        char            *end;

        if (argc < 3)
                __usage(NULL);

        shared_ptr<uint32_t> __list(
                new uint32_t[MAXLEN], default_delete<uint32_t[]>());

        uint32_t *list = __list.get();

        shared_ptr<uint32_t> __cmp_array(
                new uint32_t[MAXLEN], default_delete<uint32_t[]>());

        uint32_t *cmp_array = __cmp_array.get();

        /* Process input options */
        int     ret;

        bool show_progress = false;
        bool try_resume = false;
        double file_ratio = 1.0;

        while ((ret = getopt(argc, argv, "rip:")) != -1) {
                switch (ret) {
                case 'r':
                        try_resume = true;
                        break;

                case 'i':
                        show_progress = true;
                        break;

                case 'p':
                        file_ratio = strtod(optarg, &end);
                        if (file_ratio < 0.0 || 1.0 < file_ratio)
                                __usage("-p needs to be between 0.0 and 1.0", argv[1]);
                        break;

                case '?':
                        break;

                }
        }

        /* Read EncoderID */
        int encID = strtol(argv[optind++], &end, 10);
        if ((*end != '\0') || (encID < 0) ||
                        (encID >= NUMENCODERS) ||(errno == ERANGE))
                __usage("EncoderID '%s' invalid", argv[1]);

        /* Open a output file and tune buffer mode */
        char            ifile[NFILENAME];
        char            ofile[NFILENAME + NEXTNAME];

        strncpy(ifile, argv[optind++], NFILENAME);
        ifile[NFILENAME - 1] = '\0';

        strncpy(ofile, ifile, NFILENAME);
        strcat(ofile, enc_ext[encID]);

        FILE *cmp = fopen(ofile, (try_resume == 0)? "w" : "r+");
        if (cmp == NULL)
                eoutput("foepn(): Can't open output files");

        strcat(ofile, TOCEXT);
        FILE *toc = fopen(ofile, (try_resume == 0)? "w" : "r+");

        if (toc == NULL)
                eoutput("foepn(): Can't open output files");

        setvbuf(cmp, NULL, _IOFBF, BUFSIZ);
        setvbuf(toc, NULL, _IOFBF, BUFSIZ);

        /* Try to resume path first */
        uint32_t it = 0;
        uint64_t len = 0;
        uint64_t rlen = 0;
        uint64_t lenmax = 0;
        uint64_t cmp_pos = 0;

        if (try_resume) {
                uint32_t        hbuf[HEADERSZ];

                uint64_t tlen = 0;

                if (fread(hbuf, sizeof(uint32_t),
                                HEADERSZ, toc) == HEADERSZ) {
                        __header_validate(hbuf, tlen);

                        it = __get_resume_num(hbuf);
                        cmp_pos = __get_resume_pos(hbuf);

                        /*
                         * A resumed posision is stored in rlen
                         * for __show_progress().
                         */
                        rlen = (len = __get_resume_len(hbuf));
                        lenmax = __get_resume_lenmax(hbuf);

                        __assert(len <= lenmax);

                        uint64_t pos1 = cmp_pos * sizeof(uint32_t);
                        uint64_t pos2 = (HEADERSZ +
                                it * EACH_HEADER_TOC_SZ) * sizeof(uint32_t);

                        if (__get_file_size(cmp) < pos1 ||
                                        __get_file_size(toc) < pos2)
                                goto NORESUME;

                        /* Locate resumed positions */
                        fseek(cmp, pos1, SEEK_SET);
                        fseek(toc, pos2, SEEK_SET);

                        /*
                         * Reset file_ratio so that it follows
                         * the previous lenmax.
                         */
                        file_ratio = 1.0;

                        goto RESUME;
                }
NORESUME:
                fseek(toc, 0, SEEK_SET);
        }

        /* First off, a header is written */
        __header_written(toc);

RESUME:
        /*
         * FIXME: I think loops with mmap() is faster than that with
         * xxxread() on most linux platforms. True?
         */
        uint64_t        fsz;

        uint32_t *addr = __open_and_mmap_file(ifile, fsz);

        /* Decide which part of the input is compressed */
        lenmax = fsz >> 2;
        lenmax *= file_ratio;

        {
                uint32_t        prev_doc;
                uint32_t        cur_doc;
                uint32_t        cmp_size;
                uint32_t        num;

                while (len < lenmax) {
                        if (show_progress)
                                __show_progress("Encoded", it++, len, lenmax - rlen);

                        /* Read the numer of integers in a list */
                        num = __next_read32(addr, len);

                        if (len + num > lenmax)
                                goto LOOP_END;

                        /* Read the head of a list */
                        prev_doc = __next_read32(addr, len);

                        if (num > SKIP && num < MAXLEN) {
                                /*
                                 * For any list, TOC will contain:
                                 *      (number of elements, first elements, pointer to the compressed list)
                                 */
                                fwrite(&num, 1, sizeof(uint32_t), toc);
                                fwrite(&prev_doc, 1, sizeof(uint32_t), toc);
                                fwrite(&cmp_pos, 1, sizeof(uint64_t), toc);

                                for (uint32_t j = 0; j < num - 1; j++) {
                                        cur_doc = __next_read32(addr, len);

                                        if (cur_doc < prev_doc)
                                                cerr << "List ordering exception: list MUST be increasing" << endl;

                                        if (encID != E_BINARYIPL)
                                                list[j] = cur_doc - prev_doc - 1;
                                        else
                                                list[j] = cur_doc;

                                        prev_doc = cur_doc;
                                }

                                /* Do encoding */
                                (encoders[encID])(list, num - 1, cmp_array, cmp_size);

                                fwrite(cmp_array, sizeof(uint32_t), cmp_size, cmp);
                                cmp_pos += cmp_size;
                        } else {
                                /* Read skipped data */
                                for (uint32_t j = 0; j < num - 1; j++)
                                        cur_doc = __next_read32(addr, len);
                        }

                        __periodical_checkpoint(
                                        it, toc, cmp_pos, cmp, len, lenmax);
                }
        }
LOOP_END:

        /* Finalization */
        __close_file(addr, fsz);

        fclose(cmp);
        fclose(toc);

        return EXIT_SUCCESS;
}

/*--- Intra functions below ---*/

void
__usage(const char *msg, ...)
{
        if (msg != NULL) {
                cout << "Error: ";

                va_list vargs;

                va_start(vargs, msg);
                vfprintf(stdout, msg, vargs);
                va_end(vargs);

                cout << endl << endl;
        }

        cout << "Usage: encoders [Options] <EncoderID> <infilename>" << endl;
        cout << "Options" << endl;
        cout << "     -i: Show a progress indicator" << endl;
        cout << "     -r: Try to resume if a broken encoded file exists" << endl;
        cout << "     -p [0.0-1.0]: File ratio to compress (default:1.0)" << endl;

        cout << endl << "EncoderID\tEncoderName" << endl;
        cout << "---" << endl;

        cout << "\t0\tGamma" << endl;
        cout << "\t1\tDelta" << endl;
        cout << "\t2\tVariable Byte" << endl;
        cout << "\t3\tBinary Interpolative" << endl;
        cout << "\t4\tSimple 9" << endl;
        cout << "\t5\tSimple 16" << endl;
        cout << "\t6\tPForDelta" << endl; 
        cout << "\t7\tOPTPForDelta" << endl; 
        cout << "\t8\tVSEncodingBlocks" << endl;
        cout << "\t9\tVSE-R" << endl;
        cout << "\t10\tVSEncodingRest" << endl;
        cout << "\t11\tVSEncodingBlocksHybrid" << endl;
        cout << "\t12\tVSEncodingSimple V1" << endl;
        cout << "\t13\tVSEncodingSimple V2" << endl << endl;

        exit(1);
}

