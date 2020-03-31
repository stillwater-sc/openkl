// kpu_blas.cpp: example of BLAS operators using local KPU
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <openkl/openkl.hpp>

#include <universal/posit/posit>
//#include <universal/posit/posit.hpp>

std::string attributes(openkl::klExecutionEnvironment& target) {
	std::stringstream ss;
	ss << "+-----\n"
		<< " target             : " << target.id << '\n'
		<< " compute class      : " << openkl::klComputeResourceTypeString[target.procType] << '\n'
		<< " cores              : " << target.cores << '\n'
		<< " threads            : " << target.threads << '\n'
		<< " core frequency     : " << target.freq << '\n'
		<< " memory class       : " << openkl::klMemoryResourceTypeString[target.memType] << '\n'
		<< " memory size        : " << target.size << " MBytes\n"
		<< " memory channels    : " << target.channels << '\n'
		<< " memory page size   : " << target.pageSize << " kBytes";
	return ss.str();
}

void ShowInventory(openkl::klComputeTargets& targets) {
	std::cout << "\nInventory of compute resource targets\n";
	for (int i = 0; i < targets.size(); ++i) {
		std::cout << attributes(targets[i]) << std::endl;
	}
	std::cout << std::endl;
}

openkl::proxy* openkl::proxy::instance = 0;

int main(int argc, char* argv[])
try {
	// first step: enumerate the target devices our program could use
	openkl::klComputeTargets targets;
	openkl::klExecutionEnvironment query = openkl::klExecutionEnvironment{
		"SW-LAB-KPU",      // search by name
		openkl::LOCAL_KPU, // search by type
		64,                // match by size
		1, //threads
		100, //freq
		openkl::STATIC_MEM,
		512, // MBytes
		1,
		4
	};
	// dummy query for the moment. The idea is that we can unify step 1 and 2
	// to gather the compute target, instead of generating the whole database
	// and then subselecting.

	if (!openkl::enumerateTargets(query, targets)) {
		std::cerr << "unable to find any OpenKL devices" << std::endl;
		exit(EXIT_FAILURE);
	}

	ShowInventory(targets);

	/*
	std::cout << "posit<32,2> epsilon : " << std::numeric_limits< sw::unum::posit<32, 2> >::epsilon() << std::endl;
	std::cout << "posit<32,2> minpos  : " << sw::unum::minpos<32, 2>() << std::endl;
	*/

	// second step: among the compute targets find a compute target matching your need
	// we are going to look for a LOCAL_KPU target 
	auto isLocalKpu = [](auto& target) { return target.procType == openkl::LOCAL_KPU; };
	auto it = std::find_if(begin(targets), end(targets), isLocalKpu);
	if (it == end(targets)) {
		std::cerr << "Unable to find a LOCAL_KPU compute target: exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
	openkl::klExecutionEnvironment target(*it);

	std::cout << "Successfully selected a LOCAL_KPU target\n";
	std::cout << attributes(target) << std::endl;

	// third step: create an execution context on the device of your choice
	openkl::klComputeContext ctx;
	if (!openkl::createContext(target, ctx)) {
		std::cerr << "unable to create execution context on device " << target.id << std::endl;
		exit(EXIT_FAILURE);
	}

	// fourth step: allocate resources using the context


	// fifth step: compute
}
catch (const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}

