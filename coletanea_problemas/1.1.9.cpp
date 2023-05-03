# include <bits/stdc++.h>
using namespace std;

double Sum(int* vi, int* vj);

int main() {
    int vi = 100, vj = 300;
    double ans = Sum(&vi, &vj);
    cout << ans << endl;
    return 0;
}

double Sum(int* vi, int* vj) {
    double ans = 0.0;
    for (int i = 0; i <= *vi; i++) {
        for (int j = 5; j <= *vj; j++) {
            ans += cos(pow(i, 2) + sqrt(j));
        }
    }
    return ans;
}