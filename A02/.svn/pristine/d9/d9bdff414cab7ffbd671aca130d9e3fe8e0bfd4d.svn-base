# include "ODEsolver.hpp"
using namespace std;

void ODEsolver::SetODEfunc(const vector<std::function<double(ODEpoint)>>& F_) {
    F = F_;
}

const vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double T) { // Initial point, step size, final time
    vector<ODEpoint> v;
    v.push_back(i);

    while (i.T() < T) {
        for (int j = 0; j < F.size(); j++) {
            i[j] += step * F[j](i); // Euler step
        }

        i.T() += step;
        v.push_back(i);
    }

    MS["euler"] = v;
    return v;
}

const vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step, double T) {
    vector<ODEpoint> v;
    v.push_back(i);

    while (i.T() < T) {
        ODEpoint p = i;
        for (int j = 0; j < F.size(); j++) {
            p[j] += step * F[j](i); // predictor step (using euler)
        }

        for (int j = 0; j < F.size(); j++) {
            i[j] += step * (F[j](i) + F[j](p))/2; // corrector step
        }

        i.T() += step;
        v.push_back(i);
    }

    MS["predictor-corrector"] = v;
    return v;
}

/*
TODO IMPLEMENT LEAP FROG
*/

const vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double T) {
    vector<ODEpoint> v;
    v.push_back(i);

    while (i.T() < T) {
        vector<array<double, 2>> K(F.size());
        ODEpoint p = i;

        for (int j = 0; j < F.size(); j++) {
            K[j][0] = step * F[j](i); // K1
            p[j] += K[j][0]/2;
        }

        for (int j = 0; j < F.size(); j++) {
            K[j][1] = step * F[j](p); // K2
            i[j] += K[j][1];
        }
        
        i.T() += step;
        v.push_back(i);
    }

    MS["RK2"] = v;
    return v;
}

const vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double T) {
    vector<ODEpoint> v;
    v.push_back(i);

    while (i.T() < T) {
        vector<array<double, 4>> K(F.size());
        ODEpoint p = i;

        for (int j = 0; j < F.size(); j++) {
            K[j][0] = step * F[j](i); // K1
            p[j] += K[j][0]/2;
        }

        for (int j = 0; j < F.size(); j++) {
            K[j][1] = step * F[j](p); // K2
            p[j] = i[j] + K[j][1]/2;
        }

        for (int j = 0; j < F.size(); j++) {
            K[j][2] = step * F[j](p); // K3
            p[j] = i[j] + K[j][2];
        }

        for (int j = 0; j < F.size(); j++) {
            K[j][3] = step * F[j](p); // K4
            i[j] += (K[j][0] + 2*K[j][1] + 2*K[j][2] + K[j][3])/6;
        }
        
        i.T() += step;
        v.push_back(i);
    }

    MS["RK4"] = v;
    return v;
}
