/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/diagnostics/diagnostics-test/diagnostics-test.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/12/10 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/diagnostics/diagnostics-test/diagnostics-test.cpp#7 $
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

// STL includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#ifdef WIN32
// for Sleep()
#include <windows.h>
#else
// for usleep()
// having some trouble with other unistd.h files being found before this one
#include <unistd.h>
#endif


#ifndef WIN32
int Sleep(unsigned long milliSeconds) {
	std::chrono::timer loop_timer;
	const double seconds = milliSeconds/1000.0;
	for ( long loops = 0; loops < LONG_MAX && loop_timer.elapsed() < seconds; ++loops ) {}
	return 0;
}
#endif

// add the diagnostics header
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>

using namespace std;

int main(int argc, char* argv[]) {
	using namespace stillwater::diagnostics;
	// first, you need to get a hold of the logger
	Logger logger("mainLogger");
	// second, install a log target
	logger.addLogTarget(new ConsoleLogTarget());
	logger.addLogTarget(new FileLogTarget());
	Logger::setActiveLogger(&logger);

	int i = 4;
	DIAG_WARN(i < 5)(i);
	DIAG_ERROR(i < 0)(i);
	DIAG_FATAL(i < 1)(i);
	DIAG_INFO("diagnostics-test starting");
	DIAG_DEBUG("Debug this");

	auto startTime = chrono::steady_clock::now();
	TimeMonitor timeMonitor("myMonitor");
	timeMonitor.info(cout);
	timeMonitor.start("Loop1","1-main");
	for (int i = 0; i < 5; ++i) {
		Sleep(100);
		timeMonitor.start("subsection","Loop1");
		Sleep(200);
		timeMonitor.stop("subsection","Loop1");
		Sleep(100);
	}
	auto stopTime = chrono::steady_clock::now();
		cout << "global loop time: " << chrono::duration_cast<chrono::seconds>(stopTime - startTime).count() << "sec" << endl << flush;
	timeMonitor.stop("Loop1", "1-main");

	startTime = chrono::steady_clock::now();
	timeMonitor.start("Loop2","1-main");
	for (int i = 0; i < 10; ++i) {
		Sleep(100);
		timeMonitor.start("subsection", "Loop2");
		Sleep(300);
		timeMonitor.stop("subsection","Loop2");
		Sleep(100);
	}
	stopTime = chrono::steady_clock::now();
	cout << "global loop time: " << chrono::duration_cast<chrono::seconds>(stopTime - startTime).count() << "sec" << endl << flush;
	timeMonitor.stop("Loop2", "1-main");
	cout << timeMonitor;

	DIAG_INFO("diagnostics-test finished");
	return 0;
}

