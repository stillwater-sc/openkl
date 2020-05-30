// posit_definitions.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <universal/posit/posit.hpp>
#include <universal/posit/numeric_limits.hpp>

namespace openkl {

    // declaration with complete type
    using posit32= sw::unum::posit<32, 2>; // or something else
    
} // namespace openkl
