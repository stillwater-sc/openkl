// create_matrix_test.cpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#include <iostream>

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_info.hpp>
#include <openkl/utilities/object_content.hpp>
#include <openkl/testing/check_object_info_output.hpp>
#include <openkl/testing/check_object_content_output.hpp>

#define MTL5_VERBOSE_TESTS // to see the output

#include <mtl/mat/dense_matrix.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_equal.hpp>

using mtl::io::tout;
using mtl::check_equal;

int main()
{
    using namespace openkl;

    object_id a_id= create_dense_matrix<posit32>(2, 3);
    tout << object_info(a_id) << "\n";    
    check_object_info_output(a_id, "matrix of dimension 2x3", "create_dense_matrix");
    tout << object_content(a_id) << "\n";
    
    mtl::mat::dense_matrix<posit32> B{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
    object_id b_id= create_dense_matrix<posit32>(2, 3, B[0][0]);
    tout << object_info(b_id) << "\n";    
    check_object_info_output(b_id, "matrix of dimension 2x3", "create_dense_matrix");
    tout << object_content(b_id) << "\n";
    check_object_content_output(b_id, "{{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}}", "create_dense_matrix");
    
    return 0;
}
