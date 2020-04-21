/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryDescriptor.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	12 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #7 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/MemoryDescriptor.cpp#7 $
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
// memory library includes
#include <stillwater/shim/kpu/memory/memory_nsmacro.hpp>	// centralized namespace definition
#include <interfaces/MemoryTypeEnums.hpp>		// ETLO 2/23/07 This is an odd dependency on the namespace definition TODO fix this if you can
#include <stillwater/shim/kpu/memory/MemoryDescriptor.hpp>

using namespace stillwater::slm;

MemoryElementTypeTable memoryElementTypeTable[] = {
	ENUM_EXPANDER(MET_UNSET),
	ENUM_EXPANDER(MET_UINT8),	
	ENUM_EXPANDER(MET_UINT16),
	ENUM_EXPANDER(MET_UINT32),
	ENUM_EXPANDER(MET_UINT64),
	ENUM_EXPANDER(MET_UINT128),
	ENUM_EXPANDER(MET_UINT256),
	ENUM_EXPANDER(MET_INT8),	
	ENUM_EXPANDER(MET_INT16),
	ENUM_EXPANDER(MET_INT32),
	ENUM_EXPANDER(MET_INT64),
	ENUM_EXPANDER(MET_INT128),
	ENUM_EXPANDER(MET_INT256),
	ENUM_EXPANDER(MET_REAL16),
	ENUM_EXPANDER(MET_REAL32),
	ENUM_EXPANDER(MET_REAL64),
	ENUM_EXPANDER(MET_REAL80),
	ENUM_EXPANDER(MET_REAL128),
	ENUM_EXPANDER(MET_REAL256),
	ENUM_EXPANDER(MET_CMPLX16),
	ENUM_EXPANDER(MET_CMPLX32),
	ENUM_EXPANDER(MET_CMPLX64),
	ENUM_EXPANDER(MET_CMPLX80),
	ENUM_EXPANDER(MET_CMPLX128),
	ENUM_EXPANDER(MET_CMPLX256),
	{ MET_UNSET, NULL },
};

const char* getMemoryElementType(const MemoryElementType& type) {
	int i = 0;
	while (memoryElementTypeTable[i].m_name) {
		if (memoryElementTypeTable[i].m_value == type) {
			break;
		}
		else {
			++i;
		}
	}
	if (memoryElementTypeTable[i].m_name == NULL) {
		// we didn't find anything
		return "MET_UNKNOWN";
	}
	return memoryElementTypeTable[i].m_name;
}

std::ostream& stillwater::slm::operator<<(std::ostream& ostr, const MemoryDescriptor& rhs) {
	ostr << "(" 
		 << rhs.nrOfElements()
		 << ","
		 << getMemoryElementType(rhs.elementType())
		 << ","
		 << rhs.sizeOfElement()
		 << ")";
	return ostr;
}
