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
#include <algorithm>

#include <openkl/utilities/object.hpp>
#include <openkl/openkl.hpp>

#include <universal/posit/posit.hpp>


namespace openkl {

class dense_vector
  : public object
{

  public:
    explicit dense_vector(size_t s, const posit32& other) : s{s}, data{new posit32[s]}
    {
        std::copy(&other, &other + s, &data[0]);
    }
      
    virtual void info(std::ostream& os) const noexcept override 
    { 
        os << "vector with " << s << " entries";
    }
  private:
    size_t s;
    std::unique_ptr<posit32[]> data;
};

} // namespace openkl
