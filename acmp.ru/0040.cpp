#include <cmath>
#include <iomanip>
#include <iostream>
  
int main() {
  int n;
  std::cin >> n;
  std::cout << std::fixed << std::setprecision(0)
            << std::pow(2., n) << std::endl;
  return 0;
}
