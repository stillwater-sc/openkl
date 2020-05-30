// openkl_fwd.hpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#pragma once

#include <openkl/interface/universal/posit/posit_fwd.hpp>

/// Main name space for the OpenKL library
namespace openkl {

    // only forward declaration here, actual types in interface/universal/posit/posit_definitions.hpp
    using posit32= sw::unum::posit<32, 2>; // or something similar   

    class object_id; 

    /// Namespace for scalar operations (can be used in container classes).
    namespace scalar {
    
        struct update_store;
        struct update_plus;
        struct update_minus;
        
    }        
    
    template <typename Value> class dense_vector;
    
    template <typename Value> class dense_matrix;

	class proxy;


	class klComputeContext;
	class klInstruction;

} // namespace openkl
