# include <bits/stdc++.h>
using namespace std;
 
int main() {
    float fpi = 4 * atan(1);
    double dpi = 4 * atan(1);

    // Determina a precisao de fpi e dpi
    cout.precision(20);
    cout << fixed;

    cout << fpi  - M_PI << endl;
    cout << dpi  - M_PI << endl;
}