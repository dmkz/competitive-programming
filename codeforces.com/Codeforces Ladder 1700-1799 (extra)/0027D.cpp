/*
    Problem: 27D. Ring Road 2
    
    Solution: constructive, graphs, dfs, bipartition, O(m^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

struct Edge {
    int fi, se;
    
    Edge(int fi_ = 0, int se_ = 0) : fi(std::min(fi_, se_)), se(std::max(fi_, se_)) { }
};

std::string solve(const int nEdges, const std::vector<Edge>& edges) {
    std::vector<std::vector<int>> next(nEdges);
    for (int i = 0; i < nEdges; ++i) {
        for (int j = i+1; j < nEdges; ++j) {
            auto ei = edges[i];
            auto ej = edges[j];
            if (
                (ei.fi < ej.fi && ej.fi < ei.se && 
                !(ei.fi <= ej.se && ej.se <= ei.se)) ||
                (ei.fi < ej.se && ej.se < ei.se && 
                !(ei.fi <= ej.fi && ej.fi <= ei.se))) 
            {
                next[i].push_back(j);
                next[j].push_back(i);
            }
        }
    }
    bool isBipartite = true;
    std::string color(nEdges, '?');
    std::function<void(int,int)> visit = [&](int u, int p) {
        for (int v : next[u]) {
            if (v == p) { continue; }
            if (color[v] == '?') {
                color[v] = char('i' + 'o' - color[u]);
                visit(v, u);
            } else if (color[v] == color[u]) {
                isBipartite = false;
            }
        }
    };
    for (int i = 0; i < nEdges; ++i) {
        if (color[i] == '?') {
            color[i] = 'i';
            visit(i, 0);
        }
    }
    return isBipartite ? color : "Impossible";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        std::vector<Edge> edges;
        for (int i = 0, u, v; i < nEdges; ++i) {
            std::cin >> u >> v;
            edges.push_back(Edge(u,v));
        }
        std::cout << solve(nEdges, edges) << std::endl;
    }
    return 0;
}