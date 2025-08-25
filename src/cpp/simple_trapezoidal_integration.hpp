#ifndef SIMPLE_TRAPEZOIDAL_INTEGRATION_HPP
#define SIMPLE_TRAPEZOIDAL_INTEGRATION_HPP

template<typename Function>
double simple_trapezoidal_integrate(Function f, double a, double b, int n = 1000) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; ++i) {
        sum += f(a + i * h);
    }
    
    return h * sum;
}

#endif
