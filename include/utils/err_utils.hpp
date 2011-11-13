/*-----------------------------------------------------------------------------
 *  err_utils.hpp - A header for err_utiils.c
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

#ifndef ERR_UTILS_HPP
#define ERR_UTILS_HPP

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <assert.h>
#include <errno.h>

#define FILE_OUTPUT             0
#define CONSOLE_OUTPUT          1

#define eoutput(fmt, ...)               \
        do {                            \
                err_utils::flush_log(); \
                err_utils::err_print(__func__, __LINE__, fmt, ##__VA_ARGS__);   \
        } while (0)

#ifdef DEBUG
/* Shortcuts for debug-prints */
 #define doutput(flag, fmt, ...)                \
        do {                                    \
                if ((flag) == FILE_OUTPUT) {    \
                        err_utils::push_log(__func__, __LINE__, fmt, ##__VA_ARGS__);    \
                } else if ((flag) == CONSOLE_OUTPUT) {                          \
                        fprintf(stderr, "%s(%d): ", __func__, __LINE__);        \
                        fprintf(stderr, fmt, ##__VA_ARGS__);                    \
                        fprintf(stderr, "\n");                                  \
                }               \
        } while (0)
#else
 #define doutput(flag, fmt, ...)
#endif /* DEBUG */

#ifdef DEBUG
 #define assert_debug(cond)     assert(cond)
#else
 #define assert_debug(cond)
#endif /* DEBUG */

class err_utils {
        public:
        /* Logging functions */
        static void push_log(const char *func, int32_t line, const char *fmt, ...)
                __attribute__ ((format (printf, 3, 4))); 
        static void flush_log(void);

        /* Error functions */
        static void err_print(const char *func, int32_t line, const char *fmt, ...)
                __attribute__ ((format (printf, 3, 4))); 
};

#endif  /* ERR_UTILS_HPP */
