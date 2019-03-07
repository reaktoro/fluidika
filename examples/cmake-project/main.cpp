#include <iostream>
using namespace std;

#include <Fluidika/Fluidika.hpp>
using namespace Fluidika;

int main()
{
    auto props = waterThermoPropsWagnerPruss(300.0, 1.0e6);

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
