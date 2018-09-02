/*
    Problem: 1022. Genealogical Tree
    
    Solution: trees, dfs, topsort, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n; scanf("%d", &n);
    vvi edges(1+n);
    for (int u = 1; u <= n; ++u) {
        for (int v; (scanf("%d", &v), v) > 0; edges[u].push_back(v));
    }
    vi visited(1+n), order;
    std::function<void(int)> dfs = [&](int u) {
        if (visited[u]) return;
        visited[u] = 1;
        for (int v : edges[u]) dfs(v);
        order.push_back(u);
    };
    for (int u = 1; u <= n; ++u) dfs(u);
    std::reverse(order.begin(), order.end());
    for (auto& it : order) {
        printf("%d ", it);
    }
    return 0;
}