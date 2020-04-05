/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/memory-test.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #8 $
 * Latest	:	$Date: 2007/11/19 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/memory-test.cpp#8 $
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
// memory-test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int main(int argc, char* argv[])
{
	CppUnit::TextUi::TestRunner runner;

	// First, we retreive the instance of the TestFactoryRegistry:
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	// obtain and add a new TestSuite created by the TestFactoryRegistry 
	// that contains all the test suite registered using CPPUNIT_TEST_SUITE_REGISTRATION().
	runner.addTest( registry.makeTest() );

	// set up the logger
	using namespace stillwater::diagnostics;
	Logger logger("memory-test");
	logger.addLogTarget(new ConsoleLogTarget());
	bool bSuccess = runner.run ("", false);

	return !bSuccess;	// CMAKE defines success as 0
}

