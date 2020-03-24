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
inline void object_info(object_id id, std::ostream& os)
{
    object_repo[id]->info(os);
}

/// Get information on the object with \p id in std::cout.
inline void object_info(object_id id)
{
    object_info(id, std::cout);
}

} // namespace openkl
