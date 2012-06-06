/*-----------------------------------------------------------------------------
 *  decUnary.hpp - A transformation table for Unary codes
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

#ifndef __DECUNARY_HPP__
#define __DECUNARY_HPP__

#include <stdint.h>

namespace integer_coding {
namespace compressor {
extern uint16_t decUnary[1 << 16];
}; /* namespace: compressor */
}; /* namespace: integer_coding */

#endif /* __DECUNARY_HPP__ */
