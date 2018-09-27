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

// Catch includes
#include <catch/catch.hpp>

// Fluidik includes
#include <Fluidik/Water/ThermoModels/Utils.hpp>
#include <Fluidik/Water/ThermoModels/WagnerPruss.hpp>
#include <Fluidik/Water/WaterData.hpp>
#include <Fluidik/Water/WaterProps.hpp>
using namespace Fluidik;

// An auxiliary approx function
inline auto approx(RealConstRef value) -> Approx
{
    // The comparison tolerance set to 1.0%.
    // Note Table 13.2 in Wagner and Pruss (2002) has not sufficient significant digits to allow a strict tolerance.
    // We have thus to relax the tolerance to ensure all tests pass.
    return Approx(value).epsilon(0.01);
}

TEST_CASE("Fluidik::WaterThermoModels::WagnerPruss", "[WagnerPruss]")
{
    // Scaling factor to compare pressures in MPa scale
    const auto MPa = 1.0e6;

    // Scaling factor to compare energy-related data in kJ scale
    const auto kJ = 1.0e3;

    SECTION("when temperature and density are given")
    {
        for(auto item : waterThermoDataSinglePhaseStateWagnerPruss())
        {
            const auto T = item.temperature;
            const auto D = item.density;
            const auto wtp = waterThermoProps(T, D, waterHelmholtzPropsWagnerPruss(T, D));

            REQUIRE(wtp.temperature == approx(item.temperature));
            REQUIRE(wtp.pressure == approx(item.pressure).scale(MPa));
            REQUIRE(wtp.density == approx(item.density));
            REQUIRE(wtp.internal_energy == approx(item.internal_energy).scale(kJ));
            REQUIRE(wtp.enthalpy == approx(item.enthalpy).scale(kJ));
            REQUIRE(wtp.entropy == approx(item.entropy).scale(kJ));
            REQUIRE(wtp.cv == approx(item.cv).scale(kJ));
            REQUIRE(wtp.cp == approx(item.cp).scale(kJ));
            REQUIRE(wtp.speed_of_sound == approx(item.speed_of_sound));
        }
    }

    SECTION("when temperature and pressure are given, and density is given as initial guess")
    {
        for(auto item : waterThermoDataSinglePhaseStateWagnerPruss())
        {
            const auto T = item.temperature;
            const auto P = item.pressure;
            const auto D = item.density * 1.2; // multiply density by 1.2 to ensure we don't start with an initial guess that is the exact solution
            const auto wtp = waterThermoPropsWagnerPruss(T, P, D);

            REQUIRE(wtp.temperature == approx(item.temperature));
            REQUIRE(wtp.pressure == approx(item.pressure).scale(MPa));
            REQUIRE(wtp.density == approx(item.density));
            REQUIRE(wtp.internal_energy == approx(item.internal_energy).scale(kJ));
            REQUIRE(wtp.enthalpy == approx(item.enthalpy).scale(kJ));
            REQUIRE(wtp.entropy == approx(item.entropy).scale(kJ));
            REQUIRE(wtp.cv == approx(item.cv).scale(kJ));
            REQUIRE(wtp.cp == approx(item.cp).scale(kJ));
            REQUIRE(wtp.speed_of_sound == approx(item.speed_of_sound));
        }
    }
}
