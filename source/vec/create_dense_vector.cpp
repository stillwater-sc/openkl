// create_dense_vector.cpp
// Created: 2020-03-24
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

#include <openkl/vec/dense_vector.hpp>

namespace openkl {

    
object_id create_dense_vector(size_t s, const posit32& data)
{
    object_id oi;
    object_repo[oi]= new dense_vector{s, data};
    return oi;
}    
    


} // namespace openkl