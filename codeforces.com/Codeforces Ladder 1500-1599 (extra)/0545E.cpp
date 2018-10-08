/*
    Problem: 545E. Paths and Trees
    
    Solution: graphs, trees, Dijkstra's algorithm, Prim's algorithm, O((n+m)*log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

typedef long long ll;

const ll INF = (ll)1e18L;

struct State {
    int vertex; ll dist; int lastEdgeCost, lastEdgeId;
};

bool operator<(const State& a, const State& b) {
    if (a.dist < b.dist) return true;
    if (a.dist > b.dist) return false;
    if (a.lastEdgeCost < b.lastEdgeCost) return true;
    if (a.lastEdgeCost > b.lastEdgeCost) return false;
    return a.lastEdgeId < b.lastEdgeId || (a.lastEdgeId == b.lastEdgeId && a.vertex < b.vertex);
}

bool operator>(const State& a, const State& b) {
    return b < a;
}

bool operator==(const State& a, const State& b) {
    return !(a < b || b < a);
}

struct Edge {
    int vertex, cost, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Input edges:
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> edges(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v, c; std::cin >> u >> v >> c;
        edges[u].push_back(Edge{v,c,i+1});
        edges[v].push_back(Edge{u,c,i+1});
    }
    int s; std::cin >> s;
    // Prepare Dijkstra:
    std::vector<ll> dist(1+n, INF);
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
    queue.push(State{s, ll(0), 0, 0});
    std::vector<int> vout; ll answ = 0;
    // Dijkstra:
    while (!queue.empty()) {
        auto curr = queue.top(); queue.pop();
        if (dist[curr.vertex] != INF) continue;
        dist[curr.vertex] = curr.dist;
        if (curr.lastEdgeId != 0) {
            answ += curr.lastEdgeCost;
            vout.push_back(curr.lastEdgeId);
        }
        for (auto& e : edges[curr.vertex]) {
            if (dist[e.vertex] == INF) {
                queue.push(State{e.vertex, curr.dist + e.cost, e.cost, e.id});
            }
        }
    }
    std::cout << answ << '\n';
    for (auto& it : vout) {
        std::cout << it << ' ';
    }
    return 0;
}