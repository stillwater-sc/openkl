// read_dense_vector_test.cpp
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

#include <mtl/vec/dense_vector.hpp>
#include <mtl/operations/io/vector_output.hpp>
#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_close.hpp>

using mtl::io::tout;
using mtl::check_close;

int main()
{
    using namespace openkl;
    mtl::vec::dense_vector<posit32> v{2.3, 4.1, 6.1}, w(3);
    object_id v_id= create_dense_vector<posit32>(3, v[0]);

    read_dense_vector(v_id, w[0]);
    tout << "w after reading is " << w << "\n";
    check_close(v, w, "read_dense_vector");
    
    return 0;
}
