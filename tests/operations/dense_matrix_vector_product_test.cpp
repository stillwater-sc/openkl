// dense_matrix_vector_product_test.cpp
// Created: 2020-03-27
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <iostream>

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_info.hpp>
#include <openkl/utilities/object_content.hpp>
#include <openkl/testing/check_object_info_output.hpp>
#include <openkl/testing/check_object_content_output.hpp>
#include <openkl/scalar/update.hpp>

#include <mtl/vec/dense_vector.hpp>
#include <mtl/mat/dense_matrix.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_close.hpp>

using mtl::io::tout;
using mtl::check_close;

using namespace openkl;
    
using vtype= mtl::vec::dense_vector<posit32>;
using mtype= mtl::mat::dense_matrix<posit32>;

template <typename Updater>
void test(vtype& v_res, const mtype& A, const vtype& v_in, Updater u, const vtype& v_ref)
{
    object_id res_id= create_dense_vector(size(v_res), v_res[0]);
    object_id a_id= create_dense_matrix(3, 4, A[0][0]);
    object_id in_id= create_dense_vector(size(v_in), v_in[0]);
    
    dense_matrix_vector_product<posit32>(res_id, a_id, in_id, u);
    read_dense_vector(res_id, v_res[0]);
    check_close(v_res, v_ref, "dense_matrix_vector_product");
}

int main()
{
    using namespace openkl;
    mtype A{{1, 2, 0, 0}, {0, 0, 0, 3}, {0, 4, 5, 0}}; 
    vtype v{2, 3, 4, 5}, w(3), x{10, 11, 12}, y{30, 31, 32}, 
          ref{8, 15, 32}, ref_add{18, 26, 44}, ref_sub{22, 16, 0};

    test(w, A, v, update_store{}, ref);                               
    test(x, A, v, update_plus{}, ref_add);                               
    test(y, A, v, update_minus{}, ref_sub);                               
                                    
    return 0;
}
