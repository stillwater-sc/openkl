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
#include <openkl/execenv.hpp>
#include <openkl/proxy/proxy.hpp>
#include <openkl/shims/kpu.hpp>

namespace openkl {

	constexpr size_t OPENKL_MAX_IDENTIFIER_SIZE = 1024;



// database of execution environments
using klComputeTargets = std::vector<klExecutionEnvironment>;

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

struct klComputeContext {
	size_t value;
};

int createContext(const klExecutionEnvironment& target, klComputeContext& ctx) {
	ctx.value = 10;
	return 1;
}


} // namespace openkl
