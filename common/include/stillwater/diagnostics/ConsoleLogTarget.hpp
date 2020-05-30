/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/ConsoleLogTarget.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #2 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/ConsoleLogTarget.hpp#2 $
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
#ifndef CONSOLE_LOG_TARGET_INCLUDED
#define CONSOLE_LOG_TARGET_INCLUDED

#include "LogTarget.hpp"

NS_STILLWATER_DIAGNOSTICS_BEGIN

class ConsoleLogTarget : public LogTarget {
public:
	ConsoleLogTarget(void);
	~ConsoleLogTarget(void);
	std::ostream& operator<<(const std::string& message) {
		return std::cout << message;
	}
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // CONSOLE_LOG_TARGET_INCLUDED

