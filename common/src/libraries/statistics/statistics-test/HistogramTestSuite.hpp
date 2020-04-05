/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/HistogramTestSuite.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #1 $
 * Latest	:	$Date: 2006/10/29 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/HistogramTestSuite.hpp#1 $
 *
 * Organization:
 *		Stillwater Supercomputing Solutions
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing Solutions. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing Solutions.
 */
#pragma once

class HistogramTestSuite {
public:
	HistogramTestSuite(void) {}
	~HistogramTestSuite(void) {}

	void setUp();

	void tearDown();

	// the individual tests
	void printTestSuiteId();
	void testConstruction ();

protected:
	
};
