// subtract_dense_vector.cpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <openkl/mtl5_shim.hpp>

#include <openkl/interface/universal/posit/posit_definitions.hpp>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/get_object.hpp>

#include <openkl/scalar/update.hpp>

#include <openkl/vec/dense_vector.hpp>

namespace openkl {

template <typename Value, typename Updater>
void subtract_dense_vector(object_id u_id, object_id v_id, object_id w_id, Updater)
{
    using vtype= dense_vector<Value>;
    vtype& u= *get_object<vtype>(u_id);
    const vtype& v= *get_object<vtype>(v_id);
    const vtype& w= *get_object<vtype>(w_id);
    size_t s= u.size();
    v.size_check(s); 
    w.size_check(s);
    for (size_t i= 0; i < s; ++i)
        Updater::update(u[i], v[i] - w[i]);
}

// explicit instantiations
template void subtract_dense_vector<posit32, update_store>(object_id, object_id, object_id, update_store);
template void subtract_dense_vector<posit32, update_plus>(object_id, object_id, object_id, update_plus);
template void subtract_dense_vector<posit32, update_minus>(object_id, object_id, object_id, update_minus);


} // namespace openkl
