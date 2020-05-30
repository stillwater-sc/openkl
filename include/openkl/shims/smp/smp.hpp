// smp.hpp
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
#include <algorithm>

//#include <openkl/openkl_fwd.hpp>
#include <openkl/base_types.h>
#include <openkl/shims/shim.hpp>
#include <openkl/utilities/object.hpp>
#include <openkl/utilities/object_id.hpp>

namespace openkl {
namespace shim {

class SymmetricMultiProcessor : public Shim
{
    using self= SymmetricMultiProcessor;
public:

	SymmetricMultiProcessor(const std::string& id, size_t cores, size_t threads, size_t mhz, size_t memSize, size_t nrChannels) {
		_id = id;
		_procType = LOCAL_CPU;
		_cores = cores;
		_threads = threads;
		_mhz = mhz;
		_memoryType = VIRTUAL_MEM;
		_memorySize = memSize;
		_channels = nrChannels;
		_pageSize = 4;
	}

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT
	bool create() {
		// create a Symmetric Multi Processor functional simulator
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

	/////////////////////////////////////////////////////////////////
/// simulation statistic reporting
	void report(std::ostream& ostr) {
		ostr << *this << std::endl;
	}

	/// ostream
    friend std::ostream& operator<<(std::ostream& os, const self& server) noexcept
    {
        os << '{';
		os << "Symmetric Multi Processor without hw accelerators";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
	// none
};

} // namespace shim
} // namespace openkl
