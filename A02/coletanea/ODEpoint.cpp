#include "ODEpoint.hpp"
#include <iostream>
#include <vector>

// ODEpoint methods

ODEpoint::ODEpoint(){ time = -1;}

std::ostream& operator << (std::ostream& s, const ODEpoint& P){
    s << "[t = " << P.time << ", (";
    for (int i =0; i<P.x.size()-1; i++){
        s << P.x[i] << ", ";
    }
    s << P.x.back() << ")]";
    return s;
}

void ODEpoint::SetODEpoint(double t_, std::vector<double> v){
    time = t_;
    x = v;
}