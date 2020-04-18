/**
 * File		:	$File: //depot/Stillwater/arch/src/Libraries/slm/baseTypes/Request.hpp $
 *
 * Authors	:	E. Theodore L. Omtzigt
 * Date		:	13 January 2007
 *
 * Source Control Information:
 * Version	:	$Revision: #13 $
 * Latest	:	$Date: 2010/02/23 $
 * Location	:	$Id: //depot/Stillwater/arch/src/Libraries/slm/baseTypes/Request.hpp#13 $
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
#ifndef SLM_REQUEST_INCLUDED
#define SLM_REQUEST_INCLUDED

NS_STILLWATER_SLM_BASE_TYPES_BEGIN

/**
 * \brief typename for addresses
 */
typedef uint64 Address;

enum RequestSize {
	BYTES_PER_WORD = 4,		// 32bit words are our minimum request size
};

/**
 * \brief request type
 */
enum RequestType {
	REQTYPE_READ		= 0,
	REQTYPE_WRITE		= 1,
};
/**
 * \brief request status
 */
enum RequestStatus {
	REQSTATUS_ERROR		= 0,
	REQSTATUS_SUCCESS	= 1,
};
/**
 * \brief RequestTarget memory target for a data token or memory request
 */
enum RequestTarget {
	REQTARGET_MEMORY	= 0,
	REQTARGET_IO		= 1,
};

/**
 * \brief class managing the words of the payload
 */
class Payload {
public:
	Payload() : m_sizeInBytes(0),m_buffer(NULL),m_bOwnership(false) {}
	Payload(uint32 sizeInBytes, const uint8* data = NULL) 
		: m_buffer(new uint8[sizeInBytes]), m_sizeInBytes(sizeInBytes), m_bOwnership(true) {
			// precondition has to be that sizeInBytes words 
			// can be contained by the data ptr.
		if (data) {
			std::copy(data,data+sizeInBytes, m_buffer);
		}
		else {
			std::fill(m_buffer,m_buffer+sizeInBytes, 0x55);
		}
	}
	Payload(const Payload& payload) {
		*this = payload;
	}
	virtual ~Payload() { if (m_bOwnership && m_buffer != NULL) delete[]m_buffer; }
	Payload& operator=(const Payload& rhs) {
		if (m_bOwnership) {
			if (m_sizeInBytes != rhs.m_sizeInBytes) {
				// we need to delete the old storage and create a new one
				if (m_buffer != NULL) delete[] m_buffer;
				m_buffer		= new uint8[m_sizeInBytes];
				m_sizeInBytes	= rhs.m_sizeInBytes;
				m_bOwnership	= true;
			}
		}
		else {
			// need to create payload storage
			m_buffer		= new uint8[m_sizeInBytes];
			m_sizeInBytes	= rhs.m_sizeInBytes;
			m_bOwnership	= true;
		}
		// do the actual copy of data
		std::copy(rhs.m_buffer,rhs.m_buffer+rhs.m_sizeInBytes, m_buffer);
		return *this;
	}
	/**
	 * \brief prep is used to create an uninitialized buffer
	 * This is the most efficient way to create storage for
	 * a Response given the info provided by a Request.
	 */
	void prep(uint32 sizeInBytes) {
		if (m_bOwnership && m_buffer != NULL) {
			delete[] m_buffer;
		}
		m_sizeInBytes	= sizeInBytes;
		if (sizeInBytes > 0) {
			m_buffer		= new uint8[m_sizeInBytes];
		}
		else {
			m_buffer = NULL;
		}
		m_bOwnership	= true;
	}
	/**
	 * \brief masquerade is used to use a preallocated buffer
	 * This means we don't own the buffer and thus can't
	 * be deleting it when this object instance goes out
	 * of scope.
	 */
	void masquerade(uint32 sizeInBytes, uint8* buffer) {
		if (m_bOwnership && m_buffer != NULL) {
			delete[] m_buffer;
		}
		m_sizeInBytes	= sizeInBytes;
		m_buffer		= buffer;
		m_bOwnership	= false;
	}
	uint8* getBuffer() { return m_buffer; }

	// selectors, use const to enforce non-modification
	uint32 sizeInBytes() const { return m_sizeInBytes; }
	const uint8* getBuffer() const { return m_buffer; }
protected:
	uint32 m_sizeInBytes;
	uint8* m_buffer;
	bool   m_bOwnership;
private:
	friend std::ostream& operator<<(std::ostream& ostr, const Payload& rhs) {
		ostr << "[" << rhs.m_sizeInBytes << "bytes("
				<< (rhs.m_bOwnership ? "owner" : "masquerade")
				<< "),[";
		if (rhs.m_sizeInBytes > 8) {
			// print the first 4 and follow it with ellipses
			for (uint32 i = 0; i < rhs.m_sizeInBytes; i++) {
				ostr << hexint(rhs.m_buffer[i]) << ",";
			}
			ostr << "...]";
		}
		else {
			uint32 last = rhs.m_sizeInBytes-1;
			for (uint32 i = 0; i < last; i++) {
				ostr << hexint(rhs.m_buffer[i]) << ",";
			}
			ostr << hexint(rhs.m_buffer[last]) << "]";
		}
		return ostr;
	}
};

/**
 * \brief generic request type
 */
class Request {
public:
	typedef boost::shared_ptr<Request>	SharedPtr;

	Request() : m_type(REQTYPE_READ),m_target(REQTARGET_MEMORY),m_address(0),m_payload(0) {}
	Request(const RequestType type, const RequestTarget target, 
			const Address& address, const uint32& sizeInBytes, const uint8* data = NULL) 
		: m_type(type),m_target(target),m_address(address), m_payload(sizeInBytes,data) {}
	Request(const RequestType type, const RequestTarget target, const Address& address, const Payload& payload) 
		: m_type(type),m_target(target),m_address(address), m_payload(payload) {}
	Request(const Request& rhs) {
		*this = rhs;
	}
	virtual ~Request() {}
	Request& operator=(const Request& rhs) {
		m_type = rhs.m_type;
		m_target = rhs.m_target;
		m_address = rhs.m_address;
		m_payload = rhs.m_payload;
		m_portId = rhs.m_portId;
		return *this;
	}
	uint32 sizeInBytes() const { return m_payload.sizeInBytes(); }
	const uint8* getBuffer() const { return m_payload.getBuffer(); }

	RequestType		m_type;
	RequestTarget	m_target;
	Address			m_address;
	Payload			m_payload;
	uint32			m_portId;		// used for debug
private:
	friend std::ostream& operator<<(std::ostream& ostr, const Request& rhs) {
		return ostr << (rhs.m_target == REQTARGET_MEMORY ? "MEM_" : "IO_") 
			<< (rhs.m_type == REQTYPE_READ ? "READ(" : "WRITE(") 
			<< std::setw(10) << hexint(rhs.m_address) << "," 
			<< rhs.m_payload << ")";
	}
};

/**
 * \brief generic response type
 */
class Response {
public:
	typedef boost::shared_ptr<Response>	SharedPtr;

	Response() : m_status(REQSTATUS_ERROR),m_payload(0) {}
	Response(const RequestStatus& status, uint32 sizeInBytes, const uint8* data = NULL)
		: m_status(status),m_payload(sizeInBytes,data) {}
	Response(const RequestStatus& status, const Payload& payload) 
		: m_status(status),m_payload(payload.sizeInBytes(),payload.getBuffer()) {}
	Response(const Response& rhs) {
		*this = rhs;
	}
	virtual ~Response() {}

	Response& operator=(const Response& rhs) {
		m_status = rhs.m_status;
		m_payload = rhs.m_payload;
		return *this;
	}
	void prep(uint32 sizeInBytes) {
		m_payload.prep(sizeInBytes);
	}
	void masquerade(uint32 sizeInBytes, uint8* data) {
		m_payload.masquerade(sizeInBytes, data);
	}
	// selectors, use const to enforce non-modification
	uint32 sizeInBytes() const { return m_payload.sizeInBytes(); }
	const uint8* getBuffer() const { return m_payload.getBuffer(); }

	RequestStatus	m_status;
	Payload			m_payload;

private:
	friend std::ostream& operator<<(std::ostream& ostr, const Response& rhs) {
		return ostr << (rhs.m_status == REQSTATUS_ERROR ? "REQSTATUS_ERROR" : "REQSTATUS_SUCCESS") << rhs.m_payload;
	}
};

NS_STILLWATER_SLM_BASE_TYPES_END

#endif // SLM_REQUEST_INCLUDED


