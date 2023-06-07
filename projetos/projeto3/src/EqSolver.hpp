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

        ~EqSolver() = default;

        friend ostream& operator<<(ostream&, const EqSolver&); // Output stream

        // solvers
        const Matrix<double, Dynamic, 1>& GaussSolver(bool pivot=false);
        const Matrix<double, Dynamic, 1>& LUSolver(bool pivot=false);

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
};

# endif 