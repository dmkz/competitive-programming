/*
    Problem: 201A. Clear Symmetry
    
    Solution: math, greedy, O(x)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int solve(int x) {
    if (x == 1) {
        return 1;
    }
    if (x == 3) {
        return 5;
    }
    int n = 3;
    while (true) {
        if ((n*n+1)/2>=x) {
            return n;
        }
        n += 2;
    }
}

int main() {
    int x;
    while (std::cin >> x) {
        std::cout << solve(x) << std::endl;
    }
    return 0;
}