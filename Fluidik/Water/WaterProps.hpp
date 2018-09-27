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

namespace Fluidik {

/// A type for storing thermodynamic properties of water.
struct WaterThermoProps
{
	/// The temperature of water (in units of K)
	Real temperature;

	/// The specific volume of water (in units of m3/kg)
	Real volume;

	/// The specific entropy of water (in units of J/(kg*K))
	Real entropy;

	/// The specific Helmholtz free energy of water (in units of J/kg)
	Real helmholtz;

	/// The specific internal energy of water (in units of J/kg)
	Real internal_energy;

	/// The specific enthalpy of water (in units of J/kg)
	Real enthalpy;

	/// The specific Gibbs free energy of water (in units of J/kg)
	Real gibbs;

	/// The specific isochoric heat capacity of water (in units of J/(kg*K))
	Real cv;

	/// The specific isobaric heat capacity of water (in units of J/(kg*K))
	Real cp;

	/// The specific density of water (in units of kg/m3)
	Real density;

	/// The first-order partial derivative of density with respect to temperature (in units of (kg/m3)/K)
	Real densityT;

	/// The first-order partial derivative of density with respect to pressure (in units of (kg/m3)/Pa)
	Real densityP;

	/// The second-order partial derivative of density with respect to temperature (in units of (kg/m3)/(K*K))
	Real densityTT;

	/// The second-order partial derivative of density with respect to temperature and pressure (in units of (kg/m3)/(K*Pa))
	Real densityTP;

	/// The second-order partial derivative of density with respect to pressure (in units of (kg/m3)/(Pa*Pa))
	Real densityPP;

	/// The pressure of water (in units of Pa)
	Real pressure;

	/// The first-order partial derivative of pressure with respect to temperature (in units of Pa/K)
	Real pressureT;

	/// The first-order partial derivative of pressure with respect to density (in units of Pa/(kg/m3))
	Real pressureD;

	/// The second-order partial derivative of pressure with respect to temperature (in units of Pa/(K*K))
	Real pressureTT;

	/// The second-order partial derivative of pressure with respect to temperature and density (in units of Pa/(K*kg/m3))
	Real pressureTD;

	/// The second-order partial derivative of pressure with respect to density (in units of Pa/((kg/m3)*(kg/m3)))
	Real pressureDD;

    /// The speed of sound (in m/s)
    Real speed_of_sound;
};

/// A type for storing only a small subset of thermodynamic properties of water.
struct WaterThermoPropsSimple
{
    /// The temperature of water (in units of K)
    Real temperature;

    /// The pressure of water (in units of Pa)
    Real pressure;

    /// The specific density of water (in units of kg/m3)
    Real density;

    /// The specific internal energy of water (in units of J/kg)
    Real internal_energy;

    /// The specific enthalpy of water (in units of J/kg)
    Real enthalpy;

    /// The specific entropy of water (in units of J/(kg·K))
    Real entropy;

    /// The specific isochoric heat capacity of water (in units of J/(kg·K))
    Real cv;

    /// The specific isobaric heat capacity of water (in units of J/(kg·K))
    Real cp;

    /// The speed of sound (in m/s)
    Real speed_of_sound;
};

/// A type for storing electrostatic properties of water.
struct WaterElectroProps
{
    /// The dielectric constant of water
    Real epsilon;

    /// The first-order partial derivative of the dielectric constant with respect to temperature
    Real epsilonT;

    /// The first-order partial derivative of the dielectric constant with respect to pressure
    Real epsilonP;

    /// The second-order partial derivative of the dielectric constant with respect to temperature
    Real epsilonTT;

    /// The second-order partial derivative of the dielectric constant with respect to temperature and pressure
    Real epsilonTP;

    /// The second-order partial derivative of the dielectric constant with respect to pressure
    Real epsilonPP;

    /// The Born function \f$ Z\equiv-\frac{1}{\epsilon} \f$ (see Helgeson and Kirkham, 1974)
    Real bornZ;

    /// The Born function \f$ Y\equiv\left[\frac{\partial Z}{\partial T}\right]_{P} \f$ (see Helgeson and Kirkham, 1974)
    Real bornY;

    /// The Born function \f$ Q\equiv\left[\frac{\partial Z}{\partial P}\right]_{T} \f$ (see Helgeson and Kirkham, 1974)
    Real bornQ;

    /// The Born function \f$ N\equiv\left[\frac{\partial Q}{\partial P}\right]_{T} \f$ (see Helgeson and Kirkham, 1974)
    Real bornN;

    /// The Born function \f$ U\equiv\left[\frac{\partial Q}{\partial T}\right]_{P} \f$ (see Helgeson and Kirkham, 1974)
    Real bornU;

    /// The Born function \f$ X\equiv\left[\frac{\partial Y}{\partial T}\right]_{P} \f$ (see Helgeson and Kirkham, 1974)
    Real bornX;
};

/// A type for storing specific Helmholtz free energy of water for Helmholtz-based water thermodynamic models.
struct WaterHelmholtzProps
{
    /// The specific Helmholtz free energy of water (in units of J/kg)
    Real helmholtz;

    /// The first-order partial derivative of the specific Helmholtz free energy of water with respect to temperature
    Real helmholtzT;

    /// The first-order partial derivative of the specific Helmholtz free energy of water with respect to density
    Real helmholtzD;

    /// The second-order partial derivative of the specific Helmholtz free energy of water with respect to temperature
    Real helmholtzTT;

    /// The second-order partial derivative of the specific Helmholtz free energy of water with respect to temperature and density
    Real helmholtzTD;

    /// The second-order partial derivative of the specific Helmholtz free energy of water with respect to density
    Real helmholtzDD;

    /// The third-order partial derivative of the specific Helmholtz free energy of water with respect to temperature
    Real helmholtzTTT;

    /// The third-order partial derivative of the specific Helmholtz free energy of water with respect to temperature, temperature, and density
    Real helmholtzTTD;

    /// The third-order partial derivative of the specific Helmholtz free energy of water with respect to temperature, density, and density
    Real helmholtzTDD;

    /// The third-order partial derivative of the specific Helmholtz free energy of water with respect to density
    Real helmholtzDDD;
};

} // namespace Fluidik
