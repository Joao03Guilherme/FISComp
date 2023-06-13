#ifndef __MYFUNCTION__
#define __MYFUNCTION__

# include <cmath>
# include "Functor.hpp"

class MyFunction : public Functor {
    public:
        MyFunction(std::string s="MyFunction") : Functor(s) {;}
        ~MyFunction() = default;
        double operator()(double x) {
            return pow(x, 4) * log(x + sqrt(1 + pow(x, 2))); // Function given in the pdf
        }
};

#endif