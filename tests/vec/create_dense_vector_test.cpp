// create_dense_vector_test.cpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <iostream>

#include <openkl/mtl5_shim.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_info.hpp>
#include <openkl/testing/check_object_output.hpp>

#define MTL5_VERBOSE_TESTS // to see the output

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
    tout << "The id of my object is " << v_id.id() << "\n";
    tout << object_info(v_id) << "\n";
    
    check_object_output(v_id, "vector with 3 entries", "create_dense_vector");

    return 0;
}
