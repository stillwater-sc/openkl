// smp.cpp: device shim to functionally model a system consisting of a multi-core CPU, memory, but without hardware accelerators
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <iostream>
#include <openkl/shims/smp/smp.hpp>

namespace openkl {	
namespace shim {

// create a local cpu model
std::unique_ptr<SymmetricMultiProcessor> SymmetricMultiProcessor::instance{
	new SymmetricMultiProcessor("Intel i7 7500u", 8, 16, 2600, SIZE_32G, 6)
};

} // namespace shim
} // namespace openkl
