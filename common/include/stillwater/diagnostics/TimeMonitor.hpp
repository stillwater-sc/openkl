/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics/TimeMonitor.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics/TimeMonitor.hpp#5 $
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
#ifndef TIME_MONITOR_INCLUDED
#define TIME_MONITOR_INCLUDED

#include <cstdint>
#include <chrono>
using namespace std;
using namespace std::chrono;
using timeSample = chrono::time_point<chrono::steady_clock>;

// Forward Declarations
// none

NS_STILLWATER_DIAGNOSTICS_BEGIN


/**
 * \class TimeSegmentData
 * private data structure to maintain time segment data
 */
struct TimeSegmentData {
	TimeSegmentData () :
		m_cummulativeTime(0),
		m_nrOfUpdates(0),
		m_bActive(false)
	{}

	/**
	 * @return elapsed time in micro-seconds
	 */
	 //chrono::duration<uint64_t, chrono::microseconds> 
	long long elapsed() const {
		timeSample now = steady_clock::now();
		return chrono::duration_cast<chrono::microseconds>(now - m_startTime).count();
	}

	timeSample	m_startTime;
	bool		m_bActive;
	uint64_t	m_nrOfUpdates;
	long long	m_cummulativeTime;
};

/**
 * typedef for the aggregated map
 */
typedef std::map< std::pair<std::string, std::string>, TimeSegmentData> TimeSegmentMap;

/**
 * \class TimeMonitor TimeMonitor.hpp
 * TimeMonitor is used to track elapsed time of code
 * segments. It usage is extremely simple:
 * \pre
 * ...
 * TimeMonitor timeMonitor("monitorName");
 * timeMonitor.start("Solver", "mySegmentName");
 *	... your segment that you want to measure
 * timeMonitor.stop(Solver", "mySegmentName");
 *
 */
class TimeMonitor : public TimeSegmentMap {
public:

	/**
	 * Default constructor always needs a name
	 *
	 * \param name is the name of the monitor
	 */
	TimeMonitor(const std::string& name) : m_name(name), m_totalTime(0) {}

	/**
	 * virtual destructor; you may derive from this class
	 */
	virtual ~TimeMonitor() {};

	// operators
	// none

	// modifiers
	/**
	 * clear contents
	 */
	void clear();

	/**
	 * Start monitoring the elepsed time for named event \p name.
	 */
	void start(const std::string& name, const std::string& prefix="");

	/**
	 * Stop monitoring the elepsed time for named event \p name.
	 */
	void stop(const std::string& name, const std::string& prefix="");

	/**
	 * Suspend monitoring the elepsed time for named event \p name.
	 */
	void pause(const std::string& name, const std::string& prefix="");

	/**
	 * Restart a stopped event monitor
	 */
	void restart(const std::string& name, const std::string& prefix="");

	// selectors, use const to enforce non-modification
	/**
	 * provide name of this time segment monitor
	 */
	std::string name() const { return m_name; }

	/**
	 * provide information about the resolution of the underlying timer
	 */
	void info(std::ostream& ostr) const;

	/**
	 * @returns the total time spent on this event in micro-seconds
	 */
	int64_t getTotalTime() const { return m_totalTime; }

	/**
	 * @returns the total time spent on this event.
	 */
	int64_t getTotalTimeInSec() const { return m_totalTime / 1000000; }

	/**
	 * @return elapsed time in micro-seconds
	 */
	//chrono::duration<uint64_t, chrono::microseconds> 
	long long elapsed() const {
		timeSample now = steady_clock::now();
		return chrono::duration_cast<chrono::microseconds>(now - m_startTime).count(); 
	}
	/**
	 * @return elapsed time in micro-seconds
	 */
	long long elapsedInMilliSeconds() const {
		timeSample now = steady_clock::now();
		return chrono::duration_cast<chrono::milliseconds>(now - m_startTime).count();
	}
	/**
	 * helper method for formating
	 */
	void repeatChar(std::ostream& ostr, const uint32_t n, const char c) const {
		for (unsigned int i=0; i<n; ++i) ostr << c;
	}

protected:
	/**
	 * keep a start time for overall elapsed time of the monitor
	 */
	timeSample			m_startTime;
	/**
	 * name of the monitor. We can have multiple monitors active
	 * at any point in time.
	 */
	const std::string	m_name;
	/**
	 * total time elapsed in micro-seconds for this monitor
	 */
	long long			m_totalTime;

private:
	/**
	 * stream operators for the time segments
	 */
	friend std::ostream& operator<<(std::ostream& ostr, const TimeSegmentData& segment) {
		return ostr << (segment.m_bActive ? "Active" : "Idle");
	}
	friend std::ostream& operator<<(std::ostream& ostr, const TimeMonitor& monitor);
};

NS_STILLWATER_DIAGNOSTICS_END

#endif // TIME_MONITOR_INCLUDED


