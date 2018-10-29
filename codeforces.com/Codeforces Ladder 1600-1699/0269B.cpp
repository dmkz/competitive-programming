/*
    Problem: 269B. Greenhouse Effect
    
    Solution: dynamic programming, longest common subsequence, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef std::vector<int> vi;

int solve(const vi& a, const vi& b) {
    static int max[5001][5001];
    std::fill(&max[0][0], &max[0][0]+5001*5001,0);
    const int n = (int)a.size();
    assert((int)b.size() == n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int s = a[i-1], t = b[j-1];
            if (s == t) {
                max[i][j] = max[i-1][j-1] + 1;
            } else {
                max[i][j] = std::max(max[i-1][j], max[i][j-1]);
            }
        }
    }
    return n - max[n][n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, nTypes;
    while (std::cin >> n >> nTypes) {
        vi s(n);
        for (int i = 0; i < n; ++i) {
            double x; std::cin >> s[i] >> x;
        }
        vi t = s;
        std::sort(t.begin(), t.end());
        std::cout << solve(s, t) << std::endl;
    }
    
    return 0;
}