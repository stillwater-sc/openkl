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

class KnowledgeProcessingUnit : public ProxyShim {
public:
	static KnowledgeProcessingUnit* getInstance() {
		return instance.get();
	}

	KnowledgeProcessingUnit(size_t processingElements, size_t memSize, size_t nrChannels) {
		std::stringstream ss;
		
		ss << "Stillwater KPU T-" << processingElements << 'x' << nrChannels;
		
		id = ss.str();
		procType = LOCAL_KPU;
		cores    = processingElements;
		freq     = 100;
		memType  = STATIC_MEM;
		size     = memSize;
		channels = nrChannels;
		pageSize = 1;
	}
	
    friend std::ostream& operator<<(std::ostream& os, const KnowledgeProcessingUnit& dfa) noexcept
    {
		os << '{';
		os << "Fine-grain Domain Flow Architecture";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
	static std::unique_ptr<KnowledgeProcessingUnit> instance;

	std::string             id;
	klComputeResourceType   procType;
	size_t                  cores;
	size_t                  threads;
	size_t                  freq;     // core frequency in MHz
	klMemoryResourceType    memType;
	size_t					size;     // memory size in MBytes
	size_t                  channels; // number of channels of memory
	size_t                  pageSize; // page size in KBytes
};

} // namespace shim
} // namespace openkl
