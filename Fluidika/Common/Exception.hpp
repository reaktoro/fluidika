// Fluidika is a C++ library for calculation of thermodynamic and electrostatic properties of pure fluids.
//
// Copyright (C) 2018-2019 Allan Leal and Reaktoro Contributors
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
#include <iostream>
#include <exception>

// Fluidika includes
#include <Fluidika/Common/StringUtils.hpp>

namespace Fluidika {

/// Issue a warning message if condition is true.
template<typename... Args>
auto warning(bool condition, Args... items) -> void
{
    if(condition)
        std::cerr << "\033[1;33m***WARNING***\033[0m" << " " << str(items...) << std::endl;
}

/// Raise a runtime error if condition is true.
template<typename... Args>
auto error(bool condition, Args... items) -> void
{
    if(condition)
        throw std::runtime_error(str("\033[1;31m***ERROR***\033[0m", " ", str(items...), '\n'));
}

} // namespace Fluidika
