// write_dense_matrix.cpp
// Created: 2020-03-26
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
void write_dense_matrix(object_id a_id, const Value& data)
{
    using mtype= dense_matrix<Value>;
    check_presence_debug( a_id ); 
    check_type_debug<mtype>( a_id );
    mtype* ap= get_object<mtype>(a_id);
    ap->write(data);
}

// explicit instantiations
template void write_dense_matrix<posit32>(object_id, const posit32&);


} // namespace openkl
