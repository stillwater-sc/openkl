// target.hpp: definition of an OpenKL execution targets
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <string>

#include <openkl/openkl_fwd.hpp>
#include <openkl/base_types.h>

namespace openkl {

	/*
	 * what could you use this for?
	 * if the openkl runtime would have information about how fast certain operators run
	 * it could use dynamic dispatch to select the most appropriate compute target.
	 * Since the architecture of the target will determine what the best algorithm is
	 * that openkl would need to dispatch, openkl would need a database of high-level
	 * instructions to dispatch. Otherwise stated, the application using openkl would
	 * need to have the ability to create new 'instructions'. These instructions could
	 * be full blown distributed programs, so how would openkl incorporate them?
	 * - as a loadable executable 
	 * - as a function (lambda dispatch)
	 */


// Attributes of the execution target
struct klExecutionEnvironment {
	std::string             id;
	klComputeResourceType   procType;
	size_t                  cores;
	size_t                  threads;
	size_t                  freq;     // core frequency in MHz
	klMemoryResourceType    memType;
	size_t                  size;     // memory size in MBytes
	size_t                  channels; // number of channels of memory
	size_t                  pageSize; // page size in KBytes
};

// database of execution targets
using klComputeTargets = std::vector<klExecutionEnvironment>;

} // namespace openkl
