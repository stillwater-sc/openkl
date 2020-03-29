// openkl.hpp: cloud-native knowledge processing interface
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
#include <openkl/shims/kpu.hpp>

namespace openkl {

	constexpr size_t OPENKL_MAX_IDENTIFIER_SIZE = 1024;

	// Maybe better to map out the compute resource target universe with this classification
	// compute resource type: 
	// task-parallel one address space                           == multi-core CPU, SMP, NUMA 
	// data-parallel one address space                           == OpenCL FPGA, GPU
	// fine-grain data-flow                                      == DFM, KPU
	// coarse-grain data-flow (task-parallel streaming)          == DMM, Cloud-Native

	// what about Flynn's taxonomy
	// SISD  single instruction stream, single data stream       == CPU
	// MISD  multiple instruction streams, single data stream    == fault tolerance, voting CPUs
	// SIMD  single instruction stream, multiple data streams    == GPU
	// MIMD  multiple instruction streams, multiple data streams == OpenCL, DMM, DFM, KPU
	// SPMD  single program, multiple data streams               == DMM, KPU, fine DFM
	// MPMD  multiple programs, multiple data streams            == DMM, KPU, coarse DFM, Cloud-Native

	// hardware accelerators are cooperative with a processor. They may have
	// separate address spaces for performance reasons, or shared address spaces
	// for copy-free collaboration (network and graphics stacks).
	// The fact that a hw accelerator may have a separate address space for performance
	// is clearly an important attribute to be able to select the optimal algorithm
	// for that architecture.

// compute resource targets
enum klComputeResourceType {
	COMPUTE_NOP   = 0,
	LOCAL_CPU     = 1,
	REMOTE_CPU    = 2,
	CN_DMM        = 3,   // Cloud-Native Distributed Memory Machine
	LOCAL_KPU     = 4,
	REMOTE_KPU    = 5,
	REMOTE_KPUS   = 6,
	CN_CGDFM      = 7    // Cloud-Native Coarse-grain Data Flow Machine
};

constexpr char* klComputeResourceTypeString[] = {
	"NOP",
	"LOCAL_CPU",
	"REMOTE_CPU",
	"CN_DMM",
	"LOCAL_KPU",
	"REMOTE_KPU",
	"REMOTE_KPUS",
	"CN_CGDFM"
};

// Memory resource
// virtual paged, non-virtual static
// NUMA?
// BRAM - SRAM - DRAM - HBM - FLASH - NVMe
enum klMemoryResourceType {
	MEMORY_NOP     = 0,
	STATIC_MEM     = 1,
	VIRTUAL_MEM    = 2,
	NUMA           = 3,
	DISTRIBUTED    = 4,
};

constexpr char* klMemoryResourceTypeString[] = {
	"NOP",
	"STATIC MEMORY",
	"VIRTUAL MEMORY",
	"NUMA",
	"DISTRIBUTED"
};

struct klExecutionEnvironment {
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

using klComputeTargets = std::vector<klExecutionEnvironment>;

int enumerateTargets(const klExecutionEnvironment& query, klComputeTargets& devices) {
//	devices.push_back(klComputeTarget{ "SW-LAPTOP-250", klComputeResource{"Intel i7 7500u", LOCAL_CPU}, klMemoryResource{VIRTUAL, 1024 * 4, 2, 4096} });
//	devices.push_back(klComputeTarget{ "SW-LAB-KPU", klComputeResource{"Stillwater KPU T-64x8", LOCAL_KPU}, klMemoryResource{STATIC, 1024 * 2, 2, 4096} });
//	devices.push_back(klComputeTarget{ "SW-CLOUD-KPU", klComputeResource{"Stillwater KPU T-1024x32", REMOTE_KPU}, klMemoryResource{STATIC, 1024 * 32, 32, 4096} });

	// query the OpenKL proxy for the available targets
//	proxy* registry = proxy::getInstance();
//	for (size_t i = 0; i < registry->nrTargets(); ++i) {
//		devices.push_back(registry->getEnv(i));
//	}
	return 1;
} 

struct klComputeContext {
	size_t value;
};

int createContext(const klExecutionEnvironment& target, klComputeContext& ctx) {
	ctx.value = 10;
	return 1;
}

} // namespace openkl
