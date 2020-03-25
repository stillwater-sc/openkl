// dense_matrix.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <memory>
#include <ostream>
#include <algorithm>

#include <openkl/utilities/object.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>

namespace openkl {

// Incomplete !!!
template <typename Value>
class dense_matrix
  : public object
{
    using self= dense_matrix<Value>;
public:
    explicit dense_matrix(size_t nr, size_t nc) : nr{nr}, nc{nc}, data{new posit32[nr*nc]} {}

    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "matrix of dimension " << nr << "x" << nc;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const self& v) noexcept
    {
        return os;
    }
    
    virtual void content(std::ostream& os) const noexcept override { os << *this; }
private:
    size_t nr, nc;
    std::unique_ptr<Value[]> data;
};

using dense_matrix32= dense_matrix<posit32>;

} // namespace openkl
