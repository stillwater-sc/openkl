/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MobMemory.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	13 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #10 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MobMemory.hpp#10 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006-2007 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing, Inc. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of Stillwater
 * Supercomputing, Inc.
 */
#ifndef STILLWATER_MOB_MEMORY_INCLUDED
#define STILLWATER_MOB_MEMORY_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

// forward references
class MemoryObject;
/** 
* \class MobMemory MobMemory.hpp "MobMemory.hpp"
* \brief MobMemory manages MemoryObject oriented memory
*
*/
class MobMemory : public Memory {
public:
	/**
	 * \brief default constructor
	 * \param sizeInBytes size of memory block in bytes
	 * \param startAddress byte address of the first byte of the memory block in the overall memory map
	 * \param pageSizeInBytes size in bytes of the uniform page size for this memory
	 *
	 */
	MobMemory(uint64_t sizeInBytes, Address startAddress, uint64_t pageSizeInBytes) 
		: Memory(sizeInBytes, startAddress, pageSizeInBytes) {}
	
	/**
	 * destructor ~MobMemory()
	 */
	~MobMemory(void) {}

	// operators
	// none

// selectors, use const to enforce non-modification

	/**
	 * \brief read a MemoryObject from
	 * \param baseAddress base address of the memory block
	 * \param mob reference to a MemoryObject with its MemoryDescriptor filled in
	 * \throw PageException can throw a page 
	 *			exception when the parameters 
	 *			of the MemoryDescriptor are bad
	 *
	 * The MobMemory object uses a block oriented
	 * request interface. The MemoryObject needs 
	 * to have its MemoryDescriptor parameters set,
	 * and the read method will fill in the data blob by 
	 * copying the contents of the Memory to the mob.
	 */
	void read(Address baseAddress, MemoryObject& mob) const;

	/**
	 * \brief lower level block access API
	 */
	void read(Address baseAddress, uint64_t sizeInBytes, void* pData) const {
		Memory::read(baseAddress, sizeInBytes, pData);
	}

// modifiers
	/**
		* write(uint64_t baseAddress, MemoryObject& mob)
		* \param baseAddress the base address of the memory block to write to
		* \param mob reference to a MemoryObject containing the data
		* \throw PageException can throw a page exception
		*/
	void write(Address baseAddress, const MemoryObject& mob);
	/**
		* \brief lower level block access API
		*/
	void write(Address baseAddress, uint64_t sizeInBytes, const void* pData) {
		Memory::write(baseAddress, sizeInBytes, pData);
	}

protected:
	// helpers

};


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_MOB_MEMORY_INCLUDED


