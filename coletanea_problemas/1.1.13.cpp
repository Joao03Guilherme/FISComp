# include <bits/stdc++.h>
using namespace std;

const double G = 6.67e-11;
const double M = 5.97e24;
const double R = 6.371e6;

int main() {
    cout << sizeof(double);
    return 0;
}

double altitude(double T) {
    return pow(G * M * pow(T, 2) / (4 * pow(M_PI, 2)), 1.0 / 3) - R;
}