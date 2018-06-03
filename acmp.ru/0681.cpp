/*
    Находим ближайший полный квадрат больший n, вырезаем из него лишние квадратики.
*/

#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long Int;

int main() {
    Int n; 
    std::cin >> n;
    Int side = (Int)std::ceil(std::sqrt(n));
    Int del = side*side-n;
    Int answ = side*side*2+2*side;
    if (del < side) {
        answ -= 2*del;
    }
    if (del >= side) {
        answ -= 2*del+1;
    }
    std::cout << answ;
    return 0;
}