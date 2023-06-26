#ifndef __ODEPOINT__
#define __ODEPOINT__

#include <vector>
#include <iostream>


class ODEpoint{
    public:
        ODEpoint(); 
        ODEpoint(double t, const std::vector<double>& var): time{t},x{var} {} 

        const double& T() const {return time;} //(const) 1º: ñ altero variável, 2º: método não altera variáveis da classe
        std::vector<double>& X() {return x;} //accessor to x
        double& operator[](size_t i){return x[i];} // X[i]
	ODEpoint operator+(ODEpoint);
	ODEpoint operator*(double);

        friend std::ostream& operator<< (std::ostream&, const ODEpoint&);

        void SetODEpoint(double t_, std::vector<double> v);

    private:
        double time;
	std::vector<double> x;
};

#endif