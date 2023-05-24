# include <bits/stdc++.h>
using namespace std;

double square_multiplication(double x);
double square_recursive(double x);

int main() {
    vector<double> arr = {0.4, 2.1, 1.5};
    for (double x : arr) {
        cout << square_multiplication(x) -  - square_recursive(x)  << endl;
    }
}

double square_multiplication(double x) {
    return x * x;
}

double square_recursive(double x) {
    if (x == 0) {
        return 0;
    }
    return square_recursive(x - 1) + x + x - 1;
}