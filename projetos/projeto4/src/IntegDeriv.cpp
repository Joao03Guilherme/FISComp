# include "IntegDeriv.hpp"

IntegDeriv::IntegDeriv(Functor& f) : F(f) {;}

void IntegDeriv::integral_trapezoidal(double xi, double xf, int div, double& Integral, double& Error) {
    Integral = 0;
    Error = 0;
    double dx = (xf - xi) / div;
    double sum = 0.0;

    for (int i = 1; i < div; i++) {
        double x0 = xi + i * dx;
        double x1 = xi + (i + 1) * dx;

        Error += -pow(dx, 3) / 12 * second_derivative_five_point(x0 + dx/2, dx/2);
    }

    Integral = dx / 2 * (F(xi) + 2 * sum + F(xf));
}

void IntegDeriv::integral_simpson(double xi, double xf, int div, double& Integral, double& Error) {
    if (div % 2 != 0) div++;
    double dx = (xf - xi) / div;

    Integral = 0;
    Error = (xf - xi) * pow(dx, 4) / 180 * fourth_derivative((xi + xf) / 2, dx); // Deve estar errado

    for (int i = 1; i < div; i += 2) {
        double x0 = xi + (i - 1) * dx;
        double x1 = xi + i * dx;
        double x2 = xi + (i + 1) * dx;

        Integral += dx / 3 * (F(x0) + 4 * F(x1) + F(x2));
    }
}

double IntegDeriv::second_derivative_three_point(double x, double h) {
    return (F(x + h) - 2 * F(x) + F(x - h)) / (h * h);
}

double IntegDeriv::second_derivative_five_point(double x, double h) {
    return (-F(x - 2 * h) + 16 * F(x - h) - 30 * F(x) + 16 * F(x + h) - F(x + 2 * h)) / (12 * (h * h));
}

double IntegDeriv::fourth_derivative(double x, double h) { // Three point
    return (second_derivative_five_point(x + h, h) - 2 * second_derivative_five_point(x, h) + second_derivative_five_point(x - h, h)) / (h * h);
}

