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

/* A macro for header accesses */
#define HEADERSZ        9

/* Configurable parameters */
#define SKIP            32

/* A extension for a location file */
#define TOCEXT          ".TOC"
#define DECEXT          ".DEC"
#define NFILENAME       256
#define NEXTNAME        32

/*
 * FIXME: Some encoders might overrun the length of given
 * memory. This makes a code simple but unobvious, so we
 * need to remove it.
 */
#define TAIL_MERGIN     128

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

#define RESUME_INFO_BASE        3

#define GET_RESUME_NUM(addr)    __do_read32(addr, RESUME_INFO_BASE)
#define GET_RESUME_POS(addr)    __do_read32(addr, RESUME_INFO_BASE + 1)
#define GET_RESUME_LEN(addr)    __do_read64(addr, RESUME_INFO_BASE + 2)
#define GET_RESUME_LENMAX(addr) __do_read64(addr, RESUME_INFO_BASE + 4)

/*
 * FIXME: Need to support for more than 4GiB files
 * on 32-bit platforms.
 */
#define SET_RESUME_INFO(num, pos, len, lenmax, fp)      \
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

/*
 * Macros for reading files. A header for each compressed list
 * is composed of three etnries: the total of integers, a first
 * integer, and the next posision of a list.
 *
 * NOTICE: We assume that the size of each entry is 4B, and 
 * the alignment follows little-endian.
 */
#define EACH_HEADER_TOC_SZ      4

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
inline double
__get_time(void)
{
        double  utime;
        double  stime;
        struct rusage   usage;

        getrusage (RUSAGE_SELF, &usage);

        utime = (double)usage.ru_utime.tv_sec +
                (double)usage.ru_utime.tv_usec / 1000000.0;

        stime = (double)usage.ru_stime.tv_sec +
                (double)usage.ru_stime.tv_usec / 1000000.0;

        return (utime + stime);
}

inline uint64_t
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

inline uint32_t *
__open_and_mmap_file(
                char *filen, uint64_t &len) {
        int             file;
        int             ret;
        uint32_t        *addr;
        struct stat     sb;

        file = open(filen, O_RDONLY);
        if (file == -1)
                eoutput("oepn(): Can't open the file");

        /* Do mmap() for file */
        ret = fstat(file, &sb);
        if (ret == -1 || sb.st_size == 0)
                eoutput("fstat(): Unknown the file size");

        len = sb.st_size;

#if __i368__
        if (len > UINT32_MAX)
                eoutput("Unsupport more than 4GiB files on 32-bit platforms");
#endif 

        __fadvise_sequential(file, len);

        addr = (uint32_t *)mmap(NULL, len, PROT_READ, MAP_PRIVATE, file, 0);

        if (addr == MAP_FAILED)
                eoutput("mmap(): Can't map the file to memory");

        close(file);

        return addr;
}

inline void
__close_file(uint32_t *adr, uint64_t len)
{
        munmap(adr, len);
}

#endif  /* __BENCHMARKS__ */

