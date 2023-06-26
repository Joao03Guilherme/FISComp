# ifndef XVAR_HPP
# define XVAR_HPP

# include <vector>
# include <iostream>

class Xvar {
    public:
        Xvar() = default;
        Xvar(int); // number of dependent variables
        Xvar(std::vector<double>); 
        Xvar(const std::initializer_list<double>& v);

        ~Xvar() = default;
    
        Xvar(const Xvar&); // copy constructor

        Xvar& operator=(const Xvar&); // assignment operator
        Xvar operator+(const Xvar&); // operator+
        double& operator[](int); // X[i]
        friend Xvar operator*(double, const Xvar&); // scalar*X
        friend std::ostream& operator<< (std::ostream&, const Xvar&);

        std::vector<double>& X(); // accessor to x
        
    protected:
        std::vector<double> x;
};

# endif