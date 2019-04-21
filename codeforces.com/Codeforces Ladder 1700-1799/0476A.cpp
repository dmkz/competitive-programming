/*
    Problem: 476A. Dreamoon and Stairs
    
    Solution: brute force, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        int ret = INT_MAX;
        for (int n1 = 0; n1 <= n; ++n1) {
            if ((n - n1) % 2 != 0) { continue; }
            int n2 = (n - n1) / 2;
            if ((n1 + n2) % m == 0) {
                ret = std::min(ret, n1 + n2);
            }
        }
        if (ret == INT_MAX) { ret = -1; }
        std::cout << ret << std::endl;
    }
    return 0;
}