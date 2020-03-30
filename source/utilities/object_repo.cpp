// object_repo.cpp
// Created: 2020-03-24
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt  (theo@stillwater-sc.com)

#include <openkl/utilities/object_repo.hpp>

namespace openkl {

    object_repo_type object_repo;
    
    struct repo_cleaner_t
    {
        
        ~repo_cleaner_t() {
            for (auto p : object_repo)
                delete p.second;
        }
    };
    
    repo_cleaner_t repo_cleaner; // destructor at program end calls delete for all objects

} // namespace openkl
