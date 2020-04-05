/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/Page.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #15 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/Page.cpp#15 $
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
#include <iostream>
#include <iomanip>
#include <map>
// BOOST includes
// none
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
// memory library includes
#include "./memory_nsmacro.hpp"	// centralized namespace definition
#include "./Page.hpp"

using namespace stillwater::slm;

uint8 Page::calcPageSize2LogN(uint64 pageSizeInBytes) {
	// check to see if page size is a power of 2, throw if not
	uint64 bits = pageSizeInBytes; uint8 shifts = 0;
	while (bits) {
		if (bits & 0x1) {
			if ((bits >>= 1) != 0) {
				PAGE_EXCEPTION("Page size is not power of two")(pageSizeInBytes);
			}
		}
		else {
			bits >>= 1; ++shifts;
		}
	}
	return shifts;
}

bool Page::read(uint64 offset, size_t sizeInBytes, void* pData) const {
	bool bSuccess = false;
	if (offset < static_cast<uint64>(1 << m_pageSize2LogN) &&
		sizeInBytes <= static_cast<size_t>(1 << m_pageSize2LogN)) {
		memcpy(pData, (char*)m_pData+offset, sizeInBytes);
		bSuccess = true;
	}
	return bSuccess;
}

bool Page::write(uint64 offset, size_t sizeInBytes, const void* pData) {
	bool bSuccess = false;
	if (offset < static_cast<uint64>(1 << m_pageSize2LogN) &&
		sizeInBytes <= static_cast<size_t>(1 << m_pageSize2LogN)) {
		memcpy((char*)m_pData+offset, pData, sizeInBytes);
		bSuccess = true;
	}
	return bSuccess;
}

// create a hex dump of this page
void Page::dump(std::ostream& ostr) const {
	dumpBufferInHex(ostr,m_pData,(uint32)getPageSizeInBytes());
}
