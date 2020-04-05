/**
 * File		:	$File: //depot/Stillwater/Common/include/interfaces/ZoneTypeEnums.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	31 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2009/12/31 $
 * Location	:	$Id: //depot/Stillwater/Common/include/interfaces/ZoneTypeEnums.hpp#5 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of Stillwater
 * Supercomputing, Inc.. It may not be copied or duplicated in any form, or 
 * disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc..
 */
#ifndef ZONE_TYPE_ENUMS_INCLUDED
#define ZONE_TYPE_ENUMS_INCLUDED

NS_STILLWATER_SRM_BEGIN

/**
 * \enum ZoneType
 * \brief zone types are used to optimize specific memory usage
 */
enum ZoneType {
	ZONE_UNKNOWN    = -1,
	ZONE_DATA		= 0,	// default Zone type is data storage
	ZONE_DMA		= 1,	// DMA command buffer storage
	ZONE_MOB_DESC	= 2,	// MOB descriptors are in their own zone
};

struct ZoneTypeTable {
	ZoneType		m_value;
	const char*		m_name;
};

NS_STILLWATER_SRM_END

#endif // ZONE_TYPE_ENUMS_INCLUDED

