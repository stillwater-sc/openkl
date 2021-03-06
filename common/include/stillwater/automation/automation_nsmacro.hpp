/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation/automation_nsmacro.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	13 January 2007
 *
 * Source Control Information:
 * Version	:	$Revision: #2 $
 * Latest	:	$Date: 2007/11/17 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation/automation_nsmacro.hpp#2 $
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
#ifndef NS_STILLWATER_AUTOMATION_BEGIN
#define NS_STILLWATER_AUTOMATION_BEGIN namespace stillwater { namespace automation {
#define NS_STILLWATER_AUTOMATION_END } }

#define NS_STILLWATER_AUTOMATION_KNOBS_BEGIN namespace stillwater { namespace automation { namespace knobs {
#define NS_STILLWATER_AUTOMATION_KNOBS_END } } }

#define NS_STILLWATER_AUTOMATION_GAUGES_BEGIN namespace stillwater { namespace automation { namespace gauges {
#define NS_STILLWATER_AUTOMATION_GAUGES_END } } }

#define NS_STILLWATER_AUTOMATION_VISITORS_BEGIN namespace stillwater { namespace automation { namespace visitors {
#define NS_STILLWATER_AUTOMATION_VISITORS_END } } }

// when we include this it is clear that we want to use this namespace.
// So we declare its use also. This allows us to not have to explicity
// have to code it in the different source files where it is used.
NS_STILLWATER_AUTOMATION_BEGIN
const int stillwater_automation_dummy = 0; // dummy declaration so that we can use the using construct
NS_STILLWATER_AUTOMATION_END

using namespace stillwater::automation;
#endif // NS_STILLWATER_AUTOMATION_BEGIN
