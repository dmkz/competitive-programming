/*
    Problem: 519C. Fox and Number Game
    
    Solution: math, brute force, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, m; std::cin >> n >> m;
    // 1: 2 + 1
    // 2: 1 + 2
    int answ = 0;
    for (int n1 = 0; n1 <= n / 2; ++n1) {
        int rem1 = n - n1 * 2;
        int rem2 = m - n1;
        if (rem2 < 0) continue;
        int n2 = std::min(rem1, rem2/2);
        answ = std::max(answ,n1+n2);
    }
    std::cout << answ;
    return 0;
}