/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/statistics.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #4 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/statistics.hpp#4 $
 *
 * Organization:
 *		Stillwater Supercomputing, Inc.
 *		P.O Box 720
 *		South Freeport, ME 04078-0720
 *
 * Copyright (c) 2006 E. Theodore L. Omtzigt
 *
 * This document contains unpublished and proprietary information of
 * Stillwater Supercomputing, Inc. It may not be copied or duplicated in
 * any form, or disclosed to third parties without the written consent of 
 * Stillwater Supercomputing, Inc.
 */
#ifndef STILLWATER_STATISTICS_LIBRARY_INCLUDED
#define STILLWATER_STATISTICS_LIBRARY_INCLUDED

// STDC includes
#include <math.h>
// STL includes
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
// Platform specific
#ifdef WIN32
#include <tchar.h>
#else
// non-win32 platforms
#endif
// Stillwater includes
#include <stillwater/baseTypes.hpp>
// library includes
#include <stillwater/statistics/statistics_nsmacro.hpp>
#include <stillwater/statistics/SummaryStatistic.hpp>
#include <stillwater/statistics/Histogram.hpp>

#endif // STILLWATER_STATISTICS_LIBRARY_INCLUDED

