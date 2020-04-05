/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/CacheTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/CacheTestSuite.cpp#6 $
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
#include "stdafx.h"
#include "CacheTestSuite.hpp"
// automatic registration with the test suite factory
CPPUNIT_TEST_SUITE_REGISTRATION( CacheTestSuite );

using namespace std;

void CacheTestSuite::setUp() {
}

void CacheTestSuite::tearDown() {
}

void CacheTestSuite::printTestSuiteId() {
	cout << "CacheTestSuite" << endl;
}

void CacheTestSuite::testConstruction() {
	try {

	}
	catch (...) {
		CPPUNIT_ASSERT( false );
	}
}
#define MAX_NR_OF_ELEMENTS 16

void CacheTestSuite::testReadAllocate() {
	uint64 memorySize	= SIZE_1K;
	uint64 pageSize		= SIZE_1K;
	uint64 startAddress	= 0x0000;
	Memory memory(memorySize, startAddress, pageSize, "memory_read_allocate");
	// fill memory with byte order pattern
	memory.setLogging(false);
	memory.initializeWithByteOrder(0,memorySize);
	memory.setLogging(true);

	// create the golden image defining the correct response
	uint32 blockSize = MAX_NR_OF_ELEMENTS*sizeof(uint64);
	char* golden = new char[blockSize];
	char cntr = 0;
	for (uint32 i = 0; i < blockSize; i++) {
		golden[i] = cntr++;
	}

	// set up the cache and receiving data structures
	uint32 cacheSize			 = SIZE_1K;
	uint32 lineSize				 = SIZE_64;
	uint32 associativity		 = 1;			// direct mapped
	CacheWritePolicy writePolicy = CACHE_WRITE_ALLOCATE;
	uint32 nrOfVictimBuffers	 = 1;
	Cache cache(cacheSize, associativity, lineSize, writePolicy, nrOfVictimBuffers);
	uint64 element[MAX_NR_OF_ELEMENTS];
	Address address = 0;
	Address stride = sizeof(uint64);
	// go read two cache lines worth of data using a stream
	// of consecutive uint64 sized reads. This will generate
	// two cache line fills from memory.
	for (uint32 elementNr = 0; elementNr < MAX_NR_OF_ELEMENTS; elementNr++) {
		Request* pReq = new Request(REQTYPE_READ, REQTARGET_MEMORY,address,sizeof(uint64));
		switch (cache.lookup(pReq->m_address)) {
		case CACHE_MISS_CLEAN:	// cache doesn't have the line and the conflict line is clean
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			break;
		case CACHE_MISS_MODIFIED:	// cache doesn't have the line and the conflict line is modified and thus needs to be saved
			cache.evict(pReq->m_address);
			cache.evict(pReq->m_address);	// allocates a victim buffer and places the dirty line into it
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			break;
		case CACHE_HIT_CLEAN:
		case CACHE_HIT_MODIFIED:
			// nothing to do before reading from the cache
			break;
		}
		cache.read (pReq->m_address,		// reads the data RAM
					pReq->m_payload.sizeInBytes(), 
					pReq->m_payload.getBuffer());
		element[elementNr] = *reinterpret_cast<uint64*>(pReq->m_payload.getBuffer());
		cout << hexint(element[elementNr]) << endl;
		delete pReq;
		// immediately compare to the golden image
//		DIAG_DEBUG(hexint(element[elementNr]))(hexint(((uint64*)golden)[elementNr]));
		CPPUNIT_ASSERT(element[elementNr] == ((uint64*)golden)[elementNr]);
		address += stride;
	}
}

void CacheTestSuite::testWriteAllocate() {
	uint64 memorySize	= SIZE_1K;
	uint64 pageSize		= SIZE_1K;
	uint64 startAddress	= 0x0000;
	Memory memory(memorySize, startAddress, pageSize, "memory_write_allocate");
	// fill memory with byte order pattern
	memory.setLogging(false);
	memory.initializeWithByteOrder(0,memorySize);
	memory.setLogging(true);

	// create the golden image defining the correct response
	Address address = 0;
	Address stride = sizeof(uint64);
	uint32 blockSize = MAX_NR_OF_ELEMENTS*sizeof(uint64);
	char* golden = new char[blockSize];
	char cntr = 0;
	for (uint32 i = 0; i < blockSize; i++) {
		golden[i] = cntr++;
	}
	uint64* goldenElements = reinterpret_cast<uint64*>(golden);

	// set up the cache and receiving data structures
	uint32 cacheSize			 = SIZE_1K;
	uint32 lineSize				 = SIZE_64;
	uint32 associativity		 = 1;			// direct mapped
	CacheWritePolicy writePolicy = CACHE_WRITE_ALLOCATE;
	uint32 nrOfVictimBuffers	 = 1;
	Cache cache(cacheSize, associativity, lineSize, writePolicy, nrOfVictimBuffers);
	// write the golden block into the cache
	for (uint32 elementNr = 0; elementNr < MAX_NR_OF_ELEMENTS; elementNr++) {
		Request* pReq = new Request(REQTYPE_WRITE, REQTARGET_MEMORY,address,
			sizeof(uint64),reinterpret_cast<uint8*>(&goldenElements[elementNr]));
		switch (cache.lookup(pReq->m_address)) {
		case CACHE_MISS_CLEAN:	// cache doesn't have the line and the conflict line is clean
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			break;
		case CACHE_MISS_MODIFIED:	// cache doesn't have the line and the conflict line is modified and thus needs to be saved
			// this test makes sense conceptually
			// but is necessary in this case since we evict
			// and then immediately retire the victim 
			// after the line read has been completed
			if (cache.getAvailableVictimBuffers() == 0) {
				// make room first
				memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
				cache.retireOldestVictim();
			}
			cache.evict(pReq->m_address);	// allocates a victim buffer and places the dirty line into it
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			// retire the victim write immediately
			memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
			cache.retireOldestVictim();
			break;
		case CACHE_HIT_CLEAN:
		case CACHE_HIT_MODIFIED:
			// nothing to do before reading from the cache
			break;
		}
		cache.write(pReq->m_address,		// reads the data RAM
					pReq->m_payload.sizeInBytes(), 
					pReq->m_payload.getBuffer());
		address += stride;
	}

	// read the golden block back out of the cache and compare
	uint64 element[MAX_NR_OF_ELEMENTS];
	// go read two cache lines worth of data using a stream
	// of consecutive uint64 sized reads. This will generate
	// two cache line fills from memory.
	address = 0;
	for (uint32 elementNr = 0; elementNr < MAX_NR_OF_ELEMENTS; elementNr++) {
		Request* pReq = new Request(REQTYPE_READ, REQTARGET_MEMORY,address,sizeof(uint64));
		switch (cache.lookup(pReq->m_address)) {
		case CACHE_MISS_CLEAN:	// cache doesn't have the line and the conflict line is clean
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			break;
		case CACHE_MISS_MODIFIED:	// cache doesn't have the line and the conflict line is modified and thus needs to be saved
			// this test makes sense conceptually
			// but is necessary in this case since we evict
			// and then immediately retire the victim 
			// after the line read has been completed
			if (cache.getAvailableVictimBuffers() == 0) {
				// make room first
				memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
				cache.retireOldestVictim();
			}
			cache.evict(pReq->m_address);	// allocates a victim buffer and places the dirty line into it
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			// retire the victim write immediately
			memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
			cache.retireOldestVictim();
			break;
		case CACHE_HIT_CLEAN:
		case CACHE_HIT_MODIFIED:
			// nothing to do before reading from the cache
			break;
		}
		cache.read (pReq->m_address,		// reads the data RAM
					pReq->m_payload.sizeInBytes(), 
					pReq->m_payload.getBuffer());
		element[elementNr] = *reinterpret_cast<uint64*>(pReq->m_payload.getBuffer());
		cout << hexint(element[elementNr]) << endl;
		delete pReq;
		// immediately compare to the golden image
//		DIAG_DEBUG(hexint(element[elementNr]))(hexint(((uint64*)golden)[elementNr]));
		CPPUNIT_ASSERT(element[elementNr] == ((uint64*)golden)[elementNr]);
		address += stride;
	}
}

void CacheTestSuite::testVictimBuffer() {
	// to test the victim buffer we are generating
	// a stream of writes that alias in the lines.
	// So our write stream will constantly hit the
	// same line in the cache that will evict the
	// modified write allocated line.
	uint32 cacheSize			 = SIZE_256;
	uint32 associativity		 = 1;
	uint32 lineSize				 = SIZE_64;
	CacheWritePolicy writePolicy = CACHE_WRITE_ALLOCATE;
	uint32 nrOfVictimBuffers	 = 1;
	Cache cache(cacheSize, associativity, lineSize, writePolicy, nrOfVictimBuffers);

	uint64 memorySize	= SIZE_1K;
	uint64 pageSize		= SIZE_1K;
	uint64 startAddress	= 0x0000;
	Memory memory(memorySize,startAddress,pageSize,"memory_victim_buffer");
	memory.setLogging(false);
		memory.initializeWithByteOrder(0,memorySize);
	memory.setLogging(true);

	// create the golden image defining the correct response
	uint32 blockSize = lineSize;
	char* golden = new char[blockSize];
	// we pick the first line of each page. By design, the Page size
	// is aligned on cacheline boundaries (simply by the virtue of the
	// the Page size to be a power of 2 and bigger than the line size
	// which is also a power of 2). This implies that the first line
	// is simply a the byte order relative to the page base address.
	// So stick that pattern in the golden image.
	char cntr = 0;
	for (uint32 i = 0; i < blockSize; i++) {
		golden[i] = cntr++;
	}
	// since we are just blasting default writes into the cache,
	// the default data associated with a write is bytes of value 0x55.
	// Since we are writing uint64's we'll have 8 0x55 bytes.
	// So overwrite the byte order pattern for just the first 8 bytes
	uint32 elementSize = (uint32)sizeof(uint64);
	for (uint32 i = 0; i < elementSize; i++) {
		golden[i] = (char)0x55;
	}

	RequestGenerator writes("aliased_write_stream");
	Address address = 0x0;
	Address stride = cacheSize;
	writes.initialize(REQTYPE_WRITE,address,stride,elementSize,(uint32)(memorySize/cacheSize));
	while (writes.next()) {
		Request* pReq = writes.generate();
		cout << *pReq << endl;
		switch(cache.lookup(pReq->m_address)) {
		case CACHE_MISS_CLEAN:
			//cout << "Clean cache miss" << endl;
			// this should only happen on the first access, with m_address == 0
			CPPUNIT_ASSERT(pReq->m_address == 0);
			cache.allocate(pReq->m_address);
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			break;
		case CACHE_MISS_MODIFIED:	// cache doesn't have the line and the conflict line is modified and thus needs to be saved
			//cout << "Miss on modified line" << endl;
			// this should happen on all subsequent writes
			CPPUNIT_ASSERT(pReq->m_address != 0);
			// this test makes sense conceptually
			// but is necessary in this case since we evict
			// and then immediately retire the victim 
			// after the line read has been completed
			if (cache.getAvailableVictimBuffers() == 0) {
				// make room first
				memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
				cache.retireOldestVictim();
			}
			cache.evict(pReq->m_address);	// allocates a victim buffer and places the dirty line into it
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			// retire the victim write immediately
			memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
			CPPUNIT_ASSERT(cache.getOldestVictimBaseAddress() == pReq->m_address - stride);
			for (uint32 i = 0; i < lineSize; i++) {
				CPPUNIT_ASSERT(cache.getOldestVictim()[i] == golden[i]);
			}
			cache.retireOldestVictim();
			break;
		case CACHE_HIT_CLEAN:
		case CACHE_HIT_MODIFIED:
			CPPUNIT_ASSERT(false);	// this should not happen with the stream we have chosen
			break;
		}
		cache.write(pReq->m_address,		// writes the data RAM
					pReq->m_payload.sizeInBytes(), 
					pReq->m_payload.getBuffer());
//		cache.dump(cout);
		delete pReq;
	}

}

/**
 * the purpose of the stream API test is
 * to showcase the usage model of the
 * cache and request generators APIs.
 * This test is the smallest example that
 * constitutes a complete subsystem.
 *
 */
void CacheTestSuite::testStreamApi() {
	uint32 cacheSize	= SIZE_1K;
	uint32 lineSize		= SIZE_64;
	Cache cache(cacheSize, 1, lineSize);		
	// a 64 byte cache line is matched against the memory burst blob
	// and would contain 8 double precision elements
	uint64 memorySize	= SIZE_16K;
	uint64 pageSize		= SIZE_4K;
	Memory memory(memorySize, 0, pageSize);

	// staged filling of memory. First I create a page
	// with a byte order pattern, and then I'll write
	// that to the pages in the Memory.
	// Why do I do it this way? As an example of functionality.
	Page rawData(pageSize);
	char cntr = 0;
	for(uint32 offset = 0; offset < pageSize; offset++) {
		rawData.write(offset,1,&cntr);
		cntr++;
	}
	// rawData.dump(cout);
	// now write that page into the pages of the Memory
	int pageNr = 0;
	memory.setLogging(false);
	for (Address pageAddress = 0; pageAddress < memorySize; pageAddress += pageSize) {
		memory.write(pageAddress, pageSize, rawData.getBuffer());
//		memory.dumpPageContents(cout,pageNr++);
	}
	memory.setLogging(true);

	// The test will use a read stream generator
	// to pull data out of the cache and stream
	// it into the PA
	RequestGenerator read_stream("cache_input");

	// A 1K cache contains 16x64byte lines or
	// 128x8byte double precision elements.
	// Assuming a 16x16 processor array, we would
	// be able to bring in 64 elements and receive
	// 64 elements. This would mean that we can
	// do a dense 64x64 BLAS L3 that would have
	// 4 elements per PE.
	// To avoid conflict misses we need to map
	// the addresses of the read and write blocks
	// in 512 byte aligned blocks. We'll put the
	// read on offset 0, and the write on offset 1.
	// For the overall array we need to find a
	// different mechanism since we would like
	// to use general memory objects and not have
	// to manage memory layouts explicitely.

	Address readAddress(0);
	Address readStride = lineSize;
	read_stream.initialize(REQTYPE_READ, readAddress, readStride, lineSize, lineSize/sizeof(real64));
	while (read_stream.next()) {
		Request* pReq = read_stream.generate();
		// we need to implement the cache behavior
		// since we want to reuse the API for TLM
		switch (cache.lookup(pReq->m_address)) {
		case CACHE_MISS_CLEAN:	// cache doesn't have the line and the conflict line is clean
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			// the above can be done in different ways. Here I obtain the
			// raw pointers that point into the cache data ram data structure
			// and I reach into memory and blast it right into the data
			// structure.
			// Another, more mechanistic way would be to set up a 
			// new Request data structure, hand that off to memory,
			// and then extract the data from the payload that is 
			// filled in. That will be the way the TLM model will
			// model the cache fill.
			break;
		case CACHE_MISS_MODIFIED:	// cache doesn't have the line and the conflict line is modified and thus needs to be saved
			// this test makes sense conceptually
			// but is necessary in this case since we evict
			// and then immediately retire the victim 
			// after the line read has been completed
			if (cache.getAvailableVictimBuffers() == 0) {
				// make room first
				memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
				cache.retireOldestVictim();
			}
			cache.evict(pReq->m_address);	// allocates a victim buffer and places the dirty line into it
			cache.allocate(pReq->m_address);	// updates the tag RAM
			// read the cacheline from memory and store it in the cache data ram
			memory.read(cache.getLineBaseAddress(pReq->m_address), 
				lineSize, cache.getCacheLine(pReq->m_address));
			// retire the victim write immediately
			memory.write(cache.getOldestVictimBaseAddress(),lineSize,cache.getOldestVictim());
			cache.retireOldestVictim();
			break;
		case CACHE_HIT_CLEAN:
		case CACHE_HIT_MODIFIED:
			// nothing to do before reading from the cache
			break;
		}
		cache.read (pReq->m_address,		// reads the data RAM
					pReq->m_payload.sizeInBytes(), 
					pReq->m_payload.getBuffer());
		delete pReq;
	}
}
