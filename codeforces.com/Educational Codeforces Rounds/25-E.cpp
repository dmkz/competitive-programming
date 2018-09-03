/*
    Problem: 825E. Minimal Labels
    
    Solution: graphs, DFS, greedy, topsort, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <queue>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {    
    int n, m;
    scanf("%d %d", &n, &m);
    vvi prev(1+n); vi out(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        out[u]++;
        prev[v].push_back(u);
    }
    std::priority_queue<int> queue;
    for (int u = 1; u <= n; ++u) {
        if (out[u] == 0) {
            queue.push(u);
        }
    }
    int cnt = n; vi answ(1+n);
    while (!queue.empty()) {
        auto u = queue.top();
        queue.pop();
        answ[u] = cnt--;
        for (int v : prev[u]) {
            out[v]--;
            if (out[v] == 0) {
                queue.push(v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", answ[i]);
    }
    return 0;
}