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
#include <cassert>

#include <openkl/utilities/object.hpp>
#include <openkl/utilities/exception.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>

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
        write(other);
    }
      
    void size_check(size_t os) const { assert(s == os); }
    
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "vector with " << s << " entries";
    }
    
    void write(const Value& other) & noexcept 
    {
        std::copy(&other, &other + s, &data[0]);
    }
    
    void read(Value& other) const noexcept 
    {
        std::copy(&data[0], &data[s], &other);
    }
    
    Value& operator[](size_t i) & { return data[i]; }
    const Value& operator[](size_t i) const & { return data[i]; }
    
    size_t size() const { return s; }

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
