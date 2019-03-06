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
#include <functional>

// Fluidika includes
#include <Fluidika/Common/Real.hpp>
#include <Fluidika/Common/StateOfMatter.hpp>

namespace Fluidika {

// Forward declarations
struct WaterThermoProps;
struct WaterHelmholtzProps;

/// The type of functions that calculate specific Helmholtz free energy properties for water.
using WaterHelmholtzPropsFunction = std::function<WaterHelmholtzProps(RealConstRef,RealConstRef)>;

/// Calculate the thermodynamic properties of water with given temperature, pressure and an initial guess for density.
/// The equations of state described in Wagner and Pruss (2002) and Haar--Gallagher--Kell (1984) for calculation
/// of thermodynamic properties of water and steam are formulated so that temperature and density are given.
/// In this method we wish to provide temperature and pressure, assuming that these are the only two thermodynamic
/// conditions known. Because these equations are non-linear, an iterative Newton algorithm is used to determine
/// the water density at given temperature and pressure. Newton's algorithm requires an initial guess for water
/// density, which can be provided in this method. The closest this initial guess is to the actual water density
/// at given *(T, P)* conditions, the faster is the computation (less number of Newton iterations).
/// @param model The function that calculates specific Helmholtz free energy of water
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @param D The initial guess for the density of water (in units of kg/m3)
auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P, RealConstRef D0) -> WaterThermoProps;

/// Calculate the thermodynamic properties of water with given temperature and pressure.
/// This method uses an initial guess for water density obtained from Table 13.2 of Wagner and Pruss (2002)
/// using method @ref waterThermoDataNearestWagnerPruss. Convergence should then be faster because the initial guess
/// will most likely be fairly close to the actual water density at given temperature and pressure conditions.
/// @param model The function that calculates specific Helmholtz free energy of water
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P) -> WaterThermoProps;

/// Calculate the thermodynamic properties of water with given temperature and pressure and specific state of matter for water.
/// This method uses an initial guess for water density obtained from Table 13.2 of Wagner and Pruss (2002)
/// using either method @ref waterThermoDataMinTemperatureWagnerPruss if given state of matter is either liquid or solid,
/// and method @ref waterThermoDataMaxTemperatureWagnerPruss if gas or plasma. This is to help Newton's algorithm
/// to converge to a solution that represents the desired state of matter of water.
/// @param model The function that calculates specific Helmholtz free energy of water
/// @param T The temperature of water (in units of K)
/// @param P The pressure of water (in units of Pa)
/// @param stateofmatter The state of matter of water.
auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P, StateOfMatter stateofmatter) -> WaterThermoProps;

/// Calculate the thermodynamic properties of water with given specific Helmholtz free energy water properties computed at given temperature and density.
/// This is a general method that uses the specific Helmholtz free energy properties of water,
/// calculated at given temperature *T* and density *D*, to completely resolve all water thermodynamic properties.
/// @param T The temperature of water (in units of K)
/// @param D The density of water (in units of kg/m3)
/// @param whp The Helmholtz free energy properties of water
/// @see WaterHelmholtzProps, WaterThermoProps
auto waterThermoProps(RealConstRef T, RealConstRef D, const WaterHelmholtzProps& whp) -> WaterThermoProps;

} // namespace Fluidika
