# include "Functor.hpp"
# include <iostream>

using namespace std;

Functor::Functor(string _name) {
    name = _name;
    if (!c) c = new TCanvas(name.c_str(), name.c_str(), 800, 600);
}

Functor::~Functor() {
    if (c) delete c;
}

double Functor::operator()(double x) {
    return 0;
}

void Functor::Draw(int n_points, array<double, 2> range, array<string, 2> axis_labels) {
    ;
}