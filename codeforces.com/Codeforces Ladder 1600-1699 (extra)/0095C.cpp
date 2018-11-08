/*
    Problem: 95C. Volleyball
    
    Solution: Dijkstra's algorithm, shortest paths, graphs, O((n+m)*log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;

const ll INF = (ll)1e18L;

struct Edge {
    int vert; ll cost;
    
    Edge(int vert_ = 0, ll cost_ = 0) : vert(vert_), cost(cost_) { }
};

typedef std::vector<Edge> ve;
typedef std::vector<ve> vve;

bool operator<(const Edge& a, const Edge& b) {
    return a.cost < b.cost || (a.cost == b.cost && a.vert < b.vert);
}

bool operator>(const Edge& a, const Edge& b) {
    return b < a;
}

vl get_min_dist(int n, int s, const vve& edges) {
    vl dist(1+n, INF);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
    queue.push(Edge(s, 0));
    while (!queue.empty()) {
        auto curr = queue.top(); queue.pop();
        int u = curr.vert; ll d = curr.cost;
        if (dist[u] <= d) {
            continue;
        }
        dist[u] = d;
        for (const auto& e : edges[u]) {
            if (dist[e.vert] > d + e.cost) {
                queue.push(Edge(e.vert, d + e.cost));
            }
        }
    }
    return dist;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nV, nE, s, t;
    std::cin >> nV >> nE >> s >> t;
    
    vve edges(1+nV);
    for (int i = 0; i < nE; ++i) {
        int u, v; ll w;
        std::cin >> u >> v >> w;
        edges[u].push_back(Edge(v, w));
        edges[v].push_back(Edge(u, w));
    }
    
    vl limitFrom(1+nV), costFrom(1+nV);
    for (int i = 1; i <= nV; ++i) {
        std::cin >> limitFrom[i] >> costFrom[i];
    }
    
    vvl cost(1+nV, vl(1+nV, INF));
    
    for (int u = 1; u <= nV; ++u) {
        auto minDist = get_min_dist(nV, u, edges);
        // add vert:
        for (int v = 1; v <= nV; ++v) {
            if (minDist[v] <= limitFrom[u]) {
                cost[u][v] = costFrom[u];
            }
        }
    }
    for (int u = 1; u <= nV; ++u) {
        cost[u][u] = 0;
    }
    // start Dijkstra from vertex `s`
    vl dist(1+nV, INF), used(1+nV, false);
    dist[s] = 0;
    while (true) {
        ll min = INF; int best = 0;
        for (int v = 1; v <= nV; ++v) {
            if (!used[v] && dist[v] < min) {
                best = v;
                min = dist[v];
            }
        }
        if (!best) break;
        used[best] = true;
        for (int v = 1; v <= nV; ++v) {
            dist[v] = std::min(dist[v], dist[best] + cost[best][v]);
        }
    }
    std::cout << (dist[t] == INF ? -1 : dist[t]) << std::endl;
    return 0;
}