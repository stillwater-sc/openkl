// openkl.hpp: cloud-native knowledge processing interface
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <cstddef>
#include <vector>

#include <openkl/openkl_fwd.hpp>

namespace openkl {

	constexpr size_t OPENKL_MAX_IDENTIFIER_SIZE = 1024;

// compute resource targets
enum klComputeResourceType {
	COMPUTE_NOP   = 0,
	LOCAL_CPU     = 1,
	REMOTE_CPU    = 2,
	REMOTE_CPUS   = 3,
	LOCAL_KPU     = 4,
	REMOTE_KPU    = 5,
	REMOTE_KPUS   = 6
};

constexpr char* klComputeResourceTypeString[] = {
	"NOP",
	"LOCAL_CPU",
	"REMOTE_CPU",
	"REMOTE_CPUS",
	"LOCAL_KPU",
	"REMOTE_KPU",
	"REMOTE_KPUS"
};

// compute resource type: sequential, data-parallel, fine-grain data-flow, coarse-grain data-flow?
struct klComputeResource {
	char                    id[OPENKL_MAX_IDENTIFIER_SIZE];
	klComputeResourceType   resourceType;

};

// Memory resource
// virtual paged, non-virtual static
// NUMA?
// BRAM - SRAM - DRAM - HBM - FLASH - NVMe
enum klMemoryResourceType {
	MEMORY_NOP     = 0,
	STATIC         = 1,
	VIRTUAL        = 2,
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

struct klMemoryResource {
	klMemoryResourceType    resourceType;
	size_t					size;   // memory size in MBytes
	size_t                  channels; // number of channels of memory
	size_t                  pageSize; // page size in KBytes
};

struct klComputeTarget {
	char					id[OPENKL_MAX_IDENTIFIER_SIZE];
	klComputeResource	    compute;
	klMemoryResource        memory;
};

using klComputeTargets = std::vector<klComputeTarget>;

struct klComputeTargetQuery {
	klComputeResource computeAttributes; // attributes of compute resource we would like to use
	klMemoryResource  memoryAttributes;  // attributes of the memory we would like to use
};


int enumerate_targets(klComputeTargets& devices, klComputeTargetQuery& query) {
	devices.push_back(klComputeTarget{ "SW-LAPTOP-250", klComputeResource{"Intel i7 7500u", LOCAL_CPU}, klMemoryResource{VIRTUAL, 1024 * 4, 2, 4096} });
	devices.push_back(klComputeTarget{ "SW-LAB-KPU", klComputeResource{"Stillwater KPU T-64x8", LOCAL_KPU}, klMemoryResource{STATIC, 1024 * 2, 2, 4096} });
	devices.push_back(klComputeTarget{ "SW-CLOUD-KPU", klComputeResource{"Stillwater KPU T-1024x32", REMOTE_KPU}, klMemoryResource{STATIC, 1024 * 32, 32, 4096} });

	return 1;
} 

int create_context(klComputeTarget& target) {

	return 1;
}

} // namespace openkl
