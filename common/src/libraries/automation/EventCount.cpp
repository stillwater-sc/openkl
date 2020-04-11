/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/EventCount.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/EventCount.cpp#6 $
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
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

// Stillwater includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
// library includes
#include <stillwater/automation/automation_nsmacro.hpp>
#include <stillwater/automation/ReferenceRegistry.hpp>
#include <stillwater/automation/EventCount.hpp>
#include <stillwater/automation/EventCountSet.hpp>

NS_STILLWATER_AUTOMATION_GAUGES_BEGIN

/**
 * \brief default constructor
 */
EventCount::EventCount(const std::string& instanceName, const std::string& name, const std::string& dimension) 
	: m_name(name), m_dimension(dimension), m_instanceName(instanceName), m_count(0ll) 
{
	std::string cntrName = m_instanceName + std::string("::") + m_name;
	EventCountSet::getInstance()->addConditionally(cntrName, this);
}

/**
 * \brief set the name of the event count
 * This requires that we reassign the node in the EventCountSet
 * as well.
 */
void EventCount::setName(const std::string& instanceName, const std::string& name) {
	std::string cntrName = m_instanceName + std::string("::") + m_name;
	EventCountSet::getInstance()->remove(cntrName);
	m_name = name; m_instanceName = instanceName;
	cntrName = m_instanceName + std::string("::") + m_name;
	EventCountSet::getInstance()->addConditionally(cntrName, this);
}

/**
 * \brief virtual destructor
 *
 * If we remove an EventCount object of any kind, we need
 * to make certain that we remove it from the EventCountSet
 * as well so that that set is pointing to valid EventObjects
 */
EventCount::~EventCount() {
	std::string cntrName = m_instanceName + std::string("::") + m_name;
	EventCountSet::getInstance()->remove(cntrName);
	m_name.erase(); m_dimension.erase();
	m_sampleData.clear();
}

NS_STILLWATER_AUTOMATION_GAUGES_END

