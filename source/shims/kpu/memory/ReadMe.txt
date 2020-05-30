/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/ReadMe.txt $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2007/02/23 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/ReadMe.txt#3 $
 *
 * Organization:
 *		Stillwater Supercomputing Solutions
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing Solutions. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing Solutions.
 */
========================================================================
    STATIC LIBRARY : memory Project Overview
========================================================================

The memory library contains a functional model of a storage memory.
It allocates memory on a need-to basis.
 
The library also contains architecture models for cache structures and
the address generators that translate from dependence relationships to
precedence relationships.

The cache model will be reusable for other purposes as well. However,
the basic usage of the cache is in the following configuration to be
used as a stream generator/receiver.

		+---------+	    +-----------------------+
 push		| address | pull    |                       |  pull
	<-------|	  +-------->+	  CACHE	            +---------->memory
		+generator|elements |                       | cache lines
		+---------+	    +-----------------------+
	
	precedence			dependence
	semantics			semantics
	
The PA is on the left, the XBar connecting to the Memory Controllers
is on the right of this configuration.

Given the fact that the address generator is programmed to obtain
stream elements that tend to come from some matrix data structure
in memory, the cache is there to buffer the processor array from
the memory data path which includes a cross-bar. However, if we
are using a cache organization to hold data, then we have to content
with conflict misses between the input and output streams. It is
possible that the input stream is already consumed by the time the
output stream arrives in the cache, but it is also possible that 
the output stream kicks out the input stream thus creating a threshing
situation that will kill performance. To avoid this, we may need
a separate input stream cache and an output stream cache. In this
case the cache is really more of a glorified FIFO.

The second detail we need to discuss is how results end up in memory.
If we have a domain that doesn't have data in memory, it would be
great if we can avoid the read bandwidth created by a write-allocate
cache. However, this would require fine control over the data
structure allocation so that it is line-size aligned. If we have
that condition then we could use the write cache to absorb the 
output(result) stream and a cache eviction/clear command could 
write it all out to memory. To avoid congestion on the xbar, we
would want to sequence this cache clear command to visit the 
output caches in sequence, or in a sequence that maximizes bandwidth
given the fact that many of these streams will go to different
memory controllers.
