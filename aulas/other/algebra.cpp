#include<iostream>
#include<algorithm>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;

int main(){
    MatrixXd M1(10,4);
    M1.setRandom();
    cout << M1 << "\n\n\n";

    MatrixXd M2 = MatrixXd::Random(10,4);

    cout << M2 << "\n\n\n";
    MatrixXd M3 = (2.5*M2.array()+7.5).matrix();
    cout << M3 << "\n\n\n";
}