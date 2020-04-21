/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Memory.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #25 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Memory.hpp#25 $
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
#ifndef STILLWATER_MEMORY_INCLUDED
#define STILLWATER_MEMORY_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

// forward references
class Page;
class MemoryObject;
/** 
 * \class Memory Memory.hpp "Memory.hpp"
 * \brief Memory manages virtual memory storage for simulation models
 *
 * The memory only manages memory storage and a virtual mapping 
 * onto it. It does not manage the free and commit lists. 
 * For a working memory subsystem, a Memory and a 
 * MemoryAllocator need to collaborate.
 */
class Memory {

	typedef uint64_t							PageNumber;
	typedef std::map<Address, Address>			Range;
	typedef std::shared_ptr<Page>				PagePointer;
	typedef std::map<PageNumber, PagePointer>	PageMap;

public:
	/**
	 * default constructor Memory(uint64_t sizeInBytes)
	 * \param sizeInBytes size of memory block in bytes
	 * \param startAddress byte address of the first byte of the memory block in the overall memory map
	 * \param pageSizeInBytes size in bytes of the uniform page size for this memory
	 *
	 * The minimum information needed to create a
	 * memory is a size.
	 * The virtual memory block so created uses
	 * a linear address space. However, not all
	 * memory spaces need to be present: all is
	 * managed on demand.
	 */
	Memory(Address sizeInBytes, Address startAddress, uint64_t pageSizeInBytes, const std::string& instanceName = "Memory") : 
		m_instanceName(instanceName),
	    m_sizeInBytes(0), m_bLogging(true),
		m_startAddress(0),
		m_pageSizeInBytes(0), m_pageSize2LogN(0),
		m_reads(instanceName,"reads", "read ops"), m_writes(instanceName, "writes", "write_ops"),
		m_bytesRead(instanceName, "bytesRead", "bytes"), m_bytesWritten(instanceName, "bytesWritten", "bytes")
	{
		// double check to see if page size is a power of 2
		m_pageSize2LogN = Page::calcPageSize2LogN(pageSizeInBytes);
		// we only get here, if the page size is a power of two
		m_sizeInBytes = sizeInBytes; 
		m_startAddress = startAddress;
		m_pageSizeInBytes = pageSizeInBytes; 
		m_endAddress = startAddress + sizeInBytes;
	}
	
	/**
	 * destructor ~Memory()
	 */
	~Memory(void);

	// operators
	// none
	// potentially, operator[uint64_t] but not decided yet

	// selectors, use const to enforce non-modification
	/**
	 * \brief obtain the first address of the memory range
	 * \return uint64_t base memory address
	 */
	Address getStartAddress() const { return m_startAddress; }
	/**
	 * \brief obtain the last address of the memory range
	 * \return uint64_t end memory address
	 */
	Address getEndAddress() const { return m_endAddress; }
	/**
	 * \return uint64_t size in bytes
	 */
	uint64_t getSizeInBytes() const { return m_sizeInBytes; }
	/**
	 * \return uint64_t page size in bytes
	 */
	uint64_t getPageSizeInBytes() const { return m_pageSizeInBytes; }

	// modifiers
	void setLogging(bool bLogging) { m_bLogging = bLogging; }
	/**
	 * \param baseAddress base address of the block to reserve
	 * \param sizeInBytes size in bytes
	 * \return true if successful, false otherwise
	 */
	bool reserve(Address baseAddress, uint64_t sizeInBytes);

	/**
	 * \param baseAddress base address of the block to release
	 * \return true if found and released
	 */
	bool release(Address baseAddress);
	
	/**
	 * \brief read a block from memory
	 * \param baseAddress the base address of the memory block we want to read
	 * \param sizeInBytes size in bytes of the block we want to read
	 * \param pData pointer to the data block sufficiently large to hold the bytes to be read from memory
	 *
	 * The Memory object uses a block oriented
	 * request interface. 
	 */
	void read(Address baseAddress, uint64_t sizeInBytes, void* pData) const;

	/**
	 * \brief write a block to memory
	 * \param baseAddress the base address of the memory block we want to write
	 * \param sizeInBytes size in bytes of the block we want to write to memory
	 * \param pData pointer to the data block containing sufficient bytes (>sizeInBytes)
	 */
	void write(Address baseAddress, uint64_t sizeInBytes, const void* pData);

	/**
	 * \brief debug helper to fill the memory with a byte order
	 * Since you can't really do this for large memories, the
	 * parameters of the method help you confine the range that
	 * is filled. So this method still makes sense for a very 
	 * large memory since you may want to fill just a small region
	 * of it with a well defined pattern.
	 */
	void initializeWithByteOrder(const Address& startAddress, const Address& endAddress);

	/**
	 * \brief debug helper to write the complete memory contents to an ostream
	 * \param ostr reference to the ostr to write to
	 */
	void dumpMemoryContents(std::ostream& ostr) const;

	/**
	 * \brief debug helper to write the page data structures to an ostream
	 * \param ostr reference to the ostr to write to
	 */
	void dumpPages(std::ostream& ostr) const;

	/**
	 * \brief debug helper to write the contents of a page to an ostream
	 */
	void dumpPageContents(std::ostream& ostr, const PageNumber& pageNr) const;

	static void dumpBufferInHex(std::ostream& ostr, const char* buffer, uint32_t size);

protected:
	// member variables
	/**
	 * \brief instance name of this object
	 * This variable is mostly to disambiguate statistics and parameters
	 */
	std::string	m_instanceName;
	/**
	 * \brief cross-cutting log control
	 *
	 * Since the Memory object is so central in the 
	 * overall modeling effort, we need fine grained
	 * logging control on this object. 
	 */
	bool		m_bLogging;
	/**
	 * \brief the page size parameter. 
	 *
	 * We are caching it in Memory so that 
	 * we can manage it for all
	 * the Pages that will be allocated on behalf
	 * of this memory block.
	 *
	 * We are caching the 2logN number since it
	 * allows us to quickly calculate page anchors.
	 */
	uint8_t m_pageSize2LogN;
	/**
	 * \brief page size in bytes. 
	 *
	 * We are caching it
	 * in Memory so that we can manage it for all
	 * the Pages that will be allocated on behalf
	 * of this memory block.
	 *
	 * We are caching the page size in bytes to
	 * allow us to calculate byte addresses when
	 * we stride by page size.
	 */
	uint64_t m_pageSizeInBytes;

	// helpers
	/**
	 * \brief test to check if the memory range requested is
	 * covered by the allocated pages. 
	 * \param baseAddress starting byte address of the range
	 * \param endAddress ending byte address of the range
	 *
	 * This is a run-time
	 * check to test if we are reading/writing to 
	 * properly initialized memory ranges.
	 */
	bool isCovered(uint64_t baseAddress, uint64_t endAddress) const;

	// member variables
	/**
	 * \brief start address of this memory block
	 */
	uint64_t m_startAddress;
	/**
	 * \brief end address of this memory block
	 */
	uint64_t m_endAddress;
	/**
	 * \brief total memory block size in bytes
	 */
	uint64_t m_sizeInBytes;

	/**
	 * \brief reserved memory ranges
	 * By design: you can't read/write
	 * to memory that hasn't been reserved. It is
	 * an extra check to catch addressing failures.
	 */
	Range m_ranges;

	/**
	 * \brief The collection of pages that have been written to
	 */
	PageMap m_pages;

	// statistics
	mutable stillwater::automation::gauges::EventCount m_reads, m_writes;
	mutable stillwater::automation::gauges::EventCount m_bytesRead, m_bytesWritten;
};


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_MEMORY_INCLUDED


