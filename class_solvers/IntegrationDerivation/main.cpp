# include "IntegDeriv.hpp"
# include "MyFunction.hpp"
# include <iostream>

using namespace std;

int main() {
    MyFunction F;
    IntegDeriv I(F);

    double xi = 0.0;
    double xf = 1.0;
    double Integral, Error;

    I.MidRule(xi, xf, Integral, Error);
    cout << "Midpoint rule: " << Integral << " +/- " << Error << endl;

    I.TrapezoidalRule(xi, xf, Integral, Error);
    cout << "Trapezoidal rule: " << Integral << " +/- " << Error << endl;

    I.simpsonRule(xi, xf, Integral, Error);
    cout << "Simpson's rule: " << Integral << " +/- " << Error << endl;

    I.RombergRule(xi, xf, Integral, Error);
    cout << "Romberg rule: " << Integral << " +/- " << Error << endl;

    cout << "Monte Carlo: " << endl;
    I.MonteCarloRegion(xi, xf, 0.0, 1.0, [](double x, double y){return x*x+y*y<1;}, Integral, Error);
    cout << "Integral: " << Integral << " +/- " << Error << endl;

    return 0;
}