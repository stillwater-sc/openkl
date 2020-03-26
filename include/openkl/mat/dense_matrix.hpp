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
    
    Value& operator()(size_t r, size_t c) & { return data[r*nc+c]; }
    const Value& operator()(size_t r, size_t c) const & { return data[r*nc+c]; }
public:
    explicit dense_matrix(size_t nr, size_t nc) : nr{nr}, nc{nc}, data{new posit32[nr*nc]} {}
    
    explicit dense_matrix(size_t nr, size_t nc, const Value& other) : dense_matrix(nr, nc)
    {
        write(other);
    }

    void write(const Value& other) & noexcept 
    {
        std::copy(&other, &other + nr*nc, &data[0]);
    }
    
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "matrix of dimension " << nr << "x" << nc;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const self& A) noexcept
    {
        os << '{';
        for (size_t r= 0; r < A.nr; ++r) {
            os << '{';
            for (size_t c= 0; c < A.nc; ++c) 
                os << A(r, c) << (c + 1 == A.nc ? "}" : ", ");
            os << (r + 1 == A.nr ? "}" : ", ");
        }
        return os;
    }
    
    virtual void content(std::ostream& os) const noexcept override { os << *this; }
private:
    size_t nr, nc;
    std::unique_ptr<Value[]> data;
};

using dense_matrix32= dense_matrix<posit32>;

} // namespace openkl
