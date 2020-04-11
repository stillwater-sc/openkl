/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryObject.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #9 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryObject.hpp#9 $
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
#ifndef STILLWATER_MEMORY_OBJECT_INCLUDED
#define STILLWATER_MEMORY_OBJECT_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

/** 
 * \class MemoryObject MemoryObject.hpp "MemoryObject.hpp"
 * \brief MemoryObject represents a self-contained mob.
 *
 * Our memory is object-oriented in the sense that we
 * interact with memory on the basis of reading and
 * writing memory objects, or mobs. The MemoryObject is 
 * the class that represents a complete mob, which 
 * consists of a MemoryDescriptor and a data blob containing
 * the data of the blob. It can be seen as the cached
 * version of a blob.
 * This functionality is still in flux. ETLO 9/1/06
 */
class MemoryObject : public MemoryDescriptor {
public:
	/**
	 * \brief constructor for reading operations.
	 * \param nrOfElements number of elements the blob consists of
	 * \param elementType the type of element in the blob
	 *
	 * For reading operations, we don't have a data blob
	 * yet, so a constructor that just sets up the
	 * MemoryDescriptor is the minimum information
	 * needed to initiate the read operation.
	 */
	MemoryObject(uint64_t nrOfElements, MemoryElementType elementType) :
		MemoryDescriptor(nrOfElements, elementType) {
		m_sizeInBytes = m_nrOfElements*m_sizeOfElement;
		m_pBlob = new char[static_cast<size_t>(m_sizeInBytes)];
	}
	/**
	 * \brief constructor for writing operations.
	 * \param nrOfElements number of elements the blob consists of
	 * \param elementType the type of element in the blob
	 * \param pData pointer to the data to copy into the blob
	 *
	 * For writing operations we tend to have the data blob
	 * already, so a constructor that creates a MemoryObject
	 * including the data blob is the minimum information
	 * needed to initiate the write operation.
	 */
	MemoryObject(uint64_t nrOfElements, MemoryElementType elementType, const void* pData) :
		MemoryDescriptor(nrOfElements, elementType) {
		m_sizeInBytes = m_nrOfElements*m_sizeOfElement;
		m_pBlob = new char[static_cast<size_t>(m_sizeInBytes)];
		memcpy(m_pBlob, pData, static_cast<size_t>(m_sizeInBytes));
	}
	/**
	 * \brief default destructor cleans the blob
	 */
	~MemoryObject(void);

	// operators
	// none

	// modifiers
	/**
	 * \brief obtain a modifiable pointer to the underlying data blob
	 * \return pointer to the blob contained
	 */
	void* getBlobPtr() { return m_pBlob; }

	// selectors
	/**
	 * \brief obtain a non-modifiable pointer to the underlying data blob
	 * \return pointer to the blob contained
	 */
	const void* getConstBlobPtr() const { return m_pBlob; }
	/**
	 * \brief print a single element at index to the ostr
	 * \param ostr the ostream to print to
	 * \param index the index of the element of interest in the blob
	 * \return ostr reference
	 */
	std::ostream& printElement(std::ostream& ostr, uint64_t index) const;

protected:
	// member variables
	char* m_pBlob;

private:
	// none
};

/**
 * \brief global stream output operator
 */
std::ostream& operator<<(std::ostream& ostr, const MemoryObject& rhs);


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_MEMORY_OBJECT_INCLUDED
