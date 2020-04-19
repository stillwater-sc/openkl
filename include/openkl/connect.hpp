// connect.hpp: cloud-native knowledge processing Remote Procedure Call abstraction
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

namespace openkl {

// OpenKL RPC connection
class klRpcConnection {
public:
	klRpcConnection(const std::string& url) : _url(url) {
		// prepare an RPC connection for the application to use
	}
	~klRpcConnection() {
		// release the RPC connection
	}

	/////////////////////////////////////////////////////////////////
	/// setup
	bool connect() {
		return true;
	}


	/////////////////////////////////////////////////////////////////
	/// test
	bool test() {
		return true;
	}

private:
	std::string _url;
};




} // namespace openkl
