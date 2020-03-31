// exit.hpp
// Created: 2020-03-31
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <cstdlib>
#include <string>
#include <iostream>

namespace openkl {

void exit(std::string message)
{
    std::cerr << message << std::endl;
    std::exit(EXIT_FAILURE);

}

} // namespace openkl
