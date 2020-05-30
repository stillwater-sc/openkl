/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/statistics-test.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/11/19 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/statistics-test.cpp#4 $
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
// statistics-test.cpp : Defines the entry point for the console application.
//
// STL includes
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
// Platform specific includes
#ifdef WIN32
#include <tchar.h>
#else
#endif
// Stillwater includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>
// library includes
#include <stillwater/statistics.hpp>
#include "HistogramTestSuite.hpp"

int main(int argc, char* argv[])
{
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("statistics-test");
	logger.addLogTarget(new ConsoleLogTarget());
	logger.addLogTarget(new FileLogTarget());
	Logger::setActiveLogger(&logger);
	DIAG_INFO("statistics-test starting");

	int nrOfFailures = 0;

	// test histogram
	{
		HistogramTestSuite t;
		t.setUp();
		    t.printTestSuiteId();
		t.tearDown();

		t.setUp();
		    t.testConstruction();
		t.tearDown();
	}
	DIAG_INFO("statistics-test finished");

	return nrOfFailures;	// CMAKE defines success as 0
}

