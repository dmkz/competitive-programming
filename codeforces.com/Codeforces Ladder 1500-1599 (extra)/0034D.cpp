/*
    Problem: 34D. Road Map
    
    Solution: trees, dfs, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n, s, t;
    scanf("%d %d %d", &n, &s, &t);
    vvi edges(1+n);
    for (int i = 1; i <= n; ++i) {
        if (i == s) continue;
        int j; scanf("%d", &j);
        edges[i].push_back(j);
        edges[j].push_back(i);
    }
    
    vi parent(1+n,-1);
    std::function<void(int,int)> visit = [&](int u, int p) {
        for (int v : edges[u]) {
            if (p == v) continue;
            parent[v] = u;
            visit(v, u);
        }
    };
    visit(t,t);
    for (int i = 1; i <= n; ++i) {
        if (i == t) continue;
        printf("%d ", parent[i]);
    }
    return 0;
}