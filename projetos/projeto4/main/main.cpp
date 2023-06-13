# include "IntegDeriv.hpp"
# include "Functor.hpp"
# include "MyFunction.hpp"
# include "Rwalk1D.hpp"
# include "TCanvas.h"
# include <iostream>

using namespace std;


int main() {
    MyFunction f;
    cout << f(1) << endl;
    
    IntegDeriv I(f);
    cout << I.second_derivative_three_point(1) << endl;
    cout << I.second_derivative_five_point(1) << endl;

    double Integral, Error;
    I.integral_trapezoidal(1, 2, 100, Integral, Error);

    cout << Integral << endl;
    cout << Error << endl;

    double Integral2, Error2;
    I.integral_simpson(1, 2, 100, Integral2, Error2);

    cout << Integral2 << endl;
    cout << Error2 << endl;

    cout << I.fourth_derivative(1) << endl;

    Rwalk1D r(10, 0, 0.5, 0.5, 1, 1);
    r.Run(500);

    TMultiGraph* g = r.GetGraph();

    TCanvas* c = new TCanvas;
    c->cd();
    g->Draw("AL");
    c->SaveAs("teste.png");


   
    return 1;
}