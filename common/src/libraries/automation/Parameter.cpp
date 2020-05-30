/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/Parameter.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #9 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/Parameter.cpp#9 $
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
#include <map>
#include <variant>
// Stillwater includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
// library includes
#include <stillwater/automation/automation_nsmacro.hpp>
#include <stillwater/automation/ReferenceRegistry.hpp>
#include <stillwater/automation/ParameterVariant.hpp>
#include <stillwater/automation/Visitors.hpp>
#include <stillwater/automation/Parameter.hpp>
#include <stillwater/automation/ParameterSet.hpp>

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \brief default constructor
 */
Parameter::Parameter( const std::string& instanceName, const std::string& name, const std::string& dimension,
				const param& min, 
				const param& nominal, 
				const param& max, 
				const param& step) :
	m_instanceName(instanceName), m_name(name), m_dimension(dimension), 
	m_min(min), m_nominal(nominal), m_max(max), m_current(nominal), m_step(step) 
{
	ParameterSet::getInstance()->addConditionally(getQualifiedName(), this);
}
Parameter::Parameter( const std::string& instanceName, const std::string& name, const std::string& dimension) :
	m_instanceName(instanceName), m_name(name), m_dimension(dimension), 
	m_min(uint64_t(0)), m_nominal(uint64_t(0)), m_max(uint64_t(0)), m_current(uint64_t(0)), m_step(uint64_t(0))
{
	ParameterSet::getInstance()->addConditionally(getQualifiedName(), this);
}


/**
 * \brief virtual destructor
 *
 * If we remove an Parameter object of any kind, we need
 * to make certain that we remove it from the ParameterSet
 * as well so that that set is pointing to valid Parameter
 */
Parameter::~Parameter() {
	ParameterSet::getInstance()->remove(getQualifiedName());
	m_name.erase(); m_dimension.erase();m_instanceName.erase();
}

/**
 * \brief global ostream operator
 */
std::ostream& operator<<(std::ostream& ostr, const Parameter& rhs) {
	ostr << std::setw(30) << rhs.getQualifiedName()
		<< " == " 
		<< std::setw(10) << variant_streamer{ rhs.m_current }
		<< "(" 
		<< std::setw(5) << rhs.m_dimension 
		<< ") range["	
		<< variant_streamer{ rhs.m_min }
		<< "," 
		<< variant_streamer{ rhs.m_nominal }
		<< "," 
		<< variant_streamer{ rhs.m_max }
		<< ",(+-)" 
		<< variant_streamer{ rhs.m_step }
		<< "] ";
	return ostr;
}	
std::ostream& operator<<(std::ostream& ostr, const Parameter* rhs) {
	return ostr << *rhs;
}

NS_STILLWATER_AUTOMATION_KNOBS_END

