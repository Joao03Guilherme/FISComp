# ifndef FCmatrixAlgo_hpp
# define FCmatrixAlgo_hpp

# include <Eigen/Core>     

using Eigen::Matrix;
using Eigen::Dynamic;

class FCmatrixAlgo
{
    public:
        FCmatrixAlgo() = default;
        ~FCmatrixAlgo() = default;

        /*
        Implements Gauss elimination
        */

        static void GaussElimination(
            Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
            Matrix<double, Dynamic, 1>& C // Matrix Constants
        ); // no pivoting 

        static void GaussEliminationPivot(
            Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
            Matrix<double, Dynamic, 1>& C, // Matrix Constants
            Matrix<double, Dynamic, 1>& P // Row order indexing
        ); // with pivoting
        
        /*
        Implements LU decomposition (Doolitle)
        */
        static void LUdecomposition(
              Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
              Matrix<double, Dynamic, 1>& P, // Row order indexing
              bool pivot = false // activate pivoting
        );
       
};

# endif