/*
    Problem: 400D. Dima and Bacteria
    
    Solution: bfs, graphs, connected components, Floyd-Warshall algorithm, shortest path, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

struct Edge {
    int u, v, w;
};

const int INF = (int)1e9+1;

int main() {
    // Input vertices and calculate type of each vertex:
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges, nTypes;
    std::cin >> nVert >> nEdges >> nTypes;
    std::vector<int> cnt(1+nTypes);
    for (int i = 1; i <= nTypes; ++i) {
        std::cin >> cnt[i];
    }
    std::vector<int> sum(1+nTypes);
    for (int i = 1; i <= nTypes; ++i) {
        sum[i] = sum[i-1] + cnt[i];
    }
    std::vector<int> vType(1+nVert);
    std::vector<std::vector<int>> tList(1+nTypes);
    for (int v = 1; v <= nVert; ++v) {
        vType[v] = int(std::lower_bound(sum.begin(), sum.end(), v) - sum.begin());
        tList[vType[v]].push_back(v);
    }
    // Input edges:
    std::vector<std::vector<Edge>> edges(1+nVert);
    for (int i = 0, u, v, w; i < nEdges; ++i) {
        std::cin >> u >> v >> w;
        edges[u].push_back(Edge{u,v,w});
        edges[v].push_back(Edge{u,v,w});
    }
    // Firstly we run bfs from each vertex in graph. Graph contains only edges with cost = 0.
    std::vector<int> part(1+nVert); int nParts = 0;
    for (int v = 1; v <= nVert; ++v) {
        if (part[v]) continue;
        ++nParts;
        part[v] = nParts;
        std::queue<int> queue;
        queue.push(v);
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            for (auto& e : edges[curr]) {
                int next = e.u + e.v - curr;
                if (e.w != 0 || part[next]) continue;
                part[next] = nParts;
                queue.push(next);
            }
        }
    }
    // Check connected components:
    for (int t = 1; t <= nTypes; ++t) {
        int p = -1;
        for (int v : tList[t]) {
            if (p == -1 || p == part[v]) {
                p = part[v];
            } else {
                std::cout << "No\n";
                return 0;
            }
        }
    }
    // Construct graph between components and run Floyd-Warshall algorithm:
    std::vector<std::vector<int>> dist(1+nTypes, std::vector<int>(1+nTypes, INF));
    for (int u = 1; u <= nVert; ++u) {
        for (auto& e : edges[u]) {
            int v = e.u + e.v - u;
            int tu = vType[u], tv = vType[v];
            dist[tu][tv] = std::min(dist[tu][tv], e.w);
            dist[tv][tu] = std::min(dist[tv][tu], e.w);
        }
    }
    for (int u = 1; u <= nTypes; ++u) {
        dist[u][u] = 0;
    }
    for (int k = 1; k <= nTypes; ++k) {
        for (int u = 1; u <= nTypes; ++u) {
            for (int v = 1; v <= nTypes; ++v) {
                if (dist[u][k] < INF && dist[k][v] < INF) {
                    dist[u][v] = std::min(dist[u][v], dist[u][k] + dist[k][v]);
                }
            }
        }
    }
    // Output answer:
    std::cout << "Yes\n";
    for (int i = 1; i <= nTypes; ++i) {
        for (int j = 1; j <= nTypes; ++j) {
            std::cout << (dist[i][j] == INF ? -1 : dist[i][j]) << ' ';
        }
        std::cout << "\n";
    }
    return 0;
}