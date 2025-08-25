// #include <boost/math/quadrature/gauss_kronrod.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "simple_trapezoidal_integration.hpp"
// #include "trapezoidal_integration.hpp"

const double g = -9.81;  // This varies for altitude but will be assumed constant here.

class Atmosphere {
private:
    double R;    // specific gas constant for dry air (default units: [J/(kg*K)])
    double h0;   // geopotential altitude at sea level (boundary condition)
    double P0;   // pressure at sea level (boundary condition)

public:
    // Constructor with default parameters
    Atmosphere(double h0 = -1524, double P0 = 101325, double R = 287.052874)
        : R(R), h0(h0), P0(P0) {}

    // Temperature function
    double T(double h) const {
        return 2.7e-17 * std::pow(h, 4) -
               6.074933e-12 * std::pow(h, 3) +
               4.22889669793e-7 * std::pow(h, 2) -
               9.918936624872612e-3 * h +
               2.89661267963331567898e+2;
    }

    // Pressure function
    double P(double h) const {
        auto integrand = [this](double x) { return 1.0 / T(x); };
        // double integral = boost::math::quadrature::gauss_kronrod<double, 15>::integrate(
        double integral = numerical::simple_trapezoidal_integrate(
        // double integral = numerical::adaptive_trapezoidal_integrate(
            integrand, h0, h, 5, 1e-9);
        return P0 * std::exp((g / R) * integral);
    }

    // Density function
    double ρ(double h) const {
        return P(h) / (R * T(h));
    }

    // Drag force function
    std::vector<double> drag_force(double Cd, double A, double vh, double vx, double vy, double h, double x = 0, double y = 0) const {
        std::vector<double> velocities = {vx, vy, vh};
        std::vector<double> result(3);
        double density = ρ(h);
        for (size_t i = 0; i < 3; ++i) {
            result[i] = 0.5 * density * std::pow(velocities[i], 2) * Cd * A;
        }
        return result;
    }
};

int main() {
    Atmosphere atm_model;
    auto T = [&atm_model](double h) { return atm_model.T(h); };
    auto P = [&atm_model](double h) { return atm_model.P(h); };
    auto ρ = [&atm_model](double h) { return atm_model.ρ(h); };

    double hmax = 76200;
    double h = 10000;

    std::cout << "For h = " << h << ", T = " << T(h) << ", P = " << P(h) << ", ρ = " << ρ(h) << ".\n\n";

    double z = h;
    double m = 100;
    std::vector<double> Fd = atm_model

.drag_force(1.0, 100.0, 20.0, 100.0, 3000.0, z);
    double norm_Fd = std::sqrt(Fd[0] * Fd[0] + Fd[1] * Fd[1] + Fd[2] * Fd[2]);
    std::cout << "The drag force at altitude " << z << " is [" << Fd[0] << ", " << Fd[1] << ", " << Fd[2]
              << "] and so with a mass of " << m << " its acceleration is " << norm_Fd / m << ".\n";

    return 0;
}
