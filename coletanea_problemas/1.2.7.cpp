# include <bits/stdc++.h>
using namespace std;

double Trace(int** mx, int n);
int* Mrow(int i, int** mx, int m, int n);
int** RowMultiplication(int** mx1, int** v, int n, int m);
int** Create_Matrix(int n, int m);
void Print_Matrix(int** mx, int n, int m);


int main() {
    int n, m;
    cin >> n >> m;

    int** mx = Create_Matrix(n, m);
    int** v = Create_Matrix(m, 1);

    int** ans = RowMultiplication(mx, v, n, m);
    Print_Matrix(ans, n, 1);

    return 0;
}

void Print_Matrix(int** mx, int n, int m) {
    // Print matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cout << mx[i][j] << " ";
        }
        cout << endl;
    }
}

int** Create_Matrix(int n, int m) {
    // Create n * m matrix
    int** mx = new int*[n];
    for (int i = 0; i < n; i++) {
        mx[i] = new int[m];
    }

    // Read matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cin >> mx[i][j];
        }
    }
    
    return mx;
}

double Trace(int** mx, int n) {
    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        ans += mx[i][i];
    }
    return ans;
}

int* Mrow(int i, int** mx, int m, int n) {
    int* row = new int[n];
    for (int j = 0; j < n; j++) {
        row[j] = mx[i][j];
    }
    return row;
}

int** RowMultiplication(int** mx1, int** v, int n, int m) {
    int** ans = new int*[m];
    for (int i = 0; i < m; i++) {
        ans[i] = new int[1];
    }

    for (int i = 0; i < n; i++) {
        ans[i][0] = 0;
        for (int j = 0; j < m; j++) {
            ans[i][0] += mx1[i][j] * v[j][0];
        }
        
    }
    return ans;
}
