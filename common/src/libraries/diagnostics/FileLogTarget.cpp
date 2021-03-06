/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/diagnostics/FileLogTarget.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/diagnostics/FileLogTarget.cpp#4 $
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
#include <fstream>
#include <string>
// BOOST includes
// none
// STILLWATER includes
// none
// DIAGNOSTICS library includes
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#include <stillwater/diagnostics/FileLogTarget.hpp>

NS_STILLWATER_DIAGNOSTICS_BEGIN

FileLogTarget::FileLogTarget(const char* fileName)
: m_fileName(fileName) {
	m_file.open(fileName);
	if (m_file.is_open()) {
		std::cerr << "Successfully opened diagnostics log at: " 
			<< m_fileName << std::endl;
	}
	else {
		std::cerr << "Could not open diagnostics log at: "
			<< m_fileName << std::endl;
	}
}

FileLogTarget::~FileLogTarget(void) {
	m_file.flush();
	m_file.close();
	std::cerr << "Closed diagnostics log: " 
		<< m_fileName << std::endl;
}

NS_STILLWATER_DIAGNOSTICS_END

