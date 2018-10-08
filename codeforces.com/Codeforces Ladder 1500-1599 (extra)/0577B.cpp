/*
    Problem: 577B. Modulo sum
    
    Solution: math, number theory, dynamic programming, O(m^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int n, m; scanf("%d %d", &n, &m);
    std::vector<int> a(n);
    for (auto& it : a) { scanf("%d", &it); it %= m; }
    if (n > m || std::find(a.begin(), a.end(), 0) != a.end()) {
        printf("YES"); return 0;
    }
    std::vector<std::vector<bool>> can(1+n, std::vector<bool>(m));
    can[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        int number = a[i-1];
        for (int prev = 0; prev < m; ++prev) {
            can[i][prev] = can[i][prev] || can[i-1][prev];
            if (can[i-1][prev]) {
                int next = (prev + number) % m;
                if (next == 0) { printf("YES\n"); return 0; }
                can[i][next] = 1;
            }
        }
    }
    printf("NO\n");
    return 0;
}