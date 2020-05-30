/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/memory/RequestGenerator.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	4 August 2006
 *
 * Source Control Information:
 * Version	:	$Revision: #3 $
 * Latest	:	$Date: 2007/08/04 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/memory/RequestGenerator.hpp#3 $
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
#ifndef STILLWATER_ADDRESS_GENERATOR_INCLUDED
#define STILLWATER_ADDRESS_GENERATOR_INCLUDED

NS_STILLWATER_SLM_MEMORY_BEGIN

/** 
 * \class RequestGenerator RequestGenerator.hpp "RequestGenerator.hpp"
 * \brief RequestGenerator models a request stream operator
 *
 * In the Stillwater SA (Streaming Architecture) there is a transformation
 * from dependency relationships to precedence relationships. The
 * Processor Array (PA) works with precedence relationships, 
 * whereas memory work with dependence relationships. The
 * RequestGenerators are the vehicle with which we cross this
 * semantic difference. The RequestGenerators typically empty
 * into and out of stream caches which are optimized for the
 * typical data flow of vector streams.
 */
class RequestGenerator {
public:
	/**
	 * default constructor
	 */
	RequestGenerator(const std::string& instanceName);
	
	/**
	 * virtual destructor: we can derive from this object to implement
	 * more specialized
	 */
	~RequestGenerator();

	// operators
	// none

	// selectors, use const to enforce non-modification


	// modifiers
	/**
	 * \brief initialize sets up the address generator's starting conditions
	 * Subsequent calls to next will generate a Request structure with
	 * the attributes of the next request
	 */
	void initialize(const RequestType& type, const Address& startAddress, const Address& stride, uint32_t m_requestSizeInBytes, uint32_t requestCount);

	/**
	 * \brief test if there are still requests to be generated
	 * \return boolean true if not done, false otherwise
	 * The usage pattern is a loop like this:
	 * while (next()) {
	 *		rg.request(request);
	 * }
	 */
	bool next() const;
	/**
	 * \brief generate the next request
	 * The usage pattern is a loop like this:
	 * while (next()) {
	 *		rg.generate(request);
	 * }
	 */
	Request* generate();

protected:
	// member variables
	/**
	 * an instance name so we can tag statistics properly
	 */
	std::string			m_instanceName;
	/**
	 * the request type, one of READ or WRITE, of the address stream
	 */
	RequestType			m_type;
	/**
	 * starting address of the stream
	 */
	Address				m_startAddress;
	/**
	 * the address for the next request
	 */
	Address				m_address;
	/**
	 * address stride of subsequent requests in the stream
	 */
	Address				m_stride;
	/**
	 * request size in bytes
	 */
	uint32_t			m_requestSizeInBytes;
	/**
	 * repeat count of the stream
	 */
	uint32_t			m_requestCount;
	/**
	 * the actual request generated count
	 */
	uint32_t			m_count;

	// helpers



	// statistics

};


NS_STILLWATER_SLM_MEMORY_END

#endif // STILLWATER_ADDRESS_GENERATOR_INCLUDED


