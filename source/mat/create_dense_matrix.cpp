// create_dense_matrix.cpp
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
#include <openkl/utilities/object_repo.hpp>

#include <openkl/mat/dense_matrix.hpp>

namespace openkl {

template <typename Value>    
object_id create_dense_matrix(size_t nr, size_t nc)
{
    object_id oi;
    object_repo[oi]= new dense_matrix<Value>(nr, nc);
    return oi;
}    

template <typename Value>    
object_id create_dense_matrix(size_t nr, size_t nc, const Value& other)
{
    object_id oi;
    object_repo[oi]= new dense_matrix<Value>(nr, nc, other);
    return oi;
}    

// explicit instantiations
template object_id create_dense_matrix<posit32>(size_t, size_t);

template object_id create_dense_matrix<posit32>(size_t, size_t, const posit32&);

} // namespace openkl
