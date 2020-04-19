// kpu_blas.cpp: example of BLAS operators using local KPU
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#define PROXY_DISPATCH_CLASS_FOR_CONTEXT
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
//	openkl::klComputeContext ctx;
//	if (!openkl::createContext(target, ctx))
//		openkl::exit("Unable to create execution context on device " + target.id);

	// fourth step: allocate resources using the context


	// fifth step: compute
}

#ifdef TODO
void C_calling_sequence() {
	// first step: bind this application to the OpenKL environment
	openkl::klEnvironment env;
	if (!openkl::attach(env)) {
		openkl::exit("unable to attach to an OpenKL environment: exiting");
	}

	// second step: bind to a compute target to work with
	openkl::klComputeContext* localKPU;
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
#endif

#ifdef ABSTRACT_BASE_CLASS_FOR_CONTEXT
void ComputeVectorAngles(openkl::klComputeContext* localKPU) {
	// allocate memory blocks
	openkl::object_id a_v, b_v, c_v, d_v;
	openkl::object_id alpha, d;

	using DataType = float;
	size_t DataSize = sizeof(DataType);

	// allocate a vector of size N of type Data
	size_t N = 32;
	a_v = localKPU->claim(N * DataSize);  // <---- equivalent to create_dense_vector in Peter's API
	b_v = localKPU->claim(N * DataSize);
	c_v = localKPU->claim(N * DataSize);
	d_v = localKPU->claim(N * DataSize);
	
	// claim is just the memory allocation of a block, it is devoid of any type
	// create_dense_vector<Value>(size), and 
	// create_dense_vector<value>(size, initial_value), both carry information
	// about the object (= a dense vector), and the element type (template argument <Value>)

	// allocate a scalar
	alpha = localKPU->claim(DataSize);
	d = localKPU->claim(DataSize);

	// copy or create data on the target
	// how do we assign 2.5 literal to alpha?

	// compute
	openkl::klInstruction cmd;
	cmd.scale(b_v, alpha, a_v);
	localKPU->execute(cmd);
	cmd.add(d_v, b_v, c_v);
	localKPU->execute(cmd);
	cmd.fdp(d, b_v, c_v);  // if a and c are at 45 degrees and the same length, b and c will be 90 degrees and dot product will be 0
	localKPU->execute(cmd);

	// do we want to introduce the cmd queue here?
	// we can also create a 'program' by writing instructions in a block of memory
	// and writing that to the accelerator.

	// QUESTION: cmd queue vs program memory block
	// pros cmd queue: simple, sequential execution, natural state boundaries
	// pros program mem: can create a looping structure, for example to orchestrate CG

	// wait for completion
	// execute is blocking by default, so we have all state updated we need at this point
}
#endif

#ifdef PROXY_DISPATCH_CLASS_FOR_CONTEXT
void ComputeVectorAngles(openkl::klComputeContext& localKPU) {
	// allocate memory blocks
	openkl::object_id a_v, b_v, c_v, d_v;
	openkl::object_id alpha, d;

	using DataType = float;
	size_t DataSize = sizeof(DataType);

	// allocate a vector of size N of type Data
	size_t N = 32;
	a_v = localKPU.claim(N * DataSize);  // <---- equivalent to create_dense_vector in Peter's API
	b_v = localKPU.claim(N * DataSize);
	c_v = localKPU.claim(N * DataSize);
	d_v = localKPU.claim(N * DataSize);

	// claim is just the memory allocation of a block, it is devoid of any type
	// create_dense_vector<Value>(size), and 
	// create_dense_vector<value>(size, initial_value), both carry information
	// about the object (= a dense vector), and the element type (template argument <Value>)

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
#endif

int main(int argc, char* argv[])
try {
	// Conceptually, the OpenKL environment is a collection of compute targets.
	// When the OpenKL proxy is spoken to, it will generate that collection.
	// Why? the remote target environments may change, if you point it to
	// different cloud/remote accounts. Mmmmmm, that would imply that the proxy
	// needs to maintain credentials: is that a security issue?

	// When we create the environment we potentially need to provide it with
	// remote credentials.
	// bind this application to the OpenKL environment
	openkl::klEnvironment env;
	// Optional step: connect to remote targets
	//   The idea is that you can connect to remote systems that may have more
	//   powerful hardware acceleration using the same application program. 
	//   Before OpenKL, you create a program for each target and then you send
	//   that program to the remote target for execution.
	//   Otherwise stated, you are not yet creating distributed systems to solve
	//   the execution problem you may have. 
	//   OpenKL makes no assumption about where the 'orchestration' program runs,
	//   it just provides this main as the abstract orchestration, realizing that
	//   most remote execution in HPC are well defined remote procedure calls
	//   on remote data. These RPCs are BLAS, constraint solvers, eigen-value solvers, etc.
	//   This architecture allows other developers to create a fancy eigen-value 
	//   solver in the context of an OpenKL set of abstractions (MTL5), and 
	//   'publish' it as an OpenKL remote target.
	// Do we need new languages or compilation steps to accomplish that?
	// Don't know yet, but I want to be able to do this third party expansion
	// of functionality without any new languages are compilers. That is, avoid
	// the OpenGL/D3D HLSL and OpenCL C99 kernel compiler steps.

	// what is the connection tunnel you would need here?
	// Simple tunnels: SSH, TLS:
	// - SSH is attractive, following the same pattern as Ansible, but frequently
	//   in enterprise environments, this port/app is closed. Not so for simple
	//   kick the tires experiments, SSH would be perfect as all that infrastructure
	//   tends to be available.
	// Complex tunnels: HTTPS, grpc, capnproto
	// - HTTPS would be the simplest secure protocol, not efficient for binary data
	// - grpc is HTTP2.0: has a packet compiler step that tightly couples client and server
	// - capnproto uses promises/lazy exec: also has a packet compiler
	// - these types of connections will come and go, and thus
	//   this aspect of the architecture needs to be adaptive -> maybe use plugins?
	// - we will be talking to a remote OpenKL RPC server, not an arbitrary remote
	//   target, so we have some control
	// If we call the connection info struct something with RPC then we cover 
	// correctly the operations we will be issuing.
	// We can connect to multiple targets
	// MMMMM, we can't set up hop-and-forward pipelines.... is that a problem?
	// we could if we added other connections to the klRpcConnection struct
	// But then you would need to have a topology capability to define the graph
	// of computation you would like to set up.  MMMMMMM, do we want to bite that off?
	std::string url;
	url = "grpc::simunova.com/openkl/perf/10T";
	openkl::klRpcConnection target1(url);  // how do we do credentials?
	env.connect(target1);
	url = "grpc::stillwater-sc.com/openkl/perf/1T";
	openkl::klRpcConnection target2(url);  // how do we do credentials?
	env.connect(target2);
	if (!env.enumerate()) {
		openkl::exit("OpenKL enumeration yielded no targets: exiting");
	}

	// at this point, the OpenKL environment has a set of compute targets that
	// this application can select from. The application needs to decide which
	// targets it is going to use. This can be relatively static as in 'give me
	// the local kpu', or dynamic where the application tries to construct a
	// more complex distributed form and will try to build a distributed system.
	// The dynamic use case is particularly powerful when setting up pipelines
	// of services. Need to test that use case and what the alternatives are
	// for accomplishing these type of distributed systems. TODO

	// first: static compute target of a single KPU hw accelerator
	// obtain an execution context
#ifdef PROXY_DISPATCH_CLASS_FOR_CONTEXT
	openkl::klComputeContext localKPU;
	if (!env.bind(openkl::klComputeResourceType::LOCAL_KPU, localKPU)) {
		openkl::exit("unable to find a LOCAL_KPU compute target to bind to: exiting");
}

	ComputeVectorAngles(localKPU);
#else
	openkl::klComputeContext* localKPU = 0;
	if (!env.bind(openkl::klComputeResourceType::LOCAL_KPU, localKPU)) {
		openkl::exit("unable to find a LOCAL_KPU compute target to bind to: exiting");
	}

	ComputeVectorAngles(localKPU);
#endif


	// --- step: unbind a compute target
	if (!env.release(localKPU)) {
		openkl::exit("unable to release a LOCAL_KPU compute target: exiting");
	}

	return EXIT_SUCCESS;
}
catch (const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}

