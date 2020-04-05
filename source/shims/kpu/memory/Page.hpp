/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Page.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	5 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #16 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Page.hpp#16 $
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
#ifndef STILLWATER_PAGE_INCLUDED
#define STILLWATER_PAGE_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

/** 
	* \brief minimum page size in terms of 2logN bits
	*
	* Very small pages are useful for testing purposes
	* but the overhead of small pages can grow quickly.
	* Early experiments indicate that page sizes of 
	* SIZE_4K are absolutely minimum if you want to 
	* run decent size problems.
	*/
const uint8_t MIN_PAGE_SIZE_2LOGN = 5;	// 32 bytes
/**
	* \brief maximum page size in terms of 2logN bits
	*
	* Very large pages are also not good since it
	* compartmentalizes memory too much. The current
	* value of 16MBytes is quite arbitrary.
	*/
const uint8_t MAX_PAGE_SIZE_2LOGN = 24;	// 16MBytes

/**
	* \class PageException Page.hpp "Page.hpp"
	* \brief PageException captures all possible exceptions pertaining to page related failures
	*
	* Typically, in the code, you would use
	* the macro PAGE_EXCEPTION since it incorporates
	* the Context class to provide nice logging 
	* functionality.
	*/
class PageException : public std::runtime_error {
public:
	// we can use runtime_error instead of std::runtime_error
	// in this declaration since we derive from std::runtime_error
	// argument dependent symbol lookup of standard C++ will 
	// find the right symbol.
	explicit PageException(const std::string& message) : runtime_error(message) {}
};

// macro to throw a page exception
#define PAGE_EXCEPTION(feature) throw(PageException)*CREATE_CONTEXT_AND_CONSUME(ExceptionContext, "PAGE_EXCEPTION(" #feature ")")


/**
	* \brief memory is allocated on page granularity: Instances of class Page manage a single page of memory.
	*
	*/
class Page {
public:
	// constructors/destructors
	/**
		* \brief construct a page of size pageSizeInBytes
		* \param pageSizeInBytes size of the page in bytes
		*
		* We don't have a default constructor since we always need
		* information about the page size is. Typically, the
		* client that aggregates pages manages the page size.
		*/
	Page(uint64_t pageSizeInBytes) : m_pageSize2LogN(0), m_pData(NULL)
	{
		setPageSize2LogN(calcPageSize2LogN(pageSizeInBytes));
		m_pData = new char[(size_t)pageSizeInBytes];
	}

	/** 
		* \brief copy constructor: this is a deep copy of the Page's data
		* \param rhs Page reference to copy from
		*/
	Page(const Page& rhs) : m_pageSize2LogN(0), m_pData(NULL) {
		*this = rhs;
	}
	/**
		* \brief default destructor 
		*/
	~Page(void) {
		if (m_pData) {
			delete m_pData;
			m_pData = NULL;
		}
	}

	// operators
	/**
		* \brief assignment operator: this is a deep copy of the Page's data
		* \param rhs Page reference to copy from
		*/
	Page& operator=(const Page& rhs) {
		if (m_pData) delete m_pData;	// clean up old contents
		// do a deep copy of the data
		m_pData = new char[(size_t)rhs.getPageSizeInBytes()];
		m_pageSize2LogN = rhs.getPageSize2LogN();
		memcpy (m_pData, rhs.m_pData, (size_t)getPageSizeInBytes());
		return *this;
	}

	/**
		* \brief nice helper to go from bytes to 2logN bits
		* \param pageSizeInBytes size in bytes we want to know 2logN bits for
		* \return value of exponent e in 2^e=pageSizeInBytes
		* \throw PageException if pageSizeInBytes is not a power of 2
		*/
	static uint8_t calcPageSize2LogN(uint64_t pageSizeInBytes);

	// selectors, use const to unforce non-modifications
	/**
		* \brief return page size in 2LogN bits
		* \return value of exponent e in 2^e=pageSizeInBytes
		*/
	uint8_t getPageSize2LogN() const { return m_pageSize2LogN; }
	/**
		* \brief return page size in bytes
		* \return page size in bytes
		*/
	uint64_t getPageSizeInBytes() const { return ((uint64_t)1 << m_pageSize2LogN); }
	/**
		* \brief get a const char* to the raw buffer that holds the Page's data
		*/
	const char* getBuffer() const { return m_pData; }
	/**
		* \brief read a block from this memory page
		* \param offset in bytes of the beginning of the page
		* \param sizeInBytes size in bytes of the block that is the destination data for this read
		* \param pData pointer to the block to read from
		*/
	bool read(uint64_t offset, size_t sizeInBytes, void* pData) const;

	/**
		* \brief dump the contents of a page in typical hex byte format
		*/
	void dump(std::ostream& ostr) const;

	// modifiers

	/**
		* \brief write a block to this memory page
		* \param offset in bytes of the beginning of the page
		* \param sizeInBytes size in bytes of the block that is the source data for this write
		* \param pData pointer to the data block to write to
		*/
	bool write(uint64_t offset, size_t sizeInBytes, const void* pData);

protected:

	/**
		* \brief the page size parameter in 2LogN bits
		*
		* We are using 2LogN bits instead of size in bytes
		* because many of the computations revolve around
		* page anchors, which are obtained by shifting the
		* incoming address by m_pageSize2LogN.
		*/
	uint8_t m_pageSize2LogN;

	/**
		* \brief the page's actual storage area as a byte array
		*
		* We are using a byte array since you can do
		* pointer math on the pointer, which we'll
		* need to do the reads and writes to internal
		* regions of the page.
		*/
	char* m_pData;

	/**
		* \brief protected setter that also checks for validity
		* \param pageSize2LogN the bit position of the one and only non-zero bit
		*
		* page size is a power of two and it makes the
		* interface cleaner to make page size non-ambiguous.
		*/
	void setPageSize2LogN(uint8_t pageSize2LogN) {
		if (pageSize2LogN >= MIN_PAGE_SIZE_2LOGN && pageSize2LogN <= MAX_PAGE_SIZE_2LOGN) {
			m_pageSize2LogN = pageSize2LogN;
		}
		else {
			PAGE_EXCEPTION("INVALID PAGE SIZE: out of bounds")((int)pageSize2LogN)((int)MIN_PAGE_SIZE_2LOGN)((int)MAX_PAGE_SIZE_2LOGN);
		}
	}
};


/**
	* \class PageSequencer Page.hpp "Page.hpp"
	* \brief PageSequencer transforms a linear range into a set of page offsets
	*
	* The PageSequencer class implements an 
	* enumeration of pages given a linear
	* address range. This is an integral
	* operation of any write to and read from
	* a memory block.
	*
	* The usage model of this class is as follows:
	* assume the range to address is given by
	* [baseAddress,endAddress). Then the enumeration
	* of pages associated with this range is:
	* <pre>
	*		PageSequencer pages(baseAddress, endAddress, pageSizeInBytes);
	*		while (!page.end()) {
	*			... 
	*			do something with startOffset/endOffset
	*			...
	*			page.next();
	*		}
	* </pre>
	*/
class PageSequencer {
public:
	/**
	 * \brief initializing constructor
	 *
	 * set up a page sequence enumeration
	 * by defining the baseAddress, endAddress
	 * and the desired page blocking parameters.
	 */
	PageSequencer(uint64_t baseAddress, uint64_t endAddress, uint64_t pageSizeInBytes) :
		m_baseAddress(baseAddress), m_currentAddress(baseAddress), m_endAddress(endAddress),
			m_pageSizeInBytes(pageSizeInBytes) 
	{
		m_pageSize2LogN = Page::calcPageSize2LogN(pageSizeInBytes);
		m_pageAnchor = baseAddress >> m_pageSize2LogN;
		m_endPage = m_endAddress >> m_pageSize2LogN;
	}
	/**
	 * \brief empty destructor
	 */
	~PageSequencer() {}

	// selectors, use const to enforce non-modification
	/**
	 * test to see if we have exhausted the sequence
	 */
	bool end() const { return m_pageAnchor > m_endPage; }

	/**
	 * obtain the current page base address
	 */
	uint64_t getAnchor() const { return m_pageAnchor; }
	/**
	 * calculate the page starting offset
	 */
	uint64_t startOffset() const {
		return m_currentAddress - (m_pageAnchor << m_pageSize2LogN);
	}
	/**
	 * calculate the page end offset
	 */
	uint64_t endOffset() const {
		uint64_t endOffset = m_pageSizeInBytes;
		if (m_pageAnchor == m_endPage) {
			endOffset = m_endAddress - (m_pageAnchor << m_pageSize2LogN);
		}
		return endOffset;
	}
	// modifiers
	/**
	 * progress to the next page in the sequence
	 */
	void next() { 
		++m_pageAnchor; 
		// trick: once we have seen the first, potentially partial page
		// we can progress simply by the page anchor byte addresses
		// as the starting point of the subsequent page reads/writes
		m_currentAddress = m_pageAnchor << m_pageSize2LogN;
	}

protected:
	// member variables
	/**
	 * holds just the starting address of the sequence
	 * as a byte offset from the start of memory. It
	 * is necessary to compute the offset of the first
	 * page on which the linear range falls.
	 */
	uint64_t m_baseAddress;
	/**
	 * last address of the sequence as a byte offset
	 * from the start of memory. It is necessary to
	 * compute the offset of the last page on which
	 * the linear range falls.
	 */
	uint64_t m_endAddress;
	/**
	 * running base address that points to the
	 * start off the next block we are addressing
	 */
	uint64_t m_currentAddress;
	/**
	 * page size in bytes. used as the block sequence
	 * step size.
	 */
	uint64_t m_pageSizeInBytes;
	/**
	 * page size in 2logN bits
	 */
	uint8_t m_pageSize2LogN;
	/**
	 * page base address. This is used as an offset
	 * in the page data structure. It is updated
	 * on subsequent calls to next(), which will move
	 * the page base address up by 1.
	 */
	uint64_t m_pageAnchor;
	/**
	 * last page address of the sequence
	 */
	uint64_t m_endPage;

};


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_PAGE_INCLUDED


