// cpu_blas.cpp: example of BLAS operators using CPU
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

int main(int argc, char* argv[])
try {
	openkl::klEnvironment env;
}
catch (const char* msg) {
	std::cerr << "caught exception: " << msg << std::endl;
}
