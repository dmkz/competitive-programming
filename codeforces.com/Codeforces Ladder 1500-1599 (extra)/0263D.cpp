/*
    Problem: 263D. Cycle in Graph
    
    Solution: graphs, dfs, cycles, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

int main() {
    // Input:
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    std::vector<std::vector<int>> edges(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    // Find cycle:
    int timer = 0;
    std::vector<int> color(1+n), tin(1+n), from(1+n);
    std::function<void(int,int)> visit = [&](int u, int p) {
        from[u] = p;
        tin[u] = ++timer;
        color[u] = 1;
        for (int v : edges[u]) {
            if (v == p) continue;
            if (color[v] == 0) {
                visit(v,u);
            } else if (color[v] == 1 && tin[u] - tin[v] >= k) {
                std::vector<int> answ{v};
                for (int curr = u; curr != v; curr = from[curr]) {
                    answ.push_back(curr);
                }
                assert((int)answ.size() >= k+1);
                printf("%d\n", (int)answ.size());
                for (auto& it : answ) printf("%d ", it);
                std::exit(0);
            }
        }
        color[u] = 2;
    };
    visit(1,0);
    assert(false);
}