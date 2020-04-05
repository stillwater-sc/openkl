/**
 * File		:	$File: //depot/Stillwater/Common/src/Libraries/automation/ParameterSet.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/src/Libraries/automation/ParameterSet.cpp#6 $
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

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \brief storage for the set
 */
ParameterSet* ParameterSet::m_pParameterSet = NULL;

std::ostream& operator<<(std::ostream& ostr, const ParameterSet& rhs) {
	ParameterSet::const_iterator iter = rhs.begin();
	while (iter != rhs.end()) {
		ostr << *(iter->second) << std::endl;
		++iter;
	}
	return ostr;
}

NS_STILLWATER_AUTOMATION_KNOBS_END


