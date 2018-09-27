// Fluidik is a scientific C++ library for calculation of thermophysical properties of fluids.
//
// Copyright (C) 2018 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <sstream>
#include <string>

namespace Fluidik {
namespace internal {

inline auto str(std::stringstream&) -> void
{}

template<typename T, typename... Args>
auto str(std::stringstream& ss, const T& item, Args... items) -> void
{
    ss << item;
    str(ss, items...);
}

} // namespace internal

/// Concatenate the arguments into a string.
template<typename... Args>
auto str(Args... items) -> std::string
{
    std::stringstream ss;
    internal::str(ss, items...);
    return ss.str();
}

} // namespace Fluidik
