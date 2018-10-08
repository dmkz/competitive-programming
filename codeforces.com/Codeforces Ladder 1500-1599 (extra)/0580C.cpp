/*
    Problem: 580C. Kefa and Park
    
    Solution: trees, dfs, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n, limit;
    std::cin >> n >> limit;
    vvi edges(1+n); vi active(1+n);
    for (int u = 1; u <= n; ++u) {
        std::cin >> active[u];
    }
    for (int i = 1; i < n; ++i) {
        int u, v; std::cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int answ = 0;
    std::function<void(int,int,int,int)> visit = [&](const int u, const int p, int cur, int max) {
        if (active[u]) {
            cur++;
        } else cur = 0;
        max = std::max(max, cur);
        bool leaf = true;
        for (int v : edges[u]) {
            if (v == p) continue;
            leaf = false;
            visit(v, u, cur, max);
        }
        if (leaf) {
            answ += (max <= limit);
        }
    };
    visit(1,0,0,0);
    std::cout << answ;
    return 0;
}