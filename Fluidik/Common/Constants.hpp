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
#include <limits>

namespace Fluidik {

//=================================================================================================
// GENERAL PHYSICAL AND CHEMICAL CONSTANTS
//=================================================================================================
/// The universal gas constant (in units of J/(mol*K))
const auto universalGasConstant = 8.3144621;

/// The Faraday constant (in units of C/mol)
const auto faradayConstant = 96485.3329;

//=================================================================================================
// WATER CONSTANTS
//=================================================================================================
/// The molar mass of water in units of kg/mol
const auto waterMolarMass = 0.018015268;

/// The critical temperature of water in units of K
const auto waterCriticalTemperature = 647.096;

/// The critical pressure of water in units of Pa
const auto waterCriticalPressure = 22.064e+06;

/// The critical density of water in units of kg/m3
const auto waterCriticalDensity = 322.0;

/// The triple point temperature of water in units of K
const auto waterTriplePointTemperature = 273.16;

/// The triple point pressure of water in units of Pa
const auto waterTriplePointPressure = 611.655;

/// The triple point liquid-density of water in units of kg/m3
const auto waterTriplePointDensityLiquid = 999.793;

/// The triple point vapour-density of water in units of kg/m3
const auto waterTriplePointDensityVapour = 0.00485458;

//=================================================================================================
// UNIT CONVERTION CONSTANTS
//=================================================================================================
/// The constant factor that converts joule to calorie
const auto jouleToCalorie = 0.239005736;

/// The constant factor that converts calorie to joule
const auto calorieToJoule = 4.184;

/// The conversion factor from bar to pascal
const auto barToPascal = 1.0e+05;

/// The conversion factor from cubic centimeters to cubic meters
const auto cubicCentimeterToCubicMeter = 1.0e-06;

/// The conversion factor from cubic meters to cubic centimeters
const auto cubicMeterToCubicCentimeter = 1.0e+06;

//=================================================================================================
// MATHEMATICAL CONSTANTS
//=================================================================================================
/// The infinity value
const auto INF = std::numeric_limits<double>::infinity();

} // namespace Fluidik
