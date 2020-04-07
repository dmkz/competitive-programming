/*
    Problem: 484B. Maximum Value
    Solution: dynamic programming, number theory, brute force, O(n log(n))
*/
#include <bits/stdc++.h>
const int NMAX = 2 * 1024 * 1024;
int maxLess[NMAX], exists[NMAX];
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 0, a; i < n; i++) {
        std::cin >> a;
        exists[a] = 1;
    }
    for (int num = 2; num < NMAX; num++) {
        if (exists[num-1]) { maxLess[num] = num-1; }
        else { maxLess[num] = maxLess[num-1]; }
    }
    int res = 0;
    for (int v = 2; v < NMAX; v++) {
        if (exists[v]) {
            for (int l = v, r = 2 * v; r < NMAX; r += v, l += v) {
                int mx = maxLess[r];
                if (mx >= l) {
                    res = std::max(res, mx % v);
                }
            }
        }
    }
    std::cout << res << std::endl;
    return 0;
}