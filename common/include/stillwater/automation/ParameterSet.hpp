/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/ParameterSet.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/ParameterSet.hpp#6 $
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
#ifndef PARAMETER_SET_INCLUDED
#define PARAMETER_SET_INCLUDED

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \brief the parameter set singleton that stores the parameters
 */
class ParameterSet : public ReferenceRegistry<Parameter> {
public:
	~ParameterSet() {
		if (m_pParameterSet) {
			m_pParameterSet = NULL;
		}
	}
	static ParameterSet* getInstance() {
		if (m_pParameterSet == NULL) {
			m_pParameterSet = new ParameterSet;
		}
		return m_pParameterSet;
	}
	Parameter* query(const std::string& name) {
		ReferenceRegistry<Parameter>::iterator iter = find(name);
		if (iter != end()) {
			return iter->second;
		}
		return NULL;
	}

private:
	ParameterSet() {}
	static ParameterSet* m_pParameterSet;

	/**
	* \brief global ostream operator
	*/
	friend std::ostream& operator<<(std::ostream& ostr, const ParameterSet& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const ParameterSet* rhs) { return ostr << *rhs; }
};

NS_STILLWATER_AUTOMATION_KNOBS_END

#endif // PARAMETER_SET_INCLUDED


