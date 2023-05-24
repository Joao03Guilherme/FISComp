# include <iostream>
# include <bits/stdc++.h>
using namespace std;

double f(double x);
double z(double x);

int main() {
        vector<double> arr = {0.4, 2.1, 1.5};
        for (double x : arr) {
                cout << z(x) << endl;
        }
}

double f(double x) {
        return sin(x);
}

double z(double x) {
        return x + f(x);
}