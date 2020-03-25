// expect_exception.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <openkl/utilities/exception.hpp>

namespace openkl {



/** Expect that \p snippet throws \p Exception, otherwise throws missing_exception itself. */
template <typename Exception, typename Snippet>
void expect_exception(const Snippet& snippet)
{
    try {
        snippet();
        throw missing_exception{};
    } catch (Exception&) {
        // everything is fine, caught the expected exception
    }
}

    
} // namespace openkl
