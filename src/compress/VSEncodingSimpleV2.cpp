/*-----------------------------------------------------------------------------
 *  VSEncodingSimpleV2.cpp - A optimized implementation of VSEncoding.
 *      This code of VSEncoding removes the buffering technique of
 *      VSEncodingRest, and makes the bits of K 8-bits to save the
 *      padding areas of paritions with Dynamic Programming.
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

#include "compress/VSEncodingSimpleV2.hpp"

#define VSESIMPLEV2_LOGLEN      8
#define VSESIMPLEV2_LOGLOG      4

#define VSESIMPLEV2_LENS_LEN    (1 << VSESIMPLEV2_LOGLEN)
#define VSESIMPLEV2_LOGS_LEN    (1 << VSESIMPLEV2_LOGLOG)

/* A set of unpacking functions */
static inline void __vsesimplev2_unpack0(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack1(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack2(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack3(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack4(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack5(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack6(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack7(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack8(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack9(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack10(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack11(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack12(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack16(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack20(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));
static inline void __vsesimplev2_unpack32(uint32_t **out, uint32_t **in, uint32_t len)
        __attribute__((always_inline));

/* A interface of unpacking functions above */
typedef void (*__vsesimplev2_unpacker)(uint32_t **out, uint32_t **in, uint32_t len);

static __vsesimplev2_unpacker       __vsesimplev2_unpack[] = {
        __vsesimplev2_unpack0, __vsesimplev2_unpack1,
        __vsesimplev2_unpack2, __vsesimplev2_unpack3,
        __vsesimplev2_unpack4, __vsesimplev2_unpack5,
        __vsesimplev2_unpack6, __vsesimplev2_unpack7,
        __vsesimplev2_unpack8, __vsesimplev2_unpack9,
        __vsesimplev2_unpack10, __vsesimplev2_unpack11,
        __vsesimplev2_unpack12, __vsesimplev2_unpack16,
        __vsesimplev2_unpack20, __vsesimplev2_unpack32
};

static uint32_t __vsesimplev2_possLens[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
        81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
        97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
        113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128,
        129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
        145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160,
        161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
        177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
        193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208,
        209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
        225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240,
        241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256
};

static uint32_t __vsesimplev2_remapLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16, 16, 16, 16,
        20, 20, 20, 20,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

static uint32_t __vsesimplev2_codeLogs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 13, 13,
        14, 14, 14, 14,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

/* FIXME: Stupid codes here, so it needs to be replaced */
#ifdef USE_BOOST_SHAREDPTR
 static VSEncodingPtr __vsesimplev2 =
                VSEncodingPtr(new VSEncoding(&__vsesimplev2_possLens[0],
                NULL, VSESIMPLEV2_LENS_LEN, true));
#else
 static VSEncoding *__vsesimplev2 =
                new VSEncoding(&__vsesimplev2_possLens[0],
                NULL, VSESIMPLEV2_LENS_LEN, true);
#endif /* USE_BOOST_SHAREDPTR */

void
VSEncodingSimpleV2::encodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t &nvalue)
{
        uint32_t        i;
        uint32_t        j;
        uint32_t        numBlocks;
        uint32_t        pos1;
        uint32_t        pos2;
        uint32_t        maxB;
        uint32_t        *logs;
        uint32_t        *part;
        BitsWriter      *ds1_wt;
        BitsWriter      *ds2_wt;
        BitsWriter      *cd_wt;

        logs = new uint32_t[len];

        if (logs == NULL)
                eoutput("Can't allocate memory");

        /* Compute logs of all numbers */
        for (i = 0; i < len; i++)
                logs[i] = __vsesimplev2_remapLogs[1 + int_utils::get_msb(in[i])];

        /* Compute optimal partition */
        part = __vsesimplev2->compute_OptPartition(logs, len,
                        VSESIMPLEV2_LOGLEN + VSESIMPLEV2_LOGLOG, numBlocks);

    	/* Ready to write descripters for compressed integers */ 
        ds1_wt = new BitsWriter(out);

        if (ds1_wt == NULL)
                eoutput("Can't initialize a class");

     	/* Write the initial position of compressed integers */
        pos1 = int_utils::div_roundup(numBlocks, 32 / VSESIMPLEV2_LOGLOG);
        pos2 = int_utils::div_roundup(numBlocks, 32 / VSESIMPLEV2_LOGLEN);

        ds1_wt->bit_writer(pos1, 32);
        ds1_wt->bit_writer(pos1 + pos2, 32);

    	/* Ready to write actual compressed integers */ 
        ds2_wt = new BitsWriter(out + pos1 + 2);
        cd_wt = new BitsWriter(out + pos1 + pos2 + 2);

        if (ds2_wt == NULL || cd_wt == NULL)
                eoutput("Can't initialize a class");

        /* Write descripters & integers */
        for (i = 0; i < numBlocks; i++) {
                /* Compute max B in the block */
                for (j = part[i], maxB = 0; j < part[i + 1]; j++) {
                        if (maxB < logs[j])
                                maxB = logs[j];
                }

                if (maxB) {
                        /* Write integers */
                        for (j = part[i]; j < part[i + 1]; j++) 
                                cd_wt->bit_writer(in[j], maxB);

                        /* Allign to 32-bit */
                        cd_wt->bit_flush(); 
                }

                /* Writes the value of B and K */
                ds1_wt->bit_writer(__vsesimplev2_codeLogs[maxB], VSESIMPLEV2_LOGLOG);

                /* Compute the code for the block length.
                 * A original code is below though, it's too slow due to many loops.
                 * So, it's replace with a stupid code temporarily.
                 *
                 * for (k = 0; k < VSESIMPLEV2_LENS_LEN; k++)
                 *         if (part[i + 1] - part[i] == __vsesimplev2_possLens[k])
                 *                 break;
                 *
                 * ds2_wt->bit_writer(k, VSESIMPLEV2_LOGLEN);
                 */
                 ds2_wt->bit_writer(part[i + 1] - part[i] - 1, VSESIMPLEV2_LOGLEN);
        }

        /* Allign to 32-bit */
        ds1_wt->bit_flush(); 
        ds2_wt->bit_flush(); 

        nvalue = ds1_wt->written + ds2_wt->written + cd_wt->written;

        delete[] logs;
        delete ds1_wt;
        delete ds2_wt;
        delete cd_wt;
}

void
VSEncodingSimpleV2::decodeArray(uint32_t *in, uint32_t len,
                uint32_t *out, uint32_t nvalue)
{
        uint32_t        B;
        uint32_t        K;
        uint32_t        *bin;
        uint32_t        *kin;
        uint32_t        *data;
        uint32_t        *end;

        bin = in + 2;
        kin = in + *in + 2;
        data = in + *(in + 1) + 2;
        end = out + nvalue;
        
        while (1) {
                /* Unpacking integers with a first 4/8-bit */
                B = (*bin) >> 7 * VSESIMPLEV2_LOGLOG;
                K = (*kin) >> 3 * VSESIMPLEV2_LOGLEN;

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a second 4/8-bit */
                B = ((*bin) >> 6 * VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = ((*kin) >> 2 * VSESIMPLEV2_LOGLEN) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a thrid 4/8-bit */
                B = ((*bin) >> 5 * VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = ((*kin) >> VSESIMPLEV2_LOGLEN) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a forth 4/8-bit */
                B = ((*bin) >> 4 * VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = (*kin++) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                if (end <= out)
                        break;

                /* Unpacking integers with a second 4/8-bit */
                B = ((*bin) >> 3 * VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = (*kin) >> 3 * VSESIMPLEV2_LOGLEN;

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a second 4/8-bit */
                B = ((*bin) >> 2 * VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = ((*kin) >> 2 * VSESIMPLEV2_LOGLEN) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a second 4/8-bit */
                B = ((*bin) >> VSESIMPLEV2_LOGLOG) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = ((*kin) >> VSESIMPLEV2_LOGLEN) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                /* Unpacking integers with a second 4/8-bit */
                B = (*bin++) & (VSESIMPLEV2_LOGS_LEN - 1);
                K = (*kin++) & (VSESIMPLEV2_LENS_LEN - 1);

                (__vsesimplev2_unpack[B])(&out, &data, __vsesimplev2_possLens[K]);

                if (end <= out)
                        break;
        }
}

/* --- Intra functions below --- */

void
__vsesimplev2_unpack0(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 4); i++, pout += 4) {
                __asm__ __volatile__(
                        "pxor   %%xmm0, %%xmm0\n\t"
                        "movdqu %%xmm0, %0\n\t"
                        :"=m" (pout[0])
                        ::"memory", "%xmm0");
        }

        *out += len;
}

void
__vsesimplev2_unpack1(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, *in += 1) {
                pout[0] = *in[0] >> 31;
                pout[1] = (*in[0] >> 30) & 0x01;
                pout[2] = (*in[0] >> 29) & 0x01;
                pout[3] = (*in[0] >> 28) & 0x01;
                pout[4] = (*in[0] >> 27) & 0x01;
                pout[5] = (*in[0] >> 26) & 0x01;
                pout[6] = (*in[0] >> 25) & 0x01;
                pout[7] = (*in[0] >> 24) & 0x01;
                pout[8] = (*in[0] >> 23) & 0x01;
                pout[9] = (*in[0] >> 22) & 0x01;
                pout[10] = (*in[0] >> 21) & 0x01;
                pout[11] = (*in[0] >> 20) & 0x01;
                pout[12] = (*in[0] >> 19) & 0x01;
                pout[13] = (*in[0] >> 18) & 0x01;
                pout[14] = (*in[0] >> 17) & 0x01;
                pout[15] = (*in[0] >> 16) & 0x01;
                pout[16] = (*in[0] >> 15) & 0x01;
                pout[17] = (*in[0] >> 14) & 0x01;
                pout[18] = (*in[0] >> 13) & 0x01;
                pout[19] = (*in[0] >> 12) & 0x01;
                pout[20] = (*in[0] >> 11) & 0x01;
                pout[21] = (*in[0] >> 10) & 0x01;
                pout[22] = (*in[0] >> 9) & 0x01;
                pout[23] = (*in[0] >> 8) & 0x01;
                pout[24] = (*in[0] >> 7) & 0x01;
                pout[25] = (*in[0] >> 6) & 0x01;
                pout[26] = (*in[0] >> 5) & 0x01;
                pout[27] = (*in[0] >> 4) & 0x01;
                pout[28] = (*in[0] >> 3) & 0x01;
                pout[29] = (*in[0] >> 2) & 0x01;
                pout[30] = (*in[0] >> 1) & 0x01;
                pout[31] = *in[0] & 0x01;
        }

        *out += len;
}

void
__vsesimplev2_unpack2(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 16); i++, pout += 16, *in += 1) {
                pout[0] = *in[0] >> 30;
                pout[1] = (*in[0] >> 28) & 0x03;
                pout[2] = (*in[0] >> 26) & 0x03;
                pout[3] = (*in[0] >> 24) & 0x03;
                pout[4] = (*in[0] >> 22) & 0x03;
                pout[5] = (*in[0] >> 20) & 0x03;
                pout[6] = (*in[0] >> 18) & 0x03;
                pout[7] = (*in[0] >> 16) & 0x03;
                pout[8] = (*in[0] >> 14) & 0x03;
                pout[9] = (*in[0] >> 12) & 0x03;
                pout[10] = (*in[0] >> 10) & 0x03;
                pout[11] = (*in[0] >> 8) & 0x03;
                pout[12] = (*in[0] >> 6) & 0x03;
                pout[13] = (*in[0] >> 4) & 0x03;
                pout[14] = (*in[0] >> 2) & 0x03;
                pout[15] = *in[0] & 0x03;
        }

        *out += len;
}

void
__vsesimplev2_unpack3(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, pin += 3) {
                pout[0] = pin[0] >> 29;
                pout[1] = (pin[0] >> 26) & 0x07;
                pout[2] = (pin[0] >> 23) & 0x07;
                pout[3] = (pin[0] >> 20) & 0x07;
                pout[4] = (pin[0] >> 17) & 0x07;
                pout[5] = (pin[0] >> 14) & 0x07;
                pout[6] = (pin[0] >> 11) & 0x07;
                pout[7] = (pin[0] >> 8) & 0x07;
                pout[8] = (pin[0] >> 5) & 0x07;
                pout[9] = (pin[0] >> 2) & 0x07;
                pout[10] = (pin[0] << 1) & 0x07;
                pout[10] |= pin[1] >> 31;
                pout[11] = (pin[1] >> 28) & 0x07;
                pout[12] = (pin[1] >> 25) & 0x07;
                pout[13] = (pin[1] >> 22) & 0x07;
                pout[14] = (pin[1] >> 19) & 0x07;
                pout[15] = (pin[1] >> 16) & 0x07;
                pout[16] = (pin[1] >> 13) & 0x07;
                pout[17] = (pin[1] >> 10) & 0x07;
                pout[18] = (pin[1] >> 7) & 0x07;
                pout[19] = (pin[1] >> 4) & 0x07;
                pout[20] = (pin[1] >> 1) & 0x07;
                pout[21] = (pin[1] << 2) & 0x07;
                pout[21] |= pin[2] >> 30;
                pout[22] = (pin[2] >> 27) & 0x07;
                pout[23] = (pin[2] >> 24) & 0x07;
                pout[24] = (pin[2] >> 21) & 0x07;
                pout[25] = (pin[2] >> 18) & 0x07;
                pout[26] = (pin[2] >> 15) & 0x07;
                pout[27] = (pin[2] >> 12) & 0x07;
                pout[28] = (pin[2] >> 9) & 0x07;
                pout[29] = (pin[2] >> 6) & 0x07;
                pout[30] = (pin[2] >> 3) & 0x07;
                pout[31] = pin[2] & 0x07;
        }

        *in += int_utils::div_roundup(3 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack4(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 8); i++, pout += 8, *in += 1) {
                pout[0] = *in[0] >> 28;
                pout[1] = (*in[0] >> 24) & 0x0f;
                pout[2] = (*in[0] >> 20) & 0x0f;
                pout[3] = (*in[0] >> 16) & 0x0f;
                pout[4] = (*in[0] >> 12) & 0x0f;
                pout[5] = (*in[0] >> 8) & 0x0f;
                pout[6] = (*in[0] >> 4) & 0x0f;
                pout[7] = *in[0] & 0x0f;
        }

        *out += len;
}

void
__vsesimplev2_unpack5(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, pin += 5) {
                pout[0] = pin[0] >> 27;
                pout[1] = (pin[0] >> 22) & 0x1f;
                pout[2] = (pin[0] >> 17) & 0x1f;
                pout[3] = (pin[0] >> 12) & 0x1f;
                pout[4] = (pin[0] >> 7) & 0x1f;
                pout[5] = (pin[0] >> 2) & 0x1f;
                pout[6] = (pin[0] << 3) & 0x1f;
                pout[6] |= pin[1] >> 29;
                pout[7] = (pin[1] >> 24) & 0x1f;
                pout[8] = (pin[1] >> 19) & 0x1f;
                pout[9] = (pin[1] >> 14) & 0x1f;
                pout[10] = (pin[1] >> 9) & 0x1f;
                pout[11] = (pin[1] >> 4) & 0x1f;
                pout[12] = (pin[1] << 1) & 0x1f;
                pout[12] |= pin[2] >> 0x1f;
                pout[13] = (pin[2] >> 26) & 0x1f;
                pout[14] = (pin[2] >> 21) & 0x1f;
                pout[15] = (pin[2] >> 16) & 0x1f;
                pout[16] = (pin[2] >> 11) & 0x1f;
                pout[17] = (pin[2] >> 6) & 0x1f;
                pout[18] = (pin[2] >> 1) & 0x1f;
                pout[19] = (pin[2] << 4) & 0x1f;
                pout[19] |= pin[3] >> 28;
                pout[20] = (pin[3] >> 23) & 0x1f;
                pout[21] = (pin[3] >> 18) & 0x1f;
                pout[22] = (pin[3] >> 13) & 0x1f;
                pout[23] = (pin[3] >> 8) & 0x1f;
                pout[24] = (pin[3] >> 3) & 0x1f;
                pout[25] = (pin[3] << 2) & 0x1f;
                pout[25] |= pin[4] >> 30;
                pout[26] = (pin[4] >> 25) & 0x1f;
                pout[27] = (pin[4] >> 20) & 0x1f;
                pout[28] = (pin[4] >> 15) & 0x1f;
                pout[29] = (pin[4] >> 10) & 0x1f;
                pout[30] = (pin[4] >> 5) & 0x1f;
                pout[31] = pin[4] & 0x1f;
        }

        *in += int_utils::div_roundup(5 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack6(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 16); i++, pout += 16, pin += 3) {
                pout[0] = pin[0] >> 26;
                pout[1] = (pin[0] >> 20) & 0x3f;
                pout[2] = (pin[0] >> 14) & 0x3f;
                pout[3] = (pin[0] >> 8) & 0x3f;
                pout[4] = (pin[0] >> 2) & 0x3f;
                pout[5] = (pin[0] << 4) & 0x3f;
                pout[5] |= pin[1] >> 28;
                pout[6] = (pin[1] >> 22) & 0x3f;
                pout[7] = (pin[1] >> 16) & 0x3f;
                pout[8] = (pin[1] >> 10) & 0x3f;
                pout[9] = (pin[1] >> 4) & 0x3f;
                pout[10] = (pin[1] << 2) & 0x3f;
                pout[10] |= pin[2] >> 30;
                pout[11] = (pin[2] >> 24) & 0x3f;
                pout[12] = (pin[2] >> 18) & 0x3f;
                pout[13] = (pin[2] >> 12) & 0x3f;
                pout[14] = (pin[2] >> 6) & 0x3f;
                pout[15] = pin[2] & 0x3f;
        }

        *in += int_utils::div_roundup(6 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack7(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, pin += 7) {
                pout[0] = pin[0] >> 25;
                pout[1] = (pin[0] >> 18) & 0x7f;
                pout[2] = (pin[0] >> 11) & 0x7f;
                pout[3] = (pin[0] >> 4) & 0x7f;
                pout[4] = (pin[0] << 3) & 0x7f;
                pout[4] |= pin[1] >> 29;
                pout[5] = (pin[1] >> 22) & 0x7f;
                pout[6] = (pin[1] >> 15) & 0x7f;
                pout[7] = (pin[1] >> 8) & 0x7f;
                pout[8] = (pin[1] >> 1) & 0x7f;
                pout[9] = (pin[1] << 6) & 0x7f;
                pout[9] |= pin[2] >> 26;
                pout[10] = (pin[2] >> 19) & 0x7f;
                pout[11] = (pin[2] >> 12) & 0x7f;
                pout[12] = (pin[2] >> 5) & 0x7f;
                pout[13] = (pin[2] << 2) & 0x7f;
                pout[13] |= pin[3] >> 30;
                pout[14] = (pin[3] >> 23) & 0x7f;
                pout[15] = (pin[3] >> 16) & 0x7f;
                pout[16] = (pin[3] >> 9) & 0x7f;
                pout[17] = (pin[3] >> 2) & 0x7f;
                pout[18] = (pin[3] << 5) & 0x7f;
                pout[18] |= pin[4] >> 27;
                pout[19] = (pin[4] >> 20) & 0x7f;
                pout[20] = (pin[4] >> 13) & 0x7f;
                pout[21] = (pin[4] >> 6) & 0x7f;
                pout[22] = (pin[4] << 1) & 0x7f;
                pout[22] |= pin[5] >> 31;
                pout[23] = (pin[5] >> 24) & 0x7f;
                pout[24] = (pin[5] >> 17) & 0x7f;
                pout[25] = (pin[5] >> 10) & 0x7f;
                pout[26] = (pin[5] >> 3) & 0x7f;
                pout[27] = (pin[5] << 4) & 0x7f;
                pout[27] |= pin[6] >> 28;
                pout[28] = (pin[6] >> 21) & 0x7f;
                pout[29] = (pin[6] >> 14) & 0x7f;
                pout[30] = (pin[6] >> 7) & 0x7f;
                pout[31] = pin[6] & 0x7f;
        }

        *in += int_utils::div_roundup(7 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack8(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 4); i++, pout += 4, *in += 1) {
                pout[0] = *in[0] >> 24;
                pout[1] = (*in[0] >> 16) & 0xff;
                pout[2] = (*in[0] >> 8) & 0xff;
                pout[3] = *in[0] & 0xff;
        }

        *out += len;
}

void
__vsesimplev2_unpack9(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, pin += 9) {
                pout[0] = pin[0] >> 23;
                pout[1] = (pin[0] >> 14) & 0x01ff;
                pout[2] = (pin[0] >> 5) & 0x01ff;
                pout[3] = (pin[0] << 4) & 0x01ff;
                pout[3] |= pin[1] >> 28;
                pout[4] = (pin[1] >> 19) & 0x01ff;
                pout[5] = (pin[1] >> 10) & 0x01ff;
                pout[6] = (pin[1] >> 1) & 0x01ff;
                pout[7] = (pin[1] << 8) & 0x01ff;
                pout[7] |= pin[2] >> 24;
                pout[8] = (pin[2] >> 15) & 0x01ff;
                pout[9] = (pin[2] >> 6) & 0x01ff;
                pout[10] = (pin[2] << 3) & 0x01ff;
                pout[10] |= pin[3] >> 29;
                pout[11] = (pin[3] >> 20) & 0x01ff;
                pout[12] = (pin[3] >> 11) & 0x01ff;
                pout[13] = (pin[3] >> 2) & 0x01ff;
                pout[14] = (pin[3] << 7) & 0x01ff;
                pout[14] |= pin[4] >> 25;
                pout[15] = (pin[4] >> 16) & 0x01ff;
                pout[16] = (pin[4] >> 7) & 0x01ff;
                pout[17] = (pin[4] << 2) & 0x01ff;
                pout[17] |= pin[5] >> 30;
                pout[18] = (pin[5] >> 21) & 0x01ff;
                pout[19] = (pin[5] >> 12) & 0x01ff;
                pout[20] = (pin[5] >> 3) & 0x01ff;
                pout[21] = (pin[5] << 6) & 0x01ff;
                pout[21] |= pin[6] >> 26;
                pout[22] = (pin[6] >> 17) & 0x01ff;
                pout[23] = (pin[6] >> 8) & 0x01ff;
                pout[24] = (pin[6] << 1) & 0x01ff;
                pout[24] |= pin[7] >> 31;
                pout[25] = (pin[7] >> 22) & 0x01ff;
                pout[26] = (pin[7] >> 13) & 0x01ff;
                pout[27] = (pin[7] >> 4) & 0x01ff;
                pout[28] = (pin[7] << 5) & 0x01ff;
                pout[28] |= pin[8] >> 27;
                pout[29] = (pin[8] >> 18) & 0x01ff;
                pout[30] = (pin[8] >> 9) & 0x01ff;
                pout[31] = pin[8] & 0x01ff;
        }

        *in += int_utils::div_roundup(9 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack10(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 16); i++, pout += 16, pin += 5) {
                pout[0] = pin[0] >> 22;
                pout[1] = (pin[0] >> 12) & 0x03ff;
                pout[2] = (pin[0] >> 2) & 0x03ff;
                pout[3] = (pin[0] << 8) & 0x03ff;
                pout[3] |= pin[1] >> 24;
                pout[4] = (pin[1] >> 14) & 0x03ff;
                pout[5] = (pin[1] >> 4) & 0x03ff;
                pout[6] = (pin[1] << 6) & 0x03ff;
                pout[6] |= pin[2] >> 26;
                pout[7] = (pin[2] >> 16) & 0x03ff;
                pout[8] = (pin[2] >> 6) & 0x03ff;
                pout[9] = (pin[2] << 4) & 0x03ff;
                pout[9] |= pin[3] >> 28;
                pout[10] = (pin[3] >> 18) & 0x03ff;
                pout[11] = (pin[3] >> 8) & 0x03ff;
                pout[12] = (pin[3] << 2) & 0x03ff;
                pout[12] |= pin[4] >> 30;
                pout[13] = (pin[4] >> 20) & 0x03ff;
                pout[14] = (pin[4] >> 10) & 0x03ff;
                pout[15] = pin[4] & 0x03ff;
        }

        *in += int_utils::div_roundup(10 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack11(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 32); i++, pout += 32, pin += 11) {
                pout[0] = pin[0] >> 21;
                pout[1] = (pin[0] >> 10) & 0x07ff;
                pout[2] = (pin[0] << 1) & 0x07ff;
                pout[2] |= pin[1] >> 31;
                pout[3] = (pin[1] >> 20) & 0x07ff;
                pout[4] = (pin[1] >> 9) & 0x07ff;
                pout[5] = (pin[1] << 2) & 0x07ff;
                pout[5] |= pin[2] >> 30;
                pout[6] = (pin[2] >> 19) & 0x07ff;
                pout[7] = (pin[2] >> 8) & 0x07ff;
                pout[8] = (pin[2] << 3) & 0x07ff;
                pout[8] |= pin[3] >> 29;
                pout[9] = (pin[3] >> 18) & 0x07ff;
                pout[10] = (pin[3] >> 7) & 0x07ff;
                pout[11] = (pin[3] << 4) & 0x07ff;
                pout[11] |= pin[4] >> 28;
                pout[12] = (pin[4] >> 17) & 0x07ff;
                pout[13] = (pin[4] >> 6) & 0x07ff;
                pout[14] = (pin[4] << 5) & 0x07ff;
                pout[14] |= pin[5] >> 27;
                pout[15] = (pin[5] >> 16) & 0x07ff;
                pout[16] = (pin[5] >> 5) & 0x07ff;
                pout[17] = (pin[5] << 6) & 0x07ff;
                pout[17] |= pin[6] >> 26;
                pout[18] = (pin[6] >> 15) & 0x07ff;
                pout[19] = (pin[6] >> 4) & 0x07ff;
                pout[20] = (pin[6] << 7) & 0x07ff;
                pout[20] |= pin[7] >> 25;
                pout[21] = (pin[7] >> 14) & 0x07ff;
                pout[22] = (pin[7] >> 3) & 0x07ff;
                pout[23] = (pin[7] << 8) & 0x07ff;
                pout[23] |= pin[8] >> 24;
                pout[24] = (pin[8] >> 13) & 0x07ff;
                pout[25] = (pin[8] >> 2) & 0x07ff;
                pout[26] = (pin[8] << 9) & 0x07ff;
                pout[26] |= pin[9] >> 23;
                pout[27] = (pin[9] >> 12) & 0x07ff;
                pout[28] = (pin[9] >> 1) & 0x07ff;
                pout[29] = (pin[9] << 10) & 0x07ff;
                pout[29] |= pin[10] >> 22;
                pout[30] = (pin[10] >> 11) & 0x07ff;
                pout[31] = pin[10] & 0x07ff;
        }

        *in += int_utils::div_roundup(11 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack12(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 8); i++, pout += 8, pin += 3) {
                pout[0] = pin[0] >> 20;
                pout[1] = (pin[0] >> 8) & 0x0fff;
                pout[2] = (pin[0] << 4) & 0x0fff;
                pout[2] |= pin[1] >> 28;
                pout[3] = (pin[1] >> 16) & 0x0fff;
                pout[4] = (pin[1] >> 4) & 0x0fff;
                pout[5] = (pin[1] << 8) & 0x0fff;
                pout[5] |= pin[2] >> 24;
                pout[6] = (pin[2] >> 12) & 0x0fff;
                pout[7] = pin[2] & 0x0fff;
        }

        *in += int_utils::div_roundup(12 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack16(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pout;

        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 2); i++, pout += 2, *in += 1) {
                pout[0] = *in[0] >> 16;
                pout[1] = *in[0] & 0xffff;
        }

        *out += len;
}

void
__vsesimplev2_unpack20(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 8); i++, pout += 8, pin += 5) {
                pout[0] = pin[0] >> 12;
                pout[1] = (pin[0] << 8) & 0x0fffff;
                pout[1] |= (pin[1] >> 24);
                pout[2] = (pin[1] >> 4) & 0x0fffff;
                pout[3] = (pin[1] << 16) & 0x0fffff;
                pout[3] |= pin[2] >> 16;
                pout[4] = (pin[2] << 4) & 0x0fffff;
                pout[4] |= pin[3] >> 28;
                pout[5] = (pin[3] >> 8) & 0x0fffff;
                pout[6] = (pin[3] << 12) & 0x0fffff;
                pout[6] |= pin[4] >> 20;
                pout[7] = pin[4] & 0x0fffff;
        }

        *in += int_utils::div_roundup(20 * len, 32);
        *out += len;
}

void
__vsesimplev2_unpack32(uint32_t **out, uint32_t **in, uint32_t len)
{
        uint32_t        i;
        uint32_t        *pin;
        uint32_t        *pout;

        pin = *in;
        pout = *out;

        for (i = 0; i < int_utils::div_roundup(len, 4); i++, pout += 4, pin += 4) {
               __asm__ __volatile__(
                        "movdqu %1, %%xmm0\n\t"
                        "movdqu %%xmm0, %0\n\t"
                        :"=m" (pout[0])
                        :"m" (pin[0])
                        :"memory", "%xmm0");
        }

        *in += len;
        *out += len;
}

