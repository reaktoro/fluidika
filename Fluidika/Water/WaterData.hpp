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

// C++ includes
#include <array>

// Fluidika includes
#include <Fluidika/Common/Real.hpp>

namespace Fluidika {

// Forward declarations
struct WaterThermoPropsSimple;

/// Return the array storing all saturated-liquid thermodynamic properties in Wagner and Pruss (2002).
/// The returned array contains all saturated-liquid thermodynamic properties available in Table 13.1
/// of Wagner and Pruss (2002)\sup{\cite Wagner2002} that were computed using the IAPWS-1995 water thermodynamic model.
/// There are 192 data points stored in this array.
auto waterThermoDataSaturatedLiquidStateWagnerPruss() -> const std::array<WaterThermoPropsSimple, 193>&;

/// Return the array storing all saturated-vapor thermodynamic properties in Wagner and Pruss (2002).
/// The returned array contains all saturated-vapor thermodynamic properties available in Table 13.1
/// of Wagner and Pruss (2002)\sup{\cite Wagner2002} that were computed using the IAPWS-1995 water thermodynamic model.
/// There are 192 data points stored in this array.
auto waterThermoDataSaturatedVaporStateWagnerPruss() -> const std::array<WaterThermoPropsSimple, 193>&;

/// Return the array storing all single-phase thermodynamic properties in Wagner and Pruss (2002).
/// The returned array contains all single-phase thermodynamic properties available in Table 13.2
/// of Wagner and Pruss (2002)\sup{\cite Wagner2002} that were computed using the IAPWS-1995 water thermodynamic model.
/// There are 2180 data points stored in this array.
auto waterThermoDataSinglePhaseStateWagnerPruss() -> const std::array<WaterThermoPropsSimple, 2180>&;

/// Return an approximation for the thermodynamic properties at given temperature and pressure using Table 13.2 of Wagner and Pruss (2002).
/// This method searches for the closest temperature and pressure pair in Table 13.2 of Wagner and Pruss (2002)
/// and returns the thermodynamic properties of water at those *(T, P)* conditions.
/// Nearest pressure is searched first, then nearest temperature.
auto waterThermoDataNearestWagnerPruss(RealConstRef T, RealConstRef P) -> WaterThermoPropsSimple;

/// Return the thermodynamic properties of water at given pressure and lowest available temperature in Table 13.2 of Wagner and Pruss (2002).
auto waterThermoDataMinTemperatureWagnerPruss(RealConstRef P) -> WaterThermoPropsSimple;

/// Return the thermodynamic properties of water at given pressure and largest available temperature in Table 13.2 of Wagner and Pruss (2002).
auto waterThermoDataMaxTemperatureWagnerPruss(RealConstRef P) -> WaterThermoPropsSimple;

} // namespace Fluidika
