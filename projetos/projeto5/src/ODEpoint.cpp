# include "ODEpoint.hpp"

void ODEpoint::SetODEpoint(double t_, Xvar& p) {
    t = t_;
    X() = p.X();
}

void ODEpoint::SetODEpoint(double t_, const std::initializer_list<double>& v) {
    t = t_;
    X() = v;
}

void ODEpoint::SetODEpoint(double t_, std::vector<double> v) {
    t = t_;
    X() = v;
}
