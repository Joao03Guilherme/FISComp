#ifndef __INTEGDERIV__
#define __INTEGDERIV__
# include "Functor.hpp"
# include <vector>
# include <random>
# include <functional>

class IntegDeriv {
    public:
        IntegDeriv(Functor&);
        ~IntegDeriv() = default;

        // integration methods
	    void MidRule(double xi, double xf, double& Integral, double&
        Error);

        void TrapezoidalRule(double xi, double xf, double& Integral, double&
        Error, int numPoints = 1000);

        void simpsonRule(double xi, double xf, double& Integral, double&
        Error);

	    void RombergRule(double xi, double xf, double& Integral, double&
        Error, int order=2);

        void MonteCarloRegion(double xi, double xf, double yi, double yf, std::function<bool(double, double)> region,
        double& Integral, double& Error, int numPoints = 1000);

        // derivative methods
        double DF_fo(double x0, double dx); // point where we are differentiating, step
        double DF_central(double x0, double dx);
        double DF_bck(double x0, double dx);
        double D2F_3point(double x0, double dx = 3e-4); // for the second derivatives, dx must be ~3e-4
        double D2F_5point(double x0, double dx = 3e-4);
        double D4F(double x0, double dx = 8e-3); // dx ~ 8e-3

    private:
        Functor& F;
};

#endif