# include "EqSolver.hpp"
# include "FCmatrixAlgo.hpp"
# include <iostream>

using namespace std;

EqSolver::EqSolver() {
    M = Matrix<double, Dynamic, Dynamic>();
    C = Matrix<double, Dynamic, 1>();
}

EqSolver::EqSolver(
    const Matrix<double, Dynamic, Dynamic>& _M, // Matrix Coefficients
    const Matrix<double, Dynamic, 1>& _C // Matrix Constants
) : M(_M), C(_C) {;}

EqSolver::EqSolver(
    const Matrix<double, Dynamic, Dynamic>& _M, // Matrix Coefficients
    const Matrix<double, Dynamic, 1>& _C, // Matrix Constants
    const Matrix<double, Dynamic, 1>& _P // Row order indexing
) : M(_M), C(_C), P(_P) {;}

void EqSolver::setM(const Matrix<double, Dynamic, Dynamic>& _M) {
    M = _M;
}

void EqSolver::setC(const Matrix<double, Dynamic, 1>& _C) {
    C = _C;
}

void EqSolver::setP(const Matrix<double, Dynamic, 1>& _P) {
    P = _P;
}

ostream& operator<<(ostream& os, const EqSolver& eq) {
    os << "Matrix Coefficients: " << endl << eq.M << endl;
    os << "Matrix Constants: " << endl << eq.C << endl;
    return os;
}

const Matrix<double, Dynamic, 1>& EqSolver::GaussSolver(bool pivot) {
    FCmatrixAlgo solver;
    if (pivot) {
        solver.GaussEliminationPivot(M, C, P);
    }
    else {
        solver.GaussElimination(M, C);
    }
    return C;
}

const Matrix<double, Dynamic, 1>& EqSolver::LUSolver(bool pivot) {
    FCmatrixAlgo solver;
    solver.LUdecomposition(M, P, pivot)
    // TODO: FALTA IMPLEMENTAR;
    return C;
}

void EqSolver::IterativeJacobiSolver(
    Matrix<double, Dynamic, 1>& X, // starting solution
    int& itmax, //nb of max iterations
    double tol) // tolerance on convergence
{
    FCmatrixAlgo solver;
    solver.IterativeJacobi(M, C, X, itmax, tol);
}

void EqSolver::IterativeGaussSeidelSolver(
    Matrix<double, Dynamic, 1>& X, // starting solution
    int& itmax, //nb of max iterations
    double tol) // tolerance on convergence
{
    FCmatrixAlgo solver;
    solver.IterativeGaussSeidel(M, C, X, itmax, tol);
}