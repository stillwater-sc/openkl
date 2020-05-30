// kpu.hpp: shim for the KPU functional simulator
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
#include <openkl/base_types.h>

#include <openkl/shims/shim.hpp>
#include <stillwater/shim/kpu/kpu_fsim.hpp>


namespace openkl {
namespace shim {

class KnowledgeProcessingUnit : public Shim {
public:

	KnowledgeProcessingUnit(size_t processingElements, size_t memorySize, size_t pageSizeInBytes, size_t nrChannels) 
		: kpu(memorySize, pageSizeInBytes, nrChannels)
	{
		std::stringstream ss;
		
		ss << "Stillwater KPU T-" << processingElements << 'x' << nrChannels;
		
		_id          = ss.str();
		_procType    = LOCAL_KPU;
		_cores       = processingElements;
		_threads     = 1;
		_mhz         = 100;
		_memoryType  = STATIC_MEM;
		_memorySize  = memorySize;
		_channels    = nrChannels;
		_pageSize    = pageSizeInBytes;
	}
	

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT
	bool create() {
		// create a KPU functional simulator
		kpu.reset();
		return false;
	}

	// claim a memory block of bytes nr of bytes
	object_id claim(size_t bytes) {
		object_id hndl;

		// how do we implement memory scather?
		// this needs to be implemented by the Resource Manager

		// for now we just generate a random channel
		size_t chn = rand() % _channels;
		size_t offset = rand() % _memorySize;
		Address addr = chn * _memorySize + offset;

		// create a mob of nulls
		MemoryObject mob(bytes, MET_UINT8);
		kpu.write(addr, mob);

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
    friend std::ostream& operator<<(std::ostream& os, const KnowledgeProcessingUnit& dfa) noexcept
    {
		os << '{';
		os << "Fine-grain Domain Flow Architecture";
		os << '}';
        return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
	stillwater::slm::KpuFsim kpu;
};

} // namespace shim
} // namespace openkl
