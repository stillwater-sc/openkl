// object_id.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <cstddef>

#include <openkl/utilities/object.hpp>

namespace openkl {

/// Handle for objects on the accelerator
class object_id
{
    static size_t create_id() noexcept { static size_t next_id{0}; return next_id++; }
  public:
    object_id() : my_id{create_id()} {}

    // void object_info(std::ostream& os) const noexcept { o.
    size_t id() const noexcept { return my_id; }
  private:
    size_t  my_id;
    // object& o;
};

} // namespace openkl
