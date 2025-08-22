#ifndef TRAPEZOIDAL_INTEGRATION_HPP
#define TRAPEZOIDAL_INTEGRATION_HPP

#include <functional>
#include <cmath>

namespace numerical {

/**
 * Trapezoidal integration method
 * @param f Function to integrate
 * @param a Lower bound of integration
 * @param b Upper bound of integration
 * @param n Number of subintervals (default: 1000)
 * @return Approximation of the definite integral
 */
template<typename Function>
double trapezoidal_integrate(Function f, double a, double b, int n = 1000) {
    if (n <= 0) {
        throw std::invalid_argument("Number of subintervals must be positive");
    }
    
    if (a == b) {
        return 0.0;
    }
    
    // Handle case where a > b by swapping and negating result
    if (a > b) {
        return -trapezoidal_integrate(f, b, a, n);
    }
    
    double h = (b - a) / n;  // Step size
    double sum = 0.5 * (f(a) + f(b));  // First and last terms with 1/2 coefficient
    
    // Sum the middle terms
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return h * sum;
}

/**
 * Adaptive trapezoidal integration with error estimation
 * @param f Function to integrate
 * @param a Lower bound of integration
 * @param b Upper bound of integration
 * @param tolerance Desired accuracy (default: 1e-6)
 * @param max_iterations Maximum number of refinements (default: 20)
 * @return Approximation of the definite integral
 */
template<typename Function>
double adaptive_trapezoidal_integrate(Function f, double a, double b, 
                                    double tolerance = 1e-6, int max_iterations = 20) {
    if (a == b) {
        return 0.0;
    }
    
    // Handle case where a > b
    if (a > b) {
        return -adaptive_trapezoidal_integrate(f, b, a, tolerance, max_iterations);
    }
    
    int n = 1;
    double old_result = 0.5 * (b - a) * (f(a) + f(b));  // n=1 case
    
    for (int iter = 1; iter <= max_iterations; ++iter) {
        n *= 2;  // Double the number of subintervals
        double new_result = trapezoidal_integrate(f, a, b, n);
        
        // Check convergence using Richardson extrapolation error estimate
        double error_estimate = std::abs(new_result - old_result) / 3.0;
        
        if (error_estimate < tolerance && iter > 1) {
            return new_result;
        }
        
        old_result = new_result;
    }
    
    // If we didn't converge, return the last result
    return old_result;
}

} // namespace numerical

#endif // TRAPEZOIDAL_INTEGRATION_HPP
