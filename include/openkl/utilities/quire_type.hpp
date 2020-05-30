// quire_type.hpp
// Created: 2020-03-27
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

#include <universal/posit/quire.hpp>

namespace openkl
{
    template <typename Posit>
    using quire_type= sw::unum::quire<Posit::nbits, Posit::es, 10>;

} // namespace openkl
