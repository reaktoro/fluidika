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

// Fluidik includes
#include <Fluidik/Common/Real.hpp>
#include <Fluidik/Common/StateOfMatter.hpp>

namespace Fluidik {

// Forward declarations
struct WaterHelmholtzProps;
struct WaterThermoProps;

/// Calculate the Helmholtz free energy state of water using the Wagner and Pruss (2002) equation of state
/// @param T The temperature of water (in units of K)
/// @param D The density of water (in units of kg/m3)
/// @return The Helmholtz free energy state of water
/// @see WaterHelmholtzProps
auto waterHelmholtzPropsWagnerPruss(RealConstRef T, RealConstRef D) -> WaterHelmholtzProps;

/// Calculate the thermodynamic properties of water using the Wagner and Pruss (2002) equation of state with given temperature, pressure and an initial guess for density.
/// The equations of state described in Wagner and Pruss (2002) and Haar--Gallagher--Kell (1984) for calculation
/// of thermodynamic properties of water and steam are formulated so that temperature and density are given.
/// In this method we wish to provide temperature and pressure, assuming that these are the only two thermodynamic
/// conditions known. Because these equations are non-linear, an iterative Newton algorithm is used to determine
/// the water density at given temperature and pressure. Newton's algorithm requires an initial guess for water
/// density, which can be provided in this method. The closest this initial guess is to the actual water density
/// at given *(T, P)* conditions, the faster is the computation (less number of Newton iterations).
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @param D The initial guess for the density of water (in units of kg/m3)
auto waterThermoPropsWagnerPruss(RealConstRef T, RealConstRef P, RealConstRef D0) -> WaterThermoProps;

/// Calculate the thermodynamic properties of water using the Wagner and Pruss (2002) equation of state with given temperature and pressure.
/// This method uses an initial guess for water density obtained from Table 13.2 of Wagner and Pruss (2002)
/// using method @ref waterThermoDataNearestWagnerPruss. Convergence should then be faster because the initial guess
/// will most likely be fairly close to the actual water density at given temperature and pressure conditions.
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
auto waterThermoPropsWagnerPruss(RealConstRef T, RealConstRef P) -> WaterThermoProps;

/// Calculate the thermodynamic properties of water using the Wagner and Pruss (2002) equation of state with given temperature and pressure and specific state of matter for water.
/// This method uses an initial guess for water density obtained from Table 13.2 of Wagner and Pruss (2002)
/// using either method @ref waterThermoDataMinTemperatureWagnerPruss if given state of matter is either liquid or solid,
/// and method @ref waterThermoDataMaxTemperatureWagnerPruss if gas or plasma. This is to help Newton's algorithm
/// to converge to a solution that represents the desired state of matter of water.
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @param stateofmatter The state of matter of water.
auto waterThermoPropsWagnerPruss(RealConstRef T, RealConstRef P, StateOfMatter stateofmatter) -> WaterThermoProps;

/// Calculate the density of liquid water at a saturated-liquid state using the Wagner and Pruss (2002) equation of state
/// @param T The temperature of water (in units of K)
/// @return The density of liquid water at saturated-liquid state (in units of kg/m3)
auto waterDensitySaturatedLiquidStateWagnerPruss(RealConstRef T) -> Real;

/// Calculate the density of vapor water at a saturated-vapor state using the Wagner and Pruss (2002) equation of state
/// @param T The temperature of water (in units of K)
/// @return The density of vapor water at saturated-vapor state (in units of kg/m3)
auto waterDensitySaturatedVaporStateWagnerPruss(RealConstRef T) -> Real;

/// Calculate the saturated pressure of water using the Wagner and Pruss (2002) equation of state
/// @param T The temperature of water (in units of K)
/// @return The saturated pressure of water (in units of Pa)
auto waterPressureSaturatedStateWagnerPruss(RealConstRef T) -> Real;

} // namespace Fluidik
