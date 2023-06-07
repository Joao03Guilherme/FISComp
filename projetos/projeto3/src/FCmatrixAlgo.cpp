# include "FCmatrixAlgo.hpp"

void FCmatrixAlgo::GaussElimination(
    Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
    Matrix<double, Dynamic, 1>& C // Matrix Constants
)
{
    // Get matrix size
    int n = M.rows();

    // Forward elimination
    for (int k = 0; k < n - 1; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            double factor = M(i, k) / M(k, k);
            for (int j = k + 1; j < n; j++)
            {
                M(i, j) -= factor * M(k, j);
            }
            C(i) -= factor * C(k);
        }
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            C(i) -= M(i, j) * C(j);
        }
        C(i) /= M(i, i);
    }
}

void FCmatrixAlgo::GaussEliminationPivot(
    Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
    Matrix<double, Dynamic, 1>& C, // Matrix Constants
    Matrix<double, Dynamic, 1>& P // Row order indexing
)
{
    // Get matrix size
    int n = M.rows();

    // Forward elimination
    for (int k = 0; k < n - 1; k++)
    {
        // Pivoting
        int p = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(M(i, k)) > abs(M(p, k)))
            {
                p = i;
            }
        }
        if (p != k)
        {
            for (int j = k; j < n; j++)
            {
                double temp = M(p, j);
                M(p, j) = M(k, j);
                M(k, j) = temp;
            }
            double temp = C(p);
            C(p) = C(k);
            C(k) = temp;
            temp = P(p);
            P(p) = P(k);
            P(k) = temp;
        }

        // Elimination
        for (int i = k + 1; i < n; i++)
        {
            double factor = M(i, k) / M(k, k);
            for (int j = k + 1; j < n; j++)
            {
                M(i, j) -= factor * M(k, j);
            }
            C(i) -= factor * C(k);
        }
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            C(i) -= M(i, j) * C(j);
        }
        C(i) /= M(i, i);
    }
}

// Implement doolitle LU decomposition solver
void FCmatrixAlgo::LUdecomposition(
    Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
    Matrix<double, Dynamic, 1>& P, // Row order indexing
    bool pivot // activate pivoting
)
{
    // Get matrix size
    int n = M.rows();

    // Forward elimination
    for (int k = 0; k < n - 1; k++)
    {
        if (pivot)
        {
            // Pivoting
            int p = k;
            for (int i = k + 1; i < n; i++)
            {
                if (abs(M(i, k)) > abs(M(p, k)))
                {
                    p = i;
                }
            }
            if (p != k)
            {
                for (int j = k; j < n; j++)
                {
                    double temp = M(p, j);
                    M(p, j) = M(k, j);
                    M(k, j) = temp;
                }
                double temp = P(p);
                P(p) = P(k);
                P(k) = temp;
            }
        }

        // Elimination
        for (int i = k + 1; i < n; i++)
        {
            double factor = M(i, k) / M(k, k);
            M(i, k) = factor;
            for (int j = k + 1; j < n; j++)
            {
                M(i, j) -= factor * M(k, j);
            }
        }
    }
}

void FCmatrixAlgo::IterativeJacobi(
    Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
    Matrix<double, Dynamic, 1>& C, // Matrix Constants
    Matrix<double, Dynamic, 1>& X, // starting solution
    int& itmax, //nb of max iterations
    double tol // tolerance on convergence
)
{
    // Get matrix size
    int n = M.rows();

    // Initialize solution
    Matrix<double, Dynamic, 1> Xnew(n);

    // Iterative solver
    for (int it = 0; it < itmax; it++)
    {
        // Compute new solution
        for (int i = 0; i < n; i++)
        {
            Xnew(i) = C(i);
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    Xnew(i) -= M(i, j) * X(j); // X is the old solution
                }
            }
            Xnew(i) /= M(i, i);
        }

        // Check convergence
        double error = 0;
        for (int i = 0; i < n; i++)
        {
            error += abs(Xnew(i) - X(i));
        }
        if (error < tol)
        {
            X = Xnew;
            return;
        }

        // Update solution
        X = Xnew;
    }
}

void FCmatrixAlgo::IterativeGaussSeidel(
    Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
    Matrix<double, Dynamic, 1>& C, // Matrix Constants
    Matrix<double, Dynamic, 1>& X, // starting solution
    int& itmax, //nb of max iterations
    double tol // tolerance on convergence
)
{
    // Get matrix size
    int n = M.rows();

    // Initialize solution
    Matrix<double, Dynamic, 1> Xnew(n);

    // Iterative solver
    for (int it = 0; it < itmax; it++)
    {
        // Compute new solution
        for (int i = 0; i < n; i++)
        {
            Xnew(i) = C(i);
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    Xnew(i) -= M(i, j) * Xnew(j); // Xnew is the new solution
                }
            }
            Xnew(i) /= M(i, i);
        }

        // Check convergence
        double error = 0;
        for (int i = 0; i < n; i++)
        {
            error += abs(Xnew(i) - X(i));
        }
        if (error < tol)
        {
            X = Xnew;
            return;
        }

        // Update solution
        X = Xnew;
    }
}