// exception.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

namespace openkl {

    
/// Exception for run-time errors that doesn't fit into specific categories.
struct runtime_error : std::runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit runtime_error(const std::string& s= "Run-time error.") 
      : std::runtime_error(s) {}
};
    
/// Exception for tests, respectively not holding their assertion.
struct assertion_not_fulfilled : runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit assertion_not_fulfilled(const std::string& s= "") 
      : runtime_error("Assertion not fulfilled: " + s) {}
};

/// Exception for down casts where not the correct type is referred.
struct bad_down_cast : runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit bad_down_cast(const std::string& s= "") 
      : runtime_error("Bad down cast: " + s) {}
};

/// Exception for tests when an expected exception wasn't thrown.
struct missing_exception : runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit missing_exception(const std::string& s= "") 
      : runtime_error("Expected exception wasn't thrown: " + s) {}
};

/// Exception when no object for object_id is in object_repo.
struct missing_object : runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit missing_object(const std::string& s= "") 
      : runtime_error("No object for object_id is in object_repo: " + s) {}
};

// Exception when objects don't match, e.g., vectors of different size.
struct incompatible : runtime_error
{
    /// Error can be specified more precisely in constructor if desired.
    explicit incompatible(const std::string& s= "") 
      : runtime_error("Objects are incompatible: " + s) {}
};


    
} // namespace openkl
