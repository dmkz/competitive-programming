/*
    Problem: 507B. Amr and Pins
    
    Solution: geometry, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>

typedef long double Real;

int main() {
    Real r, x1, y1, x2, y2;
    std::cin >> r >> x1 >> y1 >> x2 >> y2;
    Real dx = x2-x1, dy = y2-y1;
    int k = (int)std::ceil(std::sqrt((dx * dx + dy * dy) / (4 * r * r)));
    std::cout << k;
    return 0;
}