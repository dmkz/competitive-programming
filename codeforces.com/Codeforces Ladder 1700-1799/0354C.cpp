/*
    Problem: 354C. Vasya and Beautiful Arrays
    
    Solution: sieve, brute force, prefix sums, O(MAX * log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, k; std::cin >> n >> k; ) {
        const int AMAX = 1000010;
        static int sum[AMAX];
        std::fill(sum,sum+AMAX,0);
        for (int i = 0; i < n; i++) {
            int v; std::cin >> v;
            sum[v]++;
        }
        for (int i = 1; i < AMAX; i++) {
            sum[i] += sum[i-1];
        }
        int answ = 1;
        for (int g = 2; g < AMAX; g++) {
            int cnt = 0;
            for (int t = 1; t * g < AMAX; t++) {
                int l = t * g;
                int r = std::min(AMAX-1, l + std::min(g - 1, k));
                cnt += (sum[r] - sum[l-1]);
            }
            if (cnt == n) {
                answ = std::max(answ, g);
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}