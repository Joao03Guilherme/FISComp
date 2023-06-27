#include "IntegDeriv.hpp"
#include <algorithm>
#include<iostream>

using namespace std;

IntegDeriv::IntegDeriv(Functor& F_) : F(F_) {}

void IntegDeriv::RombergRule(double xi, double xf, double& Integral, double& Error, int order){
	vector<vector<double>> I(order);
	double integ, err;
	for (int i = 0; i < order; ++i) {
		TrapezoidalRule(xi, xf, integ, err, 1000<<i);
		I[i].push_back(integ);
		for (int j = 1; j <= i; ++j) {
			I[i].push_back(I[i][j-1]+1./((4<<(2*(j-1)))-1)*(I[i][j-1]-I[i-1][j-1]));
		}
		for(auto& e : I[i]){
			std::cout << e <<" ";
		}std::cout << std::endl;
	}
	Integral = I.back().back();
}


void IntegDeriv::MidRule(double xi, double xf, double& Integral, double& Error){
    const int numPoints = 1000;  // Number of points for Simpson's rule
    double h = (xf - xi) / numPoints;  // Step size

    // Initialize variables
    double sum1 = 0.0;

    // Calculate the sums for Simpson's rule
    double x = xi + h/2;
    for (int i = 0; i < numPoints; i++) {
        sum1 += F(x);
	x += h;
    }


    // Calculate the integral and the error estimate
    Integral = sum1*h;
    Error = abs((h * h / 12.0) * (DF_fo(xi, h)-DF_bck(xf, h)));  // Error estimate using the derivative of the function :mean of f''

}

void IntegDeriv::simpsonRule(double xi, double xf, double& Integral, double& Error){
    const int numPoints = 1000;  // Number of points for Simpson's rule
    double h = (xf - xi) / numPoints;  // Step size

    // Initialize variables
    double sum1 = 0.0;
    double sum2 = 0.0;

    // Evaluate the function at the boundaries
    double f_xi = F(xi);
    double f_xf = F(xf);

    // Calculate the sums for Simpson's rule
    for (int i = 1; i < numPoints; i += 2) {
        double x = xi + i * h;
        sum1 += F(x);
    }

    for (int i = 2; i < numPoints; i += 2) {
        double x = xi + i * h;
        sum2 += F(x);
    }

    double mean_d4 = (D4F(xi, h) + D4F((xi+xf)/4., h) + D4F((xi+xf)/2., h) + D4F(3.*(xi+xf)/4., h) + D4F(xf, -h))/4.;

    // Calculate the integral and the error estimate
    Integral = (h / 3.0) * (f_xi + 4.0 * sum1 + 2.0 * sum2 + f_xf);
    Error = (xf - xi) * (h * h * h / 12.0) * mean_d4; // Error estimate using the mean of the 4th derivative of the function

}

void IntegDeriv::TrapezoidalRule(double xi, double xf, double& Integral, double& Error, int numPoints) {
    double h = (xf - xi) / numPoints;  // Step size

    // Initialize variables
    double sum = 0.0;
    double max_D2 = 0.0;

    // Evaluate the function at the boundaries
    double f_xi = F(xi);
    double f_xf = F(xf);

    // Calculate the sum for the trapezoidal rule
    for (int i = 1; i < numPoints; ++i) {
        double x = xi + i * h;
	double d2 = D2F_3point(x, h);
        sum += F(x);
	max_D2 = max_D2 > d2 ? max_D2 : d2;
    }

    // Calculate the integral and the error estimate
    Integral = (h / 2.0) * (f_xi + 2.0 * sum + f_xf);
    Error =  abs((xf-xi)*h*h*max_D2/12);	// Majorante do erro
    //Error = abs((h * h / 12.0) * (DF_fo(xi+h/2, h)-DF_bck(xf-h/2, h)));  // Error estimate using the derivative of the function :mean of f''

}

void IntegDeriv::MonteCarloRegion(double xi, double xf, double yi, double yf, function<bool(double, double)> region,
double& Integral, double& Error, int numPoints) {
    srand(time(NULL));
    uniform_real_distribution<double> unifx(xi, xf);
    uniform_real_distribution<double> unify(yi, yf);
    default_random_engine re;

    double area = (xf-xi) * (yf-yi);

    int NR = 0;
    for (int i = 0; i < numPoints; ++i) {
        double x = unifx(re);
        double y = unify(re);
        if (region(x,y)) NR++;
    }

    Integral = (double) NR / (double) numPoints * area;
    Error = area / numPoints * sqrt(NR * (1 - NR / numPoints));
}

// First derivatives:

// Forward difference
double IntegDeriv::DF_fo(double x0, double dx){
    return (F(x0+dx)-F(x0))/dx;
}

// Central difference
double IntegDeriv::DF_central(double x0, double dx){
    return (F(x0+dx)-F(x0-dx))/(2*dx);
}

// Backward difference
double IntegDeriv::DF_bck(double x0, double dx){
    return (F(x0)-F(x0-dx))/dx;
}

// Second derivatives:

// Three-point formula
double IntegDeriv::D2F_3point(double x0, double dx){
    return (F(x0+dx)-2*F(x0)+F(x0-dx))/(dx*dx);
}

// Five-point formula
double IntegDeriv::D2F_5point(double x0, double dx){
    return (-F(x0-2*dx)+16*F(x0-dx)-30*F(x0)+16*F(x0+dx)-F(x0+2*dx))/(12*dx*dx);
}

// Fourth Derivative
double IntegDeriv::D4F(double x0, double dx){
    return 12*(F(x0+dx)+F(x0-dx)-2*F(x0)-dx*dx*D2F_5point(x0, dx))/(dx*dx*dx*dx);
}
