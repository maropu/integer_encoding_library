/*-----------------------------------------------------------------------------
 *  VSEncoding.cpp - To scan the optimal partitions in a list
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

#include "compress/VSEncoding.hpp"

using namespace std;
using namespace opc;

/* FIXME: Need to be re-implemented in a thread-safe way */
uint32_t opc::__vsencoding_aux[
                VSENCODING_BLOCKSZ * 2 + 128];

VSEncoding::VSEncoding(uint32_t *lens,
                uint32_t *zlens, uint32_t size, bool is_aligned)
                        : is_aligned(is_aligned), poss_sz(size),
                                maxBlk(lens[size - 1]),
                                possLens(lens), posszLens(zlens)
{
        /* Set the max length of sequences */
        if (posszLens != NULL &&
                        maxBlk < posszLens[poss_sz - 1])
                maxBlk = posszLens[poss_sz - 1];
}

void
VSEncoding::compute_OptPartition(vector<uint32_t>& seq,
                uint32_t fixCost, vector<uint32_t>& parts)
{
        vector<int>             SSSP;
        vector<uint32_t>        costs;

        /*
         * costs[i] will contain the
         * cost of encoding up to i-th position.
         */
        __init_vector(SSSP, seq.size() + 1, -1);
        __init_vector(costs, seq.size() + 1);

        /*
         * This loop computes the cost of the optimal partition. 
         * The computation of the max log in each block is done
         * by scanning. Probably we could obtain a faster solution
         * by using RMQ data structures. We use this trivial
         * solution since construction time is not our main concern. 
         */   
        {
                int             j, g, l;
                int             mleft;
                uint32_t        maxB;
                uint64_t        curCost;

                for (uint32_t i = 1; i <= seq.size(); i++) {
                        mleft = (i > maxBlk)? i - maxBlk : 0;

                        for (maxB = 0, l = 0, g = 0, j = i - 1; j >= mleft; j--) {
                                if (maxB < seq[j])
                                        maxB = seq[j];

                                if (posszLens == NULL) {
                                        /*
                                         * FIXME: If the gaps of elements in possLens[] are
                                         * sparse, a process below is more efficient to hop
                                         * these gaps using the elements rather than
                                         * decrementing j.
                                         */
                                        if (i - j != possLens[l])
                                                continue;
                                        else
                                                l++;
                                } else {
                                        /*
                                         * Treat runs of 0 in a different way.
                                         * They could form larger blocks!
                                         */
                                        if (maxB != 0) {
                                                mleft = (i > maxBlk)?
                                                        i - possLens[poss_sz - 1] : 0;

                                                if (i - j != possLens[l])
                                                        continue;

                                                if (i - j == possLens[l])
                                                        l++;
                                        } else {
                                                if (i - j == possLens[l])
                                                        l++;

                                                if (i - j != posszLens[g])
                                                        continue;

                                                if (i - j == posszLens[g])
                                                        g++;
                                        }
                                }

                                /* Caluculate costs */
                                if (is_aligned)
                                        curCost = costs[j] + __div_roundup((i - j) * maxB, 32) + fixCost;
                                else
                                        curCost = costs[j] + (i - j) * maxB + fixCost;

                                if (SSSP[i] == -1)
                                        costs[i] = curCost + 1;

                                if (curCost <= costs[i]) {
                                        costs[i] = curCost;
                                        SSSP[i] = j;
                                }
                        }
                }
        }

        /* Compute number of nodes in the path */
        uint32_t psize = 0;
        uint32_t next = seq.size();

        while (next != 0) {
                next = SSSP[next];
                psize++;
        }

        /*
         * Obtain the optimal partition starting
         * from the last block.
         */
        __init_vector(parts, psize + 1);

        uint32_t idx = psize;
        next = seq.size();

        while (next != 0) {
                parts[idx--] = next;
                next = SSSP[next];
        }
}

