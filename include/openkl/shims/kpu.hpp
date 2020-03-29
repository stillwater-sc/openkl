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
#include <openkl/openkl.hpp>
#include <openkl/shims/shim.hpp>
#include <openkl/utilities/object.hpp>

namespace openkl {
namespace shim {

class kpu : public ProxyShim {
public:
	using self = kpu;

	kpu(size_t processingElements, size_t memSize, size_t nrChannels) {
		std::stringstream ss;
		ss << "Stillwater KPU T-" << processingElements << 'x' << nrChannels;
		env.id = ss.str();
		env.procType = LOCAL_KPU;
		env.cores    = processingElements;
		env.freq     = 100;
		env.memType  = STATIC_MEM;
		env.size     = memSize;
		env.channels = nrChannels;
		env.pageSize = 4;
	}
	
	openkl::klExecutionEnvironment getEnv() const {
		return env;
	}

    friend std::ostream& operator<<(std::ostream& os, const self& dfa) noexcept
    {
		os << '{';
		os << "Fine-grain Domain Flow Architecture";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
	klExecutionEnvironment env;
    std::unique_ptr<uint8_t> memory;
};

} // namespace shim
} // namespace openkl
