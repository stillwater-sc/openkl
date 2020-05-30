/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/EventCount.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #9 $
 * Latest	:	$Date: 2010/02/27 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/EventCount.hpp#9 $
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
#ifndef EVENT_COUNT_INCLUDED
#define EVENT_COUNT_INCLUDED

#include <iostream>
#include <string>
NS_STILLWATER_AUTOMATION_GAUGES_BEGIN

/**
 * \brief event count statistic
 * Event count data denotes a statistic that can be
 * accumulated by performance counters. When sample()
 * is called, the event count is stored in the sample
 * vector, and the count is reset to zero.
 */
class EventCount {
public:
	/**
	 * \brief default constructor
	 */
	EventCount(const std::string& instanceName, const std::string& name, const std::string& dimension);
	/**
	 * \brief copy constructor
	 */
	EventCount(const EventCount& rhs) {
		*this = rhs;
	}
	/**
	 * \brief conversion constructor to go from values to EventCount objects
	 */
	EventCount(uint64_t value) : m_name(""),m_dimension(""),m_count(value) {};
	/**
	 * \brief virtual destructor
	 *
	 * If we remove an EventCount object of any kind, we need
	 * to make certain that we remove it from the EventCountSet
	 * as well so that that set is pointing to valid EventCount objects
	 */			
	virtual ~EventCount();

	// operators
	/**
		* \brief assignment to an other EventCount
		*/
	EventCount& operator=(const EventCount& rhs) {
		m_instanceName = rhs.m_instanceName;
		m_name = rhs.m_name;
		m_dimension = rhs.m_dimension;
		m_count = rhs.m_count;
		m_sampleData.clear();
		m_sampleData = rhs.m_sampleData;
		return *this;
	}
	/**
		* \brief assignment to a value
		* leave the rest of the data structures alone.
		*/
	EventCount& operator=(uint64_t value) {
		m_count = value;
		return *this;
	}
	EventCount& operator+=(uint64_t value) { m_count += value; return *this; }
	EventCount& operator-=(uint64_t value) { m_count -= value; return *this; }
	EventCount& operator*=(uint64_t value) { m_count *= value; return *this; }
	EventCount& operator/=(uint64_t value) { m_count /= value; return *this; }
	EventCount& operator%=(uint64_t value) { m_count %= value; return *this; }

	// comparisons to values
	bool operator==(uint64_t value) { return m_count == value; }
	bool operator!=(uint64_t value) { return m_count != value; }
	bool operator<(uint64_t value) { return m_count < value; }
	bool operator>(uint64_t value) { return m_count > value; }
	bool operator<=(uint64_t value) { return m_count <= value; }
	bool operator>=(uint64_t value) { return m_count >= value; }

	/**
		* \brief prefix increment
		*/
	EventCount& operator++() {	// prefix
		++m_count;
		return *this;
	}
	/**
		* \brief postfix increment
		* we can't use a copy constructor here
		* like this:
		* <pre>
		* {
		*		EventCount result(this);
		*		++m_count;
		*		return result;
		* }
		* </pre>
		* because this would also trigger the destructor
		* of the same named EventCount object, which will
		* remove it from the EventCountSet.
		*/
	uint64_t operator++(int unused) { // postfix
		uint64_t result = m_count;
		++m_count;
		return result;
	}
	/**
		* \brief prefix decrement
		*/
	EventCount& operator--() {	// prefix
		--m_count;
		return *this;
	}
	/**
		* \brief postfix decrement
		* we can't use a copy constructor here
		* like this:
		* <pre>
		* {
		*		EventCount result(this);
		*		--m_count;
		*		return result;
		* }
		* </pre>
		* because this would also trigger the destructor
		* of the same named EventCount object, which will
		* remove it from the EventCountSet.
		*/
	uint64_t operator--(int unused) { // postfix
		uint64_t result = m_count;
		--m_count;
		return result;
	}
	// arithmetic operators
	/**
		* \brief arithmetic operators implemented as member functions
		* \return uint64 to trigger value assignment, not object assignment
		* We need to return a pure value to trigger
		* just the assignment of the m_count instead
		* of overriding all the sample info through
		* an assignment of an EventCount object
		*/
	uint64_t operator+(const EventCount& rhs) { return m_count + rhs.m_count; }
	uint64_t operator-(const EventCount& rhs) { return m_count - rhs.m_count; }
	uint64_t operator*(const EventCount& rhs) { return m_count * rhs.m_count; }
	uint64_t operator/(const EventCount& rhs) { return m_count / rhs.m_count; }
	uint64_t operator%(const EventCount& rhs) { return m_count % rhs.m_count; }

	///////////////////////////////////////////////////////
	// modifiers
	void reset() { m_count = 0; }
	/**
		* \brief clear the sample vector
		*/
	void clear() {
		// leave m_name alone
		m_sampleData.clear();
	}
	/**
		* \brief add a value to the count
		* This is deprecated in favor of the operators.
		*/
	void add(uint64_t increment) {
		m_count += increment;
	}
	/**
		* \brief set the name of the event count
		* This requires that we reassign the node in the EventCountSet
		* as well.
		*/
	void setName(const std::string& instanceName, const std::string& name);
	void setDimension(const std::string& dimension) { m_dimension = dimension; }
	void setIdentification(const std::string& instanceName, const std::string& name, const std::string& dimension) { 
		m_instanceName = instanceName; m_name = name; m_dimension = dimension; 
	}
	/**
		* \brief sample the count and store it in a vector
		* The intended use of EventCount is as a performance
		* counter: it can observe/assign integer values, and
		* gets sampled ever so often. The samples are stored
		* in a vector for later analysis
		*/
	uint64_t sample() {
		uint64_t value = m_count;
		m_sampleData.push_back(m_count);
		m_count = 0;
		return value;
	}

	///////////////////////////////////////////////////////
	// selectors, use const to enforce non-modification
	std::string getName() const { return m_name; }
	std::string getDimension() const { return m_dimension; }
	std::string getInstanceName() const { return m_instanceName; }
	std::string getQualifiedName() const { return m_instanceName + std::string("::") + m_name; }
	void getIdentification(std::string& name, std::string& dimension, std::string& instanceName) { 
		name = m_name; dimension = m_dimension; instanceName = m_instanceName; 
	}
	std::vector<uint64_t>& getSampleData() { return m_sampleData; }

protected:
	/**
		* \brief name of the statistic
		*/
	std::string		m_name;
	/**
		* \brief dimension of the statistic
		*/
	std::string		m_dimension;
	/**
		* \brief name of the instance to which this statistic belongs
		*/
	std::string		m_instanceName;
	/**
		* \brief the running count
		*/
	uint64_t		m_count;
	/**
		* \brief sample vector
		*/
	std::vector<uint64_t>	m_sampleData;

private:
//		friends
	// binary ordering operators
	friend bool operator==(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count == rhs.m_count; }
	friend bool operator!=(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count != rhs.m_count; }
	friend bool operator<(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count < rhs.m_count; }
	friend bool operator>(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count > rhs.m_count; }
	friend bool operator<=(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count <= rhs.m_count; }
	friend bool operator>=(const EventCount& lhs, const EventCount& rhs) { return lhs.m_count >= rhs.m_count; }

	/**
		* \brief global operators for ostreams
		*/
	friend std::ostream& operator<< (std::ostream& ostr, const EventCount& rhs) {
		return ostr << std::left << std::setw(45) << rhs.getQualifiedName() << " = " << std::setw(10) << rhs.m_count << " (" << rhs.m_dimension << ")";
	}
	friend std::ostream& operator<< (std::ostream& ostr, const EventCount* rhs) {
		return ostr << *rhs;
	}
	/**
		* \brief global operators for istreams
		*/
	friend std::istream& operator>> (std::istream& istr, EventCount& rhs);
};

/**
	* \brief macro to create EventCount objects so that the variable name and the name
	* it is known as in the EventCountSet are the same.
	*/ 
#define CREATE_GAUGE(instance,name,dim) EventCount name(instance,#name,dim)

NS_STILLWATER_AUTOMATION_GAUGES_END

#endif // EVENT_COUNT_INCLUDED


