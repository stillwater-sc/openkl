/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/Logger.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/Logger.hpp#4 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of
 * Stillwater Supercomputing, Inc . It may not be copied or duplicated in
 * any form, or disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef DIAGNOSTICS_LOGGER_INCLUDED
#define DIAGNOSTICS_LOGGER_INCLUDED

#include "LogTarget.hpp"

NS_STILLWATER_DIAGNOSTICS_BEGIN

class Logger {
public:
	Logger(const char* loggerName) : 
		m_bProvidedMissingLogTargetWarning(false), m_loggerName(loggerName) {
		getCreationDate();
		setActiveLogger(this);
	}
	virtual ~Logger();
	void addLogTarget(LogTarget* target) {
		try {
			// set up the logger id
			*target << "Logger -" << m_loggerName << "- started at " << m_today << std::endl;
			m_logTargets.push_back(target);
		} catch(...) {}
	}
	Logger& operator<<(const std::string& message) {
		if (m_logTargets.size() == 0) {
			if (!m_bProvidedMissingLogTargetWarning) {
				std::cerr << "No logging targets have been registered" << std::endl;
				std::cerr << "Please configure the logger with addLogTarget() before using" << std::endl;
				m_bProvidedMissingLogTargetWarning = true;
			}
		}
		else {
			for (size_t i = 0; i < m_logTargets.size(); i++) {
				*(m_logTargets[i]) << message << std::endl;
			}
		}
		return *this;
	}

	static Logger* getLogger() {
		if (m_pActive == NULL) {
			throw std::runtime_error("Logger has not been set up");
		}
		return m_pActive;
	}
	static void setActiveLogger(Logger* activeLogger) {
		m_pActive = activeLogger;
	}
protected:
	static Logger* m_pActive;
	bool m_bProvidedMissingLogTargetWarning;
	std::string m_loggerName;
	std::string m_today;
	std::vector<LogTarget*>	m_logTargets;
	// helper
	void getCreationDate();
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // DIAGNOSTICS_LOGGER_INCLUDED


