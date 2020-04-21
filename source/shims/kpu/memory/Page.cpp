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
// STD includes
#include <iostream>
#include <iomanip>
#include <map>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
// memory library includes
#include <stillwater/shim/kpu/memory/memory_nsmacro.hpp>	// centralized namespace definition
#include <stillwater/shim/kpu/memory/Page.hpp>

using namespace stillwater::slm;

uint8_t Page::calcPageSize2LogN(uint64_t pageSizeInBytes) {
	// check to see if page size is a power of 2, throw if not
	uint64_t bits = pageSizeInBytes; uint8_t shifts = 0;
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

bool Page::read(uint64_t offset, size_t sizeInBytes, void* pData) const {
	bool bSuccess = false;
	if (offset < static_cast<uint64_t>(uint64_t(1) << m_pageSize2LogN) &&
		sizeInBytes <= static_cast<size_t>(size_t(1) << m_pageSize2LogN)) {
		memcpy(pData, (char*)m_pData+offset, sizeInBytes);
		bSuccess = true;
	}
	return bSuccess;
}

bool Page::write(uint64_t offset, size_t sizeInBytes, const void* pData) {
	bool bSuccess = false;
	if (offset < static_cast<uint64_t>(uint64_t(1) << m_pageSize2LogN) &&
		sizeInBytes <= static_cast<size_t>(size_t(1) << m_pageSize2LogN)) {
		memcpy((char*)m_pData+offset, pData, sizeInBytes);
		bSuccess = true;
	}
	return bSuccess;
}

// create a hex dump of this page
void Page::dump(std::ostream& ostr) const {
	dumpBufferInHex(ostr,m_pData,(uint32_t)getPageSizeInBytes());
}
