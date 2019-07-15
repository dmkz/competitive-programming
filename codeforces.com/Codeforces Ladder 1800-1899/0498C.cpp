/*
    Problem: 498C. Array and Operations
    Solution: graphs, flows, dinic, dfs, bfs, number theory, O(n * sqrt(AMAX))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::pair<int,int> pii;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<pii> vpii;
typedef std::vector<vpii> vvpii;
struct Edge {
    int u, v, cost, flow;
};
const int INF = (int)1e9+7;
struct Graph {
    int nV, s, t;
    vvi adj;
    vi dist, pointer;
    std::vector<Edge> edges;
    Graph(int nV_, int s_, int t_) : nV(nV_), s(s_), t(t_), adj(nV_,vi{}) { }
    void add_edge(int u, int v, int c) {
        edges.push_back(Edge{u,v,c,0});
        edges.push_back(Edge{v,u,0,0});
        adj[u].push_back(isz(edges)-2);
        adj[v].push_back(isz(edges)-1);
    }
    bool bfs() {
        std::queue<int> queue;
        dist.assign(nV,INF);
        queue.push(s);
        dist[s] = 0;
        while (queue.size()) {
            auto u = queue.front(); queue.pop();
            if (u == t) continue;
            for (auto eid : adj[u]) {
                const auto &e = edges[eid];
                const int v = e.u + e.v - u;
                if (dist[v] == INF && e.flow < e.cost) {
                    dist[v] = dist[u] + 1;
                    queue.push(v);
                }
            }
        }
        return dist[t] < INF;
    }
    int dfs(int u, int flow) {
        if (u == t) return flow;
        if (!flow) return 0;
        for (int& p = pointer[u]; p < isz(adj[u]); p++) {
            const auto eid = adj[u][p];
            auto &e = edges[eid];
            const int v = e.u + e.v - u;
            if (dist[u] + 1 == dist[v] && e.flow < e.cost) {
                int pushed = dfs(v, std::min(flow, e.cost - e.flow));
                if (pushed) {
                    edges[eid].flow   += pushed;
                    edges[eid^1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    int dinic() {
        int answ = 0, pushed;
        while (bfs()) {
            pointer.assign(nV,0);
            while ((pushed = dfs(s,INF))) answ += pushed;
        }
        return answ;
    }
};
int solve(const int n, const vpii& edges, const vi& numbers) {
    std::map<int, vpii> map;
    for (int i = 1; i <= n; i++) {
        int x = numbers[i];
        for (int d = 2; d * d <= x; d++) {
            if (x % d == 0) {
                x /= d;
                int cnt = 1;
                while (x % d == 0) {
                    cnt++;
                    x /= d;
                }
                map[d].push_back(pii(i, cnt));
            }
        }
        if (x > 1) {
            map[x].push_back(pii(i, 1));
        }
    }
    const int s = 0, t = n+1;
    int answ = 0;
    for (const auto& divs : map) {
        Graph graph(n+2, s, t);
        for (const auto& p : divs.second) {
            if (p.first % 2 == 1) {
                graph.add_edge(s, p.first, p.second);
            } else {
                graph.add_edge(p.first, t, p.second);
            }
        }
        for (const auto& e : edges) {
            graph.add_edge(e.first, e.second, INF);
        }
        answ += graph.dinic();
    }
    return answ;
}
int main() {
    for (int n, m; std::cin >> n >> m; ) {
        vpii edges(m);
        vi numbers(1+n);
        for (int i = 1; i <= n; i++) {
            std::cin >> numbers[i];
        }
        for (auto &it : edges) {
            std::cin >> it.first >> it.second;
            if (it.first % 2 == 0) {
                std::swap(it.first, it.second);
            }
        }
        std::cout << solve(n, edges, numbers) << std::endl;
    }
    return 0;
}