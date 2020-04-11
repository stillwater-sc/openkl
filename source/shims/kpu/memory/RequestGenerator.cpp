/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/RequestGenerator.cpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #6 $
 * Latest	:	$Date: 2007/11/14 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/RequestGenerator.cpp#6 $
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
// STL includes
#include <vector>
#include <map>
#include <memory>
// STILLWATER includes
#include <stillwater/baseTypes.hpp>
#include <stillwater/exceptions.hpp>
#define STILLWATER_DIAGNOSTICS	// define macro to enable the diagnostics functionality
#include <stillwater/diagnostics.hpp>
#include <stillwater/automation.hpp>
// STILLWATER SLM components
#include <stillwater/arch/baseTypes/slmBaseTypes_nsmacro.hpp>
#include <stillwater/arch/baseTypes/Request.hpp>
// SLM Cache library includes
#include "./memory_nsmacro.hpp"	// centralized namespace definition
#include "./RequestGenerator.hpp"

using namespace stillwater::slm;

RequestGenerator::RequestGenerator(const std::string& instanceName) : m_instanceName(instanceName) {
}

RequestGenerator::~RequestGenerator() {
}

void RequestGenerator::initialize(const RequestType& type, const Address& startAddress, const Address& stride, 
								  uint32_t requestSizeInBytes, uint32_t requestCount) {
	m_type					= type;
	m_startAddress			= startAddress;
	m_address				= startAddress;
	m_stride				= stride;
	m_requestSizeInBytes	= requestSizeInBytes;
	m_requestCount			= requestCount;
	m_count					= 0;
}

bool RequestGenerator::next() const {
	return (m_count < m_requestCount ? true : false);
}

Request* RequestGenerator::generate() {
	Request* pReq = new Request(m_type, REQTARGET_MEMORY,m_address,m_requestSizeInBytes);
	m_address += m_stride;
	m_count++;
	return pReq;
}


