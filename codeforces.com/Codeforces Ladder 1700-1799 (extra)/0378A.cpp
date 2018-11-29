/*
    Problem: 378A. Playing with Dice
    
    Solution: brute force, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cstdlib>

int main() {
    int a, b;
    while (std::cin >> a >> b) {
        int na = 0, nb = 0;
        for (int x = 1; x <= 6; ++x) {
            int da = std::abs(x-a);
            int db = std::abs(x-b);
            na += da < db;
            nb += da > db;
        }
        std::cout << na << ' ' << 6 - na - nb << ' ' << nb << std::endl;
    }
    return 0;
}