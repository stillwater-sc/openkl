/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/stdafx.h $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #12 $
 * Latest	:	$Date: 2007/12/09 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/memory-test/stdafx.h#12 $
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
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
// STL includes
#include <iostream>
#include <iomanip>
#include <deque>
// BOOST includes
// none
// platform specific
#ifdef WIN32
#include <tchar.h>
#endif

// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#define STILLWATER_DIAGNOSTICS
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <Stillwater/arch/src/Libraries/slm/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <Stillwater/arch/src/Libraries/slm/baseTypes/Request.hpp>
// the memory library includes
#include "../slm_memory.hpp"

// the necessary CPPUNIT includes
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
