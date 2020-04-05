/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/diagnostics/ConsoleLogTarget.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/diagnostics/ConsoleLogTarget.cpp#5 $
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
#include <string>
// BOOST includes
// none
// STILLWATER includes
// none
// DIAGNOSTICS library includes
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#include <stillwater/diagnostics/ConsoleLogTarget.hpp>

NS_STILLWATER_DIAGNOSTICS_BEGIN

ConsoleLogTarget::ConsoleLogTarget(void)
{
}

ConsoleLogTarget::~ConsoleLogTarget(void) {
	std::cout.flush();
}

NS_STILLWATER_DIAGNOSTICS_END

