/*
    Problem: 106C. Buns
    
    Solution: dynamic programming, O(m * n * MAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = (int)1e9+7;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n, m, c0, d0;
    std::cin >> n >> m >> c0 >> d0;
    vvi max(1+m, vi(1+n,-INF));
    max[0][0] = 0;
    for (int i = 1; i * c0 <= n; ++i) {
        max[0][i*c0] = i * d0;
    }
    for (int i = 1; i <= m; ++i) {
        int a, b, c, d; std::cin >> a >> b >> c >> d;
        max[i] = max[i-1];
        for (int k = 1, lim = std::min(a/b,n/c); k <= lim; ++k) {
            for (int s = 0; s <= n; ++s) {
                if (s-k*c >= 0) {
                    max[i][s] = std::max({max[i-1][s-k*c]+k*d, max[i-1][s], max[i][s]});
                }
            }
        }
    }
    std::cout << *std::max_element(max[m].begin(), max[m].end());
    return 0;
}