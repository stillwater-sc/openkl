/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/ReferenceRegistry.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/ReferenceRegistry.hpp#4 $
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
#ifndef REFERENCE_REGISTRY_INCLUDED
#define REFERENCE_REGISTRY_INCLUDED

NS_STILLWATER_AUTOMATION_BEGIN

/**
 * \brief a registry that contains pointers to objects it doesn't own
 *
 * The ReferenceRegistry is used to hold pointers to objects
 * that the registry doesn't own. In particular, we will be storing
 * pointers to statically allocated objects.
 *
 * Since sw components can add elements to the Registry at any
 * point during execution, we want additional control to block or
 * allow this modification. Therefore, the Registry goes through
 * an explicit lock-down cycle. This allows automation software
 * to fix the contents of the registry during an enumeration cycle,
 * and it provides the sw a hook to throw an exception when the
 * sw component violates the lock-down requirement.
 *
 * The ReferenceRegistry starts off in the enabled state, and is only locked-down
 * expclitely
 */
template<class T>
class ReferenceRegistry : public std::map<std::string, T*> {
typedef typename std::map<std::string, T*>		ReferenceRegistryMap;
typedef typename ReferenceRegistryMap::iterator		registry_iterator;
typedef typename ReferenceRegistryMap::const_iterator 	registry_const_iterator;
public:
	ReferenceRegistry() : m_bLockedDown(false) {}
	~ReferenceRegistry() { this->clear(); }

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
			this->insert(typename ReferenceRegistryMap::value_type(name, that));
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
			this->erase(iter);
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
	friend std::ostream& operator<<(std::ostream& ostr, const ReferenceRegistry<T>& rhs){
		registry_const_iterator iter = rhs.begin();
		while (iter != rhs.end()) {
			ostr << "Key(" << iter->first << ") : " << *iter->second << std::endl;
			++iter;
		}
		return ostr;
	}
};

NS_STILLWATER_AUTOMATION_END

#endif // REFERENCE_REGISTRY_INCLUDED
