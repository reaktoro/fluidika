# Fluidika

Fluidika is a C++17 library for calculation of thermodynamic and electrostatic
properties of pure fluids. This library is used in, and is part of, the
[Reaktoro Project].

It currently implements the following equations of state for **thermodynamic
properties of water**:

- Haar-Gallagher-Kell (1984) (IAPWS Formulation 1984)
- Wagner and Pruss (2002) ([IAPWS-95
  Formulation](https://aip.scitation.org/doi/10.1063/1.1461829))

Equations of state for **electrostatic properties of water** include:

- Helgeson and Kirkham (1974);
- Uematsu and Franck (1980); and
- Johnson and Norton (1991)

## Overview

Below is an example in which Fluidika is used to compute thermodynamic
properties of water using the Wagner and Pruss (2002) equation of state.

~~~cpp
// C++ includes
#include <iostream>
using namespace std;

// Fluidika includes
#include <Fluidika/Fluidika.hpp>
using namespace Fluidika;

int main()
{
    // Calculate the thermodynamic properties of water at 300 K and 1 MPa (=1e6 Pa)
    WaterThermoProps props = waterThermoPropsWagnerPruss(300.0, 1.0e6);

    cout << "The temperature of water (in units of K)" << endl;
    cout << props.temperature << endl;

    cout << "The specific volume of water (in units of m3/kg)" << endl;
    cout << props.volume << endl;

    cout << "The specific entropy of water (in units of J/(kg*K))" << endl;
    cout << props.entropy << endl;

    cout << "The specific Helmholtz free energy of water (in units of J/kg)" << endl;
    cout << props.helmholtz << endl;

    cout << "The specific internal energy of water (in units of J/kg)" << endl;
    cout << props.internal_energy << endl;

    cout << "The specific enthalpy of water (in units of J/kg)" << endl;
    cout << props.enthalpy << endl;

    cout << "The specific Gibbs free energy of water (in units of J/kg)" << endl;
    cout << props.gibbs << endl;

    cout << "The specific isochoric heat capacity of water (in units of J/(kg*K))" << endl;
    cout << props.cv << endl;

    cout << "The specific isobaric heat capacity of water (in units of J/(kg*K))" << endl;
    cout << props.cp << endl;

    cout << "The specific density of water (in units of kg/m3)" << endl;
    cout << props.density << endl;

    cout << "The first-order partial derivative of density with respect to temperature (in units of (kg/m3)/K)" << endl;
    cout << props.densityT << endl;

    cout << "The first-order partial derivative of density with respect to pressure (in units of (kg/m3)/Pa)" << endl;
    cout << props.densityP << endl;

    cout << "The second-order partial derivative of density with respect to temperature (in units of (kg/m3)/(K*K))" << endl;
    cout << props.densityTT << endl;

    cout << "The second-order partial derivative of density with respect to temperature and pressure (in units of (kg/m3)/(K*Pa))" << endl;
    cout << props.densityTP << endl;

    cout << "The second-order partial derivative of density with respect to pressure (in units of (kg/m3)/(Pa*Pa))" << endl;
    cout << props.densityPP << endl;

    cout << "The pressure of water (in units of Pa)" << endl;
    cout << props.pressure << endl;

    cout << "The first-order partial derivative of pressure with respect to temperature (in units of Pa/K)" << endl;
    cout << props.pressureT << endl;

    cout << "The first-order partial derivative of pressure with respect to density (in units of Pa/(kg/m3))" << endl;
    cout << props.pressureD << endl;

    cout << "The second-order partial derivative of pressure with respect to temperature (in units of Pa/(K*K))" << endl;
    cout << props.pressureTT << endl;

    cout << "The second-order partial derivative of pressure with respect to temperature and density (in units of Pa/(K*kg/m3))" << endl;
    cout << props.pressureTD << endl;

    cout << "The second-order partial derivative of pressure with respect to density (in units of Pa/((kg/m3)*(kg/m3)))" << endl;
    cout << props.pressureDD << endl;

    cout << "The speed of sound (in m/s)" << endl;
    cout << props.speed_of_sound << endl;
}
~~~

## Installation

Installation of Fluidika using CMake is greatly simplified if [conda] is
available in your system. We recommend you to install a Python 3.x (64-bit)
installer of [Miniconda] to give you access to the `conda` application.

Once you have installed `conda`, append the [conda-forge] channel so that we
can have access to a rich collection of packages in addition to the default
channel:

~~~
conda config --append channels conda-forge
~~~

The next step is to install [conda-devenv] to create a conda development
environment containing *all required library dependencies* of Fluidika.

~~~
conda install conda-devenv
~~~

After this, you should execute:

~~~
conda activate fluidika
~~~

to activate the created conda environment.

It's now time to download Fluidika from GitHub:

~~~
git clone https://github.com/reaktoro/fluidika.git
~~~

and then start the build & install task by executing:

~~~
cmake -P install
~~~

This will install Fluidika header, library, and cmake configuration files in
your created conda environment, and not in your system. If you wish to install
Fluidika in a different location, use:

~~~
cmake -DPREFIX=/home/user/other -P install
~~~

## License

Copyright (C) 2018-2019 Allan Leal and Reaktoro Contributors

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library. If not, see <http://www.gnu.org/licenses/>.

## Contact us

Do you have a question or want to report a bug or any other issue? Please
create a [GitHub Issue] and let us know.


[GitHub Issue]: https://github.com/reaktoro/fluidika/issues/new

[Reaktoro Project]: https://github.com/reaktoro/reaktoro
[conda]: https://conda.io
[conda-forge]: https://conda-forge.org/
[Miniconda]: https://docs.conda.io/en/latest/miniconda.html
[conda-devenv]: https://conda-devenv.readthedocs.io/en/latest/
