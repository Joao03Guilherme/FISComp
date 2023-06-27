#include"BVSolver.hpp"
#include"EqSolver.hpp" // Import the EqSolver class 

using namespace std;

vector<ODEpoint> BVSolver::Solve(ODEpoint pi, ODEpoint pf, int numIntervals){
	MCoef M(MCoef::Zero(numIntervals+1, numIntervals+1)); 
	MConst B(numIntervals+1); 
	MConst y(MConst::Ones(numIntervals+1)); 

	double h = (pf.T()-pi.T())/numIntervals;

	M(0,0) = 1;
	M(numIntervals,numIntervals) = 1;
	B(0) = pi[0];
	B(numIntervals) = pf[0];

	for (int i = 1; i < numIntervals; ++i) {
		double t = pi.T()+i*h;
		double a = F[0](t);
		double b = F[1](t);
		double c = F[2](t);
		M(i, i-1) = (a/(h*h)-b/(2*h));
		M(i, i) = (c-2*a/(h*h));
		M(i, i+1) = (a/(h*h)+b/(2*h));
		B(i) = F[3](t); 
	}

	EqSolver S(M, B);
	y = S.GaussSolver(false);
	vector<ODEpoint> ret;
	for (int i = 0; i < numIntervals+1; ++i) {
		ret.push_back(ODEpoint{pi.T()+i*h, {y(i)}});
	}

	return ret;
}