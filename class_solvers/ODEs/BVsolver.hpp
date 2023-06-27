#ifndef __BVSOLVER__
#define __BVSOLVER__ 
#include <functional>
#include "ODEpoint.h"

class BVSolver {
	/* Solve 2nd order linear Boundary Value problems*/
    public:
        BVSolver(const std::array<std::function<double(double)>,4>& f): F(f){}
        ~BVSolver() = default;

        // solver methods
        std::vector<ODEpoint> Solve(ODEpoint i, ODEpoint f, int numIntervals);

    private:
        std::array<std::function<double(double)>,4> F;
};

#endif 