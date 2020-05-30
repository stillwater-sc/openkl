/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/HistogramTestSuite.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #1 $
 * Latest	:	$Date: 2006/10/29 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/statistics/statistics-test/HistogramTestSuite.cpp#1 $
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
#include <vector>
#include <stillwater/statistics.hpp>
#include "HistogramTestSuite.hpp"

using namespace std;
using namespace sw::statistics;

void HistogramTestSuite::setUp() {
}

void HistogramTestSuite::tearDown() {
}

void HistogramTestSuite::printTestSuiteId() {
	cout << "HistogramTestSuite" << endl;
}

#define NROFSAMPLES	1024

void HistogramTestSuite::testConstruction() {
	using Real = float;
	vector<Real>	dataSamples;

	for ( long i = 0; i < NROFSAMPLES; ++i ) {
		Real sample = Real(rand ());
		dataSamples.push_back (sample);
	}

	Histogram<Real>	h1 ("histogram_1");

	h1.analyze (/* autogenerate bin structure */ true, dataSamples, /* cumulative */ false, /* retain sample data */ true);
	cout << "Histogram of one random samples, and data set is retained (sampleSize == " << NROFSAMPLES << ")" << endl;
	h1.print (cout);

	dataSamples.clear ();
	for ( long i = 0; i < NROFSAMPLES; ++i ) {
		Real sample = Real(rand ());
		dataSamples.push_back (sample);
	}
	// add another data sample to an existing histogram
	// and reanalyze the union of the data sets
	h1.analyze (/* autogenerate bin structure */ true, dataSamples, /* cumulative */ false, /* retain sample data */ true);
	cout << "Union histogram of two random samples" << endl;
	h1.print (cout);

	Histogram<Real> h2 ("histogram_2");
	h2.analyze (/* autogenerate bin structure */ true, dataSamples, /* cumulative */ false, /* retain sample data */ false);
	cout << "Histogram of one random samples, but data set is not retained (sampleSize == 0)" << endl;
	h2.print (cout);
}
