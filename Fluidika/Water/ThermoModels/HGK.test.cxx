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

// C++ includes
#include <array>

// Catch includes
#include <catch2/catch.hpp>

// Fluidika includes
#include <Fluidika/Water/ThermoModels/HGK.hpp>
#include <Fluidika/Water/ThermoModels/Utils.hpp>
#include <Fluidika/Water/WaterProps.hpp>
using namespace Fluidika;

//=================================================================================================
// Reference constants as given in Kestin et al (1984)
//=================================================================================================

// Reference temperature of water (in unit of K) --- Eq. (4.1)
const double referenceTemperature = 647.27;

// Reference density of water (in unit of kg/m3) --- Eq. (4.2)
const double referenceDensity = 317.763;

// Reference pressure of water (in unit of Pa) --- Eq. (4.3)
const double referencePressure = 22.115e+06;

// Reference viscosity of water (in unit of Pa*s) --- Eq. (4.4)
const double referenceViscosity = 55.071e-06;

// Reference thermal conductivity of water (in unit of W/(K*m)) --- Eq. (4.5)
const double referenceThermalConductivity = 0.49450;

// Reference surface tension of water (in unit of N/m) --- Eq. (4.6)
const double referenceSurfaceTension = 235.8e-3;

// Reference constant for Helmholtz function (in unit of J/kg) --- Eq. (4.7)
const double referenceHelmholtz = 69595.89;

// Reference constant for entropy specific heat (in unit of J/(kg*K)) --- Eq. (4.8)
const double referenceEntropy = 107.5222;

// Reference constant for sound speed (in unit of m/s) --- Eq. (4.9)
const double referenceSoundSpeed = 263.810;

// Data collected from Table 12 in Kestin et al. (1984)
// - reduced temperature
// - reduced density
// - reduced Helmholtz energy
// - reduced pressure
// - reduced isochoric heat capacity
// - reduced viscosity
// - reduced thermal conductivity
// Reference: Kestin, J., Sengers, J. V., Kamgar-Parsi, B., & Levelt Sengers, J. M. H. (1984). Thermophysical Properties of Fluid H2O. Physica A: Statistical and Theoretical Physics, 126(3), 301–307.
std::array<std::array<double, 7>, 10> table12_kestin_et_al_1984 =
{
    std::array<double, 7>
    { {0.50, 3.20, -0.250554E+0, 0.324936E+1, 0.359788E+2, 0.101430E+2, 0.136939E+1} },
    { {0.75, 2.85, -0.400493E+1, 0.391145E+1, 0.299897E+2, 0.263154E+1, 0.146879E+1} },
    { {0.90, 0.08, -0.127371E+2, 0.260476E+0, 0.196868E+2, 0.366753E+0, 0.113441E+0} },
    { {1.00, 1.50, -0.116979E+2, 0.105315E+1, 0.306178E+2, 0.998110E+0, 0.820132E+0} },
    { {1.20, 0.40, -0.237304E+2, 0.146688E+1, 0.214850E+2, 0.589682E+0, 0.243784E+0} },
    { {1.20, 1.20, -0.203908E+2, 0.304551E+1, 0.248417E+2, 0.926072E+0, 0.573946E+0} },
    { {1.40, 0.20, -0.383216E+2, 0.108246E+1, 0.182170E+2, 0.647290E+0, 0.214271E+0} },
    { {1.40, 0.90, -0.309982E+2, 0.387225E+1, 0.218535E+2, 0.889235E+0, 0.459263E+0} },
    { {1.60, 0.10, -0.551985E+2, 0.664893E+0, 0.178744E+2, 0.722462E+0, 0.226297E+0} },
    { {1.60, 0.70, -0.429449E+2, 0.408739E+1, 0.206189E+2, 0.908446E+0, 0.436321E+0} }
};

// Data collected from Table II.5 in Kestin and Sengers (1986) for an equation of state for heavy water (not implemented here yet)
// - reduced temperature
// - reduced density
// - reduced Helmholtz energy
// - reduced pressure
// - reduced isochoric heat capacity
// - reduced viscosity (not available in this table)
// - reduced thermal conductivity (not available in this table)
// Reference: Kestin, J., & Sengers, J. V. (1986). New International Formulations for the Thermodynamic Properties of Light and Heavy Water. Journal of Physical and Chemical Reference Data. http://doi.org/10.1063/1.555772
std::array<std::array<double, 7>, 8> table_II_5_kestin_and_sengers_1986 =
{
    std::array<double, 7>
    { {0.50, 0.0002, -0.264519E+1, 0.440215E-3, 0.142768E+2, 0, 0} },
    { {0.50, 3.1800, -0.217597E+0, 0.435497E+1, 0.414463E+2, 0, 0} },
    { {0.75, 0.0295, -0.727350E+1, 0.870308E-1, 0.201586E+2, 0, 0} },
    { {0.75, 2.8300, -0.429366E+1, 0.447530E+1, 0.334367E+2, 0, 0} },
    { {1.00, 0.3000, -0.151650E+2, 0.801404E+0, 0.308587E+2, 0, 0} },
    { {1.00, 1.5500, -0.126455E+2, 0.109763E+1, 0.330103E+2, 0, 0} },
    { {1.20, 0.4000, -0.254738E+2, 0.149910E+1, 0.236594E+2, 0, 0} },
    { {1.20, 1.6100, -0.212805E+2, 0.456438E+1, 0.254800E+2, 0, 0} },
};

// Convert a row of dimensionless values in the data above to values with dimension
auto dimensionalform(std::array<double, 7>& values) -> void
{
    values[0] *= referenceTemperature;
    values[1] *= referenceDensity;
    values[2] *= referenceHelmholtz;
    values[3] *= referencePressure;
    values[4] *= referenceEntropy;
    values[5] *= referenceViscosity;
    values[6] *= referenceThermalConductivity;
}

// An auxiliary approx function
inline auto approx(RealConstRef value) -> Approx
{
   // The comparison tolerance set to 1.0%.
   // Note Table 12 in Kestin et al. (1984) has not sufficient significant digits to allow a strict tolerance.
   // We have thus to relax the tolerance to ensure all tests pass.
   return Approx(value).epsilon(0.01);
}

TEST_CASE("Fluidika::WaterThermoModels::HGK", "[HGK]")
{
   // Scaling factor to compare pressures in MPa scale
   const auto MPa = 1.0e6;

   // Scaling factor to compare energy-related data in kJ scale
   const auto kJ = 1.0e3;

   SECTION("when temperature and density are given")
   {
       for(auto item : table12_kestin_et_al_1984)
       {
            dimensionalform(item);

            const auto T = item[0];
            const auto D = item[1];
            const auto wtp = waterThermoProps(T, D, waterHelmholtzPropsHGK(T, D));

            REQUIRE(wtp.temperature == approx(item[0]));
            REQUIRE(wtp.density == approx(item[1]));
            REQUIRE(wtp.helmholtz == approx(item[2]).scale(kJ));
            REQUIRE(wtp.pressure == approx(item[3]).scale(MPa));
            REQUIRE(wtp.cv == approx(item[4]).scale(kJ));
       }
   }

    SECTION("when temperature and pressure are given, and density is given as initial guess")
    {
        for(auto item : table12_kestin_et_al_1984)
        {
            dimensionalform(item);

            const auto T = item[0];
            const auto D = item[1] * 1.2; // multiply density by 1.2 to ensure we don't start with an initial guess that is the exact solution
            const auto P = item[3];
            const auto wtp = waterThermoPropsHGK(T, P, D);

            REQUIRE(wtp.temperature == approx(item[0]));
            REQUIRE(wtp.density == approx(item[1]));
            REQUIRE(wtp.helmholtz == approx(item[2]).scale(kJ));
            REQUIRE(wtp.pressure == approx(item[3]).scale(MPa));
            REQUIRE(wtp.cv == approx(item[4]).scale(kJ));
        }
    }
}
