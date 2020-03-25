// get_object.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_repo.hpp>

#include <openkl/testing/check_presence.hpp>
#include <openkl/testing/check_type.hpp>

namespace openkl {

    /// Checks presence and correctness of down cast in debug mode and returns a pointer to object
    template <typename T>
    T* get_object(object_id oi)
    {
        check_presence_debug(oi);
        check_type_debug<T>(oi);
        return static_cast<T*>(object_repo[oi]);
    }

} // namespace openkl
