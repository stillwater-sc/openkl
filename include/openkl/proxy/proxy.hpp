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
#include <memory>

#include <openkl/openkl_fwd.hpp>
#include <openkl/utilities/object.hpp>
#include <openkl/execenv.hpp>

namespace openkl {

class proxy {
public:
	static proxy* getInstance() {
            return instance.get();
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
	static std::unique_ptr<proxy> instance;
	proxy() {
		add(klExecutionEnvironment{
			"Intel i7 7500u",
			LOCAL_CPU,
			4,
			1,
			2000,
			openkl::VIRTUAL_MEM, 
			1024 * 4, 
			2, 
			4 });
		add(klExecutionEnvironment{
			"Stillwater KPU T-64x8",
			LOCAL_KPU,
			64,
			8,
			100,
			openkl::STATIC_MEM,
			512,
			1,
			4 });
		add(klExecutionEnvironment{
			"Stillwater KPU T-1024x32",
			REMOTE_KPU,
			1024,
			32,
			100,
			openkl::STATIC_MEM,
			1024 * 32,
			32,
			4 });
	}
	std::vector<klExecutionEnvironment> resources;
};

} // namespace openkl
