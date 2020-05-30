/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/baseTypes/slmBaseTypes_nsmacro.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	13 January 2007
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2007/11/24 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/baseTypes/slmBaseTypes_nsmacro.hpp#3 $
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
#ifndef NS_STILLWATER_SLM_BASE_TYPES_BEGIN
#define NS_STILLWATER_SLM_BASE_TYPES_BEGIN namespace stillwater { namespace slm {
#define NS_STILLWATER_SLM_BASE_TYPES_END } }

// when we include this it is clear that we want to use this namespace.
// So we declare its use also. This allows us to not have to explicity
// have to code it in the different source files where it is used.
NS_STILLWATER_SLM_BASE_TYPES_BEGIN
const int stillwater_slm_base_types_dummy = 0; // dummy declaration so that we can use the using construct
NS_STILLWATER_SLM_BASE_TYPES_END
using namespace stillwater::slm;

#endif // NS_STILLWATER_SLM_BASE_TYPES_BEGIN
