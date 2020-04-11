/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Memory.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #27 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Memory.cpp#27 $
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
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
//#define STILLWATER_DIAGNOSTICS	// define macro to enable the diagnostics functionality
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <stillwater/arch/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <stillwater/arch/baseTypes/Request.hpp>
// memory library includes
#include "./memory_nsmacro.hpp"	// centralized namespace definition
#include "./Page.hpp"
#include "./Memory.hpp"

using namespace stillwater::slm;

Memory::~Memory(void)
{
	if (m_ranges.size() > 0) {
		std::cerr << "Found unreleased ranges" << std::endl;
		Range::const_iterator iter = m_ranges.begin();
		while (iter != m_ranges.end()) {
			std::cerr << "[" << hexint(iter->first) 
				 << "," << hexint(iter->second)
				 << ")" << std::endl;
			++iter;
		}
	}
}


/**
 * reserve(uint64 baseAddress, uint64 sizeInBytes)
 * \param base address
 * \param size in bytes
 * \return true if successful
 *
 * reserve notifies the Memory model that requests
 * in the range baseAddress+size are imminant.
 * The Memory will reject any addresses that haven't
 * been reserved.
 * We separate reservation and allocation so that
 * we can implement on-demand address storage allocation.
 * That is, we minimize the actual storage behind the
 * memory model to make the simulations run as memory
 * efficient as possible. The basic algorithm is that
 * only reads and writes will actually create storage,
 * and reserver/release allow the Memory model to provide
 * error checking of out of bound requests.
 */
bool Memory::reserve(uint64_t baseAddress, uint64_t sizeInBytes) {
	bool bSuccess = false;
	// check to see if we have any overlap. If we do
	// this would indicate an error in the memory
	// allocation algorithms.
	bool bRangeOverlap = false;
	uint64_t endAddress = baseAddress+sizeInBytes;
	Range::const_iterator iter = m_ranges.begin();
	while (iter != m_ranges.end()) {
		if (iter->first <= baseAddress && baseAddress < iter->second) {
			bRangeOverlap = true;
			// TODO: you might want to throw a specialized exception for this case
			break;
		}
		++iter;
	}
	if (!bRangeOverlap) {
		// allocate this range in the map
		m_ranges.insert(Range::value_type(baseAddress, endAddress));
		bSuccess = true;
	}
	return bSuccess;
}

/**
 * release(uint64 baseAddress)
 * \param base address of the memory block to release
 *
 * release takes the base address of a previously reserved
 * block of memory and, if found, removes it from the reservation
 * address map. 
 * 
 * TODO: What is the behavior of the associated allocated memory?
 * The idea that you want to potentially use this object for
 * verification implies that you don't blindly delete that
 * allocated memory and its contents. Maybe you want to set
 * it aside, but then you need to figure out what to do with
 * re-reserving the same block and the semantics of that.
 */
bool Memory::release(uint64_t baseAddress) {
	bool bSuccess = false;
	Range::iterator iter = m_ranges.find(baseAddress);
	if (iter != m_ranges.end()) {
		m_ranges.erase(iter);
		bSuccess = true;
	}

	return bSuccess;
}

/**
 * read(uint64 baseAddress)
 *
 * There are two kinds of reads:
 * 1- reads to a blob
 * 2- reads to an element in a blob
 *
 * Discussion:
 * The original thought was to store blobs in memory and
 * have the blob be lead by a descriptor. The problem with 
 * that approach is that to read the memory blob you first
 * need to read the descriptor before you can start streaming
 * data from memory. To avoid this, the machine could cache
 * the blob descriptions when they get allocated/reserved. 
 * To support that idea, we separate the descriptors from the
 * blob. This makes streaming to/from memory more efficient
 * since the descriptors are small, and the blobs are structured
 * and relatively large. So you could stream the descriptors
 * into a cache and work/retrieve them from there without 
 * ever touching memory again. Furthermore, cached descriptors 
 * would allow setting up memory streams independently 
 * from memory.
 *
 * This memory object oriented memory would be the
 * conceptual interaction with the memory. However,
 * this is a modeling library and we need non object
 * oriented memory as well. This is why we have two
 * layers of Memory managers: this one, which is the
 * low level object that deals with blocks, but carries
 * no interpretation and the MobMemory which does.
 *
 * The rest of the implementation is based on a 
 * page-oriented allocation mechanism. When we see 
 * a read to an uninitialized memory, we'll flag 
 * that as an error.
 */
void Memory::read(uint64_t baseAddress, uint64_t sizeInBytes, void* pData) const {
	if (m_bLogging) DIAG_DEBUG("Memory::read")(hexint(baseAddress))(sizeInBytes)(pData);
	++m_reads;
	m_bytesRead += sizeInBytes;
	bool bSuccess = false;
	char* pDestination = (char*)pData;
	PageSequencer page(baseAddress, baseAddress+sizeInBytes, m_pageSizeInBytes);
	while (!page.end()) {
		PageMap::const_iterator pageIter = m_pages.find(page.getAnchor());
		if (pageIter != m_pages.end()) {
			uint64_t start = page.startOffset();
			uint64_t end	 = page.endOffset();
			size_t sizeInBytes = static_cast<size_t>(end - start);
			pageIter->second->read(start, sizeInBytes, pDestination); 
			// move to the next page to be read
			page.next(); 
			// finally, move the destination data pointer the same amount
			pDestination += sizeInBytes;
		}
		else {
			// internal error
			uint64_t pageAnchor = page.getAnchor();
			PAGE_EXCEPTION("Memory::read is accessing a non-allocated page")(hexint(pageAnchor));
		}
	}
	// DO NOT use pDestination at this point, since it points beyond
	// valid memory as defined by the block of memory pointed
	// at by pData. The last statement of the while loop steps
	// beyond the end of pData on the last page.
}

/**
 * \brief write a memory block
 * \param base address of the memory to be written
 * \param size of the memory block in bytes
 * \param raw data to be written
 *
 * The Memory object allocates storage for writes only.
 * This allows us to catch reads to uninitialized memory,
 * and it optimizes the memory foot print of the simulator.
 *
 * Our API is block oriented so that we have a simple and
 * uniform interface. I decided against a proliferation of
 * methods to write specific data types, such as ints and
 * reals since each of these can still be described as a
 * block write using this API.
 *
 * Our underlying memory data structure is page oriented.
 * Since a memory block can span multiple pages, we must
 * transform the block write into a collection of page
 * writes. This is accomplished by progressing 
 * through the linear block and updating offset 
 * pointers as we go along. The class PageSequencer
 * maintains the page anchors for us.
 */
void Memory::write(uint64_t baseAddress, uint64_t sizeInBytes, const void* pData) {
	if (m_bLogging) DIAG_DEBUG("Memory::write")(hexint(baseAddress))(sizeInBytes)(pData);
	m_writes++;
	m_bytesWritten += sizeInBytes;
	const char* pSource = static_cast<const char*>(pData);
	PageSequencer page(baseAddress, baseAddress+sizeInBytes, m_pageSizeInBytes);
	while (!page.end()) {
		PageMap::const_iterator pageIter = m_pages.find(page.getAnchor());
		if (pageIter == m_pages.end()) {
			// never seen this page, so we need to allocate it
			m_pages[page.getAnchor()] = PagePointer(new Page(m_pageSizeInBytes));
		}
		uint64_t start = page.startOffset();
		uint64_t end	 = page.endOffset();
		size_t sizeInBytes = static_cast<size_t>(end - start);
		// operator[] will allocate on a new page
		m_pages[page.getAnchor()]->write(start, sizeInBytes, pSource); 
		// move to the next page to be written
		page.next(); 
		// finally, move the source data pointer the same amount
		pSource += sizeInBytes;
	}
	// DO NOT use pSource at this point, since it points beyond
	// valid memory as defined by the block of memory pointed
	// at by pData. The last statement of the while loop steps
	// beyond the end of pData on the last page.
}

/**
 * \brief find if this memory range is covered by a previous allocation
 *
 * The usage pattern of the Memory object 
 * is as follows:
 * <pre>
 *	{
 *		reserve(range1);
 *		reserve(range2);
 *		{
 *			write(block1);
 *			...
 *			read(block1); // or subblock
 *			read(block2) when block2 is not 
 *						 part of block1 is an error
 *		}
 *		release(range2);
 *		release(range1);
 *	}
 * </pre>
 */
bool Memory::isCovered(uint64_t startAddress, uint64_t endAddress) const {
	bool bIsCovered = false;
	// not implemented yet
	return bIsCovered;
}

void Memory::initializeWithByteOrder(const Address& startAddress, const Address& endAddress) {
	PRECONDITION(startAddress >= m_startAddress);
	PRECONDITION(endAddress <= m_endAddress);
	char cntr = 0;
	for (Address address = startAddress; address < endAddress; address++) {
		write(address, 1, &cntr);
		cntr++;	// this will range from 0x00 to 0xff and then wrap
	}
}

void Memory::dumpPages(std::ostream& ostr) const {
	ostr << std::endl << "Page Dump:" << std::endl;
	PageMap::const_iterator iter = m_pages.begin();
	while (iter != m_pages.end()) {
		ostr << hexint(iter->first) << std::endl;
		++iter;
	}
	ostr << "End of Page Dump" << std::endl;
}

void Memory::dumpPageContents(std::ostream& ostr, const PageNumber& pageNr) const {
	ostr << std::endl << "Page Contents Dump:" << std::endl;
	PageMap::const_iterator iter = m_pages.find(pageNr);
	if (iter != m_pages.end()) {
		ostr << hexint(iter->first) << std::endl;
		// create a hex dump of the byte data of the page
		Page* pPage = iter->second.get();
		pPage->dump(ostr);
	}
	else {
		ostr << "Page at page number = " << pageNr << " not found" << std::endl;
	}
}


