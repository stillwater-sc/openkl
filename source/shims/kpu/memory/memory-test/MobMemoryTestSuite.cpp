/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MobMemoryTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MobMemoryTestSuite.cpp#7 $
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
#include "MobMemoryTestSuite.hpp"
// automatic registration with the test suite factory
CPPUNIT_TEST_SUITE_REGISTRATION( MobMemoryTestSuite );

using namespace std;

void MobMemoryTestSuite::setUp() {
}

void MobMemoryTestSuite::tearDown() {
}

void MobMemoryTestSuite::printTestSuiteId() {
	cout << "MobMemoryTestSuite" << endl;
}


void MobMemoryTestSuite::testConstruction() {
	MobMemory* mobs = new MobMemory(SIZE_1G, 0, SIZE_4K);
	delete mobs;
}

void MobMemoryTestSuite::testReadWrite() {
	uint64 memSize = SIZE_16M;
	uint64 baseAddress = 0ll;
	uint64 endAddress = 0ll;
	endAddress = baseAddress + memSize;
	MobMemory memory(memSize, baseAddress, SIZE_4K);

	// reserve a couple 1M blocks
	uint64 base1 = SIZE_1M;
	if (!memory.reserve(SIZE_1M, SIZE_1M)) {
		throw "trouble reserving a memory block";
	}
	uint64 base2 = 5*SIZE_1M;
	if (!memory.reserve(base2, SIZE_1M)) {
		throw "trouble reserving the second memory block";
	}

	// first write a MemoryObject to the first reserved range
	double data[] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0 };
	try {
		MemoryObject mob(ARRAY_SIZE(data), MET_REAL64, data);
		memory.write(base1, mob);
		memory.write(base2, mob);
		memory.dumpPages(cout);
		MemoryObject receivingMob(sizeof(data)/sizeof(data[0]), MET_REAL64);
		memory.read(base1, receivingMob);
		// we know we have MET_REAL64 entries
		double* pData = (double*)receivingMob.getConstBlobPtr();
		for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
			CPPUNIT_ASSERT(data[i] == pData[i]);
		}
		// release the blocks
		memory.release(base1);
		memory.release(base2);
	}
	catch (PageException& e) {
		cerr << "Caught PageException: " << e.what() << endl;
		throw;
	}
}


