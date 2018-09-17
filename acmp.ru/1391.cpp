/*
    Задача: 1391. Конденсация графа
    
    Решение: графы, топологическая сортировка, dfs, конденсация, O(n + m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include <queue>

int main() {
    int n, m, nParts = 0; scanf("%d %d", &n, &m);
    std::vector<std::vector<int>> next(1+n), prev(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        next[u].push_back(v);
        prev[v].push_back(u);
    }
    std::vector<int> visited(1+n), order, part(1+n);
    std::function<void(int)> topsort = [&](int u) {
        if (visited[u]) return;
        visited[u] = 1;
        for (int v : next[u]) {
            topsort(v);
        }
        order.push_back(u);
    };
    for (int u = 1; u <= n; ++u) topsort(u);
    std::reverse(order.begin(), order.end());
    for (int u : order) {
        if (!part[u]) {
            part[u] = ++nParts;
            std::queue<int> queue; queue.push(u);
            while (!queue.empty()) {
                auto curr = queue.front(); queue.pop();
                for (int v : prev[curr]) {
                    if (!part[v]) {
                        part[v] = nParts;
                        queue.push(v);
                    }
                }
            }
        }
    }
    printf("%d\n", nParts);
    for (int u = 1; u <= n; ++u) printf("%d ", part[u]);
    return 0;
}