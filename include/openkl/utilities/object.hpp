// object.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <iostream>

namespace openkl {

/// Abstract base class for all objects like dense_vector and alike.
class object
{
  public:
    virtual void info(std::ostream&) const noexcept = 0;
    void info() const noexcept { info(std::cout); }
    virtual ~object() {}
};

} // namespace openkl
