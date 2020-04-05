/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryDescriptor.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	12 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #8 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryDescriptor.hpp#8 $
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
#ifndef STILLWATER_MEMORY_DESCRIPTOR_INCLUDED
#define STILLWATER_MEMORY_DESCRIPTOR_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

/** 
 * \class MemoryDescriptor MemoryDescriptor.hpp "MemoryDescriptor.hpp"
 * \brief MemoryDescriptor describes the parameters of a mob.
 *
 * Our memory is object-oriented in the sense that we
 * interact with memory on the basis of reading and
 * writing memory objects, or mobs. The MemoryDescriptor 
 * captures the parameters of the mob, such as the 
 * number of elements and the element type and size.
 *
 * The idea is that the hw will use these descriptors
 * on-chip to setup the address generators quickly
 * without having to touch memory. This functionality
 * is still in flux. ETLO 9/1/06
 */
class MemoryDescriptor {
public:
	MemoryDescriptor(uint64 nrOfElements, MemoryElementType elementType) :
		m_nrOfElements(nrOfElements), m_elementType(elementType) {
		m_sizeOfElement = static_cast<uint64>(elementType) & 0xFF;
		m_sizeInBytes = m_nrOfElements*m_sizeOfElement;
	}
	virtual ~MemoryDescriptor() {
		m_sizeInBytes = 0;
		m_nrOfElements  = 0;
		m_sizeOfElement = 0;
	}

	uint64 size() const { return m_sizeInBytes; }
	uint64 nrOfElements() const { return m_nrOfElements; }
	MemoryElementType elementType() const { return m_elementType; }
	uint64 sizeOfElement() const { return m_sizeOfElement; }
protected:
	uint64 m_nrOfElements;
	MemoryElementType m_elementType;
	uint64 m_sizeOfElement;
	uint64 m_sizeInBytes;
};

// global ostream operators
std::ostream& operator<<(std::ostream& ostr, const MemoryElementType& rhs);
std::ostream& operator<<(std::ostream& ostr, const MemoryDescriptor& rhs);


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_MEMORY_DESCRIPTOR_INCLUDED


