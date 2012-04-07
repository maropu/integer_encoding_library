/*-----------------------------------------------------------------------------
 *  benchmarks.hpp - A header for encoders.cpp/decoders.cpp
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

#ifndef __BENCHMARKS__
#define __BENCHMARKS__

/* Magic numbers */
#define MAGIC_NUM       0x0f823cb4
#define VMAJOR          0
#define VMINOR          2

/* Configurable parameters */
#define SKIP            32

/* A extension for a location file */
#define TOCEXT          ".TOC"
#define DECEXT          ".DEC"
#define NFILENAME       256
#define NEXTNAME        32

/* A macro for header accesses */
#define HEADERSZ                9
#define EACH_HEADER_TOC_SZ      4

/* Macros for reading 32/64bit data on memory */
#define __do_read32(addr, len)  addr[len];
#define __do_read64(addr, len)  \
        ({      \
                uint64_t        ret;    \
\
                ret = addr[len + 1];    \
                ret = (ret << 32) | addr[len];  \
\
                ret;    \
         })

/*
 * Macros for reading files. A header for each compressed list
 * is composed of three etnries: the total of integers, a first
 * integer, and the next posision of a list.
 *
 * NOTICE: We assume that the size of each entry is 4B, and 
 * the alignment follows little-endian.
 */
#define __next_read32(addr, len)        \
        ({      \
                uint32_t        ret;    \
\
                ret = __do_read32(addr, len);   \
                len += 1;       \
                ret;            \
         })

#define __next_read64(addr, len)        \
        ({      \
                uint64_t        ret;    \
\
                ret = __do_read64(addr, len);   \
                len += 2;       \
                ret;            \
         })

#define __next_pos64(addr, len)         \
        ({      \
                uint64_t        nxlen;  \
\
                nxlen = len + EACH_HEADER_TOC_SZ - 2;   \
                __do_read64(addr, nxlen);               \
         })

/* A macro for header stuffs */
#define __header_validate(addr, len)    \
        do {                            \
                uint32_t        magic;  \
                uint32_t        vmajor; \
                uint32_t        vminor; \
\
                magic = __do_read32(addr, 0);   \
                vmajor = __do_read32(addr, 1);  \
                vminor = __do_read32(addr, 2);  \
\
                if (magic != MAGIC_NUM ||               \
                        vmajor != VMAJOR || vminor != VMINOR)   \
                        eoutput("Not support input format");    \
\
                len += HEADERSZ;        \
        } while (0);


#if HAVE_DECL_POSIX_FADVISE && defined(HAVE_POSIX_FADVISE)
 #define __fadvise_sequential(fd, len)   \
        posix_fadvise(fd, 0, len, POSIX_FADV_SEQUENTIAL)
#else
 #define __fadvise_sequential(fd, len)
#endif

/* Extensions for encoders */
const char *enc_ext[] = {
        ".Gamma",
        ".Delta",
        ".VariableByte",
        ".Interpolative",
        ".Simple9",
        ".Simple16",
        ".P4D",
        ".OPT4D",
        ".VSE",
        ".VSERT",
        ".VSERest",
        ".VSEH",
        ".VSESimpleV1",
        ".VSESimpleV2"
};

/* Extensions for decoders */
const char *dec_ext[] = {
        ".Gamma",
        ".Gamma",
        ".Gamma",
        ".Delta",
        ".Delta",
        ".Delta",
        ".Delta",
        ".VariableByte",
        ".Interpolative",
        ".Simple9",
        ".Simple16",
        ".P4D",
        ".OPT4D",
        ".VSE",
        ".VSERT",
        ".VSERest",
        ".VSEH",
        ".VSESimpleV1",
        ".VSESimpleV2"
};

/* Utility inline functions below */
inline static double
__get_time(void)
{
        struct rusage   usage;

        getrusage (RUSAGE_SELF, &usage);

        double utime = (double)usage.ru_utime.tv_sec +
                (double)usage.ru_utime.tv_usec / 1000000.0;

        double stime = (double)usage.ru_stime.tv_sec +
                (double)usage.ru_stime.tv_usec / 1000000.0;

        return (utime + stime);
}

inline static uint64_t
__get_file_size(FILE *fp)
{
        fpos_t  old;
        fpos_t  size;

        fgetpos(fp, &old);

        fseek(fp, 0, SEEK_END);
        fgetpos(fp, &size);

        fsetpos(fp, &old);

        return static_cast<uint64_t>(size.__pos);
}

/* Some deleter functions */
static void __deleter_close(int *fd) {close(*fd);}
static void __deleter_fclose(FILE *fd) {fclose(fd);}

inline static uint32_t *
__open_and_mmap_file(
                char *filen, uint64_t &len) {
        struct stat     sb;

        int file = open(filen, O_RDONLY);
        if (file == -1)
                eoutput("Can't open a input file");

        shared_ptr<int> __file(&file, __deleter_close);

        /* Do mmap() for file */
        int ret = fstat(file, &sb);
        if (ret == -1 || sb.st_size == 0)
                eoutput("fstat(): Unknown the file size");

        len = sb.st_size;

#if __i368__
        if (len > UINT32_MAX)
                eoutput("Unsupport more than 4GiB files on 32-bit platforms");
#endif 

        __fadvise_sequential(file, len);

        uint32_t *addr = (uint32_t *)mmap(
                        NULL, len, PROT_READ, MAP_PRIVATE, file, 0);
        if (addr == MAP_FAILED)
                eoutput("mmap(): Can't map the file to memory");

        return addr;
}

#endif  /* __BENCHMARKS__ */

