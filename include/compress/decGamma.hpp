/*-----------------------------------------------------------------------------
 *  decGamma.hpp - A transformation table for Gamma codes
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

#ifndef __DECGAMMA_HPP__
#define __DECGAMMA_HPP__

#include <stdint.h>

namespace opc {
extern uint32_t decGamma[1 << 16];
}; /* namespace: opc */

#endif /* __DECGAMMA_HPP__ */
