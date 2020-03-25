// object_info.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <ostream>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_repo.hpp>


namespace openkl {

/// Get information on the object with \p id in \p os.
struct object_info_t
{
    explicit object_info_t(object_id id) : id{id} {}
    object_id id; 
};

/// Get information on the object with \p id.
inline object_info_t object_info(object_id id)
{
    return object_info_t{id}; 
}
    
std::ostream& operator<<(std::ostream& os, object_info_t oi)
{
    object_repo[oi.id]->info(os);
    return os;
}
    
} // namespace openkl
