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

	constexpr size_t SIZE_1G = 1073741824ll;
	constexpr size_t SIZE_2G = 2147483648ll;
	constexpr size_t SIZE_3G = 3221225472ll;
	constexpr size_t SIZE_4G = 4294967296ll;
	constexpr size_t SIZE_5G = 5368709120ll;
	constexpr size_t SIZE_6G = 6442450944ll;
	constexpr size_t SIZE_7G = 7516192768ll;
	constexpr size_t SIZE_8G = 8589934592ll;
	constexpr size_t SIZE_16G = 17179869184ll;
	constexpr size_t SIZE_32G = 34359738368ll;
	constexpr size_t SIZE_64G = 68719476736ll;
	constexpr size_t SIZE_128G = 137438953472ll;
	constexpr size_t SIZE_256G = 274877906944ll;
	constexpr size_t SIZE_512G = 549755813888ll;
	constexpr size_t SIZE_1T = 1009511627776ll;

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
