// environment.hpp: cloud-native knowledge processing environment
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

#include <openkl/proxy/proxy.hpp>

namespace openkl {

// OpenKL environment manages the connection to an execution environment
class klEnvironment {
public:
	klEnvironment() {
		// constructor that attaches an application to the OpenKL environment
		proxy* registry = proxy::getInstance();
		std::cout << registry->nrTargets() << " compute resource targets found\n";
	}
	~klEnvironment() {
		// destructor that detaches an application from the OpenKL environment
	}
	// bind an application to a compute target
	int bind(const klComputeResourceType type, klComputeContext& ctx) {

		return 1;
	}

	// release a compute target from an application binding
	int release(klComputeContext& ctx) {

		return 1;
	}

};

// bind an application to the OpenKL environment
int attach(klEnvironment& env) {
	// create an OpenKL context for the application
	return 1;
}

// release an application from the OpenKL environment
int detach(klEnvironment& env) {
	// free up the attached state and release the application
	// from the OpenKL context
	return 1;
}

int enumerateTargets(const klExecutionEnvironment& query, klComputeTargets& devices) {
	// query the OpenKL proxy for the available targets
	proxy* registry = proxy::getInstance();
	std::cout << registry->nrTargets() << " compute resource targets found\n";
	if (registry->nrTargets() == 0) return 0;
	for (size_t i = 0; i < registry->nrTargets(); ++i) {
		devices.push_back(registry->getEnv(i));
	}
	return 1;
} 


} // namespace openkl
