// shim.hpp
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
#include <openkl/utilities/object.hpp>

namespace openkl {
namespace shim {

	// base class for shims
class Shim {
public:
	Shim() = default;
	Shim(const Shim&) = default;
	Shim& operator=(const Shim&) = default;

	void set(const std::string& id,
		     klComputeResourceType procType, size_t cores, size_t threads, size_t mhz, 
		     klMemoryResourceType memType, size_t memSize, size_t memChannels, size_t pageSize) {
		_id = id;
		
		// processing component
		_procType = procType;
		_cores = cores;
		_threads = threads;
		_mhz = mhz;

		// memory component
		_memoryType = memType;
		_memorySize = memSize;
		_channels = memChannels;
		_pageSize = pageSize;
	}

	std::string             id() { return _id; }
	klComputeResourceType   procType() { return _procType; }
	size_t cores() { return _cores; }
	size_t threads() { return _threads; }
	size_t mhz() { return _mhz; }

	klMemoryResourceType    memoryType() { return _memoryType; }
	size_t memorySize() { return _memorySize; }
	size_t channels() { return _channels; }
	size_t pageSize() { return _pageSize; }

protected:
	std::string             _id;
	klComputeResourceType   _procType;
	size_t                  _cores;
	size_t                  _threads;
	size_t                  _mhz;     // core frequency in MHz
	klMemoryResourceType    _memoryType;
	size_t                  _memorySize;     // memory size in MBytes
	size_t                  _channels; // number of channels of memory
	size_t                  _pageSize; // page size in KBytes
};

} // namespace shim
} // namespace openkl
