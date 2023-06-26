#include "ODEpoint.hpp"
#include "ODEsolver.hpp"
#include "Xvar.hpp"
#include <iostream>
#include <cmath>
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TAxis.h"

using namespace std;

const double g = 9.8;
const double l = 10;
const double k = 0.2;

/*
DIFFERENTIAL EQUATION

dy^2/dt^2 = -g

dy/dt = v
dv/dt = -g

*/

double dydt(ODEpoint p) {
    return p[1];
}

double dvdt(ODEpoint p) {
    return -g;
}

int main() {
    ODEsolver s;
    s.SetODEfunc({dydt, dvdt});

    double dt = 0.01;
    ODEpoint i(0, {200, 150});
    s.Euler(i, dt, 50);
    s.PredictorCorrector(i, dt, 50);
    s.RK2(i, dt, 50);
    s.RK4(i, dt, 50);
    
    array<vector<double>, 4> v;
    vector<double> t;

    for (auto p : s.GetODEpoints("euler")) {
        v[0].push_back(p[0]);
        t.push_back(p.T());
    }

    for (auto p : s.GetODEpoints("predictor-corrector")) {
        v[1].push_back(p[0]);
    }

    for (auto p : s.GetODEpoints("RK2")) {
        v[2].push_back(p[0]);
    }

    for (auto p : s.GetODEpoints("RK4")) {
        v[3].push_back(p[0]);
    }

    TMultiGraph *mg = new TMultiGraph();
    TCanvas *c = new TCanvas("c", "c", 1000, 1000);

    TGraph *geuler = new TGraph(t.size(), &t[0], &v[0][0]);
    geuler->SetLineColor(kRed);
    mg->Add(geuler);

    TGraph *gpc = new TGraph(t.size(), &t[0], &v[1][0]);
    gpc->SetLineColor(kBlue);
    mg->Add(gpc);

    TGraph *grk2 = new TGraph(t.size(), &t[0], &v[2][0]);
    grk2->SetLineColor(kGreen);
    mg->Add(grk2);

    TGraph *grk4 = new TGraph(t.size(), &t[0], &v[3][0]);
    grk4->SetLineColor(kBlack);
    mg->Add(grk4);


    mg->SetTitle("Euler vs Predictor-Corrector vs RK2 vs RK4");
    mg->GetXaxis()->SetTitle("t");
    mg->GetYaxis()->SetTitle("y");
    mg->Draw("AL");

    TLegend *legend = new TLegend(0.9, 0.8, 0.7, 0.9);
    legend->AddEntry(geuler, "Euler", "l");
    legend->AddEntry(gpc, "Predictor-Corrector", "l");
    legend->AddEntry(grk2, "RK2", "l");
    legend->AddEntry(grk4, "RK4", "l");
    legend->Draw();


    c->SaveAs("graph.png");
    return 0;
}
