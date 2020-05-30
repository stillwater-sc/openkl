// write_dense_vector.cpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/get_object.hpp>

#include <openkl/vec/dense_vector.hpp>

namespace openkl {

template <typename Value>    
void write_dense_vector(object_id v_id, const Value& data)
{
    using vtype= dense_vector<Value>;
    vtype* vp= get_object<vtype>(v_id);
    vp->write(data);
}

// explicit instantiations
template void write_dense_vector<posit32>(object_id, const posit32&);

    
} // namespace openkl
