/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/ParameterSpaceEnumerator.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/ParameterSpaceEnumerator.hpp#7 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing, Inc. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef PARAMETER_SPACE_ENUMERATOR_INCLUDED
#define PARAMETER_SPACE_ENUMERATOR_INCLUDED

NS_STILLWATER_AUTOMATION_KNOBS_BEGIN

/**
 * \class ParameterRangeMap
 * \brief map between parameter name and a value range. Used for enumeration of that parameter.
 */
class ParameterRangeMap : public std::map<std::string,ParameterRange> {
private:
	friend std::ostream& operator<<(std::ostream& ostr, const ParameterRangeMap& rhs) {
		int index = 0;
		ParameterRangeMap::const_iterator iter = rhs.begin();
		while (iter != rhs.end()) {
			// the key and the name of the ParameterRange are the same
			// so we can ignore it when printing the map.
			ostr << "[" << std::setw(3) << index++ << "] = " 
				<< " range: "
				<< iter->second
				<< std::endl;
			++iter;
		}
		return ostr;
	}
};

/**
 * \brief the basic Parameter holding the range and current value and descriptive information
 */
class ParameterSpaceEnumerator {
public:

	// constructor
	ParameterSpaceEnumerator(ParameterSet* pSet) : m_pSet(pSet) { 
		// once we define an enumerator on the set, we lock down the underlying Registry
		m_pSet->setLockDown(true);
	}
	// destructor
	~ParameterSpaceEnumerator() {
		// when the enumerate goes out of scope, we unlock the underlying Registry
		m_pSet->setLockDown(false);
	}

	// modifiers
	/**
	* \brief reset all the registered ranges so a new enumeration can start
	*/
	void reset();

	/**
	* \brief generate the next configuration
	* \return true if a new configuration has been successfully generated, false otherwise
	*/
	bool next();
	/**
	* \brief register a parameter range to be enumerated
	*/
	bool addRange(const ParameterRange& range);

	// selectors, use const to enforce non-modification
	/**
		* \brief list the Parameter Set of the underlying locked Registry
		*/
	void listParameterSet(std::ostream& ostr) const;
	/**
		* \brief list the Enumeration Set
		*/
	void listEnumerationSet(std::ostream& ostr) const;

protected:
	// member variables
	/**
	* \brief the map of parameters
	*
	* Why is this a pointer? Because the ParameterSet
	* is being constructed as a singleton, and we simple
	* register this singleton with this class so it can
	* layer enumeration functionality on top of the singleton.
	*/
	ParameterSet*		m_pSet;
	/**
	* \brief the map of ranges
	*
	* This is a map since we don't want the same range 
	* registered twice.
	*/
	ParameterRangeMap	m_ranges;

private:
	// none

};

NS_STILLWATER_AUTOMATION_KNOBS_END

#endif // PARAMETER_SPACE_ENUMERATOR_INCLUDED
