// destroy.cpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#include <openkl/openkl_fwd.hpp>
#include <openkl/mtl5_shim.hpp>

#include <openkl/utilities/object_id.hpp>
#include <openkl/utilities/object_repo.hpp>

#include <openkl/testing/check_presence.hpp>


namespace openkl {

void destroy(object_id oi)
{
    check_presence( oi ); 
    delete object_repo[oi];
    object_repo.erase(oi);
}


} // namespace openkl
