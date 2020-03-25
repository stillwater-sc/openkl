// check_type.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <openkl/utilities/exception.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_repo.hpp>

namespace openkl {

/// Throws \ref bad_down_cast if object referred by \p oi cannot be downcasted to type \p Target.
template <typename Target>
void check_type(object_id oi)
{
    Target* tp= dynamic_cast<Target*>(object_repo[oi]); 
    if (tp == nullptr)
        throw bad_down_cast{};
}

/// Throws \ref bad_down_cast in debug mode if object referred by \p oi cannot be downcasted to type \p Target.
template <typename Target>
void check_type_debug(object_id oi)
{
  #ifndef NDEBUG
    check_type<Target>(oi);
  #endif
}


} // namespace openkl
