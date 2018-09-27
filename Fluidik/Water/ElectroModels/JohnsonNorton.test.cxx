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
#include <Fluidik/Water/ElectroModels/JohnsonNorton.hpp>
#include <Fluidik/Water/ThermoModels/HGK.hpp>
#include <Fluidik/Water/WaterProps.hpp>

using namespace Fluidik;

// The electrostatic data from Tables 20-24 in Johnson and Norton (1991)
std::array<std::array<double, 6>, 25> electro_values_johnson_norton_collected =
{
    // P (bar), T (celsius), epsilon, Q Born (1/bar), Y Born (1/K), X Born (1/K^2)
    std::array<double, 6>
    {{250, 375, 0.10541e+2, 0.45508e-3, -0.24371e-2, -0.28048e-3}},
    {{300, 375, 0.12188e+2, 0.15763e-3, -0.11214e-2, -0.49519e-4}},
    {{350, 375, 0.13155e+2, 0.94292e-4, -0.79310e-3, -0.22555e-4}},
    {{400, 375, 0.13877e+2, 0.66862e-4, -0.63604e-3, -0.13617e-4}},
    {{450, 375, 0.14465e+2, 0.51595e-4, -0.54165e-3, -0.94162e-5}},
    {{250, 400, 0.27268e+1, 0.38536e-2, -0.59716e-2,  0.29417e-3}},
    {{300, 400, 0.62851e+1, 0.24803e-2, -0.80815e-2, -0.64866e-3}},
    {{350, 400, 0.92227e+1, 0.42644e-3, -0.21818e-2, -0.12071e-3}},
    {{400, 400, 0.10612e+2, 0.19452e-3, -0.12538e-2, -0.42576e-4}},
    {{450, 400, 0.11545e+2, 0.12066e-3, -0.91001e-3, -0.22362e-4}},
    {{250, 425, 0.21427e+1, 0.24521e-2, -0.28794e-2,  0.54020e-4}},
    {{300, 425, 0.29543e+1, 0.26610e-2, -0.46465e-2,  0.13608e-3}},
    {{350, 425, 0.46821e+1, 0.20476e-2, -0.55596e-2,  0.32679e-4}},
    {{400, 425, 0.68494e+1, 0.79885e-3, -0.31555e-2, -0.96022e-4}},
    {{450, 425, 0.83912e+1, 0.35883e-3, -0.18263e-2, -0.52942e-4}},
    {{250, 450, 0.19009e+1, 0.19851e-2, -0.19919e-2,  0.23621e-4}},
    {{300, 450, 0.23460e+1, 0.19996e-2, -0.27407e-2,  0.42733e-4}},
    {{350, 450, 0.30502e+1, 0.19041e-2, -0.35698e-2,  0.64149e-4}},
    {{400, 450, 0.41456e+1, 0.14967e-2, -0.38413e-2,  0.35239e-4}},
    {{450, 450, 0.55045e+1, 0.89658e-3, -0.30530e-2, -0.24675e-4}},
    {{250, 475, 0.17551e+1, 0.17222e-2, -0.15433e-2,  0.13720e-4}},
    {{300, 475, 0.20648e+1, 0.16900e-2, -0.19908e-2,  0.21217e-4}},
    {{350, 475, 0.24906e+1, 0.16119e-2, -0.24624e-2,  0.30173e-4}},
    {{400, 475, 0.30809e+1, 0.14468e-2, -0.28459e-2,  0.34396e-4}},
    {{450, 475, 0.38635e+1, 0.11651e-2, -0.29229e-2,  0.22331e-4}},
};

// The expected electrostatic data using Johnson and Norton (1991) model
// This has been previously calculated and checked against the collected values
std::array<std::array<double, 6>, 25> electro_values_johnson_norton_expected =
{
    // P (bar), T (celsius), epsilon, Q Born (1/Pa), Y Born (1/K), X Born (1/K^2)
    std::array<double, 6>
    {{250, 375, 1.054080e+01, 4.550753e-09, -2.437143e-03, -2.797131e-04}},
    {{300, 375, 1.218774e+01, 1.576271e-09, -1.121407e-03, -4.931451e-05}},
    {{350, 375, 1.315539e+01, 9.429215e-10, -7.931025e-04, -2.244223e-05}},
    {{400, 375, 1.387697e+01, 6.686167e-10, -6.360427e-04, -1.354016e-05}},
    {{450, 375, 1.446501e+01, 5.159477e-10, -5.416544e-04, -9.358222e-06}},
    {{250, 400, 2.726794e+00, 3.853566e-08, -5.971650e-03,  2.942215e-04}},
    {{300, 400, 6.277783e+00, 2.423672e-08, -7.872379e-03, -5.625152e-04}},
    {{350, 400, 9.222743e+00, 4.264371e-09, -2.181847e-03, -1.203128e-04}},
    {{400, 400, 1.061234e+01, 1.945158e-09, -1.253849e-03, -4.239836e-05}},
    {{450, 400, 1.154502e+01, 1.206552e-09, -9.100070e-04, -2.225399e-05}},
    {{250, 425, 2.142696e+00, 2.452107e-08, -2.879379e-03,  5.402458e-05}},
    {{300, 425, 2.954329e+00, 2.661005e-08, -4.646484e-03,  1.361258e-04}},
    {{350, 425, 4.682069e+00, 2.047555e-08, -5.559594e-03,  3.301617e-05}},
    {{400, 425, 6.849387e+00, 7.988526e-09, -3.155520e-03, -9.566326e-05}},
    {{450, 425, 8.391184e+00, 3.588292e-09, -1.826312e-03, -5.273598e-05}},
    {{250, 450, 1.900882e+00, 1.985084e-08, -1.991888e-03,  2.362266e-05}},
    {{300, 450, 2.345964e+00, 1.999633e-08, -2.740738e-03,  4.273907e-05}},
    {{350, 450, 3.050218e+00, 1.904091e-08, -3.569773e-03,  6.417906e-05}},
    {{400, 450, 4.145610e+00, 1.496713e-08, -3.841315e-03,  3.534563e-05}},
    {{450, 450, 5.504512e+00, 8.965779e-09, -3.052961e-03, -2.450544e-05}},
    {{250, 475, 1.755139e+00, 1.722244e-08, -1.543339e-03,  1.372018e-05}},
    {{300, 475, 2.064756e+00, 1.690020e-08, -1.990829e-03,  2.121839e-05}},
    {{350, 475, 2.490621e+00, 1.611918e-08, -2.462371e-03,  3.017939e-05}},
    {{400, 475, 3.080932e+00, 1.446774e-08, -2.845898e-03,  3.441697e-05}},
    {{450, 475, 3.863490e+00, 1.165101e-08, -2.922880e-03,  2.237989e-05}},
};

auto fixunits(std::array<double, 6>& values) -> void
{
    values[0] *= 1e+5; // pressure from bar to Pa
    values[1] += 273.15; // temperature from celsius to kelvin
    values[3] *= 1e-5; // Q Born from 1/bar to 1/Pa
}

TEST_CASE("Fluidik::WaterElectroModel::JohnsonNorton", "[JohnsonNorton]")
{
    for(auto values : electro_values_johnson_norton_expected)
    {
        fixunits(values);
        const auto P = values[0]; // pressure in Pa
        const auto T = values[1]; // temperature in K
        const auto wtp = waterThermoPropsHGK(T, P);
        const auto wep = waterElectroPropsJohnsonNorton(wtp);

        const auto tol = 1e-6;
        const auto bar = 1e5;

        CHECK(wep.epsilon == Approx(values[2]).epsilon(tol));
        CHECK(wep.bornQ == Approx(values[3]).epsilon(tol).scale(bar));
        CHECK(wep.bornY == Approx(values[4]).epsilon(tol));
        CHECK(wep.bornX == Approx(values[5]).epsilon(tol));
    }
}
