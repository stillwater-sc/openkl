/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/diagnostics/TimeMonitor.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/08/28 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/diagnostics/TimeMonitor.cpp#5 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006-2007 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of
 * Stillwater Supercomputing, Inc. It may not be copied or duplicated in
 * any form, or disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
// STL includes
#include <iostream>
#include <string>
#include <map>
#include <chrono>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
// DIAGNOSTICS library includes
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#include <stillwater/diagnostics/TimeMonitor.hpp>

using namespace std;

NS_STILLWATER_DIAGNOSTICS_BEGIN

void TimeMonitor::clear() {
	// This is more of a debug helper to properly
	// use the TimeMonitor. This is not performance
	// critical code and thus we can cycle through
	// the whole set to find any dangling segments.
	// When we find a dangling segment, we don't
	// throw an exception we simply log a message
	for (TimeSegmentMap::iterator event = this->begin(); event != this->end(); ++event) {
		if (event->second.m_bActive) {
			std::cout
				<< "Dangling time segments in monitor "
				<< m_name << std::endl
				<< "event " << event->first.second << " is still being monitored!"
				<< std::endl;
		}
	}
	TimeSegmentMap::clear();
	// restart the global timer
	m_startTime = chrono::steady_clock::now();
}

void TimeMonitor::start(const std::string& name, const std::string& prefix) {
	TimeSegmentData& event = this->operator[](std::make_pair(prefix,name));
	if (event.m_bActive) {
		std::cerr << "ERROR logging event " << name << std::endl
			<< "Did you forget to stop logging it?" << std::endl;
	}

	event.m_bActive   = true;
	event.m_startTime = chrono::steady_clock::now();
}

void TimeMonitor::stop(const std::string& name, const std::string& prefix)
{
	TimeSegmentData& event = this->operator[](std::make_pair(prefix,name));
	if (!event.m_bActive) {
		std::cerr << "ERROR logging event " << name << std::endl
			<< "Did you forget to start or restart it?" << std::endl;
	}
    
	event.m_bActive			= false;
	timeSample stopTime     = chrono::steady_clock::now();
	long long elapsed_time	= event.elapsed();
	m_totalTime				+= elapsed_time;
	event.m_cummulativeTime	+= elapsed_time;
	event.m_nrOfUpdates++;	 
}

void TimeMonitor::pause(const std::string& name, const std::string& prefix)
{
 	TimeSegmentData& event = this->operator[](std::make_pair(prefix,name));
	if (!event.m_bActive) {
		std::cerr << "ERROR pausing event " << name << std::endl
			<< "Did you forget to start logging it?" << std::endl;	  
	}
    
	long long elapsed_time	 = event.elapsed();
	m_totalTime				+= elapsed_time;
	event.m_cummulativeTime	+= elapsed_time;
}

void TimeMonitor::restart (const std::string& name, const std::string& prefix)
{
	TimeSegmentData& event = this->operator [](std::make_pair(prefix,name));
	if (!event.m_bActive) {
		std::cerr << "ERROR restarting event " << name << std::endl
			<< "Did you forget to start or pause it?" << std::endl;	  
	}
    
	event.m_bActive = true;
	event.m_startTime = chrono::steady_clock::now();
}

// selectors

void TimeMonitor::info (std::ostream& ostr) const {
	/*
	boost::timer t;
	ostr << "timer::elapased_min() reports " << t.elapsed_min() << " seconds\n";
	ostr << "timer::elapased_max() reports " << t.elapsed_max()
		<< " seconds, which is " << t.elapsed_max()/3600.0 << " hours\n";
	*/
}

// friends
std::ostream& operator<<(std::ostream& ostr, const TimeMonitor& monitor) {
 	if (!monitor.empty()) {
		ostr << std::endl;
		const int64_t elapsed_time = monitor.elapsed();

		// Figure out the formatting required based on the event names
		uint32_t event_col_width            = 30;
		const uint32_t ncalls_col_width     = 10;
		const uint32_t tot_time_col_width   = 12;
		const uint32_t avg_time_col_width   = 12;
		const uint32_t pct_active_col_width = 13;

		// Calculate the proper event column width
		TimeSegmentMap::const_iterator event = monitor.begin();
		while (event != monitor.end()) {
			if (event->first.second.size()+3 > event_col_width) {
				event_col_width = static_cast<uint8_t>(event->first.second.size()+3);
			}
			++event;
		}

		// Set the total width of the column
		const uint32_t total_col_width =
			event_col_width     +
			ncalls_col_width    +
			tot_time_col_width  +
			avg_time_col_width  +
			pct_active_col_width+1;

		// Print dashed line
		ostr << "+";
		monitor.repeatChar(ostr, total_col_width, '-');
		ostr << "+" << endl;
	        
		ostr << "| " 
			<< monitor.name()
			<< " Performance: Elapsed time=" << monitor.elapsedInMilliSeconds() << "msec"
			<< ", Active time=" << monitor.getTotalTime() << "sec"
			<< " | " << endl;
	    
		ostr << "+";
		monitor.repeatChar(ostr, total_col_width, '-'); 
		ostr << "+" << endl;
	    
		// Write out the header for the events listing
		ostr << "| " << left
			<< setw(event_col_width) << string("Event")
			<< setw(ncalls_col_width) << string("nCalls")    
			<< setw(tot_time_col_width) << string("Total")    
      		<< setw(avg_time_col_width) << string("Avg")
			<< setw(pct_active_col_width) << string("Percent of")    
			<< "|\n| "
      		<< setw(event_col_width) << string("")
       		<< setw(ncalls_col_width) << string("")
       		<< setw(tot_time_col_width) << string("Time")
       		<< setw(avg_time_col_width) << string("Time")
       		<< setw(pct_active_col_width) << string("Active Time")
			<< "|\n|";
		    
		monitor.repeatChar(ostr, total_col_width, '-'); ostr << "|\n|";
		monitor.repeatChar(ostr, total_col_width, '-'); ostr << "|\n";

		uint64_t summed_function_calls = 0;
		int64_t  summed_total_time     = 0;
		float    summed_percentage     = 0.0f;

		std::string last_header("");
		
		const int64_t totalTime = monitor.getTotalTime();
		TimeSegmentMap::const_iterator iter = monitor.begin();
		while (iter != monitor.end()) {
			const TimeSegmentData& event = iter->second;

			const uint64_t	count    = event.m_nrOfUpdates;
			const int64_t	time     = event.m_cummulativeTime;
			const float 	avg_time = time / static_cast<float>(count);
			const float 	percent  = (totalTime != 0.0f) ? float(time / totalTime * 100.0f) : 0.0f;

			summed_function_calls += count;
			summed_total_time     += time;
			summed_percentage     += percent;

			// Print the event name
			if (iter->first.first == "") {
				ostr << "| "
					<< setw(event_col_width) << left << iter->first.second;
			}
			else {
				if (last_header != iter->first.first) {
					last_header = iter->first.first;

					// print blank line
					ostr << "|";
					monitor.repeatChar(ostr,total_col_width, ' ');
					ostr << "|\n";

					// print header name (account for additional space before the header)
					ostr << "| "
						<< setw(total_col_width-1) << left << iter->first.first
						<< "|\n";
				}
			}
			ostr << "|   " << setw(event_col_width-2) << left << iter->first.second;
			ostr << setw(ncalls_col_width) << count;
			ostr.setf(std::ios::fixed);
			ostr << setw(tot_time_col_width) << setprecision(4) << time;
			ostr << setw(avg_time_col_width) << setprecision(6) << avg_time;
			ostr << setw(pct_active_col_width) << setprecision(2) << percent;
			ostr << "|" << endl;
			++iter;	
		}
		// Cummulative time segments
		ostr << '+';	monitor.repeatChar(ostr, total_col_width, '-');	ostr << '+';
		ostr << endl << "| " << setw(event_col_width) << "Totals:";

	#ifdef INTEGER_FORMAT
		ostr << width(ncalls_col_width) << summed_function_calls;
	#else
		/** incase you want to print in scientific mode */
		ostr.setf(std::ios::scientific);
		ostr << setw(ncalls_col_width) << setprecision(3) << static_cast<float>(summed_function_calls);
		ostr.unsetf(std::ios::scientific);
	#endif
		
		// Print the total time spent in logged function calls
		ostr.setf(std::ios::fixed);
		ostr << setw(tot_time_col_width) << setprecision(4) << summed_total_time;
		ostr << setw(avg_time_col_width) << "";
		ostr << setw(pct_active_col_width) << setprecision(2) << summed_percentage;
		ostr << "|\n";
		ostr << '+';
		monitor.repeatChar(ostr, total_col_width, '-');	
		ostr << '+';
		ostr << endl;
	}

 	return ostr;
}


#ifdef LATER
std::string get_info_header() const
{
  OStringStream out;
  
  if (log_events)
    {
     
      // Get system information
      struct utsname sysInfo;
      uname(&sysInfo);
      
      // Get user information
      struct passwd* p = getpwuid(getuid());
      out << "\n";

      // Construct string stream objects for each of the outputs
      OStringStream pid_stream;
      OStringStream nprocs_stream;
      OStringStream time_stream;
      OStringStream os_stream;
      OStringStream host_stream;
      OStringStream osrel_stream;
      OStringStream osver_stream;
      OStringStream machine_stream;
      OStringStream user_stream;

      // Put pointers to these streams in a vector
      std::vector<OStringStream*> v(9);
      v[0] = &pid_stream;
      v[1] = &nprocs_stream;
      v[2] = &time_stream;
      v[3] = &os_stream;
      v[4] = &host_stream;
      v[5] = &osrel_stream;
      v[6] = &osver_stream;
      v[7] = &machine_stream;
      v[8] = &user_stream;

      
#ifdef HAVE_LOCALE						       
      time_stream    << "| Time:           " << dateStr.str()          ; 
#endif								       
      
      os_stream      << "| OS:             " << sysInfo.sysname        ; 
      host_stream    << "| HostName:       " << sysInfo.nodename       ; 
      osrel_stream   << "| OS Release:     " << sysInfo.release        ; 
      osver_stream   << "| OS Version:     " << sysInfo.version        ; 
      machine_stream << "| Machine:        " << sysInfo.machine        ; 
      user_stream    << "| Username:       " << p->pw_name             ; 
      
      // Find the longest string, use that to set the line length for formatting.
      unsigned int max_length = 0;
      for (unsigned int i=0; i<v.size(); ++i)
	if (v[i]->str().size() > max_length)
	  max_length = v[i]->str().size();
      
      // Print dashed line
      this->_character_line(max_length+2, '-', out);
      out << '\n';

      // Loop over all the strings and print them out with end-formatting
      for (unsigned int i=0; i<v.size(); ++i)
	{
	  if (v[i]->str().size() > 0)
	    {
	      out << v[i]->str();
	      OSSStringright(out, max_length+4 - v[i]->str().size(), "|\n");
	    }
	}

      // Print dashed line
      this->_character_line(max_length+2, '-', out);
      out << '\n';
    }

  return out.str();
}
#endif

NS_STILLWATER_DIAGNOSTICS_END
