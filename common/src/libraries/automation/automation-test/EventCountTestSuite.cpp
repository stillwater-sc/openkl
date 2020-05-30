/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/automation-test/EventCountTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/automation-test/EventCountTestSuite.cpp#4 $
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
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stillwater/statistics.hpp>
#include <stillwater/automation.hpp>
#include "EventCountTestSuite.hpp"

using namespace std;

void EventCountTestSuite::setUp() {
}

void EventCountTestSuite::tearDown() {
}

void EventCountTestSuite::printTestSuiteId() {
	cout << "EventCountTestSuite" << endl;
}

// define some gauges for the test
NS_STILLWATER_AUTOMATION_GAUGES_BEGIN
	EventCount e1("Proc-1", "e1", "clocks");
	EventCount e2("Proc-1/Cache", "e2", "misses");
	EventCount e3("Proc-1/Cache", "e3", "hits");
	EventCount e4("Proc-1/Cache", "e4", "references");
	EventCount a1("Proc-2", "e1", "clocks");
	EventCount a2("Proc-2/Cache", "e2", "misses");
	EventCount a3("Proc-2/Cache", "e3", "hits");
	EventCount a4("Proc-2/Cache", "e4", "references");
NS_STILLWATER_AUTOMATION_GAUGES_END

void EventCountTestSuite::testConstruction() {
	using namespace gauges;
	// when we are using the statistics
	// let's get in the habit of locking down
	// the registry. This is more to catch
	// bad code in the operators that might
	// create an anonymous EventCount object
	// that wants to register itself.
	EventCountSet::getInstance()->setLockDown(true);

	e1 = 10; ++e1; e1++; --e1; e1--;
	e2 = 3; e2 = e2*3; e2 = e2/gauges::EventCount(3);
	e3 = 7; 
	e4 = e3 + e2;	// you can do arithmetic with the objects

	assert(e1 == 10);
	assert(e2 ==  3);
	assert(e4 == e2 + e3);
}

#define NROFSAMPLES	1024

void EventCountTestSuite::testSampling() {
	using namespace gauges;
	EventCountSet::getInstance()->setLockDown(false);
	EventCount e5("e5", "samples", "no dimension");
	EventCountSet::getInstance()->setLockDown(true);
	cout << "Statistics Set before sampling:" << endl << EventCountSet::getInstance() << endl;
	for ( long i = 0; i < NROFSAMPLES; i++ ) {
		e5 = rand ();
		e5.sample();
	}
	std::vector<uint64_t>& samples = e5.getSampleData();
	assert(samples.size() == NROFSAMPLES);
	cout << "Statistics Set after sampling:" << endl << EventCountSet::getInstance() << endl;

	// The following is a more typical usage
	// make a summary stat out of it
	sw::statistics::SummaryStatistic<uint64_t> summary(e5.getName(), e5.getDimension());
	summary.analyze(e5.getSampleData());
	std::cout << summary << std::endl;
	summary.summaryStats(std::cout);

}
