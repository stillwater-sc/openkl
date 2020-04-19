// context.hpp: cloud-native knowledge processing context
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <cstddef>
#include <vector>

#include <openkl/openkl_fwd.hpp>
#include <openkl/utilities/object_repo.hpp>

namespace openkl {

#ifdef PROXY_DISPATCH_CLASS_FOR_CONTEXT
class klComputeContext {
public:
	virtual ~klComputeContext() {
		// release the compute context
	}

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT

	// claim a memory block of bytes nr of bytes
	object_id claim(size_t bytes) {
		// dispatch the claim
		return object_id();
	}
	// release a previous claim
	void release(object_id& hndl) {
	}

	/////////////////////////////////////////////////////////////////
	/// EXECUTION MANAGEMENT
	void execute(const klInstruction& cmd) {
		// dispatch the execute
	}

	// reusable base functionality 
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

private:
	// none
};
#else
// abstract base class modeling a compute context for an application
class klComputeContext {
public:
	 virtual ~klComputeContext() {
		// release the compute context
	}

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT

	// claim a memory block of bytes nr of bytes
	 virtual object_id claim(size_t bytes) = 0;
	// release a previous claim
	 virtual void release(object_id& hndl) = 0;

	/////////////////////////////////////////////////////////////////
	/// EXECUTION MANAGEMENT
	 virtual void execute(const klInstruction& cmd) = 0;

	 // reusable base functionality 
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

private:
	// none
};
#endif



} // namespace openkl
