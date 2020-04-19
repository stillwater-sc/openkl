// kpu.hpp
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <memory>
#include <ostream>
#include <sstream>
#include <algorithm>

#include <openkl/openkl_fwd.hpp>
#include <openkl/base_types.h>
#include <openkl/shims/shim.hpp>
#include <openkl/utilities/object.hpp>



namespace openkl {



namespace shim {

class KnowledgeProcessingUnit : public Shim {
public:

	KnowledgeProcessingUnit(size_t processingElements, size_t memSize, size_t nrChannels) {
		std::stringstream ss;
		
		ss << "Stillwater KPU T-" << processingElements << 'x' << nrChannels;
		
		_id          = ss.str();
		_procType    = LOCAL_KPU;
		_cores       = processingElements;
		_threads     = 1;
		_mhz         = 100;
		_memoryType  = STATIC_MEM;
		_memorySize  = memSize;
		_channels    = nrChannels;
		_pageSize    = 1;
	}
	

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT
	bool create() {
		// create a KPU functional simulator
		return false;
	}

	// claim a memory block of bytes nr of bytes
	object_id claim(size_t bytes) {
		object_id hndl;

		return hndl;
	}
	// release a previous claim
	void release(object_id& hndl) {
	}

	/////////////////////////////////////////////////////////////////
	/// EXECUTION MANAGEMENT
	void execute(const klInstruction& cmd) {

	}

	/// ostream
    friend std::ostream& operator<<(std::ostream& os, const KnowledgeProcessingUnit& dfa) noexcept
    {
		os << '{';
		os << "Fine-grain Domain Flow Architecture";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:

};

} // namespace shim
} // namespace openkl
