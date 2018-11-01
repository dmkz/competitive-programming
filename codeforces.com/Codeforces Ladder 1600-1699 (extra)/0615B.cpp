/*
    Problem: 615B. Longtail Hedgehog
    
    Solution: graphs, dynamic programming, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<int> mxLen(1+n, 1), degree(1+n);
        std::vector<std::vector<int>> next(1+n);
        for (int i = 0, u, v; i < m; ++i) {
            std::cin >> u >> v;
            if (u > v) std::swap(u, v);
            next[u].push_back(v);
            degree[u]++;
            degree[v]++;
        }
        for (int u = 1; u < n; ++u) {
            for (int v : next[u]) {
                if (v > u) {
                    mxLen[v] = std::max(mxLen[v], mxLen[u]+1);
                }
            }
        }
        ll answ = 0;
        for (int u = 1; u <= n; ++u) {
            answ = std::max((ll)mxLen[u] * degree[u], answ);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}