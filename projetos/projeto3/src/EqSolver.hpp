# ifndef EqSolver_hpp
# define EqSolver_hpp

# include <Eigen/Dense>

using Eigen::Matrix;
using Eigen::Dynamic;
using std::ostream;

class EqSolver {
    public:
        EqSolver();

        EqSolver(
            const Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
            const Matrix<double, Dynamic, 1>& C // Matrix Constants
        );

        EqSolver(
            const Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
            const Matrix<double, Dynamic, 1>& C, // Matrix Constants
            const Matrix<double, Dynamic, 1>& P // Row order indexing
        );

        ~EqSolver() = default;

        void setM(const Matrix<double, Dynamic, Dynamic>& M);
        void setC(const Matrix<double, Dynamic, 1>& C);
        void setP(const Matrix<double, Dynamic, 1>& P);

        friend ostream& operator<<(ostream&, const EqSolver&); // Output stream

        // solvers
        const Matrix<double, Dynamic, 1>& GaussSolver(bool pivot=false); // Gauss elimination
        const Matrix<double, Dynamic, 1>& LUSolver(bool pivot=false); // LU decomposition

        void IterativeJacobiSolver(
            Matrix<double, Dynamic, 1>&, // starting solution
            int& itmax, //nb of max iterations
            double tol=1.E-3); // tolerance on convergence

        void IterativeGaussSeidelSolver(
            Matrix<double, Dynamic, 1>&, // starting solution
            int& itmax, //nb of max iterations
            double tol=1.E-3); // tolerance on convergence

    private:
        Matrix<double, Dynamic, Dynamic> M; // Matrix Coefficients
        Matrix<double, Dynamic, 1> C; // Matrix Constants
        Matrix<double, Dynamic, 1> P; // Row order indexing
};

# endif 