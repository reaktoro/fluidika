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

#include "Utils.hpp"

// C++ includes
#include <cmath>
using std::abs;
using std::sqrt;

// Fluidika includes
#include <Fluidika/Common/Constants.hpp>
#include <Fluidika/Common/Exception.hpp>
#include <Fluidika/Water/WaterData.hpp>
#include <Fluidika/Water/WaterProps.hpp>

namespace Fluidika {

auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P, RealConstRef D0) -> WaterThermoProps
{
    // Auxiliary constants for the Newton's iterations
    const auto max_iters = 100;
    const auto tolerance = 1.0e-08;

    // Determine an adequate initial guess for (dimensionless) density based on the physical state of water
    Real D = D0;

    // The specific Helmholtz free energy properties of water
    WaterHelmholtzProps h;

    // Apply the Newton's method to the pressure-density equation
    for(int i = 1; i <= max_iters; ++i)
    {
        h = model(T, D);

        const auto f  = (D*D*h.helmholtzD - P)/waterCriticalPressure;
        const auto df = (2*D*h.helmholtzD + D*D*h.helmholtzDD)/waterCriticalPressure;

        D = (D > f/df) ? D - f/df : P/(D*h.helmholtzD);

        if(abs(f) < tolerance)
            return waterThermoProps(T, D, h);
    }

    warning(true, "The calculation of water density at temperature ",  T, " K and pressure ", P, "Pa did not converge.");

    return {};
}

auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P) -> WaterThermoProps
{
    const auto D0 = waterThermoDataNearestWagnerPruss(T, P).density;
    return waterThermoProps(model, T, P, D0);
}

auto waterThermoProps(const WaterHelmholtzPropsFunction& model, RealConstRef T, RealConstRef P, StateOfMatter stateofmatter) -> WaterThermoProps
{
    switch(stateofmatter) {
    case StateOfMatter::Solid:
    case StateOfMatter::Liquid:
        return waterThermoProps(model, T, P, waterThermoDataMinTemperatureWagnerPruss(P).density);
    case StateOfMatter::Gas:
    case StateOfMatter::Plasma:
    default:
        return waterThermoProps(model, T, P, waterThermoDataMaxTemperatureWagnerPruss(P).density);
    }
}

auto waterThermoProps(RealConstRef T, RealConstRef D, const WaterHelmholtzProps& whp) -> WaterThermoProps
{
    WaterThermoProps wtp;

    // Set the temperature and density of the thermodynamic state of water
    wtp.temperature = T;
    wtp.density = D;

    // Set the pressure and its partial derivatives of the thermodynamic state of water
    wtp.pressure   = D*D*whp.helmholtzD;
    wtp.pressureD  = 2*D*whp.helmholtzD + D*D*whp.helmholtzDD;
    wtp.pressureT  = D*D*whp.helmholtzTD;
    wtp.pressureDD = 2*whp.helmholtzD + 4*D*whp.helmholtzDD + D*D*whp.helmholtzDDD;
    wtp.pressureTD = 2*D*whp.helmholtzTD + D*D*whp.helmholtzTDD;
    wtp.pressureTT = D*D*whp.helmholtzTTD;

    // Set the density and its partial derivatives of the thermodynamic state of water
    wtp.density   = D;
    wtp.densityT  = -wtp.pressureT/wtp.pressureD;
    wtp.densityP  =  1.0/wtp.pressureD;
    wtp.densityTT = -wtp.densityT*wtp.densityP*(wtp.densityT*wtp.pressureDD + 2*wtp.pressureTD + wtp.pressureTT/wtp.densityT);
    wtp.densityTP = -wtp.densityP*wtp.densityP*(wtp.densityT*wtp.pressureDD + wtp.pressureTD);
    wtp.densityPP = -wtp.densityP*wtp.densityP*wtp.densityP*wtp.pressureDD;

    // Set the specific volume of water
    wtp.volume = 1/D;

    // Set the specific entropy of water
    wtp.entropy = -whp.helmholtzT;

    // Set the specific Helmholtz free energy of water
    wtp.helmholtz = whp.helmholtz;

    // Set the specific internal energy of water
    wtp.internal_energy = wtp.helmholtz + T * wtp.entropy;

    // Set the specific enthalpy of water
    wtp.enthalpy = wtp.internal_energy + wtp.pressure/D;

    // Set the specific Gibbs free energy of water
    wtp.gibbs = wtp.enthalpy - T * wtp.entropy;

    // Set the specific isochoric heat capacity of water
    wtp.cv = -T * whp.helmholtzTT;

    // Set the specific isobaric heat capacity of water
    wtp.cp = wtp.cv + T/(D*D)*wtp.pressureT*wtp.pressureT/wtp.pressureD;

    // Set the speed of sound of water
    wtp.speed_of_sound = sqrt(wtp.pressureD - wtp.pressureT * (-whp.helmholtzTD) / (-whp.helmholtzTT)); // see notes/how-to-calculate-speed-of-water.lyx

    return wtp;
}

} // namespace Fluidika
