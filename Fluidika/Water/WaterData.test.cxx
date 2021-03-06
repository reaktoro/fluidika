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

// Catch includes
#include <catch2/catch.hpp>

// Fluidika includes
#include <Fluidika/Water/WaterData.hpp>
#include <Fluidika/Water/WaterProps.hpp>
using namespace Fluidika;

TEST_CASE("Fluidika::WaterThermoDataWagnerPruss", "[WaterThermoDataWagnerPruss]")
{
    for(auto item : waterThermoDataSinglePhaseStateWagnerPruss())
    {
        const auto T = item.temperature;
        const auto P = item.pressure;
        const auto wps = waterThermoDataNearestWagnerPruss(T, P);
        REQUIRE(wps.temperature == T);
        REQUIRE(wps.pressure == P);
    }
}
