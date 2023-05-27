#include <cstdio> // printf
#include <cstdlib> // 
#include <iostream> // cout

using namespace std;

double factorial(int);

int main()
{
  cout << "teste" << endl;
  auto result = factorial(10);
  cout << "factorial: " << result << " " << typeid(result).name() << endl;
  return 0;
}

double factorial(int n) {
  double result=1.;
  while (n>1) {
    result *= n;
    n--;
  }
  return result;
}

void test() {
  return;
}
