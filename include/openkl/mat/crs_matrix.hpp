// crs_matrix.hpp
// Created: 2020-03-31
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

#include <openkl/openkl_fwd.hpp>
#include <openkl/utilities/object.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/mat/matrix_output.hpp>

namespace openkl {

template <typename Value>
class crs_matrix
  : public object
{
    std::pair<bool, size_t> index(size_t r, size_t c) const
    {
        for (size_t ii= pattern[r], e= pattern[r+1]; ii < e; ++ii)
            if (columns[ii] == c)
                return {true, ii};
        return {false, 0};        
    }
  public:
    explicit crs_matrix(size_t nr, size_t nc, size_t nnz, const size_t& starts,
                         const size_t& columns, const Value& other)
       : nr{nr}, nc{nc}, nnz{nnz}, pattern{new std::size_t[nr + 1 + nnz]}, columns{&pattern[nr+1]},
         data{new Value[nnz]}
    {
        std::copy(&starts, &starts + (nr+1), &pattern[0]);
        std::copy(&columns, &columns + nnz, this->columns);
        std::copy(&other, &other + nnz, &data[0]);
    }
    
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "matrix of dimension " << nr << "x" << nc;
    }
    
    Value operator()(size_t r, size_t c) const noexcept 
    { 
        auto mi= index(r, c); 
        return mi.first ? data[mi.second] : Value{0}; 
    }
    
    size_t num_rows() const noexcept { return nr; }
    size_t num_cols() const noexcept { return nc; }
    
    virtual void content(std::ostream& os) const noexcept override { os << *this; }
  private:
    size_t                         nr, nc, nnz;
    std::unique_ptr<std::size_t[]> pattern;
    std::unique_ptr<Value[]>       data;
    std::size_t*                   columns;
};

template <typename Value>
std::ostream& operator<<(std::ostream& os, const crs_matrix<Value>& A) noexcept
{
    return matrix_output(os, A);
}

using crs_matrix32= crs_matrix<posit32>;

} // namespace openkl
