/*
    Problem: 274B. Zero Tree
    
    Solution: topological sorting, trees, greedy, dfs, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

typedef long long ll;

int main() {
    // Input tree:
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<std::vector<int>> next(1+n);
    for (int i = 1, u, v; i < n; ++i) {
        std::cin >> u >> v;
        next[u].push_back(v);
        next[v].push_back(u);
    }
    // Topological sorting:
    std::vector<int> order, parent(1+n, -1);
    std::function<void(int,int)> topsort = [&](int u, int p) {
        if (parent[u] != -1) return;
        parent[u] = p;
        for (int v : next[u]) {
            if (v == p) continue;
            topsort(v, u);
        }
        order.push_back(u);
    };
    topsort(1, 0);
    // Greedy over order of topsorting:
    std::vector<ll> inc(1+n), dec(1+n), value(1+n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> value[i];
    }
    for (int u : order) {
        ll val = value[u] + inc[u] - dec[u];
        if (val > 0) {
            dec[u] += val;
        } else {
            inc[u] -= val;
        }
        int p = parent[u];
        inc[p] = std::max(inc[p], inc[u]);
        dec[p] = std::max(dec[p], dec[u]);
    }
    std::cout << inc[0] + dec[0] << std::endl;
    return 0;
}