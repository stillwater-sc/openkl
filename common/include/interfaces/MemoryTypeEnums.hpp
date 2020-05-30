/**
 * File		:	$File: //depot/Stillwater/Common/include/interfaces/MemoryTypeEnums.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	31 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/08/03 $
 * Location	:	$Id: //depot/Stillwater/Common/include/interfaces/MemoryTypeEnums.hpp#6 $
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
#ifndef MEMORY_TYPE_ENUMS_INCLUDED
#define MEMORY_TYPE_ENUMS_INCLUDED

/**
 * \brief encoding the type AND the size in bytes with an integer/real bit
 * do we need to also support complex?
 * is this encoding power friendly?
 *		I would think that a binary encoding where there is
 *		only 1 bit high is a better encoding.
 *		This would mean size in bytes as a direct encoding.
 *		Since we stop at data sizes of 32 bytes, we
 *		can start the encoding of integer/real/complex
 *		at the second byte. Thus the first byte is a
 *		binary encoding of the number of bytes, and
 *		the second byte encodes integer/real/complex
 */
enum MemoryElementType { 
	MET_UNSET	 = 0,
	MET_UINT8    = 0x001,	
	MET_UINT16   = 0x002,
	MET_UINT32   = 0x004,
	MET_UINT64   = 0x008,
	MET_UINT128  = 0x010,
	MET_UINT256  = 0x020,
	MET_INT8     = 0x101,	
	MET_INT16    = 0x102,
	MET_INT32    = 0x104,
	MET_INT64    = 0x108,
	MET_INT128   = 0x110,
	MET_INT256   = 0x120,
	MET_REAL16   = 0x202,
	MET_REAL32   = 0x204,
	MET_REAL64   = 0x208,
	MET_REAL80   = 0x20A,
	MET_REAL128  = 0x220,
	MET_REAL256  = 0x240,
	MET_CMPLX16  = 0x402,
	MET_CMPLX32  = 0x404,
	MET_CMPLX64  = 0x408,
	MET_CMPLX80  = 0x40A,
	MET_CMPLX128 = 0x420,
	MET_CMPLX256 = 0x440,
	MET_UNKNOWN  = 0xFFF,
};

// structure to map the above enum values to strings
struct MemoryElementTypeTable {
	MemoryElementType	m_value;
	const char*			m_name;
};

#endif // MEMORY_TYPE_ENUMS_INCLUDED

