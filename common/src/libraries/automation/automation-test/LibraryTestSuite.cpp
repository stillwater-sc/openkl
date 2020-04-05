/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/automation-test/LibraryTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	27 October 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #8 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/automation-test/LibraryTestSuite.cpp#8 $
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
#include <iostream>
#include <iomanip>
#include <variant>
#include <cassert>
// Stillwater automation 
#include <stillwater/automation.hpp>
#include "LibraryTestSuite.hpp"
// automatic registration with the test suite factory


using namespace std;

void LibraryTestSuite::setUp() {
}

void LibraryTestSuite::tearDown() {
}

void LibraryTestSuite::printTestSuiteId() {
	cout << "LibraryTestSuite" << endl;
}

// the requirements for the parameter space library is to
// provide a global parameter registration process so that
// configuration of the sw component can be automated.
// Parameters are used in different ways, for example:
//	- as member variables in a class
//	- as parameters in the constructor
//	- as setters/getters
//	- global/static variables
//
// For automation, the parameter needs to be resettable,
// that is, the parameter must be able to be changed
// and the change must properly reconfigure the object.
// Since many parameters setup a complex data structure,
// such as a memory system, for which parameters cannot
// be modified on the fly, we need to define some protocol 
// along which the automation proceeds.
// However, I don't want to give up yet on parameters
// which could be changed on the fly.
//
// For parameters that require complex data structure
// construction, the most robust way to work with them
// is at program startup time. In this case, the 'program'
// becomes a function call, and the automation protocol
// is simply:
//	while (!notDone) {
//		select next point in parameter space
//		resultSet = program();
//	}
//
// In the SystemC case, this works as long as the elaboration
// network is constant. So if a parameter pertains to changes
// in the elaboration network, we need to make the enumeration
// protocol external. Otherwise stated, the 'program' is an
// executable, and the parameter space configuration set is
// a configuration file.

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN
	// define the knobs of the model

	// I am using typed values to make to populate the param variant
	// with an explicit type

	// define a parameter
	uint16_t min1 = 14; // 2^14 = 16KBytes
	uint16_t nominal1 = 18; // 2^18 = 256KBytes
	uint16_t max1 = 21; // 2^21 = 2MBytes
	uint16_t step1 = 1; // double/half in size each step
	Parameter cacheSize("module1", "cacheSize", "2LogN", min1, nominal1, max1, step1);

	// define a uint32 parameter
	uint32_t min2 = 25000; // psec
	uint32_t nominal2 = 40000; // psec
	uint32_t max2 = 250000; // psec
	uint32_t step2 = 5000; // psec	
	Parameter latency("module2", "latency", "psec", min2, nominal2, max2, step2);
NS_STILLWATER_AUTOMATION_KNOBS_END

NS_STILLWATER_AUTOMATION_GAUGES_BEGIN
	// define the gauges of the model
	// we may want to define a macro so that we have the 
	// same name as the variable name
	CREATE_GAUGE("Default",m1Clks,"clks");
	CREATE_GAUGE("Default",m2Clks,"clks");
NS_STILLWATER_AUTOMATION_GAUGES_END

class Module1 {
public:
	Module1() {
		m_pCacheSize = knobs::ParameterSet::getInstance()->query("module1::cacheSize");
	}
	void run() {
		std::cout << "Module1's parameter is: " << m_pCacheSize << std::endl;
		gauges::m1Clks++;
	}

protected:
	knobs::Parameter* m_pCacheSize;
};

class Module2 {
public:
	Module2() {
		m_pLatency = knobs::ParameterSet::getInstance()->query("module2::latency");
	}
	void run() {
		std::cout << "Module2's parameter is: " << m_pLatency << std::endl;
		gauges::m2Clks++;
	}
protected:
	knobs::Parameter* m_pLatency;
};

class Model {
public:
	Model(const char* name) : m_name(name) {}
	void run(int iterationNr) {
		cout << "Iteration " << iterationNr << endl;
		m_module1.run();
		m_module2.run();
	}
protected:
	std::string m_name;
	Module1	m_module1;
	Module2 m_module2;
};

void LibraryTestSuite::testConstruction() {
	try {
		// create a little program:
		Model testModel("testModel");

		// using the above basic blocks creates the stylistic 
		// behavior of a separate in-process thread that will contain
		// the parameter space enumerate.

		// let's create an enumerator to cycle
		// through a subset of the parameter space
		knobs::ParameterSet* pParamSet = knobs::ParameterSet::getInstance();
		knobs::ParameterSpaceEnumerator enumerator(pParamSet);		// this will lock down the Registry

		// First let's see what we have in the parameter set
		enumerator.listParameterSet(std::cout);
		cout << "Statistics Set:" << endl << gauges::EventCountSet::getInstance() << endl;

		cout << "First test using cumulative gauges counts" << endl;
		// set up a subset to enumerate
		// this subrange can be non-exclusive in the sense that its
		// extremes do not need to be elements of the parameter's range.
		// If they are not, we'll take the closest valid value in the 
		// parameter's range. For minimums, this would be the next value up,
		// and for maximums the next value down.

		// define a range:
		knobs::ParameterRange latencyRange("module2.latency", uint32_t(25000l), uint32_t(35000l));	// [25ns, 50ns) specified in terms of psec
		enumerator.addRange(latencyRange);
		// and now enumerate that set
		cout << "Enumerating subset of the latency parameter of module 2" << endl;
		enumerator.listEnumerationSet(cout);
		enumerator.reset();
		int iterationNr = 1;
		gauges::EventCountSet::reset();
		testModel.run(iterationNr++);
		while(enumerator.next()) {	// this side effects all the parameters that were registered with addRange()
			testModel.run(iterationNr++);
		}
		cout << "\nFinal Result statistics" << endl << gauges::EventCountSet::getInstance() << endl;

		cout << "Second test resetting the gauges set each time around the iteration" << endl;
		// reset the ranges
		enumerator.reset();  iterationNr = 1;
		gauges::EventCountSet::reset();
		testModel.run(iterationNr++);
		cout << "Result statistics" << endl << gauges::EventCountSet::getInstance() << endl;
		// and do it again
		while(enumerator.next()) {
			gauges::EventCountSet::reset();
			testModel.run(iterationNr++);
			cout << "Result statistics" << endl << gauges::EventCountSet::getInstance() << endl;
		}
		cout << "\nFinal Result statistics" << endl << gauges::EventCountSet::getInstance() << endl;
		// once the enumerator goes out of scope, the Registry is unlocked
	}
	catch (...) {
		assert( false );
	}
}

void LibraryTestSuite::testValueRetrieval() {
	try {
		knobs::ParameterSet::getInstance()->clear();
//		ParameterSet::getInstance()->setLockDown(false);	// no need to to this explicitely since all tests should leave the Registry open when the last enumerate exists
		uint16_t min(1);
		uint16_t nominal(5);
		uint16_t max(10);
		uint16_t step(1);
		knobs::Parameter param("default", "param", "dodas", min, nominal, max, step);
		assert(std::get<uint16_t>(param.getMin()) == min);
		assert(std::get<uint16_t>(param.getNominal()) == nominal);
		assert(std::get<uint16_t>(param.getMax()) == max);
	}
	catch (std::runtime_error& e) {
		// when the Registry is in lock down mode this exception can be thrown
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	catch (...) {
		assert( false );
	}
}
