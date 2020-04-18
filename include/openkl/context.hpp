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

// compute context for an application
class klComputeContext {
public:
	klComputeContext() {
		// prepare a compute context for the application to use
	}
	~klComputeContext() {
		// release the compute context
	}

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT

	// claim a memory block of bytes nr of bytes
	object_id claim(size_t bytes) {
		object_id hndl;

		return hndl;
	}
	// release a previous claim
	void release(object_id& hndl) {
		hndl.reset();
	}

	/////////////////////////////////////////////////////////////////
	/// EXECUTION MANAGEMENT
	void execute(const klInstruction& cmd) {

	}

private:
	size_t value;
};




} // namespace openkl
