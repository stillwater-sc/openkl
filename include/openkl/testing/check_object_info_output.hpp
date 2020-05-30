// check_object_info_output.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <string>
#include <sstream>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_info.hpp>
#include <openkl/utilities/exception.hpp>

namespace openkl {

/// Check whether object_info of \p test_value is equal \p expected_output, otherwise throw an assertion_not_fulfilled for \p context.
void check_object_info_output(object_id oi, std::string expected_output, std::string context)
{
    std::ostringstream oss;
    oss << object_info(oi);
    if (oss.str() != expected_output) {
        const std::string message = "In context " + context + ": expected output '" + expected_output
        + "', got '" + oss.str() + "'.";
        std::cerr << message << std::endl;
        throw assertion_not_fulfilled{message};
    }
}

} // namespace openkl
