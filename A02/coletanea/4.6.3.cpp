# include <iostream>
# include "ODEpoint.hpp"
# include "ODEsolver.hpp"
# include "TGraph.h"
# include "TCanvas.h"
# include "TAxis.h"

using namespace std;

double dydx(ODEpoint p) {
    return 3 * p[0] - p[1] + 8;
}

int main() {
    ODEpoint p0(0, {3});
    ODEsolver S({dydx});

    double dt = 0.01, T = 2.0;

    S.Euler(p0, dt, T);
    S.PredictorCorrector(p0, dt, T);
    S.RK2(p0, dt, T);
    S.RK4(p0, dt, T);

    vector<double> euler_x, euler_y;
    vector<double> predictor_x, predictor_y;
    vector<double> rk2_x, rk2_y;
    vector<double> rk4_x, rk4_y;

    for (auto p : S.GetODEpoints("euler")) {
        euler_x.push_back(p.T());
        euler_y.push_back(p[0]);
    }

    for (auto p : S.GetODEpoints("predictor-corrector")) {
        predictor_x.push_back(p.T());
        predictor_y.push_back(p[0]);
    }

    for (auto p : S.GetODEpoints("RK2")) {
        rk2_x.push_back(p.T());
        rk2_y.push_back(p[0]);
    }

    for (auto p : S.GetODEpoints("RK4")) {
        rk4_x.push_back(p.T());
        rk4_y.push_back(p[0]);
    }

    TCanvas C("canvas", "canvas", 800, 800);
    TGraph geuler(euler_x.size(), euler_x.data(), euler_y.data());
    TGraph gpredictor(predictor_x.size(), predictor_x.data(), predictor_y.data());
    TGraph grk2(rk2_x.size(), rk2_x.data(), rk2_y.data());
    TGraph grk4(rk4_x.size(), rk4_x.data(), rk4_y.data());

    geuler.SetLineColor(kRed);
    gpredictor.SetLineColor(kBlue);
    grk2.SetLineColor(kGreen);
    grk4.SetLineColor(kBlack);

    geuler.Draw("APL");
    gpredictor.Draw("PL");
    grk2.Draw("PL");
    grk4.Draw("PL");

    C.SaveAs("4.6.3.png");
    return 0;
}