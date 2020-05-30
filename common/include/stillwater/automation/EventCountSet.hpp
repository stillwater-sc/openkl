/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/EventCountSet.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/EventCountSet.hpp#5 $
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
#ifndef EVENT_COUNT_SET_INCLUDED
#define EVENT_COUNT_SET_INCLUDED

NS_STILLWATER_AUTOMATION_GAUGES_BEGIN

/**
 * \brief the singleton that stores the statistics
 */
class EventCountSet : public ReferenceRegistry<EventCount> {
public:
	~EventCountSet() {
		if (m_pEventCountSet) {
			m_pEventCountSet = NULL;
		}
	}
	static EventCountSet* getInstance() {
		if (m_pEventCountSet == NULL) {
			m_pEventCountSet = new EventCountSet;
		}
		return m_pEventCountSet;
	}
	/**
		* \brief reset the complete set
		*/
	static void reset() {
		if (m_pEventCountSet) {
			EventCountSet::iterator iter = m_pEventCountSet->begin();
			while (iter != m_pEventCountSet->end()) {
				iter->second->reset();
				++iter;
			}
		}
	}

	/**
		* \brief obtain named event pointer
		*/
	EventCount* query(const std::string& name) {
		EventCountSet::iterator iter = find(name);
		if (iter != end()) {
			return iter->second;
		}
		return NULL;
	}

	/**
		* \brief reset a named event
		*/
	void reset(const std::string& name) {
		EventCount* p;
		if ((p = query(name)) != NULL) {
			p->reset();
		}
	}


private:
	EventCountSet() {}
	static EventCountSet* m_pEventCountSet;

	/**
	* \brief global ostream operator
	*/
	friend std::ostream& operator<<(std::ostream& ostr, const EventCountSet& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const EventCountSet* rhs) { return ostr << *rhs; }
};

NS_STILLWATER_AUTOMATION_GAUGES_END

#endif // EVENT_COUNT_SET_INCLUDED


