/*
    Problem: 213C. Relay Race
    
    Solution: dynamic programming, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int solve(const int n, const vvi& arr) {
    const int INF = (int)1e9+7;
    vvi curr(n, vi(n, -INF)), next(n, vi(n, -INF));
    curr[0][0] = arr[0][0];
    // n-1+n-1 = 2 * n - 2
    for (int diag = 1; diag < 2 * n - 1; diag++) {
        next.assign(n, vi(n, -INF));
        for (int r1 = 0; r1 <= std::min(n-1, diag); ++r1) {
            for (int r2 = 0; r2 <= std::min(n-1, diag); ++r2) {
                const int c1 = diag - r1;
                const int c2 = diag - r2;
                if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) { continue; }
                int extra = (r1 == r2 ? arr[r1][c1] : arr[r1][c1] + arr[r2][c2]);
                next[r1][r2] = std::max({
                    curr[r1-0][r2-0] + extra,
                    (r1 > 0 ? curr[r1-1][r2-0] + extra : -INF),
                    (r2 > 0 ? curr[r1-0][r2-1] + extra : -INF),
                    (r1 > 0 && r2 > 0 ? curr[r1-1][r2-1] + extra : -INF)
                });
            }
        }
        curr.swap(next);
    }
    return curr.back().back();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vvi arr(n, vi(n));
        for (auto &row : arr) {
            for (auto &it : row) {
                std::cin >> it;
            }
        }
        std::cout << solve(n, arr) << std::endl;
    }
    return 0;
}