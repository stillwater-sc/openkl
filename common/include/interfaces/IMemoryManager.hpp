/**
 * File		:	$File: //depot/Stillwater/Common/include/interfaces/IMemoryManager.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	20 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2009/12/31 $
 * Location	:	$Id: //depot/Stillwater/Common/include/interfaces/IMemoryManager.hpp#5 $
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
#ifndef IMEMORY_MANAGER_INCLUDED
#define IMEMORY_MANAGER_INCLUDED

NS_STILLWATER_SRM_BEGIN

// forward references
class IMemory;
class MemoryManagementPolicy;

/**
 * \class IMemoryManager MemoryManager.hpp "MemoryManager.hpp"
 * \brief the memory manager interface
 */
class IMemoryManager {
public:
	IMemoryManager() {}
	IMemoryManager(IMemory*, MemoryManagementPolicy*);
	virtual ~IMemoryManager() {};
	virtual void reset() = 0;
	virtual uint64 allocate(uint64 sizeInBytes, ZoneType type = ZONE_DATA) = 0;
	virtual bool deallocate(uint64 startAddress) = 0;
};

NS_STILLWATER_SRM_END

#endif // IMEMORY_MANAGER_INCLUDED
