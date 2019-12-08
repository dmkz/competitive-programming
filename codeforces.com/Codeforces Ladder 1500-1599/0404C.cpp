/*
    Problem: 404C. Restore Graph
    Solution: graphs, constructive
*/
#include <iostream>
#include <vector>
#include <algorithm>
struct Edge { int a, b; };
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert, mxDegree;
    std::cin >> nVert >> mxDegree;
    
    std::vector<std::vector<int>> distList(nVert);
    for (int i = 0; i < nVert; ++i) {
        int dist; std::cin >> dist;
        if (dist >= nVert) {
            std::cout << -1; return 0;
        }
        distList[dist].push_back(i);
    }
    while (distList.back().empty()) distList.pop_back();
    if (distList.empty() || distList.front().size() != 1u) {
        std::cout << -1; return 0;
    }
    std::vector<Edge> edges;
    std::vector<int> degree(nVert);
    for (int d = 1; d < (int)distList.size(); ++d) {
        if (distList[d-1].empty()) {
            std::cout << -1; return 0;
        }
        int prev = 0;
        for (auto& next : distList[d]) {
            int curr = distList[d-1][prev];
            edges.push_back(Edge{curr+1, next+1});
            degree[curr]++;
            degree[next]++;
            (++prev) %= (int)distList[d-1].size();
        }
    }
    for (int i = 0; i < nVert; ++i) {
        if (degree[i] > mxDegree) {
            std::cout << -1;
            return 0;
        }
    }
    std::cout << edges.size() << '\n';
    for (auto& e : edges) {
        std::cout << e.a << ' ' << e.b << '\n';
    }
    return 0;
}