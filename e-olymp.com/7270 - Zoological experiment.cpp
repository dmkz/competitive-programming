/*
    Problem: 7270 - Zoological experiment
    
    Solution: probability, Markov's chains, graphs, dfs, matrix multipliction, O(n^3 * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <functional>
#include <cassert>

typedef long double Real;

struct Matrix {

    int nRows, nCols;

    std::vector<std::vector<Real>> data;
    
    Matrix(const int nRows_, const int nCols_) : nRows(nRows_), nCols(nCols_) {
        data.resize(nRows);
        for (auto &row : data) { row.resize(nCols); }
    }
    
    Matrix& operator=(const Matrix& other) {
        nRows = other.nRows;
        nCols = other.nCols;
        data = other.data;
        return *this;
    }
    
    Matrix transpose() const {
        Matrix res(nCols, nRows);
        for (int row = 0; row < nRows; ++row) {
            for (int col = 0; col < nCols; ++col) {
                res(col,row) = data[row][col];
            }
        }
        return res;
    }
    
    Real& operator()(int row, int col) {
        assert(0 <= row && row < (int)data.size());
        assert(0 <= col && col < (int)data[row].size());
        return data[row][col];
    }
    
    const Real& operator()(int row, int col) const {
        assert(0 <= row && row < (int)data.size());
        assert(0 <= col && col < (int)data[row].size());
        return data[row][col];
    }
    
    Matrix operator*(const Matrix& other) const {
        auto M = other.transpose();
        Matrix res(nRows, M.nRows);
        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < M.nRows; ++j) {
                Real sum = 0;
                for (int k = 0; k < nCols; ++k) {
                    sum += data[i][k] * M(j,k);
                }
                res(i,j) = sum;
            }
        }
        return res;
    }
};

typedef std::pair<int,int> pii;

Real solve(const int nVert, const std::vector<pii>& edges, const int s, const int t) {
    std::vector<std::vector<int>> next(1+nVert);
    for (auto & e : edges) {
        int u = e.first, v = e.second;
        next[u].push_back(v);
        next[v].push_back(u);
    }
    std::vector<int> part(1+nVert), color(1+nVert), isBipartite{1};
    int nParts = 0; 
    std::function<void(int,int)> dfs = [&](int u, int p) {
        for (int v : next[u]) {
            if (v == p) { continue; }
            if (!part[v]) {
                color[v] = 3 - color[u];
                part[v] = part[u];
                dfs(v, u);
            } else if (color[u] == color[v]) {
                assert(part[u] < (int)isBipartite.size());
                isBipartite[part[u]] = false;
            }
        }
    };
    for (int u = 1; u <= nVert; ++u) {
        if (!part[u]) {
            isBipartite.push_back(true);
            nParts++;
            part[u] = nParts;
            assert(part[u] < (int)isBipartite.size());
            color[u] = 1;
            dfs(u,0);
        }
    }
    Real answ = 0;
    if (part[s] != part[t]) {
        return answ;
    }
    assert(part[s] < (int)isBipartite.size());
    if (isBipartite[part[s]] && color[s] != color[t]) {
        return answ;
    }
    Matrix M(1+nVert, 1+nVert);
    for (int u = 1; u <= nVert; ++u) {
        for (int v : next[u]) {
            M(u,v) = Real(1) / next[u].size();
        }
    }
    while (true) {
        auto was = M;
        M = M * M;
        Real sum = 0;
        for (int row = 0; row <= nVert; ++row) {
            for (int col = 0; col <= nVert; ++col) {
                Real delta = M(row,col) - was(row,col);
                sum += delta * delta;
            }
        }
        if (sum < 1e-9) {
            break;
        }
    }
    if (s == t && next[s].size() == 0u) {
        return Real(1);
    }
    Matrix vec1(1, 1+nVert), vec2(1, 1+nVert);
    vec1(0, s) = 1;
    vec2(0, next[s].front()) = 1;
    vec1 = vec1 * M;
    vec2 = vec2 * M;
    for (int u = 0; u <= nVert; ++u) { answ += (vec1(0, u) * vec1(0, u) + vec2(0, u) * vec2(0, u)) / 2; }
    return answ;
}

int main() {
    int nVert, nEdges;
    std::cin >> nVert >> nEdges;
    std::vector<pii> edges(nEdges);
    for (auto &p : edges) { std::cin >> p.first >> p.second; }
    int s, t; std::cin >> s >> t;
    std::cout << std::fixed << std::setprecision(9) << solve(nVert, edges, s, t) << std::endl;
    return 0;
}