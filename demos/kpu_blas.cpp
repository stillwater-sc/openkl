// kpu_blas.cpp: example of BLAS operators using local KPU
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <openkl/openkl.hpp>
#include <openkl/utilities/exit.hpp>

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

void FinegrainControl() {
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

	// second step: among the compute targets find a compute target matching your need
	// we are going to look for a LOCAL_KPU target 
	auto isLocalKpu = [](auto& target) { return target.procType == openkl::LOCAL_KPU; };
	auto it = std::find_if(begin(targets), end(targets), isLocalKpu);
	if (it == end(targets))
		openkl::exit("Unable to find a LOCAL_KPU compute target: exiting");
	openkl::klExecutionEnvironment target{ *it };

	std::cout << "Successfully selected a LOCAL_KPU target\n";
	std::cout << attributes(target) << std::endl;

	// third step: create an execution context on the device of your choice
	openkl::klComputeContext ctx;
//	if (!openkl::createContext(target, ctx))
//		openkl::exit("Unable to create execution context on device " + target.id);

	// fourth step: allocate resources using the context


	// fifth step: compute
}

void C_calling_sequence() {
	// first step: bind this application to the OpenKL environment
	openkl::klEnvironment env;
	if (!openkl::attach(env)) {
		openkl::exit("unable to attach to an OpenKL environment: exiting");
	}

	// second step: bind to a compute target to work with
	openkl::klComputeContext localKPU;
	if (!env.bind(openkl::klComputeResourceType::LOCAL_KPU, localKPU)) {
		openkl::exit("unable to find a LOCAL_KPU compute target to bind to: exiting");
	}

	// third step: set up a computation


	// --- step: unbind a compute target
	if (!env.release(localKPU)) {
		openkl::exit("unable to release a LOCAL_KPU compute target: exiting");
	}

	// last step: release the application from the OpenKL environment
	if (!openkl::detach(env)) {
		openkl::exit("unable to detach from an OpenKL context: exiting");
	}
}

void ComputeVectorAngles(openkl::klComputeContext& localKPU) {
	// allocate memory blocks
	openkl::object_id a_v, b_v, c_v, d_v;
	openkl::object_id alpha, d;

	using DataType = float;
	size_t DataSize = sizeof(DataType);

	// allocate a vector of size N of type Data
	size_t N = 32;
	a_v = localKPU.claim(N * DataSize);
	b_v = localKPU.claim(N * DataSize);
	c_v = localKPU.claim(N * DataSize);
	d_v = localKPU.claim(N * DataSize);

	// allocate a scalar
	alpha = localKPU.claim(DataSize);
	d = localKPU.claim(DataSize);

	// copy or create data on the target
	// how do we assign 2.5 literal to alpha?

	// compute
	openkl::klInstruction cmd;
	cmd.scale(b_v, alpha, a_v);
	localKPU.execute(cmd);
	cmd.add(d_v, b_v, c_v);
	localKPU.execute(cmd);
	cmd.fdp(d, b_v, c_v);  // if a and c are at 45 degrees and the same length, b and c will be 90 degrees and dot product will be 0
	localKPU.execute(cmd);

	// do we want to introduce the cmd queue here?
	// we can also create a 'program' by writing instructions in a block of memory
	// and writing that to the accelerator.

	// QUESTION: cmd queue vs program memory block
	// pros cmd queue: simple, sequential execution, natural state boundaries
	// pros program mem: can create a looping structure, for example to orchestrate CG

	// wait for completion
	// execute is blocking by default, so we have all state updated we need at this point
}

int main(int argc, char* argv[])
try {
	// bind this application to the OpenKL environment
	openkl::klEnvironment env;

	// obtain an execution context
	openkl::klComputeContext localKPU;
	if (!env.bind(openkl::klComputeResourceType::LOCAL_KPU, localKPU)) {
		openkl::exit("unable to find a LOCAL_KPU compute target to bind to: exiting");
	}

	ComputeVectorAngles(localKPU);

	// --- step: unbind a compute target
	if (!env.release(localKPU)) {
		openkl::exit("unable to release a LOCAL_KPU compute target: exiting");
	}

	return EXIT_SUCCESS;
}
catch (const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}

