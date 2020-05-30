// object_id.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <cstddef>

#include <openkl/utilities/object.hpp>

namespace openkl {

/// Handle for objects on the accelerator
class object_id
{
    static size_t create_id() noexcept { static size_t next_id{1}; return next_id++; } // maybe atomic for next_id
  public:
    object_id() : my_id{create_id()} {}

    size_t id() const noexcept { return my_id; }

	void reset() noexcept {
		my_id = 0; // 0 is protected
	}
  private:
    size_t  my_id;
};

inline bool operator<(object_id o1, object_id o2) { return o1.id() < o2.id(); }

} // namespace openkl
