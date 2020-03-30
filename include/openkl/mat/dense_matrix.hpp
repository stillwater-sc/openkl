// dense_matrix.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <memory>
#include <ostream>
#include <algorithm>

#include <openkl/openkl_fwd.hpp>
#include <openkl/utilities/object.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/mat/matrix_output.hpp>

namespace openkl {

template <typename Value>
class dense_matrix
  : public object
{
    using self= dense_matrix<Value>;
    // using vtype= dense_vector<Value>; // corresponding vector type, hopefully not needed
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
    
    void read(Value& other) const noexcept 
    {
        std::copy(&data[0], &data[0] + nr*nc, &other);
    }
    
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "matrix of dimension " << nr << "x" << nc;
    }
    
    Value& operator()(size_t r, size_t c) & noexcept { return data[r*nc+c]; }
    const Value& operator()(size_t r, size_t c) const & noexcept { return data[r*nc+c]; }
    
    size_t num_rows() const noexcept { return nr; }
    size_t num_cols() const noexcept { return nc; }
    
    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
    size_t nr, nc;
    std::unique_ptr<Value[]> data;
};

template <typename Value>
std::ostream& operator<<(std::ostream& os, const dense_matrix<Value>& A) noexcept
{
    return matrix_output(os, A);
}

using dense_matrix32= dense_matrix<posit32>;

} // namespace openkl
