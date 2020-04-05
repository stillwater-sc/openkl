/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/FileLogTarget.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #2 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/FileLogTarget.hpp#2 $
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
#ifndef FILE_LOG_TARGET_INCLUDED
#define FILE_LOG_TARGET_INCLUDED

// inherited class definitions
#include "LogTarget.hpp"

NS_STILLWATER_DIAGNOSTICS_BEGIN

class FileLogTarget : public LogTarget {
public:
	FileLogTarget(const char* fileName = "diagnostics.log");
	~FileLogTarget(void);
	std::ostream& operator<<(const std::string& message) {
		return (m_file << message);
	}
protected:
	std::string m_fileName;
	std::ofstream m_file;
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // FILE_LOG_TARGET_INCLUDED
