// system.hpp
// Created: 2020-03-29
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

namespace openkl {
namespace shim {

template <typename Value>
class system
  : public object
{
    using self= system<Value>;
    
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

} // namespace shim
} // namespace openkl
