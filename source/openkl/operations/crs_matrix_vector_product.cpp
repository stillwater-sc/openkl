// crs_matrix_vector_product.cpp
// Created: 2020-03-31
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>

#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <universal/posit/quire.hpp>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/get_object.hpp>
#include <openkl/utilities/quire_type.hpp>

#include <openkl/scalar/update.hpp>

#include <openkl/vec/dense_vector.hpp>

#include <openkl/mat/crs_matrix.hpp>

namespace openkl
{

template <typename Value, typename Updater>
void crs_matrix_vector_product(object_id u_id, object_id a_id, object_id v_id, Updater)
{
    using vtype= dense_vector<Value>;
    using mtype= crs_matrix<Value>;
    vtype& u= *get_object<vtype>(u_id);
    const mtype& A= *get_object<mtype>(a_id);
    const vtype& v= *get_object<vtype>(v_id);
    size_t nr{ A.num_rows() }, nc{ A.num_cols() };
    u.size_check(nr);
    v.size_check(nc);
    for (size_t r= 0; r < nr; ++r) {
        quire_type<Value> accu{0};   
        for (size_t ii= A.pattern[r], e= A.pattern[r+1]; ii < e; ++ii)
            accu+= A.data[ii] * v[A.columns[ii]];
        Value accuv;
        convert(accu.to_value(), accuv);
        Updater::update(u[r], accuv);
    }
}

// explicit instantiations
template void crs_matrix_vector_product<posit32, update_store>(object_id, object_id, object_id, update_store);
template void crs_matrix_vector_product<posit32, update_plus>(object_id, object_id, object_id, update_plus);
template void crs_matrix_vector_product<posit32, update_minus>(object_id, object_id, object_id, update_minus);


} // namespace openkl
