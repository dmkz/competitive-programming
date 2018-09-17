/*
    Задача: 1385. Получи дерево
    
    Решение: графы, деревья, поиск в глубину, O(n+m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<std::vector<int>> next(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        next[u].push_back(v);
        next[v].push_back(u);
    }
    std::vector<int> fi, se, parent(1+n, -1);
    std::function<void(int, int)> make_tree = [&](int u, int p) {
        parent[u] = p;
        if (p != 0) {fi.push_back(p); se.push_back(u);}
        for (int v : next[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                make_tree(v, u);
            }
        }
    };
    make_tree(1, 0);
    assert((int)fi.size() == n-1);
    for (int i = 0; i < n-1; ++i) {
        printf("%d %d\n", fi[i], se[i]);
    }
    return 0;
}