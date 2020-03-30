// proxy.hpp
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <openkl/openkl_fwd.hpp>
#include <openkl/utilities/object.hpp>

namespace openkl {

	// forward reference
	struct klExecutionEnvironment;

class proxy {
public:
	static proxy* getInstance() {
		if (!instance) instance = new proxy;
		return instance;
	}

	void add(klExecutionEnvironment target) {
		resources.push_back(target);
	}
    
	size_t nrTargets() const {
		return resources.size();
	}

	klExecutionEnvironment getEnv(size_t i) {
		return resources[i];
	}

private:
	static proxy* instance;
	proxy() { instance = 0; }
	std::vector<klExecutionEnvironment> resources;
};

} // namespace openkl
