/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/Registry.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/Registry.hpp#6 $
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
#ifndef REGISTRY_INCLUDED
#define REGISTRY_INCLUDED

NS_STILLWATER_AUTOMATION_BEGIN

/**
 * \brief a registry that manages dynamically allocated entities
 *
 * This class is a generic class that can be used to contain
 * and manage dynamically allocated entities. In the Parameter Space
 * library we use it to contain and manage Parameters, but Registry<T>
 * is more general than that. It basically stores a name and a
 * boost::shared_ptr<T> to a type.
 *
 * Since sw components can add elements to the Registry at any
 * point during execution, we want additional control to block or
 * allow this modification. Therefore, the Registry goes through
 * an explicit lock-down cycle. This allows automation software
 * to fix the contents of the registry during an enumeration cycle,
 * and it provides the sw a hook to throw an exception when the
 * sw component violates the lock-down requirement.
 *
 * The Registry starts off in the enabled state, and is only locked-down
 * expclitely
 */
template<class T>
class Registry : public std::map<std::string, std::shared_ptr<T> > {
public:
	typedef typename std::map<std::string, std::shared_ptr<T> >	RegistryMap;
	typedef typename RegistryMap::iterator						registry_iterator;
	typedef typename RegistryMap::const_iterator				registry_const_iterator;
	Registry() : m_bLockedDown(false) {}
	~Registry() { this->clear(); }

	// modifiers
	/**
		* \brief add an element to the Registry
		* \return true if added, false otherwise
		* \throw run-time error if trying to add when locked-down
		*
		* The element will be rejected if we are in lock-down mode
		* or if the key is already in the Registry.
		*/
	bool addConditionally(const std::string& name, T* that) {
		if (m_bLockedDown) THROW_RUNTIME_ERROR("Registry is in lock-down mode but asked to add a new element");
		bool bSuccess = false;
		registry_iterator iter = this->find(name);
		if (iter == this->end()) {
			insert(RegistryMap::value_type(name, boost::shared_ptr<T>(that)));
			bSuccess = true;
		}
		else {
			// "Name already exists in this Registry: ignored"
			bSuccess = false;
		}
		return bSuccess;
	}
	/**
		* \brief remove a named key/value pair from the set
		*/
	bool remove(const std::string& name) {
		bool bSuccess = false;
		registry_iterator iter = this->find(name);
		if (iter != this->end()) {
			erase(iter);
			bSuccess = true;
		}
		return bSuccess;
	}
	/**
		* \brief set the lockdown state
		*/
	void setLockDown(bool bLockDown) { m_bLockedDown = bLockDown; }

protected:
	// member variables
	bool	m_bLockedDown;

private:
	/**
		* \brief global ostream operator
		*/
	friend std::ostream& operator<<(std::ostream& ostr, const Registry<T>& rhs){
		registry_const_iterator iter = rhs.begin();
		while (iter != rhs.end()) {
			ostr << "Key(" << iter->first << ") : " << *(iter->second.get()) << std::endl;
			++iter;
		}
		return ostr;
	}
};

NS_STILLWATER_AUTOMATION_END

#endif // REGISTRY_INCLUDED
