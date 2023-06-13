# ifndef ODESOLVER_HPP
# define ODESOLVER_HPP

# include "ODEpoint.hpp"
# include <vector>
# include <functional>
# include <map>

using std::vector;
using std::map;
using std::string;

class ODEsolver {
    public:
        ODEsolver() = default;
        ODEsolver(const vector<std::function<double(ODEpoint)>>& F_) : F(F_) {;}
        ~ODEsolver() = default;

        // set functions
        void SetODEfunc(const vector<std::function<double(ODEpoint)>> &);

        // Getters
        const vector<ODEpoint>& GetODEpoints(string key) { return MS[key]; }

        // solver methods
        const vector<ODEpoint>& Euler(ODEpoint i, double step, double T);
        const vector<ODEpoint>& PredictorCorrector(ODEpoint i, double step, double T);
        const vector<ODEpoint>& LeapFrog(ODEpoint i, double step, double T);
        const vector<ODEpoint>& RK2(ODEpoint i, double step, double T);
        const vector<ODEpoint>& RK4(ODEpoint i, double step, double T);

    private:
        vector<std::function<double(ODEpoint)>> F;
        map<string, vector<ODEpoint> > MS; // key: "euler", "trapezoidal",
};

# endif