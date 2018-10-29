/*
    Problem: 84A. Toy Army
    
    Solution: greedy, constructive, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int solve(int nSteps, int nSoldiers) {
    if (nSteps == 0) return 0;
    return nSoldiers + solve(nSteps-1, nSoldiers / 2);
}

int main() {
    int n;
    while (std::cin >> n) {
        std::cout << solve(2, n) << std::endl;
    }
    return 0;
}