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

#include "UematsuFranck.hpp"

// C++ includes
#include <cmath>
using std::sqrt;

// Fluidik includes
#include <Fluidik/Common/Exception.hpp>
#include <Fluidik/Water/WaterProps.hpp>

namespace Fluidik {

auto waterElectroPropsUematsuFranck(const WaterThermoProps& wtp) -> WaterElectroProps
{
    // Temperature and pressure for electrostatic properties calculation
    const auto T = wtp.temperature;
    const auto P = wtp.pressure;

    // Temperature and pressure valid ranges (with some margin) in Uematsu and Franck (1980)
    const auto Tmin = 273.15 - 1;
    const auto Tmax = 823.15 + 1;
    const auto Pmin = 0.0;
    const auto Pmax = (5000.0 + 1) * 1e+5;

    // Check if valid temperature
    warning(T < Tmin || T > Tmax, "Evaluating electrostatic properties of water at ", T, " K and ", P/1e5, " bar using Uematsu and Franck (1980) model. "
        "This temperature is not within the valid temperature range for this model: 273.15 to 823.15 K.");

    // Check if valid pressure
    warning(P < Pmin || P > Pmax, "Evaluating electrostatic properties of water at ", T, " K and ", P/1e5, " bar using Uematsu and Franck (1980) model. "
        "This pressure is not within the valid pressure range for this model: 0 to 5000 bar.");

    // The parameters of Uematsu and Franck (1980) electrostatic model
    const UematsuFranckParams params = {
		 0.762571e+1,
		 0.244003e+3,
		-0.140569e+3,
		 0.277841e+2,
		-0.962805e+2,
		 0.417909e+2,
		-0.102099e+2,
		-0.452059e+2,
		 0.846395e+2,
		-0.358644e+2
	};

	return waterElectroPropsUematsuFranck(wtp, params);
}

auto waterElectroPropsUematsuFranck(const WaterThermoProps& wtp, const UematsuFranckParams& params) -> WaterElectroProps
{
	const auto& A1 = params.A1;
	const auto& A2 = params.A2;
	const auto& A3 = params.A3;
	const auto& A4 = params.A4;
	const auto& A5 = params.A5;
	const auto& A6 = params.A6;
	const auto& A7 = params.A7;
	const auto& A8 = params.A8;
	const auto& A9 = params.A9;
	const auto& A10 = params.A10;

	WaterElectroProps we = {};

	const auto T = wtp.temperature;

	const auto alpha  = -wtp.densityT/wtp.density;
    const auto beta   =  wtp.densityP/wtp.density;
    const auto alphaT = -wtp.densityTT/wtp.density + alpha*alpha;
    const auto betaT  =  wtp.densityTP/wtp.density + alpha*beta;
    const auto betaP  =  wtp.densityPP/wtp.density - beta*beta;

    // The reference density (in kg/m3) in Uematsu and Franck (1980) dielectric constant model
    const auto Tr = 298.15;

    // The reference density (in kg/m3) in Uematsu and Franck (1980) dielectric constant model
    const auto Dr = 1000.0;

	const auto t = T/Tr;
	const auto tt = t*t;
	const auto ttt = t*tt;
	const auto tttt = t*ttt;

	const auto r = wtp.density/Dr;

	const Real k[] = { 1.0, A1/t, A2/t + A3 + A4*t, A5/t + A6*t + A7*tt, A8/tt + A9/t + A10 };
	const Real k_t[] = { 0.0, -A1/tt, -A2/tt + A4, -A5/tt + A6 + 2*A7*t, -2*A8/ttt - A9/tt };
	const Real k_tt[] = { 0.0, 2*A1/ttt, 2*A2/ttt, 2*A5/ttt + 2*A7, 6*A8/tttt + 2*A9/ttt };

	for(auto i = 0; i <= 4; ++i)
	{
		const auto ri    = pow(r, i);
		const auto ki    = k[i];
		const auto ki_t  = k_t[i]/Tr;
		const auto ki_tt = k_tt[i]/(Tr*Tr);

		we.epsilon   += ki*ri;
		we.epsilonT  += ri*(ki_t - i*alpha*ki);
		we.epsilonP  += ri*ki*i*beta;
		we.epsilonTT += ri*(ki_tt - i*(alpha*ki_t + ki*alphaT) - i*alpha*(ki_t - i*alpha*ki));
		we.epsilonTP += ri*ki*i*beta*(ki_t/ki - i*alpha + betaT/beta);
		we.epsilonPP += ri*ki*i*beta*(i*beta + betaP/beta);
	}

	const auto epsilon2 = we.epsilon * we.epsilon;

	we.bornZ = -1.0/we.epsilon;
	we.bornY = we.epsilonT/epsilon2;
	we.bornQ = we.epsilonP/epsilon2;
	we.bornU = we.epsilonTP/epsilon2 - 2.0*we.bornY*we.bornQ*we.epsilon;
	we.bornN = we.epsilonPP/epsilon2 - 2.0*we.bornQ*we.bornQ*we.epsilon;
	we.bornX = we.epsilonTT/epsilon2 - 2.0*we.bornY*we.bornY*we.epsilon;

	return we;
}

} // namespace Fluidik
