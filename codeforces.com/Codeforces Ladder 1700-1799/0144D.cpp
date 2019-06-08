/*
    Problem: 144D. Missile Silos
    
    Solution: Dijkstra's algorithm, graphs, shortest paths, O(V * log(E))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef long long ll;
const ll INF = (ll)1e18L;
struct State { int vert; ll dist; };
struct Edge { int u, v; ll d; };
bool operator<(const State& a, const State& b) {
    return a.dist < b.dist || (a.dist == b.dist && a.vert < b.vert); 
}
template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
int solve(const int nV, const int nE, const int s) {
    std::vector<std::vector<State>> adj(nV+1);
    std::vector<Edge> edges(nE);
    for (int i = 0; i < nE; i++) {
        int u, v, w; std::cin >> u >> v >> w;
        adj[u].push_back(State{v,w});
        adj[v].push_back(State{u,w});
        edges[i] = {u,v,w};
    }
    std::vector<ll> dist(1+nV, INF);
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
    queue.push(State{s,0});
    while (!queue.empty()) {
        auto st = queue.top(); queue.pop();
        if (dist[st.vert] <= st.dist) { continue; }
        dist[st.vert] = st.dist;
        for (auto next : adj[st.vert]) {
            queue.push(State{next.vert, next.dist + st.dist});
        }
    }
    int answ = 0, L; std::cin >> L;
    for (int u = 1; u <= nV; u++) {
        answ += (dist[u] == L);
    }
    for (const auto & it : edges) {
        auto p1 = L - dist[it.u];
        if (0 < p1 && p1 < it.d) {
            auto d1 = std::min(dist[it.u] + p1, dist[it.v] + it.d - p1);
            if (d1 == L) { answ++; }
            else { p1 = -1; }
        }
        auto p2 = L - dist[it.v];
        if (0 < p2 && p2 < it.d) {
            auto d2 = std::min(dist[it.v] + p2, dist[it.u] + it.d - p2);
            if (d2 == L && it.d - p2 != p1) { answ++; }
            else { p2 = -1; }
        }
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int nV, nE, s; std::cin >> nV >> nE >> s; std::cout << solve(nV, nE, s) << std::endl);
    return 0;
}