/*
    Problem: 1109. Conference
    
    Solution: graphs, flows, max matching, dinic, O(sqrt(n) n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

#define size(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
const int INF = (int)1e9+7;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Graph {

    int n, s, t;

    vvi cost, flow;
    
    vi pointer, dist;

    Graph(int n_, int s_, int t_) : n(n_), s(s_), t(t_) {
        cost.assign(n, vi(n,0));
        flow.assign(n, vi(n,0));
        pointer.assign(n, 0);
        dist.assign(n,-1);
    }
    
    void add_edge(int u, int v, int cost_) {
        cost[u][v] = cost_;
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
    
    int dfs(int u, int value) {
        if (!value) return 0;
        if (u == t) return value;
        for (int& v = pointer[u]; v < n; ++v) {
            if (dist[v] != dist[u]+1) continue;
            int pushed = dfs(v, std::min(value, cost[u][v] - flow[u][v]));
            if (pushed) {
                flow[u][v] += pushed;
                flow[v][u] -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int dinic() {
        int value = 0, pushed;
        while (bfs()) {
            pointer.assign(n,0);
            while ((pushed = dfs(s, INF))) {
                value += pushed;
            }
        }
        return value;
    }
    
};

int main() {
    int n, m, k; scanf("%d %d %d", &n, &m, &k);
    // vertices in first part: from 1 to n
    // vertices in second part: from n+1 to n+m
    // s = 0, t = n+m+1
    Graph G(n+m+2, 0, n+m+1);
    while (k--) {
        int u, v; scanf("%d %d", &u, &v);
        G.add_edge(u,v+n,1);
    }
    for (int u = 1; u <= n; ++u) {
        G.add_edge(0,u,1);
    }
    for (int u = n+1; u <= n + m; ++u) {
        G.add_edge(u,n+m+1,1);
    }
    printf("%d", n+m-G.dinic());
    return 0;
}