/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MobMemoryTestSuite.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2007/04/27 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/MobMemoryTestSuite.hpp#3 $
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
#pragma once

class MobMemoryTestSuite : public CppUnit::TestFixture {
public:
	MobMemoryTestSuite(void) {}
	~MobMemoryTestSuite(void) {}

	void setUp();

	void tearDown();

	// the test suite definition
	// First, we declare the suite, passing the class name to the macro: 
	CPPUNIT_TEST_SUITE( MobMemoryTestSuite );
	// The suite created by the static suite() method is 
	// named after the class name. Then, we declare each 
	// test case of the fixture: 
	CPPUNIT_TEST( printTestSuiteId );
	CPPUNIT_TEST( testConstruction );
	CPPUNIT_TEST( testReadWrite );
	// Finally, we end the suite declaration: 
	CPPUNIT_TEST_SUITE_END();

	// the individual tests
	void printTestSuiteId();
	void testConstruction ();
	void testReadWrite();

protected:
	
};
