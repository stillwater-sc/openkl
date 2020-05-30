// instruction.hpp: cloud-native knowledge processing interface
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
#include <openkl/target.hpp>

namespace openkl {

using klCmd = uint32_t;
using klArg = object_id;
constexpr size_t OPENKL_MAX_ARGS = 16;
object_id NOARG;

// DEBATE: blas or vector instructions?
// vector predicates are key in MATLAB and similar environments

// All these instructions are polymorphic, that is the operation is
// independent of type.

// BLAS L1 instructions
constexpr uint32_t KL_BLAS_VSCALE  = 0x00001000;  // scale a vector
constexpr uint32_t KL_BLAS_VADD    = 0x00001001;  // sum of two vectors element-wise
constexpr uint32_t KL_BLAS_AXPY    = 0x00001002;  // scale and sum
constexpr uint32_t KL_BLAS_DOT     = 0x00001003;  // regular dot
constexpr uint32_t KL_BLAS_FDP     = 0x00001004;  // fused dot
constexpr uint32_t KL_BLAS_VMUL    = 0x00001005;  // multiply two vectors element-wise
constexpr uint32_t KL_BLAS_L1NORM  = 0x00001006;  // sum of absolute values
constexpr uint32_t KL_BLAS_L2NORM  = 0x00001007;  // sqrt of sum of squares

// BLAS L2 instructions 
constexpr uint32_t KL_BLAS_MSCALE  = 0x00002000;
constexpr uint32_t KL_BLAS_MV      = 0x00002001;

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

} // namespace openkl
