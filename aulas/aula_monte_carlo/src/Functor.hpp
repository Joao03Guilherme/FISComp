# ifndef __FUNCTOR_HPP__
# define __FUNCTOR_HPP__

# include <string>
# include "TCanvas.h"

using namespace std;

class Functor {
    public:
        Functor(string name = "");
        virtual ~Functor();

        virtual double operator()(double x);
        virtual void Draw(int n_points, array<double, 2> range, array<string, 2> axis_labels);

    protected:
        string name;
        TCanvas *c = nullptr;
};

# endif