// create_crs_matrix.cpp
// Created: 2020-03-31
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

#include <openkl/mat/crs_matrix.hpp>

namespace openkl {

template <typename Value>    
object_id create_crs_matrix(size_t nr, size_t nc, size_t nnz, const size_t& starts,
                            const size_t& column_indices, const Value& data)
{
    object_id oi;
    object_repo[oi]= new crs_matrix<Value>(nr, nc, nnz, starts, column_indices, data);
    return oi;   
}

template object_id create_crs_matrix<posit32>(size_t nr, size_t nc, size_t nnz, const size_t& starts,
                                              const size_t& column_indices, const posit32& data);
} // namespace openkl
