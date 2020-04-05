/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MobMemory.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	13 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #13 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MobMemory.cpp#13 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006-2007 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing, Inc. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of Stillwater
 * Supercomputing, Inc.
 */
// STL includes
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
// BOOST includes
#include <boost/shared_ptr.hpp>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <Stillwater/arch/src/Libraries/slm/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <Stillwater/arch/src/Libraries/slm/baseTypes/Request.hpp>
// memory library includes
#include "./memory_nsmacro.hpp"	// centralized namespace definition
#include <interfaces/MemoryTypeEnums.hpp>	// this is shared but the translation mechanism is in this library TODO fix me ETLO 2/23/07
#include "./Page.hpp"
#include "./Memory.hpp"
#include "./MemoryDescriptor.hpp"
#include "./MemoryObject.hpp"
#include "./MobMemory.hpp"

using namespace std;
using namespace stillwater::slm;

/**
 * read(uint64 baseAddress, MemoryObject& mob)
 *
 * There are two kinds of reads:
 * 1- reads to a blob
 * 2- reads to an element in a blob
 *
 * Discussion:
 * The original thought is to store blobs in memory and
 * have the blob be lead by a descriptor. The problem with 
 * that approach is that to read the memory blob you first
 * need to read the descriptor before you can start streaming
 * data from memory. To avoid this, the machine could cache
 * the blobs when they get allocated/reserved. To support
 * that idea, we can separate the descriptors from the data.
 * This makes streaming to and from memory much more efficiet
 * since the descriptors are small, and the blobs are structured
 * and relatively large. So you could stream the descriptors
 * into a cache and work/retrieve them from there without 
 * ever touching memory again. The descriptors then can set
 * up the memory stream independently from memory.
 *
 * These optimizations point to a low level Memory object
 * implementation that is simply block oriented without
 * any interpretation of the blobs or descriptors. This
 * lower level implementation can be used for many different
 * implementations and thus is best for this low level
 * object.
 *
 * The rest of the implementation is based on a page-oriented
 * allocation mechanism. When we see a read to an uninitialized
 * memory, we'll flag that as an error.
 */
void MobMemory::read(Address baseAddress, MemoryObject& mob) const {
	Memory::read(baseAddress, mob.size(), mob.getBlobPtr());
}

void MobMemory::write(Address baseAddress, const MemoryObject& mob) {
	Memory::write(baseAddress, mob.size(), mob.getConstBlobPtr());
}
