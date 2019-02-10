/*
    Problem: 269C. Flawed Flow
    
    Solution: greedy, constructive, graphs, max flow reconstruction, O(n + m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

struct Edge {
    int u, v, w, direction;
    Edge(const int u_ = 0, const int v_ = 0, const int w_ = 0, const int direction_ = -1)
        : u(u_), v(v_), w(w_), direction(direction_) { }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        std::vector<Edge> edges(nEdges);
        std::vector<int> sumFlow(nVert);
        std::vector<int> currFlow(nVert);
        std::vector<bool> visited(nVert);
        std::vector<std::vector<int>> next(nVert);
        for (int i = 0; i < nEdges; ++i) {
            auto &e = edges[i];
            std::cin >> e.u >> e.v >> e.w;
            e.u--, e.v--;
            next[e.u].push_back(i);
            next[e.v].push_back(i);
            sumFlow[e.u] += e.w;
            sumFlow[e.v] += e.w;
        }
        std::queue<int> queue;
        queue.push(0);
        visited[nVert-1] = 1;
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            assert(!visited[curr]);
            visited[curr] = 1;
            for (auto eid : next[curr]) {
                auto &e = edges[eid];
                if (e.direction == -1) {
                    e.direction = (curr == e.u ? 0 : 1);
                    int v = e.u + e.v - curr;
                    currFlow[v] += e.w;
                    if (2 * currFlow[v] == sumFlow[v] && !visited[v]) {
                        queue.push(v);
                    }
                }
            }
        }
        for (auto &e : edges) { std::cout << e.direction << '\n'; }
        std::cout << std::endl;
    }
    return 0;
}