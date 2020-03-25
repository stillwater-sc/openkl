// check_type_test.cpp
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
#include <openkl/mat/dense_matrix.hpp>
#include <openkl/vec/dense_vector.hpp>
#include <openkl/utilities/object_id.hpp>
#include <openkl/testing/expect_exception.hpp>
#include <openkl/testing/check_type.hpp>

#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_equal.hpp>

using mtl::io::tout;
using mtl::check_equal;

int main()
{
    using namespace openkl;

    object_id w_id= create_dense_vector<posit32>(4);

    // shall pass
    check_type<dense_vector32>(w_id);
    
    // shall throw
    expect_exception<bad_down_cast>([w_id](){ check_type<dense_matrix32>(w_id); });

    object_id a_id= create_dense_matrix<posit32>(2, 3);

    // shall pass
    check_type<dense_matrix32>(a_id);
    
    // shall throw
    expect_exception<bad_down_cast>([a_id](){ check_type<dense_vector32>(a_id); });

    return 0;
}
