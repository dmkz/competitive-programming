/*
    Problem: 448A. Rewards
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int a(0), b(0), n;
    for (int i = 0; i < 3; ++i) { int v; std::cin >> v; a += v; }
    for (int i = 0; i < 3; ++i) { int v; std::cin >> v; b += v; }
    std::cin >> n;
    for (int k = 0; k <= n; ++k) {
        if (a - 5 * k > 0 || b - 10 * (n-k) > 0) {
            continue;
        }
        std::cout << "YES"; return 0;
    }
    std::cout << "NO";
    return 0;
}