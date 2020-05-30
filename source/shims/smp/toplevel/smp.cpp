// smp.cpp: device shim to functionally model a system consisting of a multi-core CPU, memory, but without hardware accelerators
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <iostream>

namespace openkl {	
namespace shim {

	// SMP model semantic version
	static size_t SMP_MAJOR = 0;
	static size_t SMP_MINOR = 0;
	static size_t SMP_PATCH = 1;

} // namespace shim
} // namespace openkl
