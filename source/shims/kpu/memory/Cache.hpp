/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Cache.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Cache.hpp#6 $
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
#ifndef STILLWATER_CACHE_INCLUDED
#define STILLWATER_CACHE_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

enum CacheWritePolicy {
	CACHE_WRITE_THROUGH			= 0,
	CACHE_WRITE_PROTECTED		= 1,
	CACHE_WRITE_ALLOCATE		= 2,
};

enum CacheLineState {
	CACHE_LINE_CLEAN			= 0,
	CACHE_LINE_MODIFIED			= 1,
};

enum CacheLookupState {
	CACHE_MISS_CLEAN			= 0,
	CACHE_MISS_MODIFIED			= 1,
	CACHE_HIT_CLEAN				= 2,
	CACHE_HIT_MODIFIED			= 3,
};

/** 
 * \class Cache Cache.hpp "Cache.hpp"
 * \brief Cache models a cache.
 *
 */
class Cache {
public:
	/**
	 * default constructor
	 * \param sizeInBytes size of memory block in bytes
	 * \param associativity denotes the number of sets the cache is divided into
	 * \param lineSizeInBytes denotes the size in bytes of the data that is cached
	 * Given the fact that we assume Address type addresses (which are rounded
	 * up to 64bit), the lineSize determines the number of tag bits that are
	 * stored and thus the lookup strategy.
	 * Both the cache size and line size need to be powers of 2.
	 */
	Cache(uint32 sizeInBytes, 
		uint32 associativity = 1, 
		uint32 lineSizeInBytes = SIZE_256, 
		const CacheWritePolicy& writePolicy = CACHE_WRITE_ALLOCATE,
		uint32 nrOfVictimBuffers = 1);
	
	/**
	 * destructor 
	 */
	~Cache(void);

	// operators
	// none

	// selectors, use const to enforce non-modification
	/**
	 * \brief lookup an address to see in what state the cache is
	 */
	CacheLookupState lookup(const Address& address) const;
	/**
	 * \brief predicate test for precondition
	 */
	bool isPresent(const Address& address) const;
	/**
	 * \brief get the write policy
	 */
	CacheWritePolicy getWritePolicy() const { return m_writePolicy; }
	/**
	 * \brief check victim buffer availability
	 */
	uint32 getAvailableVictimBuffers() const { return m_nrOfVictimBuffers - m_victimLines.size(); }
	/**
	 * \brief get the line base address given a byte address
	 */
	Address getLineBaseAddress(const Address& address) const {
		return address & m_tagMask;
	}
	/**
	 * \brief get the line nr
	 */
	uint32 getLineNr(const Address& address) const {
		return (uint32)((address & m_lineMask) >> m_lineNrShift);
	}
	/**
	 * \brief get a pointer to the raw storage for the associated line
	 */
	const char* getCacheLine(const Address& address) const {
		return &m_pData[getLineNr(address)*m_lineSizeInBytes];
	}
	/**
	 * \brief get a pointer to the raw storage for the oldest victim
	 */
	const char* getOldestVictim() const {
		return m_victimLines.front();
	}
	/**
	 * \brief get the base address of the oldest victim
	 */
	Address getOldestVictimBaseAddress() const {
		return m_victimBaseAddresses.front();
	}

	/**
	 * \brief read a block from the cache
	 * \param baseAddress the base address of the memory block we want to read
	 * \param sizeInBytes size in bytes of the block we want to read
	 * \param pData pointer to the data block sufficiently large to hold the bytes to be read from memory
	 *
	 * The read request can address sub-line size elements, but not larger elements. 
	 */
	void read(const Address& baseAddress, uint32 sizeInBytes, void* pData) const;
	// modifiers
	/**
	 * \brief allocate a tag in the tag ram
	 */
	void allocate(const Address& address);
	/**
	 * \brief write a block to memory
	 * \param baseAddress the base address of the memory block we want to write
	 * \param sizeInBytes size in bytes of the block we want to write to memory
	 * \param pData pointer to the data block containing sufficient bytes (>sizeInBytes)
	 */
	void write(const Address& baseAddress, uint32 sizeInBytes, const void* pData);
	/**
	 * \brief take a dirty line and move it out into a victim buffer
	 */
	void evict(const Address& address);
	/**
	 * \brief retire the oldest victim
	 */
	void retireOldestVictim();
	/**
	 * \brief get a pointer to the raw storage for the associated line
	 */
	char* getCacheLine(const Address& address) {
		return &m_pData[getLineNr(address)*m_lineSizeInBytes];
	}

	/**
	 * \brief debug helper
	 */
	void dump(std::ostream& ostr) const;

protected:
	// member variables
	/**
	 * total size in bytes of the cache
	 *
	 * Why 32bits? Will it be reasonable that this model will be used
	 * when 32bits is no longer enough to represent caches? I felt
	 * it not reasonable so I selected 32bits. Future will tell... ETLO
	 */
	uint32				m_sizeInBytes;
	/**
	 * associativity of the cache
	 */
	uint32				m_associativity;
	/**
	 * line size in bytes
	 */
	uint32				m_lineSizeInBytes;
	/**
	 * the write policy of the cache
	 */
	CacheWritePolicy	m_writePolicy;
	/**
	 * the tag store containing the line state
	 */
	Address*			m_tags;
	/**
	 * the actual line map
	 */
	CacheLineState*		m_lineStates;
	/**
	 * calculated value of the size of the tag/lineState stores
	 */
	uint32				m_nrOfLines;
	/**
	 * the raw data store: this is a 1D array of bytes
	 * with the cache line offset calculation as a
	 * mechanism to address the first byte of each
	 * cache line.
	 */
	char*				m_pData;
	/**
	 * the mask used to separate the tag bits from the offset bits
	 */
	Address				m_tagMask;
	/**
	 * the mask used to calculate the line number in the cache
	 */
	Address				m_lineMask;
	/**
	 * the max number of victim buffers for this cache
	 */
	uint32				m_nrOfVictimBuffers;
	/**
	 * the actual victim buffer storage
	 */
	char*				m_victimBuffer;
	/**
	 * the victim buffer FIFO
	 */
	std::deque<char*>	m_victimLines;
	/**
	 * the victim buffer FIFO for base addresses
	 */
	std::deque<Address>	m_victimBaseAddresses;
	/**
	 * the shift amount of the line offset so that we obtain
	 * a line number
	 */
	uint32				m_lineNrShift;
	/**
	 * the mask used to calculate the offset in the line
	 */
	Address				m_offsetMask;

	// helpers



	// statistics
	mutable stillwater::automation::gauges::EventCount m_reads, m_writes;
	mutable stillwater::automation::gauges::EventCount m_bytesRead, m_bytesWritten;
};


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_CACHE_INCLUDED

