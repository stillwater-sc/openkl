/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Cache.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Cache.cpp#7 $
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
#include <deque>
#include <memory>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#define STILLWATER_DIAGNOSTICS	// define macro to enable the diagnostics functionality
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <Stillwater/arch/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <Stillwater/arch/baseTypes/Request.hpp>
// SLM Cache library includes
#include <stillwater/shim/kpu/memory/memory_nsmacro.hpp>	// centralized namespace definition
#include <stillwater/shim/kpu/memory/Cache.hpp>

using namespace stillwater::slm;

Cache::Cache(uint32_t sizeInBytes, uint32_t associativity, uint32_t lineSizeInBytes, const CacheWritePolicy& writePolicy, uint32_t nrOfVictimBuffers) :
	m_pData(NULL), m_tags(NULL), m_lineStates(NULL),
	m_sizeInBytes(sizeInBytes), m_associativity(associativity), m_lineSizeInBytes(lineSizeInBytes),m_writePolicy(writePolicy),m_nrOfVictimBuffers(nrOfVictimBuffers),
	m_reads("default", "reads", "read ops"), m_writes("default", "writes", "write_ops"),
	m_bytesRead("default", "bytesRead", "bytes"), m_bytesWritten("default", "bytesWritten", "bytes")
{
	// double check to see if cache and line size are powers of 2
	// and if not, fix them up to the next largest power of 2
	if ( population::fastCount(sizeInBytes) > 1) {
		// round up
		m_sizeInBytes = 2 << population::topMostBitSet(sizeInBytes);
	}
	if ( population::fastCount(lineSizeInBytes) > 1) {
		// round up
		m_lineSizeInBytes = 2 << population::topMostBitSet(lineSizeInBytes);
	}
	// configure the tag mask
	m_tagMask = 0xFFFFFFFFFFFFFFFF << population::topMostBitSet(m_lineSizeInBytes);
	m_offsetMask = ~m_tagMask;
	Address sizeMask = 0xFFFFFFFFFFFFFFFF << population::topMostBitSet(m_sizeInBytes);
	m_lineMask = m_tagMask ^ sizeMask;	// XOR between the two so that we get the aliased line nr when using this mask
	m_lineNrShift = population::topMostBitSet(m_lineSizeInBytes);
	std::cout << "lineSize    is " << m_lineSizeInBytes << " bytes" << std::endl;
	std::cout << "tagMask     is " << hexint(m_tagMask) << std::endl;
	std::cout << "lineMask    is " << hexint(m_lineMask) << std::endl;
	std::cout << "offsetMask  is " << hexint(m_offsetMask) << std::endl;
	std::cout << "line shift  is " << m_lineNrShift << std::endl;

	// create the raw data store. We look at it as a
	// raw block of bytes, and use an offset from the
	// beginning to access lines
	m_pData = new char[m_sizeInBytes];
	// create the tag store
	m_nrOfLines = (m_sizeInBytes/m_associativity)/m_lineSizeInBytes;
	m_tags = new Address[m_nrOfLines];
	m_lineStates = new CacheLineState[m_nrOfLines];
	m_victimBuffer = new char[m_lineSizeInBytes*m_nrOfVictimBuffers];
	for (uint32_t lineNr = 0; lineNr < m_nrOfLines; ++lineNr) {
		m_tags[lineNr] = 0x1;	// the tags will always be the top bits of an address and thus this equates to no line
		m_lineStates[lineNr] = CACHE_LINE_CLEAN;
	}
}

Cache::~Cache() {
	if (m_pData) {
		delete[] m_pData;
		m_pData = NULL;
	}
	if (m_tags) {
		delete[] m_tags;
		m_tags = NULL;
	}
	if (m_lineStates) {
		delete[] m_lineStates;
		m_lineStates = NULL;
	}
}

CacheLookupState Cache::lookup(const Address& address) const {
	CacheLookupState state;
	// construct the tag
	Address tag = address & m_tagMask;
	// construct the lineNr
	Address lineNr = getLineNr(address);
	// see if we have a match to that line
	if (m_tags[lineNr] == tag) {
		// we have a hit
		if (m_lineStates[lineNr] == CACHE_LINE_CLEAN) {
			state = CACHE_HIT_CLEAN;
		}
		else {
			state = CACHE_HIT_MODIFIED;
		}
	}
	else {
		// we have a miss
		if (m_lineStates[lineNr] == CACHE_LINE_CLEAN) {
			state = CACHE_MISS_CLEAN;
		}
		else {
			state = CACHE_MISS_MODIFIED;
		}
	}
	return state;
}

bool Cache::isPresent(const Address& address) const {
	// construct the tag
	Address tag = address & m_tagMask;
	// see if we have that tag
	return (m_tags[getLineNr(address)] == tag ? true : false);
}

void Cache::allocate(const Address& address) {
	// construct the tag
	Address tag = address & m_tagMask;
	uint32_t lineNr = getLineNr(address);
	m_tags[lineNr] = tag;
	m_lineStates[lineNr] = CACHE_LINE_CLEAN;
}

void Cache::evict(const Address& address) {
	PRECONDITION(getAvailableVictimBuffers() > 0);
	uint32_t offset = (uint32_t)m_victimLines.size()*m_lineSizeInBytes;	// calc offset in victim buffer
	memcpy(&m_victimBuffer[offset],getCacheLine(address),m_lineSizeInBytes); // copy the line from the cache to the victim buffer
	// store the base address and FIFO ptr
	m_victimLines.push_back(&m_victimBuffer[offset]);
	m_victimBaseAddresses.push_back(m_tags[getLineNr(address)]);
}

void Cache::retireOldestVictim() {
	m_victimLines.pop_front();
	m_victimBaseAddresses.pop_front();
}

void Cache::read(const Address& address, uint32_t sizeInBytes, void* pData) const {
	PRECONDITION(isPresent(address));
	uint32_t offset = (uint32_t)(address & m_offsetMask);
	memcpy(pData,getCacheLine(address)+offset,sizeInBytes);
}

void Cache::write(const Address& address, uint32_t sizeInBytes, const void* pData) {
	PRECONDITION(isPresent(address));
	Address tag = address & m_tagMask;
	uint32_t lineNr = getLineNr(address);
	m_lineStates[lineNr] = CACHE_LINE_MODIFIED;
	uint32_t offset = (uint32_t)(address & m_offsetMask);
	memcpy(getCacheLine(address)+offset, pData,sizeInBytes);
}

// create a hex dump of this page
void Cache::dump(std::ostream& ostr) const {
	ostr << "Data RAM" << std::endl;
	dumpBufferInHex(ostr,m_pData,m_sizeInBytes);
	ostr << "Tag RAM" << std::endl;
	dumpBufferInHex(ostr,(const char*)m_tags,m_nrOfLines*sizeof(Address));
	ostr << "Victim RAM" << std::endl;
	dumpBufferInHex(ostr,m_victimBuffer,m_nrOfVictimBuffers*m_lineSizeInBytes);
}


