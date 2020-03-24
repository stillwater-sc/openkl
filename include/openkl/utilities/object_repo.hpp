// object_repo.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <map>

#include <openkl/utilities/object.hpp>
#include <openkl/utilities/object_id.hpp>

namespace openkl
{

    using object_repo_type= std::map<object_id, object*>;
    
    /// Contains and owns all objects
    extern object_repo_type object_repo;
    
} // namespace openkl
