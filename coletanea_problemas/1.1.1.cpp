#include <iostream>
using namespace std;
int main() {
        int n, m;
        cout << "Enter integers: " << flush;
        cin >> n >> m ;
        if (n>m) { //swap
                int buf = m;
                m = n;
                n = buf;
        }
        cout << "This program adds all integers between " << n << " and " << m
        << endl;
        double sum = 0.;
        for (int i=n; i<=m; i++) {
                sum += i;
        }
        cout << "Result = " << sum << endl;
}