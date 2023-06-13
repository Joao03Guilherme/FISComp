#ifndef __INTEGDERIV__
#define __INTEGDERIV__

#include "Functor.hpp"

class IntegDeriv {
    public:
        IntegDeriv(Functor& f);
        ~IntegDeriv() = default;

        // integration methods
        void integral_trapezoidal(double xi, double xf, int div, double& Integral, double& Error);
        void integral_simpson(double xi, double xf, int div, double& Integral, double& Error);

        // Derivation methods
        double second_derivative_three_point(double x, double h=0.01);
        double second_derivative_five_point(double x, double h=0.01);

        double fourth_derivative(double x, double h=0.01);

    private:
        Functor& F;
};

#endif