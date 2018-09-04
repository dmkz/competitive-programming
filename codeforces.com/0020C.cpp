/*
    Problem: 20C. Dijkstra?
    
    Solution: graphs, shortest path, Dijkstra's algorithm, O((n+m)*log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

typedef long long ll;

const ll INF = (ll)1e18L;

struct Edge {
    int vert; ll cost;
};

bool operator<(const Edge& a, const Edge& b) {
    return a.cost < b.cost || (a.cost == b.cost && a.vert < b.vert);
}

bool operator>(const Edge& a, const Edge& b) {
    return b < a;
}

bool operator==(const Edge& a,const Edge& b) {
    return !(a < b || b < a);
}

int main() {
    // Input graph:
    int n, m; 
    scanf("%d %d", &n, &m);
    std::vector<std::vector<Edge>> edges(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        edges[u].push_back(Edge{v,cost});
        edges[v].push_back(Edge{u,cost});
    }
    // Dijkstra's algorithm:
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
    std::vector<ll> dist(1+n, INF);
    std::vector<int> from(1+n, -1);
    queue.push(Edge{1, 0});
    dist[1] = 0;
    while (!queue.empty()) {
        auto curr = queue.top(); queue.pop();
        int u = curr.vert; ll d = curr.cost;
        if (dist[u] < d) { continue; }
        for (auto& e : edges[u]) {
            int v = e.vert;
            if (dist[v] > dist[u] + e.cost) {
                dist[v] = dist[u] + e.cost;
                from[v] = u;
                queue.push(Edge{v,dist[v]});
            }
        }
    }
    // Output:
    if (from[n] == -1) { printf("-1"); return 0; }
    std::vector<int> path;
    for (int v = n; v != -1; v = from[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    for (auto& it : path) printf("%d ", it);
    return 0;
}