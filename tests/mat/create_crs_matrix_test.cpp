// create_crs_matrix_test.cpp
// Created: 2020-03-31
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <iostream>
#include <vector>

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>
#include <openkl/interface/universal/posit/posit_definitions.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_info.hpp>
#include <openkl/utilities/object_content.hpp>
#include <openkl/testing/check_object_info_output.hpp>
#include <openkl/testing/check_object_content_output.hpp>

#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_close.hpp>

using mtl::io::tout;
using mtl::check_close;

int main()
{
    using namespace openkl;

    std::vector<size_t> starts{0, 2, 3, 5}, columns{0, 1, 3, 1, 2};
    std::vector<posit32> values{1, 2, 3, 4, 5};
    object_id a_id= create_crs_matrix<posit32>(3, 4, 5, starts[0], columns[0], values[0]);
    tout << object_info(a_id) << "\n";    
    check_object_info_output(a_id, "matrix of dimension 3x4", "create_crs_matrix");
    tout << object_content(a_id) << "\n";
    check_object_content_output(a_id, "{{1, 2, 0, 0}, {0, 0, 0, 3}, {0, 4, 5, 0}}", "create_crs_matrix");
    
    return 0;
}
