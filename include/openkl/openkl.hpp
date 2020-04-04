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
#include <openkl/utilities/object_repo.hpp>
#include <openkl/execenv.hpp>
#include <openkl/proxy/proxy.hpp>
#include <openkl/shims/kpu/kpu.hpp>

namespace openkl {


// database of execution environments
using klComputeTargets = std::vector<klExecutionEnvironment>;

// fwd reference
class klComputeContext;

class klEnvironment {
public:
	klEnvironment() {
		// constructor that attaches an application to the OpenKL environment
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

using klCmd = uint32_t;
using klArg = object_id;
constexpr size_t OPENKL_MAX_ARGS = 16;
object_id NOARG;

// DEBATE: blas or vector instructions?
// vector predicates are key in MATLAB and similar environments

// All these instructions are polymorphic, that is the operation is
// independent of type.

// BLAS L1 instructions
uint32_t KL_BLAS_VSCALE  = 0x00001000;  // scale a vector
uint32_t KL_BLAS_VADD    = 0x00001001;  // sum of two vectors element-wise
uint32_t KL_BLAS_AXPY    = 0x00001002;  // scale and sum
uint32_t KL_BLAS_DOT     = 0x00001003;  // regular dot
uint32_t KL_BLAS_FDP     = 0x00001004;  // fused dot
uint32_t KL_BLAS_VMUL    = 0x00001005;  // multiply two vectors element-wise
uint32_t KL_BLAS_L1NORM  = 0x00001006;  // sum of absolute values
uint32_t KL_BLAS_L2NORM  = 0x00001007;  // sqrt of sum of squares

// BLAS L2 instructions 
uint32_t KL_BLAS_MSCALE  = 0x00002000;
uint32_t KL_BLAS_MV      = 0x00002001;

// the multi-argument OpenKL instruction descriptor
class klInstruction {
public:
	// c[i] = a * b[i]
	void scale(klArg& c, const klArg& a, const klArg& b) {
		cmd = KL_BLAS_VSCALE;
		args[0] = c;
		args[1] = a;
		args[2] = b;
		args[3] = NOARG;
	}
	// c[i] = a[i] + b[i]
	void add(klArg& c , const klArg& a, const klArg& b) {
		cmd = KL_BLAS_VADD;
		args[0] = a;
		args[1] = b;
		args[2] = c;
		args[3] = NOARG;
	}

	// d[i] = a * b[i] + c[i]
	void axpy(klArg& d, const klArg& a, const klArg& b, const klArg& c) {
		cmd = KL_BLAS_AXPY;
		args[0] = d;
		args[1] = a;
		args[2] = b;
		args[3] = c;
		args[4] = NOARG;
	}
	// c = a[i] * b[i]
	void dot(klArg& c, const klArg& a, const klArg& b) {
		cmd = KL_BLAS_DOT;
		args[0] = c;
		args[1] = a;
		args[2] = b;
		args[3] = NOARG;
	}
	// c = a[i] * b[i] with deferred rounding
	void fdp(klArg& c, const klArg& a, const klArg& b) {
		cmd = KL_BLAS_FDP;
		args[0] = c;
		args[1] = a;
		args[2] = b;
		args[3] = NOARG;
	}
	klCmd cmd;
	klArg args[OPENKL_MAX_ARGS];
};

class klComputeContext {
public:
	klComputeContext() {
		// prepare a compute context for the application to use
	}
	~klComputeContext() {
		// release the compute context
	}

	/////////////////////////////////////////////////////////////////
	/// RESOURCE MANAGEMENT

	// claim a memory block of bytes nr of bytes
	object_id claim(size_t bytes) {
		object_id hndl;

		return hndl;
	}
	// release a previous claim
	void release(object_id& hndl) {
		hndl.reset();
	}

	/////////////////////////////////////////////////////////////////
	/// EXECUTION MANAGEMENT
	void execute(const klInstruction& cmd) {

	}

private:
	size_t value;
};




} // namespace openkl
