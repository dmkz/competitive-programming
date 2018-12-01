/*
    Problem: 197A. Plate Game
    
    Solution: geometry, game theory, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int a, b, r;
    while (std::cin >> a >> b >> r) {
        std::cout << (a >= 2 * r && b >= 2 * r ? "First\n" : "Second\n");
    }
    return 0;
}