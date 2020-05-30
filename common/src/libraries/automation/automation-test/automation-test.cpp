/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/automation-test/automation-test.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2010/01/15 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/automation-test/automation-test.cpp#6 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of
 * Stillwater Supercomputing, Inc. It may not be copied or duplicated in
 * any form, or disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */

// STL includes
#include <iostream>
#include <iomanip>
#include <map>
// Platform specific
#ifdef WIN32
#include <tchar.h>
#else
#endif
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
// diagnostic services
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>
// the automation library includes
#include <stillwater/automation.hpp>

#include "EventCountTestSuite.hpp"

int main(int argc, char* argv[])
{
	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("automation-test");
	logger.addLogTarget(new ConsoleLogTarget());
	DIAG_INFO("automation-test starting");

	int nrFailures = 0;

	using namespace gauges;
	cout << "Statistics Set before start of test suite:" << endl << EventCountSet::getInstance() << endl;
	cout << endl;

	// test the event counting functionality
	{
	    EventCountTestSuite t;
	    t.setUp();
	        t.printTestSuiteId();
	    t.tearDown();
	    t.setUp();
	        t.testConstruction();
	    t.tearDown();
	    t.setUp();
	        t.testSampling();
	    t.tearDown();
    }

	DIAG_INFO("automation-test finished");
	return nrFailures;	// for CTEST, 0 is success
}

