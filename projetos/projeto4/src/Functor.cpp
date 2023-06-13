# include "Functor.hpp"

using namespace std;

TCanvas* Functor::c = nullptr;

Functor::Functor(string s) : name(s) {;}

double Functor::operator()(double x) {
    return 0; // Default implementation
}

void Functor::Draw(double xi, double xf, int num, string xtitle, string ytitle) {
    if (c == nullptr) c = new TCanvas("c", "c", 800, 600);

    TGraph *g = new TGraph(num);
    g->SetTitle(name.c_str());
    g->GetXaxis()->SetTitle(xtitle.c_str());
    g->GetYaxis()->SetTitle(ytitle.c_str());
    double dx = (xf-xi)/(num-1);

    for (int i=0; i<num; i++) {
        double x = xi + i*dx;
        g->SetPoint(i, x, (*this)(x));
    }

    g->Draw("AL");
    c->Draw();
}
