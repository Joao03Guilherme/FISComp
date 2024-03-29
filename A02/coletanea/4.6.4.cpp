# include <iostream>
# include "ODEpoint.hpp"
# include "ODEsolver.hpp"
# include "TGraph.h"
# include "TCanvas.h"
# include "TAxis.h"


using namespace std;

double dzdx(ODEpoint p) {
    return sin(p.T()) + p[0];
}

double dydx(ODEpoint p) {
    return cos(p.T()) - p[1];
}

int main() {
    ODEpoint p0(0, {0, 0});
    ODEsolver S({dydx, dzdx});

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

    C.SaveAs("4.6.4.png");
    return 0;
}