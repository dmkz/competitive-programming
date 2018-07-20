/*
    Problem: 620A. Professor GukiZ's Robot
    
    Solution: math, implementation, O(1)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;
    
    std::cout << std::max(std::abs(y2-y1), std::abs(x2 - x1)) << std::endl;
    
    
    return 0;
}