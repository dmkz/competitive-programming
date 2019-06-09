/*
    Problem: 455C. Civilization
    
    Solution: trees, bfs, dsu, O(V + E + Q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int INF = (int)1e9+7;
// Each tree -> (center, diameter)
// Subtask #1: For each tree in input find (center, diameter), create dsu
// Subtask #2: Use dsu for connect trees with edge between centers
int findMaxVert(const vi& dist, const vi& comp) {
    int u = comp.front();
    for (int v : comp) {
        if (dist[v] > dist[u]) {
            u = v;
        }
    }
    return u;
}
void bfs(int s, const vvi& adj, vi& dist, vi& comp) {
    static std::queue<int> queue;
    assert(isz(queue) == 0);
    comp.clear();
    dist[s] = 0; queue.push(s);
    while (isz(queue) > 0) {
        int u = queue.front(); queue.pop();
        comp.push_back(u);
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                assert(dist[v] == INF);
                dist[v] = dist[u] + 1;
                queue.push(v);
            }
        }
    }
}
struct DSU {
    vi center, size, diameter;
    DSU(int n) : center(1+n), size(1+n), diameter(1+n) {}
    int get_center(int u) { return u == center[u] ? u : center[u] = get_center(center[u]); }
    void union_sets(int u, int v) {
        u = get_center(u); v = get_center(v);
        if (u == v) { return; }
        if (size[u] < size[v]) { std::swap(u,v); }
        size[u] += size[v];
        center[v] = u;
        diameter[u] = std::max(diameter[u], std::max(diameter[v], 1 + (diameter[v]+1)/2+(diameter[u]+1)/2));
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int nV, nE, nQ; std::cin >> nV >> nE >> nQ; ) {
        vvi adj(1+nV); vi dist(1+nV,INF), uDist(1+nV,INF), vDist(1+nV,INF), comp;
        for (int i = 0, u, v; i < nE; i++) {
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // Building DSU:
        DSU dsu(nV);
        for (int vert = 1; vert <= nV; vert++) {
            if (!dsu.center[vert]) {
                bfs(vert, adj, dist, comp);
                int u = findMaxVert(dist,comp);
                bfs(u, adj, uDist, comp);
                int v = findMaxVert(uDist,comp);
                bfs(v, adj, vDist, comp);
                int diam = uDist[v], center = -1;
                for (int w : comp) {
                    int du = uDist[w], dv = vDist[w];
                    if (du > dv) { std::swap(du, dv); }
                    if (du == diam / 2 && dv == (diam+1)/2) { center = w; }
                }
                dsu.size[center] = isz(comp);
                dsu.diameter[center] = diam;
                for (int w : comp) {
                    dsu.center[w] = center;
                    dist[w] = uDist[w] = vDist[w] = INF;
                }
            }
        }
        for (int i = 0, t, u, v; i < nQ; i++) {
            std::cin >> t >> u;
            if (t == 1) { std::cout << dsu.diameter[dsu.get_center(u)] << "\n"; }
            else { std::cin >> v; dsu.union_sets(u,v); }
        }
    }
    return 0;
}