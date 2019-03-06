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

/// Calculate the electrostatic properties of water using Uematsu and Franck (1980) model with revised parameters from Johnson and Norton (1991).
/// This function calculates electrostatic properties of water using Uematsu and Franck (1980)
/// [@cite{Uematsu1980}] model for dielectric constant of water but with revised parameters
/// given in Table 19 of Johnson and Norton (1991) [@cite{Johnson1991}]:
/// ~~~
/// A1  =  0.1470333593e+02;
/// A2  =  0.2128462733e+03;
/// A3  = -0.1154445173e+03;
/// A4  =  0.1955210915e+02;
/// A5  = -0.8330347980e+02;
/// A6  =  0.3213240048e+02;
/// A7  = -0.6694098645e+01;
/// A8  = -0.3786202045e+02;
/// A9  =  0.6887359646e+02;
/// A10 = -0.2729401652e+02;
/// ~~~
/// This electrostatic model is valid for temperatures 273.15-1273.15 K and pressures 0-5000 bar.
/// @param wtp The thermodynamic properties of water
auto waterElectroPropsJohnsonNorton(const WaterThermoProps& wtp) -> WaterElectroProps;

} // namespace Fluidika
