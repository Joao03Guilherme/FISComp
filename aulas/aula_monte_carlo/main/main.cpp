# include "Functor.hpp"
# include "MyFunc.hpp"
# include "IntegDeriv.hpp"

int main() {
    Functor *f = new MyFunc("f(x) = x^2");
    cout << f(1) << endl;
    return 0;
}