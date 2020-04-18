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
#include <openkl/shims/kpu/kpu.hpp>

namespace openkl {

	constexpr size_t SIZE_1G   =    1073741824ll;
	constexpr size_t SIZE_2G   =    2147483648ll;
	constexpr size_t SIZE_3G   =    3221225472ll;
	constexpr size_t SIZE_4G   =    4294967296ll;
	constexpr size_t SIZE_5G   =    5368709120ll;
	constexpr size_t SIZE_6G   =    6442450944ll;
	constexpr size_t SIZE_7G   =    7516192768ll;
	constexpr size_t SIZE_8G   =    8589934592ll;
	constexpr size_t SIZE_16G  =   17179869184ll;
	constexpr size_t SIZE_32G  =   34359738368ll;
	constexpr size_t SIZE_64G  =   68719476736ll;
	constexpr size_t SIZE_128G =  137438953472ll;
	constexpr size_t SIZE_256G =  274877906944ll;
	constexpr size_t SIZE_512G =  549755813888ll;
	constexpr size_t SIZE_1T   = 1009511627776ll;

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
		// get the KPU from the PCIe device inventory 
		// (which we emulate with a set of shims
		shims.push_back(new shim::KnowledgeProcessingUnit(64, 16 * 1024 * 1024, 4));
		shims.push_back(new shim::KnowledgeProcessingUnit(1024, SIZE_32G, 32));

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
		/*
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
		*/
	}
	std::vector<klExecutionEnvironment> resources;
	std::vector<shim::Shim*> shims;
};

} // namespace openkl
