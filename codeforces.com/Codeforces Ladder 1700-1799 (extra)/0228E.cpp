/*
    Problem: 228E. The Road to Berland is Paved With Good Intentions
    
    Solution: matrices, gauss elimination, linear algebra, graphs, O(n^2*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>

struct Edge {int u, v, w; };

bool solve(const int nVertices, const int nEdges, const std::vector<Edge>& edges, std::vector<int>& answ) {
    std::vector<std::vector<int>> matrix(1+nEdges, std::vector<int>(1+nVertices+1));
    for (int i = 1; i <= nEdges; ++i) {
        const auto &e = edges[i-1];
        matrix[i][e.u] = 1;
        matrix[i][e.v] = 1;
        matrix[i].back() = 1 - e.w;
    }
    for (int col = 1, leadRow = 1; col <= nVertices; ++col) {
        {
            int r = leadRow;
            while (r <= nEdges && matrix[r][col] == 0) ++r;
            if (r > nEdges) { continue; }
            std::swap(matrix[leadRow], matrix[r]);
        }
        for (int r = leadRow+1; r <= nEdges; ++r) {
            if (matrix[r][col]) {
                for (int k = col; k <= nVertices+1; ++k) {
                    (matrix[r][k] += matrix[leadRow][k]) %= 2;
                }
            }
        }
        ++leadRow;
    }
    // if rank > nVertices = no solution
    while (!matrix.empty() && matrix.back() == std::vector<int>(1+nVertices+1, 0)) {
        matrix.pop_back();
    }
    if (matrix.empty()) {
        return true;
    }
    
    if (matrix.back().back() == 1 && std::accumulate(matrix.back().begin(), matrix.back().end(), 0) == 1) {
        return false;
    }
    assert(matrix.size() <= 1+nVertices);
    while (matrix.size() > 1u) {
        int pos = 0;
        while (pos < (int)matrix.back().size() && !matrix.back()[pos]) { ++pos; }
        assert(pos < (int)matrix.back().size());
        answ[pos] = matrix.back().back();
        for (int k = pos+1; k <= nVertices; ++k) {
            answ[pos] = (answ[pos] + answ[k] * matrix.back()[k]) % 2;
        }
        matrix.pop_back();
    }
    return true;
}

int main() {
    int nVertices, nEdges;
    while (std::cin >> nVertices >> nEdges) {
        std::vector<Edge> edges(nEdges);
        for (auto &e : edges) { std::cin >> e.u >> e.v >> e.w; }
        std::vector<int> answ(1+nVertices, 1);
        bool can = solve(nVertices, nEdges, edges, answ);
        if (!can) {
            std::cout << "Impossible" << std::endl;
            continue;
        }
        std::vector<int> tmp;
        for (int u = 1; u <= nVertices; ++u) {
            if (answ[u]) { tmp.push_back(u); }
        }
        std::cout << tmp.size() << std::endl;
        for (auto it : tmp) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}