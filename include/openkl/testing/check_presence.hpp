// check_presence.hpp
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

/// Throws \ref missing_object if object referred by \p oi isn't stored in object_repo.
void check_presence(object_id oi)
{
    if (object_repo.count(oi) == 0)
        throw missing_object{};
}

/// Throws \ref missing_object in debug mode if object referred by \p oi isn't stored in object_repo.
void check_presence_debug(object_id oi)
{
  #ifndef NDEBUG
    check_presence(oi);
  #endif
}

} // namespace openkl
