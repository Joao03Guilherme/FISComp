# include <iostream>
# include "ODEpoint.hpp"
# include "ODEsolver.hpp"
# include "TGraph.h"
# include "TCanvas.h"
# include "TAxis.h"


using namespace std;

/*
Equation:

dy/dt = v
dv/dt = k/m * v - g
*/

const double g = 9.81;
const double k = 0.3; 
const double m = 80;

double dydt(ODEpoint p) {
    return p[1];
}

double dvdt(ODEpoint p) {
    return k / m * p[1] - g;
}

int main() {
    ODEpoint p0(0, {2000, 0});
    ODEsolver S({dydt, dvdt});

    double dt = 0.1, T = 2.0;
    S.RK4(p0, dt, T);

    vector<double> rk4x, rk4y, rk4z;

    for (auto p : S.GetODEpoints("RK4")) {
        rk4x.push_back(p.T());
        rk4y.push_back(p[0]);
        rk4z.push_back(p[1]);
    }

    TCanvas C("canvas", "canvas", 1000, 1000);
    TGraph g1(rk4x.size(), rk4x.data(), rk4y.data());
    TGraph g2(rk4x.size(), rk4x.data(), rk4z.data());

    g2.Draw("APL");
    g1.Draw("PL");

    C.SaveAs("4.6.5.png");
    return 0;
}