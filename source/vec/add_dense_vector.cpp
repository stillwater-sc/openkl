// add_dense_vector.hpp
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

template <typename Value, typename Update>
void add_dense_vector(object_id u_id, object_id v_id, object_id w_id, Update up)
{
    using vtype= dense_vector<Value>;
    vtype* u= get_object<vtype>(u_id);
    const vtype* v= get_object<vtype>(v_id);
    const vtype* w= get_object<vtype>(w_id);
    u->add(*v, *w, up);
}

// explicit instantiations
template void add_dense_vector<posit32, update_store>(object_id, object_id, object_id, update_store);
template void add_dense_vector<posit32, update_plus>(object_id, object_id, object_id, update_plus);
template void add_dense_vector<posit32, update_minus>(object_id, object_id, object_id, update_minus);



} // namespace openkl
