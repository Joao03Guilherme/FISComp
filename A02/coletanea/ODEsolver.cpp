#include "ODEsolver.hpp"

ODEsolver::ODEsolver(const vector<function<double(ODEpoint)>>& F_) : F(F_){;}

void ODEsolver::SetODEfunc(const vector<function<double(ODEpoint)>>& F_) {
    F = F_;
}

const vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i); // create initial ODEpoint from whom we calculate the next
    while (V.back().T() < T){
        ODEpoint Pcur = V.back();
        V.push_back(Pcur+Func(Pcur)*step);
    }

    MS["euler"] = V;
    return MS["euler"];
}

const vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i); // create initial ODEpoint from whom we calculate the next
    while (V.back().T() < T){
        ODEpoint Pcur = V.back();
        ODEpoint Ppred = Pcur+Func(Pcur)*step;
        V.push_back(Pcur+(Func(Pcur)+Func(Ppred))*0.5*step);
    }

    MS["predictor-corrector"] = V;
    return MS["predictor-corrector"];
}

const vector<ODEpoint>& ODEsolver::LeapFrog(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i);
    int n = 0;
    ODEpoint P0 = V.back();
    ODEpoint P1 = P0+Func(P0)*step;
    V.push_back(P1);

    while (V.back().T() < T){
        ODEpoint Pprev = V[V.size()-2];
        ODEpoint Pcur = V.back();
        ODEpoint Pnext = Pprev+Func(Pcur)*2*step;
        V.push_back(Pnext);        
    }

    MS["leapfrog"] = V;

    return MS["leapfrog"];
}

const vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double T){
    vector<ODEpoint> V;
    V.push_back(i);
    while(V.back().T() < T){
        ODEpoint Pcur = V.back();
	ODEpoint K1 = Func(Pcur)*step;
	ODEpoint K2 = Func(Pcur+K1*0.5)*step;
        V.push_back(Pcur+K2);
    }
    MS["RK2"] = V;
    return MS["RK2"];
}

const vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double T){
    vector<ODEpoint> V;
    V.push_back(i);
    while(V.back().T() < T){
        ODEpoint Pcur = V.back();
	ODEpoint K1 = Func(Pcur)*step;
	ODEpoint K2 = Func(Pcur+K1*0.5)*step;
	ODEpoint K3 = Func(Pcur+K2*0.5)*step;
	ODEpoint K4 = Func(Pcur+K3)*step;
        V.push_back(Pcur+(K1+K2*2+K3*2+K4)*(1./6));
    }
    MS["RK4"] = V;
    return MS["RK4"];
}

ODEpoint ODEpoint::operator+(ODEpoint P){
	vector<double> var(x);
	for (int i = 0; i < var.size(); ++i) {
		var[i] += P[i];
	}
	return {time+P.time, var};
}

ODEpoint ODEpoint::operator*(double d){
	vector<double> var(x);
	for (int i = 0; i < var.size(); ++i) {
		var[i] *= d;
	}
	return {time*d, var};
}

ODEpoint ODEsolver::Func(ODEpoint P){
	ODEpoint P0(1, P.X());
	for (int i = 0; i < F.size(); ++i) {
		P0[i] = F[i](P);
	}
	return P0;
}