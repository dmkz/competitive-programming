/*
    Problem: 743D. Chloe and pleasant prizes
    
    Solution: trees, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef long long ll;

const ll INF = (ll)1e18L;

void update(ll& a, ll& b, ll c, ll d) {
    if (c < d) { std::swap(c, d); }
    if (a+b < c+d) {
        a = c;
        b = d;
    }
    if (a < b) { std::swap(a, b); }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<ll> self(1+n, -INF);
        auto max1 = self, max2 = self;
        std::vector<std::vector<int>> next(1+n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> self[i];
        }
        for (int i = 1, u, v; i < n; ++i) {
            std::cin >> u >> v;
            next[u].push_back(v);
            next[v].push_back(u);
        }
        
        std::function<void(int,int)> getSum = [&](int u, int p) {
            for (int v : next[u]) {
                if (v == p) continue;
                getSum(v, u);
                self[u] += self[v];
            }
        };
        getSum(1, 0);
        
        std::function<void(int,int)> visit = [&](int u, int p) {
            ll prefMax = -INF;
            for (int v : next[u]) {
                if (v == p) continue;
                visit(v, u);
                self[u] = std::max(self[u], self[v]);
                update(max1[u], max2[u], max1[v], max2[v]);
                ll maxInSubtree = std::max(self[v], max1[v]);
                update(max1[u], max2[u], prefMax, maxInSubtree);
                prefMax = std::max(prefMax, maxInSubtree);
            }
        };
        visit(1, 0);        
        
        if (max2[1] == -INF) {
            std::cout << "Impossible" << std::endl;
        } else {
            std::cout << max1[1] + max2[1] << std::endl;
        }
    }
    return 0;
}