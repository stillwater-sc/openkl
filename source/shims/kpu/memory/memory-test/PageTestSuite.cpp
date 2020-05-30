/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/PageTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #10 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/PageTestSuite.cpp#10 $
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
#include "PageTestSuite.hpp"
// automatic registration with the test suite factory
CPPUNIT_TEST_SUITE_REGISTRATION( PageTestSuite );

using namespace std;

void PageTestSuite::setUp() {
}

void PageTestSuite::tearDown() {
}

void PageTestSuite::printTestSuiteId() {
	cout << "PageTestSuite" << endl;
}

void PageTestSuite::testConstruction() {
	try {
		Page* pPage1 = new Page(SIZE_4K);
		Page* pPage2 = new Page(*pPage1);
		Page page1(*pPage1);
		Page page2 = *pPage1;
		delete pPage1;
		delete pPage2;
	}
	catch (...) {
		CPPUNIT_ASSERT( false );
	}
}

void PageTestSuite::testPageSequencer() {
	uint64 base = SIZE_2K;
	uint64 blockSize = SIZE_16K;
	uint64 pageSize = SIZE_4K;
	PageSequencer page(base, base+blockSize, pageSize);
	uint64 pageAnchor = 0;
	uint64 nrOfPages = 1;	// be careful here: we start with the first page, and page.next() gets us to the next one
	while (!page.end()) {
#ifdef _DEBUG
		if (pageAnchor == 0) cout << endl;
		cout << "anchor = " << page.getAnchor() << ","
				<< "offset = " << page.startOffset() << ","
				<< "end    = " << page.endOffset() << endl;
#endif
		CPPUNIT_ASSERT(page.getAnchor() == pageAnchor++);
		if (page.startOffset() > 0) {
			CPPUNIT_ASSERT(page.startOffset() == SIZE_2K);	// assuming default page size of 4K
		}
		if (page.endOffset() < SIZE_4K) {
			CPPUNIT_ASSERT(page.endOffset() == SIZE_2K);
		}
		else {
			CPPUNIT_ASSERT(page.endOffset() == SIZE_4K);
		}
		page.next();
		++nrOfPages;

	}
	CPPUNIT_ASSERT( nrOfPages = blockSize/pageSize + 1 );
}

/**
 * the partial page writer test is going to write portions
 * of the page to some partial cover of a single page.
 * This tests the page anchor math of the write and
 * read methods
 */
void PageTestSuite::testPartialPageReadWrite() {
	Page page(SIZE_4K);
	uint32 w1;
	w1 = 0xA5A5A5A5;
	page.write(0*sizeof(w1), sizeof(w1), &w1);
	page.write(1*sizeof(w1), sizeof(w1), &w1);
	page.write(2*sizeof(w1), sizeof(w1), &w1);
	page.write(3*sizeof(w1), sizeof(w1), &w1);
	uint32 w2;
	page.read(3*sizeof(w1), sizeof(w2), &w2);	CPPUNIT_ASSERT( w1 == w2 );
	page.read(2*sizeof(w1), sizeof(w2), &w2);	CPPUNIT_ASSERT( w1 == w2 );
	page.read(1*sizeof(w1), sizeof(w2), &w2);	CPPUNIT_ASSERT( w1 == w2 );
	page.read(0*sizeof(w1), sizeof(w2), &w2);	CPPUNIT_ASSERT( w1 == w2 );
}

void PageTestSuite::testPageExceptions() {
	try {
		uint64 tooSmallAPage = 1 << (MIN_PAGE_SIZE_2LOGN-1);
		new Page(tooSmallAPage);	// this will throw a PageException
	}
	catch(PageException& e) {
#ifdef _DEBUG
		cout << endl << "Exception Type " << typeid(e).name() << endl;
		cout << "Properly caught PageException: " << e.what() << endl;
#else
		e.what();
#endif
	}
	try {
		uint64 tooBigAPage = 1 << (MAX_PAGE_SIZE_2LOGN+1);
		new Page(tooBigAPage);	// this will throw a PageException
	}
	catch(PageException& e) {
#ifdef _DEBUG
		cout << "Exception Type " << typeid(e).name() << endl;
		cout << "Properly caught PageException: " << e.what() << endl;
#else
		e.what();
#endif
	}
	try {
		uint64 notAPowerOfTwoPage = SIZE_4K+SIZE_2K;
		new Page(notAPowerOfTwoPage);	// this will throw a PageException
	}
	catch(PageException& e) {
#ifdef _DEBUG
		cout << "Exception Type " << typeid(e).name() << endl;
		cout << "Properly caught PageException: " << e.what() << endl << endl;
#else
		e.what();
#endif
	}
}


