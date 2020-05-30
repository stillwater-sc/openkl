/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/diagnostics/Logger.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/diagnostics/Logger.cpp#5 $
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
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>
// BOOST includes
// none
// STILLWATER includes
// none
// DIAGNOSTICS library includes
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#include <stillwater/diagnostics/Logger.hpp>

NS_STILLWATER_DIAGNOSTICS_BEGIN

Logger* Logger::m_pActive = NULL;

Logger::~Logger(void)
{
	for (size_t i = 0; i < m_logTargets.size(); i++) {
		delete m_logTargets[i];
	}
}

void Logger::getCreationDate() {
#ifdef OLD_C_STYLE
	// unsafe
	struct tm *today;
    time_t ltime;

	char datestr[80];
	char timestr[80];

	time( &ltime );
	today = localtime_s( &ltime );
	sprintf(datestr, "%02d%02d%04d",
		today->tm_mon + 1,
		today->tm_mday,
		today->tm_year + 1900);
	sprintf(timestr, "%02d%02d%02d",
		today->tm_hour,
		today->tm_min,
		today->tm_sec);
	m_today = std::string(datestr) + std::string("_") + std::string(timestr);
#endif
	time_t now = time(0);
	tm  ltm;
	localtime_s(&ltm, &now);
	std::string datestr;
	{
		std::stringstream ss;
		ss.fill('0');
		ss << std::setw(2) << ltm.tm_mon + 1
			<< std::setw(2) << ltm.tm_mday
			<< std::setw(4) << ltm.tm_year + 1900;
		datestr = ss.str();
	}
	std::string timestr;
	{
		std::stringstream ss;
		ss.fill('0');
		ss << std::setw(2) << ltm.tm_hour
			<< std::setw(2) << ltm.tm_min
			<< std::setw(2) << ltm.tm_sec;
		timestr = ss.str();
	}
	m_today = datestr + std::string("_") + timestr;
}

NS_STILLWATER_DIAGNOSTICS_END
