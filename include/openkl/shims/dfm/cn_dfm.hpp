// cloud_native_cfdfm.hpp
// Created: 2020-03-29
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

namespace openkl {
namespace shim {

template <typename Value>
class cncgdfm
{
    using self= cncgdfm<Value>;
    
    friend std::ostream& operator<<(std::ostream& os, const self& dfm) noexcept
    {
		os << '{';
		os << "Cloud-Native Coarse-grain Data Flow Machine";
		os << '}';       
		return os;
    }
    
//    virtual void content(std::ostream& os) const noexcept override { os << *this; }
    
private:
    std::unique_ptr<Value[]> data;
};

} // namespace shim
} // namespace openkl
