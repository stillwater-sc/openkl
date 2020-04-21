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
#include <openkl/target.hpp>
// hook into the proxy predefined shims
#include <openkl/base_types.h>
#include <openkl/shims/shim.hpp>
#include <openkl/shims/smp/smp.hpp>
#include <openkl/shims/kpu/kpu.hpp>

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

	klExecutionEnvironment getTarget(size_t i) {
		return resources[i];
	}

	bool createContextOnTarget(size_t i) {
//		if (i < resources.size()) {
//			contexts.push_back(shims[i]->createContext());
//		}
	}
private:
	static std::unique_ptr<proxy> instance;
	proxy() {
		// get the KPU from the PCIe device inventory, which we emulate with a set of shims
		shims.push_back(new shim::SymmetricMultiProcessor("Intel i7 7500u", 8, 16, 2600, SIZE_32G, 6));
		shims.push_back(new shim::KnowledgeProcessingUnit(64, 16 * 1024 * 1024, 2048, 4));
		shims.push_back(new shim::KnowledgeProcessingUnit(1024, SIZE_1G, 4096, 32));

		// generate the simplified execution target specs for the app
		for (auto s : shims) {
			add(klExecutionEnvironment{
				s->id(),
				s->procType(),
				s->cores(),
				s->threads(),
				s->mhz(),
				s->memoryType(),
				s->memorySize(),
				s->channels(),
				s->pageSize()
				});
		}
	}
	std::vector<klExecutionEnvironment> resources;
	std::vector<shim::Shim*> shims;

	// is this structure just a result of providing emulation services
	// or is this pattern required?
	std::vector<klComputeContext*> contexts;
};

} // namespace openkl
