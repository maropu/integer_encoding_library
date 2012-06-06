/*-----------------------------------------------------------------------------
 *  Simple9.cpp - A implementation of Simple9
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

#include "compress/policy/Simple9.hpp"

using namespace integer_coding::compressor;
using namespace integer_coding::utility;

#define SIMPLE9_DESC_FUNC(num, log)     \
        static bool                     \
        try##num##_##log##bit(uint32_t *n, uint32_t len)        \
        {                                       \
                uint32_t        i;              \
                uint32_t        min;            \
\
                min = (len < num)? len : num;   \
\
                for (i = 0; i < min; i++) {     \
                        if (__get_msb(n[i]) > log - 1)  \
                                return false;   \
                }               \
\
                return true;    \
        }

/* Fuction difinition by macros */
SIMPLE9_DESC_FUNC(28, 1);
SIMPLE9_DESC_FUNC(14, 2);
SIMPLE9_DESC_FUNC(9, 3);
SIMPLE9_DESC_FUNC(7, 4);
SIMPLE9_DESC_FUNC(5, 5);
SIMPLE9_DESC_FUNC(4, 7);
SIMPLE9_DESC_FUNC(3, 9);
SIMPLE9_DESC_FUNC(2, 14);

/* A set of unpacking functions */
static inline void __simple9_unpack1_28(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack2_14(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack3_9(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack4_7(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack5_5(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack7_4(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack9_3(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack14_2(uint32_t **out, uint32_t **in);
static inline void __simple9_unpack28_1(uint32_t **out, uint32_t **in);

/* A interface of unpacking functions above */
typedef void (*__simple9_unpacker)(uint32_t **out, uint32_t **in);

static __simple9_unpacker       __simple9_unpack[SIMPLE9_LEN] = {
        __simple9_unpack1_28, __simple9_unpack2_14,
        __simple9_unpack3_9, __simple9_unpack4_7,
        __simple9_unpack5_5, __simple9_unpack7_4,
        __simple9_unpack9_3, __simple9_unpack14_2,
        __simple9_unpack28_1, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL
};

void
Simple9::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        uint32_t        min;
        BitsWriter      wt(out);

        while (len > 0) {
                if (try28_1bit(in, len)) {
                        /* Descripter Number: 0 */
                        wt.bit_writer(0, 4);

                        min = (len < 28)? len : 28;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 1);
                } else if (try14_2bit(in, len)) {
                        /* Descripter Number: 1 */
                        wt.bit_writer(1, 4);

                        min = (len < 14)? len : 14;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 2);
                } else if (try9_3bit(in, len)) {
                        /* Descripter Number: 2 */
                        wt.bit_writer(2, 4);

                        min = (len < 9)? len : 9;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 3);
                } else if (try7_4bit(in, len)) {
                        /* Descripter Number: 3 */
                        wt.bit_writer(3, 4);

                        min = (len < 7)? len : 7;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 4);
                } else if (try5_5bit(in, len)) {
                        /* Descripter Number: 4 */
                        wt.bit_writer(4, 4);

                        min = (len < 5)? len : 5;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 5);
                } else if (try4_7bit(in, len)) {
                        /* Descripter Number: 5 */
                        wt.bit_writer(5, 4);

                        min = (len < 4)? len : 4;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 7);
                } else if (try3_9bit(in, len)) {
                        /* Descripter Number: 6 */
                        wt.bit_writer(6, 4);

                        min = (len < 3)? len : 3;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 9);
                } else if (try2_14bit(in, len)) {
                        /* Descripter Number: 7 */
                        wt.bit_writer(7, 4);

                        min = (len < 2)? len : 2;
                        for (uint32_t i = 0; i < min; i++)
                                wt.bit_writer(*in++, 14);
                } else {
                        if ((*in >> 28) > 0)
                                eoutput("Input's out of range: %u", *in);

                        /* Descripter Number: 8 */
                        wt.bit_writer(8, 4);

                        min = 1;
                        wt.bit_writer(*in++, 28);
                }

                /* Align to 32-bit */
                wt.bit_flush();

                len -= min;
        }

        nvalue = wt.get_written();
}

void
Simple9::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue) const
{
        if (in == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: in");

        if (out == NULL)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: out");

        if (len == 0 || len > MAXLEN)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: len");

        if (nvalue == 0)
                THROW_COMPRESSOR_EXCEPTION("Invalid input: nvalue");

        uint32_t *end = out + nvalue;

        while (end > out) {
                (__simple9_unpack[*in >>
                 (32 - SIMPLE9_LOGDESC)])(&out, &in);
        }
}

/* --- Intra functions below --- */

void
__simple9_unpack1_28(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 27) & 0x01;
        pout[1] = (pin[0] >> 26) & 0x01;
        pout[2] = (pin[0] >> 25) & 0x01;
        pout[3] = (pin[0] >> 24) & 0x01;
        pout[4] = (pin[0] >> 23) & 0x01;
        pout[5] = (pin[0] >> 22) & 0x01;
        pout[6] = (pin[0] >> 21) & 0x01;
        pout[7] = (pin[0] >> 20) & 0x01;
        pout[8] = (pin[0] >> 19) & 0x01;
        pout[9] = (pin[0] >> 18) & 0x01;
        pout[10] = (pin[0] >> 17) & 0x01;
        pout[11] = (pin[0] >> 16) & 0x01;
        pout[12] = (pin[0] >> 15) & 0x01;
        pout[13] = (pin[0] >> 14) & 0x01;
        pout[14] = (pin[0] >> 13) & 0x01;
        pout[15] = (pin[0] >> 12) & 0x01;
        pout[16] = (pin[0] >> 11) & 0x01;
        pout[17] = (pin[0] >> 10) & 0x01;
        pout[18] = (pin[0] >> 9) & 0x01;
        pout[19] = (pin[0] >> 8) & 0x01;
        pout[20] = (pin[0] >> 7) & 0x01;
        pout[21] = (pin[0] >> 6) & 0x01;
        pout[22] = (pin[0] >> 5) & 0x01;
        pout[23] = (pin[0] >> 4) & 0x01;
        pout[24] = (pin[0] >> 3) & 0x01;
        pout[25] = (pin[0] >> 2) & 0x01;
        pout[26] = (pin[0] >> 1) & 0x01;
        pout[27] = pin[0] & 0x01;

        *in = pin + 1;
        *out = pout + 28;
}

void
__simple9_unpack2_14(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 26) & 0x03;
        pout[1] = (pin[0] >> 24) & 0x03;
        pout[2] = (pin[0] >> 22) & 0x03;
        pout[3] = (pin[0] >> 20) & 0x03;
        pout[4] = (pin[0] >> 18) & 0x03;
        pout[5] = (pin[0] >> 16) & 0x03;
        pout[6] = (pin[0] >> 14) & 0x03;
        pout[7] = (pin[0] >> 12) & 0x03;
        pout[8] = (pin[0] >> 10) & 0x03;
        pout[9] = (pin[0] >> 8) & 0x03;
        pout[10] = (pin[0] >> 6) & 0x03;
        pout[11] = (pin[0] >> 4) & 0x03;
        pout[12] = (pin[0] >> 2) & 0x03;
        pout[13] = pin[0] & 0x03;

        *in = pin + 1;
        *out = pout + 14;
}

void
__simple9_unpack3_9(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 25) & 0x07;
        pout[1] = (pin[0] >> 22) & 0x07;
        pout[2] = (pin[0] >> 19) & 0x07;
        pout[3] = (pin[0] >> 16) & 0x07;
        pout[4] = (pin[0] >> 13) & 0x07;
        pout[5] = (pin[0] >> 10) & 0x07;
        pout[6] = (pin[0] >> 7) & 0x07;
        pout[7] = (pin[0] >> 4) & 0x07;
        pout[8] = (pin[0] >> 1) & 0x07;

        *in = pin + 1;
        *out = pout + 9;
}

void
__simple9_unpack4_7(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 24) & 0x0f;
        pout[1] = (pin[0] >> 20) & 0x0f;
        pout[2] = (pin[0] >> 16) & 0x0f;
        pout[3] = (pin[0] >> 12) & 0x0f;
        pout[4] = (pin[0] >> 8) & 0x0f;
        pout[5] = (pin[0] >> 4) & 0x0f;
        pout[6] = pin[0] & 0x0f;

        *in = pin + 1;
        *out = pout + 7;
}

void
__simple9_unpack5_5(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 23) & 0x1f;
        pout[1] = (pin[0] >> 18) & 0x1f;
        pout[2] = (pin[0] >> 13) & 0x1f;
        pout[3] = (pin[0] >> 8) & 0x1f;
        pout[4] = (pin[0] >> 3) & 0x1f;

        *in = pin + 1;
        *out = pout + 5;
}

void
__simple9_unpack7_4(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 21) & 0x7f;
        pout[1] = (pin[0] >> 14) & 0x7f;
        pout[2] = (pin[0] >> 7) & 0x7f;
        pout[3] = pin[0] & 0x7f;

        *in = pin + 1;
        *out = pout + 4;
}

void
__simple9_unpack9_3(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 19) & 0x01ff;
        pout[1] = (pin[0] >> 10) & 0x01ff;
        pout[2] = (pin[0] >> 1) & 0x01ff;

        *in = pin + 1;
        *out = pout + 3;
}

void
__simple9_unpack14_2(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = (pin[0] >> 14) & 0x3fff;
        pout[1] = pin[0] & 0x3fff;

        *in = pin + 1;
        *out = pout + 2;
}

void
__simple9_unpack28_1(uint32_t **out, uint32_t **in)
{
        uint32_t        *pout;
        uint32_t        *pin;

        pout = *out;
        pin = *in;

        pout[0] = pin[0] & 0x0fffffff;

        *in = pin + 1;
        *out = pout + 1;
}
