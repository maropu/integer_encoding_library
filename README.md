An encoder/decoder collection for a sequence of integers
=================

Overview
-----------

This library is assumed to encode and decode a sequence of integers
with highly positive skewness. The skewness is a distribution where
the mass of the distribution is concentrated on the left, i.e., an
element of the sequence is rarely a large integer. The library
includes a processor-friendly fast coder, called VSEncoder, and other
earlier coders for their comparisons. There are many alternatives of
VSEncoder, and more specifically the following are implemented in
this library:

* VSEncodingBlocks and VSE-R

Original implementation of VSEncoder. It splits a sequence of
integers into partitions, and these integers in each partition
are stored as constant values. When splitting, it calculates 
optimal partitions with Dynamic Programming. More details can be
found in http://portal.acm.org/citation.cfm?id=1871592

* VSEncodingRest

This alternative of VSEncoding employs different memory layout
from the original implementation. VSEncodingBlocks and VSE-R unpack
a bunch of integers with same sizes individually at first, and then
re-permute these integers so as to restore an original sequence of
these integers. Because the re-permuting processing could be a
bottleneck, VSEncodingRest writes each partition by one word aligned
without the re-permuting. Moreover, it fits a part of subsequent
encoded partitions in the unused spaces of each aligned partition.

* VSEncodingBlocksHybrid

VSEncodingBlocksHybrid uses VSEncodingRest for short lists and
VSEncodingBLocks for the long ones.

* VSEncodingSimple V1/V2

VSEncodingRest suffers from some amounts of branch penalties inside
processors that the space-saving technique causes. VSEncodingSimple
removes this technique, and calculates partitions so as to minimize
unused spaces in each aligned partition with Dynamic Programming.
VSEncodingSimple v1 and v2 allocate 4-bit and 8-bit to represent
the length of partitions, respectively.


NOTE: This library aims at a research tool for performance
benchmarks, not a qualified product. So, some improvements to remove
risks such memory leaks are pended for the time being.

Prequisites
-----------

License
-----------

Apache License, Version 2.0 http://www.apache.org/licenses/LICENSE-2.0

History
-----------

2012-04-03 version 0.2.0:

* Support to compile it as a shared library.

2011-11-13 version 0.1.0:

* Basic functions implemented, and a first release.

Authors
-----------

* Takeshi Yamamuro, linguin.m.s_at_gmail.com
* Fabrizio Silvestri, fabrizio.silvestri_at_isti.cnr.it
* Rossano Venturini, rossano.venturini_at_isti.cnr.it

