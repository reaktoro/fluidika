// Fluidika is a scientific C++ library for calculation of thermophysical properties of fluids.
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

// Fluidika includes
#include <Fluidika/Common/Real.hpp>

namespace Fluidika {

// Forward declarations
struct WaterElectroProps;
struct WaterThermoProps;

/// Calculate the electrostatic properties of water using Helgeson and Kirkham (1974) electrostatic model.
/// @param wtp The thermodynamic properties of water
auto waterElectroPropsHelgesonKirkham(const WaterThermoProps& wtp) -> WaterElectroProps;

} // namespace Fluidika