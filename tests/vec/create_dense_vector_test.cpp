// create_dense_vector_test.cpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <iostream>

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>
#include <openkl/utilities/object_id.hpp>

// #include <openkl/vec/create_dense_vector.hpp>

#include <universal/posit/posit.hpp>

#include <mtl/vec/dense_vector.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_equal.hpp>

using mtl::io::tout;
using mtl::check_equal;

int main()
{
    using namespace openkl;
    
    mtl::vec::dense_vector<posit32> v{2.3, 4.1, 6.1};
    object_id v_id= create_dense_vector(size(v), v[0]);
    std::cout << "Id of my object is " << v_id.id() << std::endl;

    return 0;
}
