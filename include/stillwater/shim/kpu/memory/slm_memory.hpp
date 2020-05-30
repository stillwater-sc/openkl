/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/slm_memory.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	18 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #8 $
 * Latest	:	$Date: 2010/01/01 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/slm_memory.hpp#8 $
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
 *
 * This standard include file to use
 * the functionality of the SLM Memory library
 * is intended just for the test bench
 * of the library. For global use a similarly
 * named include file will be provided but
 * it will be served from a central location.
 */
#include <stillwater/baseTypes.hpp>
#include <stillwater/statistics.hpp>
#include <stillwater/automation.hpp>

#include "./memory_nsmacro.hpp"
#include <interfaces/MemoryTypeEnums.hpp>	// TODO fix me ETLO 2/23/07
#include "./Page.hpp"
#include "./MemoryDescriptor.hpp"
#include "./Memory.hpp"
#include "./MemoryObject.hpp"
#include "./MobMemory.hpp"

#include "./Cache.hpp"
#include "./RequestGenerator.hpp"

/**
 * The slm_memory library contains debugging/logging capability that is enabled
 * for each individual class in the cpp file.
 * This allows us to generate detailed debugging log information on a per component basis.
 * However, this makes it also possible for an other developer to modify the behavior
 * of logging. The failure mode is when another developer modifies the logging enable
 * and checks in the file. This could turn on or off detailed logging and mess up
 * another developers view of the world. The production code should always have logging
 * disabled, and only inside a sandbox should the logging be enabled.
 */