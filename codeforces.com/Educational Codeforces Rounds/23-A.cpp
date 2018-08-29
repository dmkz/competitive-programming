/*
    Problem: 817A. Treasure Hunt
    
    Solution: math, number theory, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>

bool solve(int dx, int dy, int x, int y) {
    // a * dx = x
    // (a+2k) * dy = y
    if (x % dx != 0 || y % dy != 0) return false;
    int a = x / dx;
    int b = y / dy;
    return std::abs(b-a) % 2 == 0;
}

int main() {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    x2 -= x1;
    y2 -= y1;
    int dx, dy; std::cin >> dx >> dy;
    std::cout << (solve(dx, dy, std::abs(x2), std::abs(y2)) ? "YES" : "NO");
    return 0;
}