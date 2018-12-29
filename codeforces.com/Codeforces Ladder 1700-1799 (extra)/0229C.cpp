/*
    Problem: 229C. Triangles
    
    Solution: combinatorics, graphs, math, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

struct Edge { int u, v; };

auto solve(const int nVert, const std::vector<Edge>& edges) {
    auto answ = 1LL * nVert * (nVert-1) * (nVert-2) / 6LL;
    std::vector<int> count(1+nVert, 1);
    for (const auto &e : edges) {
        answ -= nVert - count[e.u]++ - count[e.v]++;
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        std::vector<Edge> edges(nEdges);
        for (auto &e : edges) {
            std::cin >> e.u >> e.v;
        }
        std::cout << solve(nVert, edges) << std::endl;
    }
    return 0;
}