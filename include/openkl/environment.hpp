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
		registry = 0;
	}
	~klEnvironment() {
		// destructor that detaches an application from the OpenKL environment
	}

	/////////////////////////////////////////////////////////////////////////////
	//             SETUP and TEARDOWN an OpenKL environment

	// bind an application to a compute target
	int bind(const klComputeResourceType type, klComputeContext& ctx) {
		// cycle through the registry to find a matching resource type
		// how to make this more modern C++? make the proxy a collection type?
		if (registry == 0) return 0;
		for (size_t i = 0; i < registry->nrTargets(); ++i) {
			if (registry->getTarget(i).procType == type) {
				// how do you create a compute context in a general way?
				// factory pattern
			}
		}
		return 1;
	}

	// release a compute target from an application binding
	int release(klComputeContext& ctx) {

		return 1;
	}

	/////////////////////////////////////////////////////////////////////////////
	//             SETUP and TEARDOWN RPC connections
	int connect(klRpcConnection& tunnel) {
		return 1;
	}

	bool enumerate() {
		registry = proxy::getInstance();
		if (registry->nrTargets() == 0) return false;
		std::cout << registry->nrTargets() << " compute resource targets found\n";
		return true;
	}

private:
	////////////////////////////////////////////////////////
	// RPC connections
	std::vector<klRpcConnection> connections;

	// registry of compute targets this OpenKL environment has access to
	proxy* registry;
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
		devices.push_back(registry->getTarget(i));
	}
	return 1;
} 


} // namespace openkl
