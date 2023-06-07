# include "EqSolver.hpp"
# include "FCmatrixAlgo.hpp"
# include <Eigen/Dense>
# include <iostream>

using namespace std;
using namespace Eigen;

int main() {
    double R1 = 30;
    double R2 = 50;
    double R3 = 5;
    double R4 = 10;
    double R5 = 15;
    double R6 = 20;
    double R7 = 25;
    double R8 = 55;
    double V0 = 20;

    
    Matrix<double, Dynamic, Dynamic> M; M.resize(4, 4);
    M << R1+R4+R6, -R4, -R6, 0,
        -R4, R2+R4+R5, -R5, 0,
        -R6, -R5, R5+R6+R7+R8, -R8,
        0, 0, -R8, R3+R8;

    Matrix<double, Dynamic, 1> C; C.resize(4, 1);
    C << V0, 0, 0, 0;

    Matrix<double, Dynamic, 1> P; P.resize(4, 1);
    P << 0, 1, 2, 3;

    EqSolver eqSolver(M, C);
    cout << eqSolver << endl;

    cout << "Gauss solver" << endl;
    cout << eqSolver.GaussSolver() << endl;

    eqSolver.setM(M);
    eqSolver.setC(C);
    cout << "LU solver" << endl;
    cout << eqSolver.LUSolver() << endl;

    eqSolver.setM(M);
    eqSolver.setC(C);
    cout << "Iterative Jacobi solver" << endl;
    Matrix<double, Dynamic, 1> X; X.resize(4, 1);
    X << 0, 0, 0, 0;
    int itmax = 100;
    double tol = 1.E-3;
    eqSolver.IterativeJacobiSolver(X, itmax, tol);
    cout << X << endl;

    cout << "Iterative Gauss-Seidel solver" << endl;
    X << 0, 0, 0, 0;
    eqSolver.IterativeGaussSeidelSolver(X, itmax, tol);
    cout << X << endl;

}