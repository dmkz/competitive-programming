/*
    Problem: 507E. Breaking Good
    Solution: graphs, Dijkstra's algorithm, std::priority_queue, O(n log(m))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
struct Edge { 
    int u, v, broken; 
};
struct State {
    int vert, dist, broken, lastRoad;
};
bool operator<(State a, State b) {
    if (a.dist < b.dist) return true;
    if (a.dist > b.dist) return false;
    return a.broken < b.broken || (a.broken == b.broken && a.vert < b.vert);
}
template<typename T> bool operator>(T a, T b) { return b < a; }
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int nVert, nEdges; std::cin >> nVert >> nEdges; ) {
        std::vector<Edge> edges(nEdges);
        std::vector<std::vector<int>> adj(1+nVert);
        for (int i = 0; i < nEdges; i++) {
            int u, v, c; std::cin >> u >> v >> c;
            edges[i] = {u,v,1-c};
            adj[u].push_back(i);
            adj[v].push_back(i);
        }
        std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
        queue.push(State{1, 0, 0, -1});
        std::vector<int> dist(1+nVert, 10 * nVert), broken(1+nVert, 10 * nVert), lastRoad(1+nVert, -1);
        while (isz(queue)) {
            auto curr = queue.top(); queue.pop();
            if (dist[curr.vert] < curr.dist || (dist[curr.vert] == curr.dist && broken[curr.vert] < curr.broken)) {
                continue;
            }
            dist[curr.vert] = curr.dist;
            broken[curr.vert] = curr.broken;
            lastRoad[curr.vert] = curr.lastRoad;
            for (int id : adj[curr.vert]) {
                const auto &e = edges[id];
                int v = e.u + e.v - curr.vert;
                auto next = curr;
                next.dist++;
                next.broken += e.broken;
                next.vert = v;
                next.lastRoad = id;
                queue.push(next);
            }
        }
        std::vector<bool> used(nEdges);
        for (int d = dist[nVert], curr = nVert; d > 0; d--) {
            assert(dist[curr] == d);
            const int id = lastRoad[curr];
            used[id] = true;
            const auto &e = edges[id];
            curr = e.u + e.v - curr;
        }
        std::vector<Edge> answ;
        for (int i = 0; i < nEdges; i++) {
            if (used[i]) {
                if (edges[i].broken) {
                    answ.push_back(edges[i]);
                }
            } else {
                if (!edges[i].broken) {
                    answ.push_back(edges[i]);
                }
            }
        }
        std::cout << isz(answ) << "\n";
        for (auto &it : answ) {
            std::cout << it.u << ' ' << it.v << ' ' << it.broken << '\n';
        }
    }
    return 0;
}