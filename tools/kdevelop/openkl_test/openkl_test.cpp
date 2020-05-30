{% load kdev_filters %}
// {{ name }}.cpp
// Created: {% now "yyyy-MM-dd" %}
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



#include <mtl/operations/io/test_ostream.hpp>
#include <mtl/testing/check_close.hpp>



using mtl::io::tout;
using mtl::check_close;




int main()
{
    using namespace openkl;
   
    
    

    
    return 0;
}


