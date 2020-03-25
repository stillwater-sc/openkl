// object_content.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

namespace openkl {


/// Get content of the object with \p id in \p os.
struct object_content_t
{
    explicit object_content_t(object_id id) : id{id} {}
    object_id id; 
};

/// Get content of the object with \p id.
inline object_content_t object_content(object_id id)
{
    return object_content_t{id}; 
}
    
std::ostream& operator<<(std::ostream& os, object_content_t oi)
{
    object_repo[oi.id]->content(os);
    return os;
}
    
} // namespace openkl
