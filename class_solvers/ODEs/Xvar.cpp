# include "Xvar.hpp"
using namespace std;


Xvar::Xvar(int n) {
    x.resize(n);
}

Xvar::Xvar(vector<double> v) : x(v) {;}

Xvar::Xvar(const initializer_list<double>& v) : x(v) {;}

Xvar::Xvar(const Xvar& v) : x(v.x) {;} // copy constructor

Xvar& Xvar::operator=(const Xvar& v) { // assignment operator
    x = v.x;
    return *this;
}

Xvar Xvar::operator+(const Xvar& v) { // operator+
    Xvar w(x.size());
    for (int i = 0; i < x.size(); i++) {
        w[i] = x[i] + v.x[i];
    }
    return w;
}

double& Xvar::operator[](int i) { // X[i]
    return x[i];
}

Xvar operator*(double a, const Xvar& v) { // scalar*X
    Xvar w(v.x.size());
    for (int i = 0; i < v.x.size(); i++) {
        w[i] = a*v.x[i];
    }
    return w;
}

ostream& operator<< (ostream& os, const Xvar& v) {
    for (int i = 0; i < v.x.size(); i++) {
        os << v.x[i] << " ";
    }
    return os;
}

vector<double>& Xvar::X() { // accessor to x
    return x;
}
