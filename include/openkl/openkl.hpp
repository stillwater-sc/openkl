// openkl.hpp: cloud-native knowledge processing interface
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <cstddef>
#include <vector>

#include <openkl/openkl_fwd.hpp>

namespace openkl {



enum klDeviceClass {
	LOCAL_HOST    = 0,
	REMOTE_CPU    = 1,
	REMOTE_DMM    = 2,
	LOCAL_KPU     = 3,
	REMOTE_KPU    = 4,
	REMOTE_DM_KPU = 5
};

const char* klDeviceClassString[] = {
	"LOCAL_HOST",
	"REMOTE_CPU",
	"REMOTE_DMM",
	"LOCAL_KPU",
	"REMOTE_KPU",
	"REMOTE_DM_KPU"
};

struct klDevice {
	char          id[1024];
	klDeviceClass device_class;
	unsigned long memory; // memory size in MBytes
};

using klDeviceList = std::vector<klDevice>;

struct klDeviceQuery {
	klDeviceClass deviceType; // type of device we would like to use
	unsigned long memory; // minimum memory requirement in MBytes
};


int enumerate_devices(klDeviceList& devices, klDeviceQuery& query) {
	devices.push_back(klDevice{ "Intel i7 7500u", LOCAL_HOST, 1024 * 4 });
	devices.push_back(klDevice{ "Stillwater KPU T1/512M", LOCAL_KPU, 512 });
	devices.push_back(klDevice{ "Stillwater KPU T1/2G", REMOTE_KPU, 1024 * 2 });

	return 1;
} 

int create_context(klDevice& device) {

	return 1;
}

} // namespace openkl
