# include "Functor.hpp"

Functor::Functor(string _name) : name(_name) {
    if (!c) c = new TCanvas("c", "c", 800, 600);
}

Functor::~Functor() {
    if (c) delete c;
}

Functor::operator()(double x) {
    return 0;
}

void Functor::Draw(int n_points, array<double, 2> range, array<string, 2> axis_labels) {
    return;
}