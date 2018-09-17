/*
    Задача: 219. Симпатичные таблицы
    
    Решение: максимальный поток, алгоритм Диница, графы, O((N+M)^3)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

const int INF = (int)1e9+1;

struct Graph {
    
    int n, s, t;
    
    std::vector<std::vector<int>> flow, cost;
    
    std::vector<int> dist, ptr;
    
    Graph(int n_, int s_, int t_) : n(n_), s(s_), t(t_) {
        flow.assign(n, std::vector<int>(n));
        cost.assign(n, std::vector<int>(n));
    }
    
    void add_edge(int u, int v, int c) {
        cost[u][v] = c;
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
            if (dist[v] != dist[u] + 1) continue;
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
            while ((pushed = dfs(s, INF))) answ += pushed;
        }
        return answ;
    }
};

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    std::vector<int> srow(1+nRows), scol(1+nCols);
    for (int r = 1; r <= nRows; ++r) scanf("%d", &srow[r]);
    for (int c = 1; c <= nCols; ++c) scanf("%d", &scol[c]);
    int n = nRows + nCols + 2, s = 0, t = nRows+nCols+1, answ = 0;
    Graph graph(n, s, t);
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            int val; scanf("%d", &val);
            if (val == -1) {
                graph.add_edge(r, nRows + c, INF);
            } else {
                srow[r] -= val;
                scol[c] -= val;
                answ += val;
                if (srow[r] < 0 || scol[c] < 0) {
                    printf("-1"); return 0;
                }
            }
        }
    }
    for (int r = 1; r <= nRows; ++r) {
        graph.add_edge(s, r, srow[r]);
    }
    for (int c = 1; c <= nCols; ++c) {
        graph.add_edge(c+nRows, t, scol[c]);
    }
    printf("%d", answ+graph.dinic());
    return 0;
}