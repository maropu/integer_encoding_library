/*-----------------------------------------------------------------------------
 *  BitsReader.hpp - A coder interface to read compressed data
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

#ifndef __BITSREADER_HPP__
#define __BITSREADER_HPP__

#include "xxx_common.hpp"

/* A transformation table for fast decoding */
#include "compress/policy/decUnary.hpp"
#include "compress/policy/decGamma.hpp"
#include "compress/policy/decDelta.hpp"

namespace integer_coding {
namespace utility {

class BitsReader {
private:
        uint32_t        *data;
        uint64_t        buffer;
        uint32_t        Fill; 

public:
        /* Constructor */
        BitsReader();
        explicit BitsReader(uint32_t *in);

        /* Destructor */
        ~BitsReader() throw();
                
        uint32_t bit_reader(uint32_t bits);

        /* Unary code */
        void N_UnaryArray(uint32_t *out, uint32_t nvalues);
        void F_UnaryArray(uint32_t *out, uint32_t nvalues);

        uint32_t N_Unary();
        uint32_t F_Unary();
        uint32_t F_Unary32();
        uint32_t F_Unary16();
        
        /* Gamma code */
        void N_GammaArray(uint32_t *out, uint32_t nvalues);
        void F_GammaArray(uint32_t *out, uint32_t nvalues);
        void FU_GammaArray(uint32_t *out, uint32_t nvalues);

        uint32_t N_Gamma();
        uint32_t F_Gamma();
        uint32_t FU_Gamma();

        /* Delta code */
        void N_DeltaArray(uint32_t *out, uint32_t nvalues);
        void FU_DeltaArray(uint32_t *out, uint32_t nvalues);
        void FG_DeltaArray(uint32_t *out, uint32_t nvalues);
        void F_DeltaArray(uint32_t* out, uint32_t nvalues);

        uint32_t N_Delta();
        uint32_t F_Delta();
        uint32_t FU_Delta();

        /* Binary Interpolative code */
        void InterpolativeArray(uint32_t* out, uint32_t nvalues,
                        uint32_t offset, uint32_t lo, uint32_t hi);

        uint32_t readMinimalBinary(uint32_t b);
}; /* BitsReader */

}; /* namespace: utility */
}; /* namespace: integer_coding */

#endif /* __BITSREADER_HPP__  */
