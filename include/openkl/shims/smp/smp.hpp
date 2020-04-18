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

namespace openkl {
namespace shim {

class SymmetricMultiProcessor : public Shim
{
    using self= SymmetricMultiProcessor;
public:
	static SymmetricMultiProcessor* getInstance() {
		return instance.get();
	}

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

    friend std::ostream& operator<<(std::ostream& os, const self& server) noexcept
    {
        os << '{';
		os << "Symmetric Multi Processor without hw accelerators";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
	static std::unique_ptr<SymmetricMultiProcessor> instance;
};

} // namespace shim
} // namespace openkl
