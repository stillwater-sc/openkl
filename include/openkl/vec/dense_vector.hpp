// dense_vector.hpp
// Created: 2020-03-24
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
#include <openkl/openkl.hpp>

#include <universal/posit/posit.hpp>


namespace openkl {

template <typename Value>
class dense_vector
  : public object
{
    using self= dense_vector<Value>;
  public:
    explicit dense_vector(size_t s) : s{s}, data{new posit32[s]} {}
      
    explicit dense_vector(size_t s, const posit32& other) : dense_vector(s)   
    {
        std::copy(&other, &other + s, &data[0]);
    }
      
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "vector with " << s << " entries";
    }
    
    friend std::ostream& operator<<(std::ostream& os, const self& v) noexcept
    {
        os << '{';
        if (v.s > 0)
            os << v.data[0];
        for (size_t i= 1; i < v.s; ++i)
            os << ", " << v.data[i];
        return os << '}';
    }
    
    virtual void content(std::ostream& os) const noexcept override { os << *this; }
  private:
    size_t s;
    std::unique_ptr<Value[]> data;
};

using dense_vector32= dense_vector<posit32>;

} // namespace openkl
