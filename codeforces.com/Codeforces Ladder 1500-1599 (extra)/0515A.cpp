/*
    Problem: 515A. Drazil and Date
    
    Solution: geometry, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int x, y, s; std::cin >> x >> y >> s;
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    int diff = s - (x+y); if (diff < 0) diff = -diff;
    std::cout << ( s >= (x+y) && diff % 2 == 0 ? "Yes" : "No");
    return 0;
}