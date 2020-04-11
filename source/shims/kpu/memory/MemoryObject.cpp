/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryObject.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #10 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryObject.cpp#10 $
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
// STL includes
// none
// BOOST include
// none
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include "./memory_nsmacro.hpp"	// centralized namespace definition
#include <interfaces/MemoryTypeEnums.hpp>
// memory library includes
#include "./MemoryDescriptor.hpp"
#include "./MemoryObject.hpp"

NS_STILLWATER_SLM_MEMORY_BEGIN

std::ostream& operator<<(std::ostream& ostr, const MemoryObject& rhs) {
	ostr << "("
		<< rhs.nrOfElements()
		<< ","
		<< rhs.sizeOfElement()
		<< ") : [";
	for ( uint64_t i = 0; i < rhs.nrOfElements()-1; i++ ) {
		rhs.printElement(ostr, i) << "," ;
	}
	rhs.printElement(ostr, rhs.nrOfElements()-1) << "]" << std::endl;
	return ostr;
}

/**
 * destructor cleans up the data blob
 */
MemoryObject::~MemoryObject(void)
{
	if (m_pBlob) {
		delete[] m_pBlob;
		m_pBlob = NULL;
	}
}

std::ostream& MemoryObject::printElement(std::ostream& ostr, uint64_t index) const {
	if (index < this->m_nrOfElements) {
		switch(this->m_elementType) {
		case	MET_UINT8:
			ostr << ((uint8_t*) this->m_pBlob)[index];
			break;
		case	MET_UINT16:
			ostr << ((uint16_t*) this->m_pBlob)[index];
			break;		
		case	MET_UINT32:
			ostr << ((uint32_t*) this->m_pBlob)[index];
			break;
		case	MET_UINT64:
			ostr << ((uint64_t*) this->m_pBlob)[index];
			break;
		case	MET_UINT128:
		case	MET_UINT256:
			ostr << "128 and 256 bit ints not supported yet";
			break;
		case	MET_INT8:
			ostr << ((int8_t*) this->m_pBlob)[index];
			break;
		case	MET_INT16:
			ostr << ((int16_t*) this->m_pBlob)[index];
			break;		
		case	MET_INT32:
			ostr << ((int32_t*) this->m_pBlob)[index];
			break;
		case	MET_INT64:
			ostr << ((int64_t*) this->m_pBlob)[index];
			break;
		case	MET_INT128:
		case	MET_INT256:
			ostr << "128 and 256 bit ints not supported yet";
			break;
		case	MET_REAL16:
			ostr << "16 bit reals not supported yet";
			break;
		case	MET_REAL32:
			ostr << ((float*) this->m_pBlob)[index];
			break;
		case	MET_REAL64:
			ostr << ((double*) this->m_pBlob)[index];
			break;
		case	MET_REAL80:
		case	MET_REAL128:
		case	MET_REAL256:
			ostr << "80, 128 and 256 bit reals not supported yet";
			break;
		case	MET_CMPLX16:
		case	MET_CMPLX32:
		case	MET_CMPLX64:
		case	MET_CMPLX80:
		case	MET_CMPLX128:
		case	MET_CMPLX256:
			ostr << "complex not supported yet";
			break;
		default:
			ostr << "unknown data type: ignored";
		}
	}
	else {
		ostr << "index out of bound";
	}
	return ostr;
}


NS_STILLWATER_SLM_MEMORY_END


