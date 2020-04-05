/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/automation.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	1 September 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #5 $
 * Latest	:	$Date: 2007/08/14 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/automation.hpp#5 $
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
#ifndef AUTOMATION_LIBRARY_INCLUDED
#define AUTOMATION_LIBRARY_INCLUDED

// STL includes
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <variant>

// Platform specific
#ifdef WIN32
#include <tchar.h>
#else
#endif

// STILLWATER includes
#include <stillwater/baseTypes.hpp>

// library includes
#include <stillwater/automation/automation_nsmacro.hpp>
// Registry class used by Parameter
#include <stillwater/automation/Registry.hpp>			// a generic registry of objects through a map of name and shared_ptr<> key/value pairs
#include <stillwater/automation/ReferenceRegistry.hpp>	// a generic registry of objects through a map of name and ptr key/value pairs
// EventCount classes
#include <stillwater/automation/EventCount.hpp>
#include <stillwater/automation/EventCountSet.hpp>
// Parameter Space classes
#include <stillwater/automation/ParameterVariant.hpp>	// the core data type used to contain parameter values
#include <stillwater/automation/Visitors.hpp>			// visitor classes to operate on parameters, which are boost variants
#include <stillwater/automation/Parameter.hpp>			// Parameter uses the ParameterSet in its constructor
#include <stillwater/automation/ParameterSet.hpp>		// the singleton that actually holds the parameters
#include <stillwater/automation/ParameterFactory.hpp>
#include <stillwater/automation/ParameterSpaceEnumerator.hpp>

#endif // AUTOMATION_LIBRARY_INCLUDED


