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

#pragma once

// Fluidika includes
#include <Fluidika/Common/Real.hpp>

namespace Fluidika {

struct WaterElectroProps;
struct WaterThermoProps;
struct WaterProps;

enum class WaterThermoModel;
enum class WaterElectroModel;
//
//class WaterThermoModelParams;
//class WaterThermoModelParamsWagnerPruss;
//class WaterThermoModelParamsHGK;
//
//class WaterElectroModelParams;
//class WaterElectroModelParamsJohnsonNorton;
//
//struct WaterThermoModelParamsWagnerPruss;
//struct WaterThermoModelParamsHGK;
//struct WaterThermoModelParams;
//struct WaterElectroModelParamsJohnsonNorton;
//struct WaterElectroModelParams;
struct WaterModelParams;

// TODO Figure 11 in Johnson and Norton 1991 - reproduce
/// The class for calculation of thermodynamic and electrostatic properties of water.
class Water
{
public:
    /// Construct a default Water instance.
    Water();

    auto setThermoModelWagnerPruss() -> void;

    auto setThermoModelHGK() -> void;

    auto setElectroModelModelJohnsonNorton() -> void;

    auto thermoModel() const -> WaterThermoModel;

    auto electroModel() const -> WaterThermoModel;

    auto thermoProps(RealConstRef T, RealConstRef P) const -> WaterThermoProps;

    auto electroProps(WaterThermoProps thermoprops) const -> WaterElectroProps;

    auto props(RealConstRef T, RealConstRef P) const -> WaterProps;

    auto params() const -> const WaterModelParams;

private:
};
} // namespace Fluidika
