/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MemoryTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MemoryTestSuite.cpp#7 $
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
#include "MemoryTestSuite.hpp"
// automatic registration with the test suite factory
CPPUNIT_TEST_SUITE_REGISTRATION( MemoryTestSuite );

using namespace std;

void MemoryTestSuite::setUp() {
}

void MemoryTestSuite::tearDown() {
}

void MemoryTestSuite::printTestSuiteId() {
	cout << "MemoryTestSuite" << endl;
}

void MemoryTestSuite::testConstruction() {
	Memory* memory = new Memory(SIZE_1G, 0, SIZE_4K);
	delete memory;
}

/**
 * the singel page read/write test writes and reads
 * back a block of memory that fits within a single
 * page. It tests the basic page anchor/page allocation
 * scheme.
 *
 * The test writes the same block twice: once page
 * aligned, that is, the base address is the start
 * address of a page, and the second time not-page
 * aligned, where the base address maps into the 
 * middle of the page.
 */
void MemoryTestSuite::testSinglePageReadWrite() {
	// first write a MemoryObject to the first reserved range
	double data[] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0 };
	double receiver[] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	try {
		uint64 memSize = SIZE_16M;
		uint64 baseAddress = 0ll;
		uint64 endAddress = baseAddress + memSize;
		uint64 pageSize =  SIZE_1K;
		Memory memory(memSize, baseAddress, pageSize);
		// reserve one page starting at the second page
		uint64 base1 = SIZE_1K;
		if (!memory.reserve(base1, SIZE_1K)) {
			PAGE_EXCEPTION("reserve failed")(base1)(SIZE_1K);
		}

		memory.write(base1, sizeof(data), data);	// page aligned
		memory.write(base1+sizeof(data), sizeof(data), data); // not page aligned
		memory.dumpPages(cout);
		memory.read(base1, sizeof(receiver), receiver); // page aligned read
		for (int i = 0; i < ARRAY_SIZE(data); i++) {
			CPPUNIT_ASSERT(data[i] == receiver[i]);
		}
		// we don't need to clear the receiver
		// since we will get bytes from the
		// read deposited.
		// This second read will test if we can
		// read from the same page at a different
		// offset. This scenario brought out a bug.
		memory.read(base1+sizeof(data), sizeof(receiver), receiver); // not-page aligned read
		for (int i = 0; i < ARRAY_SIZE(data); i++) {
			CPPUNIT_ASSERT(data[i] == receiver[i]);
		}
		// release the block
		memory.release(base1);
	}
	catch (PageException& e) {
		cerr << "Caught PageException: " << e.what() << endl;
		throw;
	}
}

/**
 * the page straddling test is going to write
 * a block of memory that will straddle 
 * multiple pages. This will test the page
 * sequencing algorithms of the Memory object.
 */
void MemoryTestSuite::testPageStraddlingReadWrite() {
	try {
		uint64 memSize = SIZE_16M;
		uint64 baseAddress = 0ll;
		uint64 endAddress = baseAddress + memSize;
		uint32 pageSize = SIZE_1K;
		Memory memory(memSize, baseAddress, pageSize);
		// reserve 4 pages starting at the second page
		uint64 base1 = pageSize;
		if (!memory.reserve(base1, 4*pageSize)) {
			PAGE_EXCEPTION("reserve failed")(base1)(4*pageSize);
		}
		// create a block of memory two pages in size
		uint32 nrOfElements = 2*pageSize/sizeof(uint64);
		uint64* data = new uint64[nrOfElements];
		uint64* receiver = new uint64[nrOfElements];
		// write the offset in each element
		// so it is easy to test
		for (uint32 i = 0; i < nrOfElements; ++i) {
			data[i] = i;
			receiver[i] = 0xA5A5A5A5A5A5A5A5;
		}
		// write it to the memory starting on
		// the second half of the second page
		memory.write(base1+pageSize/2, 2*pageSize, data);
		memory.dumpPages(cout);
		memory.read(base1+pageSize/2, 2*pageSize, receiver); 
		for (uint32 i = 0; i < nrOfElements; i++) {
//			DIAG_DEBUG(i)(data[i])(receiver[i]);
			CPPUNIT_ASSERT(data[i] == receiver[i]);
		}
		// release the block
		memory.release(base1);
	}
	catch (PageException& e) {
		cerr << "Caught PageException: " << e.what() << endl;
		throw;
	}
}
