// read_dense_matrix.cpp
// Created: 2020-03-27
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

#include <openkl/mat/dense_matrix.hpp>

namespace openkl
{

template <typename Value>    
void read_dense_matrix(object_id A, Value& data)
{
    using mtype= dense_matrix<Value>;
    mtype* ap= get_object<mtype>(A);
    ap->read(data);
}

// explicit instantiations
template void read_dense_matrix<posit32>(object_id, posit32&);



} // namespace openkl
