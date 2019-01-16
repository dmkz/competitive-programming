/*
    Problem: 7267. A path to knowledge
    
    Solution: Dijkstra's algorithm, graphs, probability, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

const int INF = (int)1e9+7;

struct Edge { int u, v, w; };

typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Edge> ve;
typedef std::vector<ld> vd;

bool operator<(const Edge& a, const Edge& b) {
    return a.w < b.w || (a.w == b.w && (a.u < b.u || (a.u == b.u && a.v < b.v)));
}

bool operator>(const Edge& a, const Edge& b) { return b < a; }
bool operator!=(const Edge& a, const Edge& b) { return b < a || b < a; }
bool operator==(const Edge& a, const Edge& b) { return !(b != a); }
bool operator>=(const Edge& a, const Edge& b) { return !(a < b); }
bool operator<=(const Edge& a, const Edge& b) { return !(a > b); }

vi dijkstra(const int s, const int nVert, const vvi& adj, const ve& list) {
    vi dist(1+nVert, INF);
    std::priority_queue<Edge, ve, std::greater<Edge>> queue;
    queue.push(Edge{0,s,0});
    while (!queue.empty()) {
        auto state = queue.top(); queue.pop();
        int v = state.v, d = state.w;
        if (dist[v] <= d) { continue; }
        dist[v] = d;
        for (auto eid : adj[v]) {
            const auto &e = list[eid];
            int next = e.u + e.v - v;
            assert(next != v);
            queue.push(Edge{v,next,d+e.w});
        }
    }
    return dist;
}

typedef std::pair<int,int> pii;

vd expected(const int s, const int t, const int nVert, const vi& distFromS, const vvi& adj, const ve& list) {
    // we will build new graph which contains only edges, included in shortest paths, and prepare topological order
    vvi to(1+nVert), from(1+nVert);
    std::priority_queue<pii> queue;
    queue.push(pii(distFromS[t], t));
    vi visited(1+nVert), order;
    while (!queue.empty()) {
        auto curr = queue.top().second; queue.pop();
        if (visited[curr]) { continue; }
        visited[curr] = 1;
        order.push_back(curr);
        for (int eid : adj[curr]) {
            const auto &e = list[eid];
            const int next = e.u + e.v - curr;
            if (distFromS[next] + e.w == distFromS[curr]) {
                to[next].push_back(curr);
                from[curr].push_back(next);
                queue.push(pii(distFromS[next], next));
            }
        }
    }
    // Dynamic programming:
    vd countFromS(1+nVert,0), countFromT(1+nVert,0), answ(1+nVert);
    countFromS[s] = countFromT[t] = 1;
    for (int v : order) {
        for (int next : from[v]) {
            countFromT[next] += countFromT[v];
        }
    }
    std::reverse(order.begin(), order.end());
    for (int v : order) {
        for (int next : to[v]) {
            countFromS[next] += countFromS[v];
        }
    }
    for (int u = 1; u <= nVert; ++u) {
        answ[u] = 2 * countFromS[u] * countFromT[u] / countFromS[t];
    }
    return answ;
}

vd solve(const int nVert, const int nEdges, const ve& list) {
    // Prepare edges:
    vvi edges(1+nVert);
    for (int i = 0; i < nEdges; ++i) {
        const auto &e = list[i];
        if (e.u != e.v) {
            edges[e.u].push_back(i);
            edges[e.v].push_back(i);
        }
    }
    // Run Dijkstra's algorithm:
    const int s = 1, t = nVert;
    auto distFromS = dijkstra(s, nVert, edges, list);
    // Calculate expected value:
    return expected(s, t, nVert, distFromS, edges, list);
}

int main() {
    std::cout << std::fixed << std::setprecision(9);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        std::vector<Edge> edges(nEdges);
        for (auto &e : edges) { std::cin >> e.u >> e.v >> e.w; }
        auto answ = solve(nVert, nEdges, edges);
        for (int i = 1; i <= nVert; ++i) { std::cout << answ[i] << ' '; }
        std::cout << std::endl;
    }
    return 0;
}