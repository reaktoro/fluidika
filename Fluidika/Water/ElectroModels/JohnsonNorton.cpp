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

#include "JohnsonNorton.hpp"

// Fluidika includes
#include <Fluidika/Common/Exception.hpp>
#include <Fluidika/Water/WaterProps.hpp>
#include <Fluidika/Water/ElectroModels/UematsuFranck.hpp>

namespace Fluidika {

auto waterElectroPropsJohnsonNorton(const WaterThermoProps& wtp) -> WaterElectroProps
{
    // Temperature and pressure for electrostatic properties calculation
    const auto T = wtp.temperature;
    const auto P = wtp.pressure;

    // Temperature and pressure valid ranges (with some margin) in Johnson and Norton (1991)
    const auto Tmin = 273.15 - 1;
    const auto Tmax = 1273.15 + 1;
    const auto Pmin = 0.0;
    const auto Pmax = (5000.0 + 1) * 1e+5;

    // Check if valid temperature
    warning(T < Tmin || T > Tmax, "Evaluating electrostatic properties of water at ", T, " K and ", P/1e5, " bar using Johnson and Norton (1991) model. "
        "This temperature is not within the valid temperature range for this model: 273.15 to 1273.15 K.");

    // Check if valid pressure
    warning(P < Pmin || P > Pmax, "Evaluating electrostatic properties of water at ", T, " K and ", P/1e5, " bar using Johnson and Norton (1991) model. "
        "This pressure is not within the valid pressure range for this model: 0 to 5000 bar.");

    // The parameters of Johnson and Norton (1991) electrostatic model
    const UematsuFranckParams params{
         0.1470333593e+02,
         0.2128462733e+03,
        -0.1154445173e+03,
         0.1955210915e+02,
        -0.8330347980e+02,
         0.3213240048e+02,
        -0.6694098645e+01,
        -0.3786202045e+02,
         0.6887359646e+02,
        -0.2729401652e+02};

    return waterElectroPropsUematsuFranck(wtp, params);
}

} // namespace Fluidika
