/*
    Problem: 1056. Computer Net
    
    Solution: trees, dfs, tree diameter, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int INF = (int)1e9+1;
int main() {
    int n; scanf("%d", &n);
    vvi edges(1+n);
    for (int i = 2; i <= n; ++i) {
        int p; scanf("%d", &p);
        edges[p].push_back(i);
        edges[i].push_back(p);
    }
    vi height(1+n), parent(1+n); int max = 1;
    std::function<void(int,int,int)> dfs = [&](int u, int p, int h) {
        parent[u] = p;
        height[u] = h;
        for (int v : edges[u]) {
            if (v == p) continue;
            dfs(v,u,h+1);
        }
        if (height[u] > height[max]) {
            max = u;
        }
    };
    dfs(1,0,0);
    dfs(max,0,0);
    for (int u = max; u != 0; u = parent[u]) {
        if (height[max] / 2 == height[u] || (height[max]+1)/2 == height[u]) {
            printf("%d ", u);
        }
    }
    return 0;
}