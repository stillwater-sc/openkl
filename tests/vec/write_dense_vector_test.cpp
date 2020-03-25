// write_dense_vector_test.cpp
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
#include <openkl/testing/check_object_info_output.hpp>
#include <openkl/testing/check_object_content_output.hpp>

// #define MTL5_VERBOSE_TESTS // to see the output

#include <mtl/vec/dense_vector.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_equal.hpp>

using mtl::io::tout;
using mtl::check_equal;

int main()
{
    using namespace openkl;
    mtl::vec::dense_vector<posit32> v{2.3, 4.1, 6.1};

    object_id w_id= create_dense_vector<posit32>(3);
    tout << "The id of my object is " << w_id.id() << "\n";
    tout << object_info(w_id) << "\n";    
    check_object_info_output(w_id, "vector with 3 entries", "create_dense_vector");
    
    write_dense_vector(w_id, v[0]);
    tout << object_content(w_id) << "\n";   
    check_object_content_output(w_id, "{2.3, 4.1, 6.1}", "write_dense_vector"); // disable with formating issues
    
    return 0;
}
