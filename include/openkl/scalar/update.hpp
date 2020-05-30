// update.hpp
// Created: 2020-03-25
//
// Copyright (C) 2020-present: Stillwater Supercomputing, Inc. & SimuNova UG
//
// This file is part of the OpenKL project, which is released under an MIT Open Source license.
// Authors: Peter Gottschling (peter.gottschling@simunova.com)
//          Theodore Omtzigt (theo@stillwater-sc.com)

#pragma once

namespace openkl {

/// Update Element by storing new value
struct update_store
{
    /// Update Element by storing new value
    template <typename Value1, typename Value2>
    constexpr static inline Value1& update(Value1& x, Value2 const& y) noexcept
    {
        return x= y;
    }
};

/// Update Element by adding new value
struct update_plus
{
    /// Update Element by adding new value
    template <typename Value1, typename Value2>
    constexpr static inline Value1& update(Value1& x, Value2 const& y) noexcept
    {
        return x+= y;
    }
};

/// Update Element by subtracting new value
struct update_minus
{
    /// Update Element by subtracting new value
    template <typename Value1, typename Value2>
    constexpr static inline Value1& update(Value1& x, Value2 const& y) noexcept
    {
        return x-= y;
    }
};
 

} // namespace openkl
