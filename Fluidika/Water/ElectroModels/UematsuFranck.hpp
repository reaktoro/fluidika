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

/// The type to store parameters in Uematsu and Franck (1980) water electrostatic model.
struct UematsuFranckParams
{
    /// The parameter A@sub{1} in the model.
    Real A1;

    /// The parameter A@sub{2} in the model.
    Real A2;

    /// The parameter A@sub{3} in the model.
    Real A3;

    /// The parameter A@sub{4} in the model.
    Real A4;

    /// The parameter A@sub{5} in the model.
    Real A5;

    /// The parameter A@sub{6} in the model.
    Real A6;

    /// The parameter A@sub{7} in the model.
    Real A7;

    /// The parameter A@sub{8} in the model.
    Real A8;

    /// The parameter A@sub{9} in the model.
    Real A9;

    /// The parameter A@sub{10} in the model.
    Real A10;
};

/// Calculate the electrostatic properties of water using Uematsu and Franck (1980) model.
/// This function calculates electrostatic properties of water using Uematsu and Franck (1980)
/// [@cite{Uematsu1980}] model for dielectric constant of water.
/// The parameters are those found in Table 3 of Uematsu and Franck (1980):
/// ~~~
/// A1  =  0.762571e+1;
/// A2  =  0.244003e+3;
/// A3  = -0.140569e+3;
/// A4  =  0.277841e+2;
/// A5  = -0.962805e+2;
/// A6  =  0.417909e+2;
/// A7  = -0.102099e+2;
/// A8  = -0.452059e+2;
/// A9  =  0.846395e+2;
/// A10 = -0.358644e+2;
/// ~~~
/// This electrostatic model is valid for temperatures between 273.15 and 823.15 K,
/// pressures 0 and 5000 bar, and water densities 0 and 1150 kg/m@sup{3}.
/// @param wtp The thermodynamic properties of water
auto waterElectroPropsUematsuFranck(const WaterThermoProps& wtp) -> WaterElectroProps;

/// Calculate the electrostatic properties of water using Uematsu and Franck (1980) model.
/// This function calculates electrostatic properties of water using
/// Uematsu and Franck (1980) [@cite{Uematsu1980}] model for dielectric constant of water.
/// See equation (1) and Table 3 in Uematsu and Franck (1980).
/// @param wtp The thermodynamic properties of water
/// @param params The parameters in the Uematsu and Franck (1980) model
auto waterElectroPropsUematsuFranck(const WaterThermoProps& wtp, const UematsuFranckParams& params) -> WaterElectroProps;

} // namespace Fluidika
