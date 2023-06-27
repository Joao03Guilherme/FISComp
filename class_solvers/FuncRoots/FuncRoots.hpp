# ifndef __FUNCROOTS__
# define __FUNCROOTS__

class FuncRoots {
    public:
        FuncRoots() = default;
        virtual ~FuncRoots() = default;

        virtual double operator()(double x) = 0;
        virtual double Derivative(double x, double h=0.01) = 0;
        virtual double SecondDerivative(double x, double h=0.01) = 0;
};