// add_dense_vector_test.cpp
// Created: 2020-03-25
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
#include <openkl/scalar/update.hpp>

#include <mtl/vec/dense_vector.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_close.hpp>

using mtl::io::tout;
using mtl::check_close;

using namespace openkl;
    
using vtype= mtl::vec::dense_vector<posit32>;

template <typename Updater>
void test(object_id u_id, object_id v_id, object_id w_id, Updater updater, 
          vtype expected)
{
    const vtype ones(3, 1.0); 
    write_dense_vector(u_id, ones[0]); // reset in every test
    subtract_dense_vector<posit32>(u_id, v_id, w_id, updater);
    vtype res(3);
    read_dense_vector(u_id, res[0]);
    std::cout << "The result is " << res << '\n';
    check_close(res, expected, "subtract_dense_vector", 1000.0);
}

int main()
{
    vtype u(3), v{4.4, 5.5, 6.6}, w{1.1, 2.2, 3.3};
    object_id u_id= create_dense_vector(size(u), u[0]);
    object_id v_id= create_dense_vector(size(v), v[0]);
    object_id w_id= create_dense_vector(size(w), w[0]);
    
    test(u_id, v_id, w_id, update_store{}, vtype{3.3, 3.3, 3.3});
    test(u_id, v_id, w_id, update_plus{}, vtype{4.3, 4.3, 4.3});
    test(u_id, v_id, w_id, update_minus{}, vtype{-2.3, -2.3, -2.3});
    
    
    return 0;
}
