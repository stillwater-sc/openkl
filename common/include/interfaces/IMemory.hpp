/**
 * File		:	$File: //depot/Stillwater/Common/include/interfaces/IMemory.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/interfaces/IMemory.hpp#4 $
 *
 * Organization:
 *		Stillwater Supercomputing Solutions
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing Solutions. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing Solutions.
 */
#ifndef IMEMORY_INCLUDED
#define IMEMORY_INCLUDED

NS_STILLWATER_SRM_BEGIN

/**
	* \class IMemory IMemory.hpp "IMemory.hpp"
	* \brief The IMemory interface defines the
	*		  memory discovery interface
	*
	* It is mainly used to decouple the SRM module
	* from the architectural simulator. We want
	* the SRM module to be useful for the simulator,
	* but not inject simulation module dependencies.
	* Otherwise stated: we want the SRM to be
	* usable by the simulator, but we don't want
	* the SRM to have any compile dependencies on
	* the architectural prototyping efforts.
	*/
class IMemory {
public:
	IMemory() {};
	virtual ~IMemory(void) {};
	// selectors
	virtual uint64 getSizeInBytes() const = 0;
	virtual uint64 getPageSizeInBytes() const = 0;
	virtual void print(std::ostream& ostr) const = 0;
};

NS_STILLWATER_SRM_END

#endif // IMEMORY_INCLUDED


