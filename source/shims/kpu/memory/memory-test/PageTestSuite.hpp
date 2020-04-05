/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/PageTestSuite.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/PageTestSuite.hpp#6 $
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

class PageTestSuite : public CppUnit::TestFixture {
public:
	PageTestSuite(void) {}
	~PageTestSuite(void) {}

	void setUp();

	void tearDown();

	// the test suite definition
	// First, we declare the suite, passing the class name to the macro: 
	CPPUNIT_TEST_SUITE( PageTestSuite );
	// The suite created by the static suite() method is 
	// named after the class name. Then, we declare each 
	// test case of the fixture: 
	CPPUNIT_TEST( printTestSuiteId );
	CPPUNIT_TEST( testConstruction );
	CPPUNIT_TEST( testPageSequencer );
	CPPUNIT_TEST( testPartialPageReadWrite );
	CPPUNIT_TEST( testPageExceptions );
	// Finally, we end the suite declaration: 
	CPPUNIT_TEST_SUITE_END();

	// the individual tests
	void printTestSuiteId();
	void testConstruction ();
	void testPageSequencer();
	void testPartialPageReadWrite();
	void testPageExceptions();

protected:
	std::vector<Page*> m_pages;

};
