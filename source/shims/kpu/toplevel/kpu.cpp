// kpu.cpp: device shim to functionally model a KPU hardware accelerator 
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <iostream>

/*
A KPU consists of 
  - front-end consisting of DMA and cmd queues
  - Notification, Interrupt, and Panic controller
  - memory controller(s)
  - memory modules organized in concurrent channels
  - stream caches
  - streamers
  - compute fabric
  */


namespace openkl {	
namespace shim {

	// KPU model semantic version
	static size_t KPU_MAJOR = 0;
	static size_t KPU_MINOR = 0;
	static size_t KPU_PATCH = 1;

} // namespace shim
} // namespace openkl

