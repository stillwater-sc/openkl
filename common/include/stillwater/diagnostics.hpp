/**
 * File		:	$File: //depot/Stillwater/Common/include/stillwater/diagnostics.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	29 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #10 $
 * Latest	:	$Date: 2010/01/03 $
 * Location	:	$Id: //depot/Stillwater/Common/include/stillwater/diagnostics.hpp#10 $
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
#ifndef STILLWATER_DIAGNOSTICS_INCLUDED
#define STILLWATER_DIAGNOSTICS_INCLUDED

// STD library
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>

/**
 * \class CONSUME_RECURSIVELY
 */
enum CONSUME_RECURSIVELY {
	IGNORE_A = 0,
	IGNORE_B = 1
};

// context base class
#include <stillwater/Context.hpp>

// diagnostics classes 
#include <stillwater/diagnostics/diagnostics_nsmacro.hpp>
#include <stillwater/diagnostics/DiagContext.hpp>
#include <stillwater/diagnostics/ConsoleLogTarget.hpp>
#include <stillwater/diagnostics/FileLogTarget.hpp>
#include <stillwater/diagnostics/Logger.hpp>
#include <stillwater/diagnostics/TimeMonitor.hpp>

// provide the capability to null the diagnostics macros to nothingness
// If STILLWATER_DIAGNOSTICS is defined, the macros will recursively
// consume and transform the information into the proper contexts
#ifdef STILLWATER_DIAGNOSTICS
	// provide some compilation feedback for this state
	#ifdef WIN32
	#pragma Reminder("Diagnostics are turned ON for this source file")
	#endif

	#define IGNORE_A(expr) IGNORE_B
	#define IGNORE_B(expr) IGNORE_A

	#define DIAG_STREAM *(::stillwater::diagnostics::Logger::getLogger())
	#define DIAG_CONTEXT *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "")

	#define DIAG_FATAL *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "FATAL")
	#define DIAG_ERROR *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "ERROR")
	#define DIAG_WARN *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "WARN")
	#define DIAG_INFO *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "INFO")
	#define DIAG_DEBUG *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "DEBUG")

	#define DIAG_LOW_DETAIL *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "LOW")
	#define DIAG_MEDIUM_DETAIL *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "MEDIUM")
	#define DIAG_HIGH_DETAIL *(::stillwater::diagnostics::Logger::getLogger()) << *CREATE_CONTEXT_AND_CONSUME(::stillwater::diagnostics::DiagContext, "HIGH")

#else
	// provide some compilation feedback for this state
//	#ifdef WIN32
//	#pragma Reminder("Diagnostics are turned OFF for this source file")
//	#endif

	// we have to fake out the macros
	#define IGNORE_A(expr) IGNORE_B
	#define IGNORE_B(expr) IGNORE_A

	#define DIAG_STREAM std::cerr
	#define DIAG_CONTEXT(expr) IGNORE_A

	#define DIAG_DEBUG(expr) IGNORE_A
	#define DIAG_INFO(expr) IGNORE_A
	#define DIAG_WARN(expr) IGNORE_A
	#define DIAG_ERROR(expr) IGNORE_A
	#define DIAG_FATAL(expr) IGNORE_A

	#define DIAG_LOW_DETAIL IGNORE_A
	#define DIAG_MEDIUM_DETAIL IGNORE_A
	#define DIAG_HIGH_DETAIL IGNORE_A

#endif // STILLWATER_DIAGNOSTICS

// auto-linking
#ifdef WIN32
	// Since diagnostics.hpp gets included everywhere, the
	// default behavior is to NOT auto-link. The application's
	// precompiled header needs to set the AUTO_LINK macro
	// to have diagnostics linked in.
	#ifdef AUTO_LINK
		/////////////////////////////////////////////////////////////////
		// The DevStudio compiler supports pragmas that specify to the linker
		// which libraries to link against. This can be used to 
		// automatically link the proper library given an include file
		// and the compiler's flags.
		#ifdef _DEBUG
		// automatic linking
			#pragma message ("Linking with Static Multi-threaded DLL-RT Debug (mdd) Library diagnostics_mdd.lib")
			#pragma comment (lib, "diagnostics_mdd.lib")
		#else
			#pragma message ("Linking with Static Multi-threaded DLL-RT Release (mdr) Library diagnostics_mdr.lib")
			#pragma comment (lib, "diagnostics_mdr.lib")
		#endif
	#endif
#endif

#endif // STILLWATER_DIAGNOSTICS_INCLUDED

