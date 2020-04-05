/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/ParameterSpaceEnumerator.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/ParameterSpaceEnumerator.cpp#7 $
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
#include <stillwater/automation/ParameterSpaceEnumerator.hpp>

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \brief list the parameters of the aggregated parameter set
 */
void ParameterSpaceEnumerator::listParameterSet(std::ostream& ostr) const {
	ostr << "Contents of the Parameter Space:" << std::endl << *m_pSet << std::endl;
}

/**
 * \brief list the ranges of the enumeration set
 */
void ParameterSpaceEnumerator::listEnumerationSet(std::ostream& ostr) const {
	ostr << "Contents of the Enumeration Set: " 
		<< static_cast<int>(m_ranges.size()) << " ranges" << std::endl 
		<< m_ranges << std::endl;
}


/**
 * \brief reset the registered ranges
 * The purpose of reset is to start an enumeration.
 * Such an enumeration, takes all the registered
 * ranges and drives the appropriate minimum value
 * into the respective Parameters. 
 *
 * This is all done as a side effect!!!! So this
 * doesn't work for complex reconfiguration parameters.
 */
void ParameterSpaceEnumerator::reset() {
	ParameterRangeMap::const_iterator iter = m_ranges.begin();
	while (iter != m_ranges.end()) {
		// drive the first valid minimum into the parameter
		ParameterSet::const_iterator paramIter = m_pSet->find(iter->second.m_name);
		if (paramIter != m_pSet->end()) {
			paramIter->second->setCurrent(iter->second.m_min);
		}
		++iter;
	}
}
/**
 * \brief next() generates the next valid configuration
 *
 * TODO: still need to implement a general enumeration algorithm
 */
bool ParameterSpaceEnumerator::next() {
	bool bSuccess = false;
	std::string parameterName = "module2.latency";
	Parameter* pParam;
	if (pParam = m_pSet->query(parameterName)) {
		bSuccess = pParam->step();
		if (bSuccess) {
			// the value still needs to pass the subrange test
			ParameterRangeMap::const_iterator range = m_ranges.find(parameterName);
			if (range != m_ranges.end()) {
				// the range is inclusive
				if (pParam->getCurrent() < range->second.m_max ||
					pParam->getCurrent() == range->second.m_max) {
					bSuccess = true;
				}
				else {
					bSuccess = false;
				}
			}
			else {
				bSuccess = false;
			}
		}
	}
	else {
		std::cerr << "No such parameter" << std::endl;
	}
	return bSuccess;
}
/**
 * \brief add a parameter range for enumeration
 * \return true if successfully added, false otherwise
 */
bool ParameterSpaceEnumerator::addRange(const ParameterRange& range) {
	bool bFound = false;
	if (m_pSet->query(range.m_name)) {
		bFound = true;
		m_ranges.insert(ParameterRangeMap::value_type(range.m_name, range));
	}
	return bFound;
}

NS_STILLWATER_AUTOMATION_KNOBS_END



