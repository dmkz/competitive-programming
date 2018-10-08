/*
    Problem: 574B. Bear and Three Musketeers
    
    Solution: sorting, graph, O(m^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

const int INF = (int)1e9+1;

struct Edge {
    int u, v;
    
    Edge(int u_ = 0, int v_ = 0) : u(std::min(u_,v_)), v(std::max(u_,v_)) { }
};

bool operator<(const Edge& a, const Edge& b) {
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

int main() {
    // Input:
    int nVert, nEdges;
    scanf("%d %d", &nVert, &nEdges);
    std::vector<Edge> edges;
    std::vector<int> size(1+nVert);
    for (int i = 0; i < nEdges; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        edges.push_back(Edge(u,v));
        size[u]++; size[v]++;
    }
    // Mark edges:
    std::vector<bool> is((nVert+1)*(nVert+1), false);
    for (auto& e : edges) {
        is[e.u * (nVert+1) + e.v] = 1;
    }
    std::sort(edges.begin(), edges.end());
    // Algo: brute pairs (u1,v1) and (u2, v2) and from edges:
    int min = INF;
    for (int i = 0; i < nEdges; ++i) {
        const auto& ei = edges[i];
        for (int j = i+1; j < nEdges; ++j) {
            const auto& ej = edges[j];
            if (ej.u == ei.u ) {
                int u = ej.v, v = ei.v;
                if (u > v) std::swap(u,v);
                if (is[u * (nVert+1) + v]) {
                    min = std::min(min, size[ei.u]+size[u]+size[v]-6);
                }
            } else if (ej.u == ei.v) {
                int u = ei.u, v = ej.v;
                if (u > v) std::swap(u,v);
                if (is[u * (nVert+1) + v]) {
                    min = std::min(min, size[ei.v]+size[u]+size[v]-6);
                }
            }
        }
    }
    if (min == INF) min = -1;
    printf("%d", min);
    return 0;
}