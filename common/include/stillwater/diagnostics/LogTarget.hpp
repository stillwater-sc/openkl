/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/LogTarget.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/LogTarget.hpp#4 $
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
#ifndef LOG_TARGET_INCLUDED
#define LOG_TARGET_INCLUDED

NS_STILLWATER_DIAGNOSTICS_BEGIN

class LogTarget {
public:
	LogTarget() {};
	virtual ~LogTarget() {};
	virtual std::ostream& operator<<(const std::string& message) { return std::cerr << message; }
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // LOG_TARGET_INCLUDED

