#include <iostream>
#include <cstdint>
#include <cmath>

typedef long double Real;
typedef long long Int;

int main() {
    Real n1, n2, n3, n4;
    std::cin >> n1 >> n2 >> n3 >> n4;
    Int answ = (Int)std::floor(std::sqrt(std::min(n1, n2) + std::min(n3, n4)));
    std::cout << answ << std::endl;
    return 0;
}