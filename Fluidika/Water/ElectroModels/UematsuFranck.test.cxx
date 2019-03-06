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

// Catch includes
#include <catch2/catch.hpp>

// Fluidika includes
#include <Fluidika/Water/ElectroModels/UematsuFranck.hpp>
#include <Fluidika/Water/ThermoModels/HGK.hpp>
#include <Fluidika/Water/WaterProps.hpp>
using namespace Fluidika;

// The dielectric constants of water and steam collected from Table 4 in Uematsu and Franck (1990)
// Each row corresponds to a different pressure, and each column to a different temperature.
// See pressure and temperature values below.
const std::array<std::array<double, 18>, 26> epsilon_uematsu_franck_1990 =
{
    std::array<double, 18>
    {{ 87.81, 78.46, 69.91, 62.24,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00,  1.00}},
    {{ 87.83, 78.47, 69.92, 62.25, 55.43, 49.36, 43.95,  1.01,  1.01,  1.01,  1.01,  1.01,  1.01,  1.01,  1.01,  1.00,  1.00,  1.00}},
    {{ 87.86, 78.49, 69.94, 62.27, 55.44, 49.37, 43.96, 39.11,  1.02,  1.02,  1.02,  1.02,  1.02,  1.02,  1.01,  1.01,  1.01,  1.01}},
    {{ 87.93, 78.55, 69.99, 62.33, 55.50, 49.43, 44.02, 39.17, 34.79,  1.07,  1.06,  1.05,  1.04,  1.04,  1.03,  1.03,  1.02,  1.02}},
    {{ 88.05, 78.65, 70.09, 62.42, 55.59, 49.52, 44.12, 39.28, 34.90, 30.89, 27.15,  1.13,  1.11,  1.08,  1.07,  1.06,  1.05,  1.04}},
    {{ 88.28, 78.85, 70.27, 62.59, 55.76, 49.70, 44.30, 39.47, 35.11, 31.13, 27.43, 23.90, 20.39,  1.23,  1.17,  1.14,  1.11,  1.10}},
    {{ 88.75, 79.24, 70.63, 62.94, 56.11, 50.05, 44.66, 39.85, 35.52, 31.58, 27.95, 24.54, 21.24, 14.07,  1.64,  1.42,  1.32,  1.26}},
    {{ 89.20, 79.63, 70.98, 63.28, 56.44, 50.39, 45.01, 40.22, 35.91, 32.01, 28.43, 25.11, 21.95, 15.66,  5.91,  2.07,  1.68,  1.51}},
    {{ 89.64, 80.00, 71.32, 63.61, 56.77, 50.72, 45.34, 40.56, 36.28, 32.40, 28.87, 25.61, 22.56, 16.72, 10.46,  3.84,  2.34,  1.90}},
    {{ 90.07, 80.36, 71.66, 63.93, 57.08, 51.03, 45.67, 40.89, 36.63, 32.78, 29.28, 26.08, 23.10, 17.55, 12.16,  6.57,  3.45,  2.48}},
    {{ 90.49, 80.72, 71.98, 64.24, 57.39, 51.34, 45.98, 41.21, 36.96, 33.13, 29.67, 26.50, 23.58, 18.24, 13.28,  8.53,  4.90,  3.26}},
    {{ 90.90, 81.07, 72.30, 64.54, 57.69, 51.64, 46.20, 41.52, 37.28, 33.47, 30.03, 26.90, 24.02, 18.84, 14.16,  9.87,  6.31,  4.20}},
    {{ 91.29, 81.42, 72.62, 64.84, 57.98, 51.93, 46.57, 41.82, 37.59, 33.79, 30.37, 27.27, 24.43, 19.37, 14.88, 10.88,  7.50,  5.16}},
    {{ 91.67, 81.75, 72.92, 65.13, 58.27, 52.21, 46.86, 42.11, 37.89, 34.10, 30.70, 27.62, 24.81, 19.85, 15.50, 11.70,  8.47,  6.06}},
    {{ 92.04, 82.08, 73.22, 65.42, 58.55, 52.49, 47.14, 42.39, 38.17, 34.40, 31.01, 27.95, 25.17, 20.29, 16.05, 12.39,  9.29,  6.88}},
    {{ 92.89, 82.84, 73.93, 66.09, 59.19, 53.12, 47.78, 43.05, 38.86, 35.13, 31.78, 28.76, 26.03, 21.26, 17.21, 13.77, 10.88,  8.53}},
    {{ 93.71, 83.57, 74.62, 66.74, 59.82, 53.75, 48.40, 43.68, 39.50, 35.78, 32.46, 29.47, 26.77, 22.09, 18.16, 14.85, 12.07,  9.80}},
    {{ 94.48, 84.28, 75.27, 67.36, 60.42, 54.34, 48.98, 44.27, 40.10, 36.39, 33.09, 30.12, 27.45, 22.83, 18.98, 15.74, 13.04, 10.81}},
    {{ 95.20, 84.94, 75.89, 67.95, 61.00, 54.90, 49.54, 44.83, 40.66, 36.97, 33.67, 30.72, 28.07, 23.49, 19.69, 16.51, 13.86, 11.65}},
    {{ 95.87, 85.58, 76.50, 68.53, 61.55, 55.44, 50.08, 45.36, 41.20, 37.51, 34.22, 31.28, 28.64, 24.09, 20.33, 17.19, 14.56, 12.38}},
    {{ 96.51, 86.20, 77.08, 69.08, 62.08, 55.96, 50.59, 45.87, 41.70, 38.02, 34.74, 31.81, 29.17, 24.65, 20.91, 17.80, 15.19, 13.01}},
    {{ 97.69, 87.34, 78.17, 70.14, 63.10, 56.94, 51.55, 46.82, 42.65, 38.97, 35.69, 32.77, 30.15, 25.65, 21.94, 18.85, 16.25, 14.07}},
    {{ 98.75, 88.40, 79.19, 71.12, 64.05, 57.86, 52.45, 47.70, 43.52, 39.83, 36.56, 33.64, 31.02, 26.53, 22.83, 19.74, 17.14, 14.93}},
    {{ 99.72, 89.39, 80.13, 72.03, 64.94, 58.74, 53.30, 48.53, 44.33, 40.64, 37.36, 34.43, 31.81, 27.32, 23.62, 20.52, 17.89, 15.66}},
    {{100.60, 90.30, 81.02, 72.89, 65.78, 59.56, 54.10, 49.31, 45.10, 41.38, 38.09, 35.16, 32.54, 28.04, 24.32, 21.20, 18.55, 16.28}},
    {{101.42, 91.16, 81.84, 73.69, 66.57, 60.33, 54.85, 50.05, 45.82, 42.09, 38.78, 35.84, 33.21, 28.70, 24.96, 21.82, 19.14, 16.83}},
};

// The temperature values (in C) in Table 4 in Uematsu and Franck (1990)
const std::array<double, 18> temperatures = {{ 0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 350, 400, 450, 500, 550 }};

// The pressure values (in MPa) in Table 4 in Uematsu and Franck (1990)
const std::array<double, 26> pressures = {{ 0.1, 0.5, 1.0, 2.5, 5.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0 }};

TEST_CASE("Fluidika::WaterElectroModels::UematsuFranck", "[UematsuFranck]")
{
    const auto nt = temperatures.size();
    const auto np = pressures.size();

    const auto MPa = 1.0e6;

    for(std::size_t i = 0; i < nt; ++i) for(std::size_t j = 0; j < np; ++j)
    {
        const auto expected = epsilon_uematsu_franck_1990[j][i];
        const auto P = pressures[j] * MPa; // pressure in Pa
        const auto T = temperatures[i] + 273.15; // temperature in K
        const auto stateofmatter = expected < 10.0 ? StateOfMatter::Gas : StateOfMatter::Liquid;
        const auto wtp = waterThermoPropsHGK(T, P, stateofmatter);
        const auto wep = waterElectroPropsUematsuFranck(wtp);

        const auto tol = 1e-2;

        CHECK(wep.epsilon == Approx(expected).epsilon(tol));
    }
}
