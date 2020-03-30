// matrix_output.hpp
// Created: 2020-03-30
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <cstddef>
#include <iostream>

namespace openkl {

template <typename Matrix>
std::ostream& matrix_output(std::ostream& os, const Matrix& A) 
{
    os << '{';
    for (size_t r= 0; r < A.num_rows(); ++r) {
        os << '{';
        for (size_t c= 0; c < A.num_cols(); ++c) 
            os << A(r, c) << (c + 1 == A.num_cols() ? "}" : ", ");
        os << (r + 1 == A.num_rows() ? "}" : ", ");
    }
    return os;
}

} // namespace openkl
