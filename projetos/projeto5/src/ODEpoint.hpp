# ifndef ODEpoint_HPP
# define ODEpoint_HPP

# include "Xvar.hpp"

class ODEpoint : public Xvar {
    public:
        ODEpoint() : t(0) {;}
        ODEpoint(double t_, Xvar a_) : t(t_), Xvar(a_) {;}
        ODEpoint(double t_, const std::vector<double>& v) : t(t_), Xvar(v) {;}
        ODEpoint(double t_, const std::initializer_list<double>& v) : t(t_), Xvar(v) {;}

        void SetODEpoint(double t_, Xvar& p);
        void SetODEpoint(double t_, const std::initializer_list<double>& v);
        void SetODEpoint(double t_, std::vector<double> v);
        double& T() { return t;} // accessor to time

        ODEpoint operator+(ODEpoint p);
        ODEpoint operator*(double a);

    private:
        double t; // time
};

# endif