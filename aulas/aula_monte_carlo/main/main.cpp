# include "Functor.hpp"
# include "MyFunc.hpp"
# include "IntegDeriv.hpp"
# include <iostream>

using namespace std;

int main() {
    Functor F("MyFunc");
    cout << F(1) << endl;
    return 0;
}