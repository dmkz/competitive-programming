/*
    Problem: 1872. Spacious Office
    
    Solution: max matching, dfs, bfs, flows, dinic, O(sqrt(n) n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

const int INF = (int)1e9+1;
const int MAX = 2048;

namespace Graph {

    int n, s, t;
    static int cost[MAX][MAX], flow[MAX][MAX];
    std::vector<int> ptr, dist;
    void init(int n_, int s_, int t_) {
        n = n_, s = s_, t = t_;
        ptr.assign(n,0);
        dist.assign(n,-1);
    }

    void connect(int u, int v) {
        cost[u][v] = 1;
    }
    
    bool bfs() {
        dist.assign(n, -1);
        std::queue<int> queue;
        queue.push(s);
        dist[s] = 0;
        while (!queue.empty()) {
            auto u = queue.front(); queue.pop();
            for (int v = 0; v < n; ++v) {
                if (dist[v] == -1 && flow[u][v] < cost[u][v]) {
                    dist[v] = dist[u] + 1;
                    queue.push(v);
                }
            }
        }
        return dist[t] != -1;
    }

    int dfs(int u, int flow_) {
        if (!flow_) return 0;
        if (u == t) return flow_;
        for (int& v = ptr[u]; v < n; ++v) {
            if (dist[v] != dist[u]+1) continue;
            int pushed = dfs(v, std::min(flow_, cost[u][v] - flow[u][v]));
            if (pushed) {
                flow[u][v] += pushed;
                flow[v][u] -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    
    int dinic() {
        int answ = 0;
        while (bfs()) {
            ptr.assign(n, 0);
            int pushed;
            while ((pushed = dfs(s, INF))) {
                answ += pushed;
            }
        }
        return answ;
    }
}


int main() {
    int n; scanf("%d", &n);
    std::vector<int> min(n), max(n), need(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &need[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &min[i], &max[i]);
    }
    // s = 0, left part from 1 to n, right part from n+1 to 2*n, t = 2*n+1
    int s = 0, t = 2*n+1;
    Graph::init(t+1, s, t);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (need[i] < min[j] || need[i] > max[j]) continue;
            Graph::connect(1+i, n+1+j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        Graph::connect(  s, i);
        Graph::connect(n+i, t);
    }
    int value = Graph::dinic();
    if (value != n) { printf("Let's search for another office."); return 0; }
    std::vector<int> f(1+n);
    for (int i = 1; i <= n; ++i) {
        for (int j = n+1; j <= 2 * n; ++j) {
            if (Graph::flow[i][j]) {
                f[i] = j;
                break;
            }
        }
    }
    bool multiply = false;
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            int a = f[i], b = f[j];
            if (Graph::cost[i][b] && Graph::cost[j][a]) {
                multiply = true;
            }
        }
    }
    if (multiply) { printf("Ask Shiftman for help."); return 0; }
    printf("Perfect!\n");
    std::vector<int> answ(1+n);
    for (int i = 1; i <= n; ++i) {
        answ[f[i]-n] = i;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", answ[i]);
    }
    return 0;
}