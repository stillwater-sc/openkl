// kpu.cpp: device shim to functionally model a KPU hardware accelerator 
// Created: 2020-03-29
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)
#include <iostream>
//#include <openkl/rm.hpp>
#include <openkl/shims/kpu.hpp>

/*
A KPU consists of 
  - DMA front-end
  - Notification, Interrupt, and Panic controller
  - memory controller(s)
  - memory modules organized in concurrent channels
  - stream caches
  - streamers
  - compute fabric
  */


namespace openkl {	namespace shim {



} // namespace shim
} // namespace openkl

