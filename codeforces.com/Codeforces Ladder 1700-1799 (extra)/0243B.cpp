/*
    Problem: 243B. Hydra
    
    Solution: graphs, sorting, binary search, O(E * sqrt(V) * log(V))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()

struct Edge {
    int u, v;
    
    Edge(int u_ = 0, int v_ = 0) : u(std::min(u_,v_)), v(std::max(u_,v_)) { }
};

bool operator<(const Edge& a, const Edge& b) {
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int NMAX = (int)1e5;

namespace Used { int data[1+NMAX]; };

bool difference(vvi& next, int& u, int& v, int nH, int nT, vi& fi, vi& se, vi& same) {
    if (next[u].size() > next[v].size()) {
        return difference(next, v, u, nT, nH, se, fi, same);
    }
    fi.clear(); se.clear(); same.clear();
    // size[u] < size[v];
    auto &vec_u = next[u];
    auto &vec_v = next[v];
    // Fill arrays `fi` and `same`. 
    // fi = {vertices in list[u], but not in list[v]}; 
    // same = {vertices in both lists}
    for (auto vert : vec_u) {
        if (vert == v || vert == u) { continue; }
        if (std::binary_search(all(vec_v), vert)) {
            same.push_back(vert);
        } else {
            fi.push_back(vert);
        }
    }
    if ((int)(fi.size() + same.size()) < nH) { return false; }
    // Mark used vertices in array `used`:
    for (auto &it : fi)   { Used::data[it] = 1; }
    for (auto &it : same) { Used::data[it] = 3; }
    // Fill array 'se'. se = {vertices in list[v], but not in list[u]}
    for (auto vert : vec_v) {
        if (vert == u || vert == v) { continue; }
        if (Used::data[vert] == 0) { se.push_back(vert); }
        if ((int)(fi.size() + se.size() + same.size()) >= nH + nT &&
            (int)(fi.size() + same.size()) >= nH && (int)(se.size()+same.size()) >= nT) 
        { break; }
    }
    // Check if answer was found:
    bool ok = ((int)(fi.size() + se.size() + same.size()) >= nH + nT &&
            (int)(fi.size() + same.size()) >= nH && (int)(se.size()+same.size()) >= nT);
    // Unmark used vertices:
    for (auto &it : fi)   { Used::data[it] = 0; }
    for (auto &it : same) { Used::data[it] = 0; }
    if (!ok) { return false; }
    // Move `same` vertices in `fi` and `se` arrays:
    while (!same.empty()) {
        if ((int)fi.size() < nH) { fi.push_back(same.back()); }
        else { se.push_back(same.back()); }
        same.pop_back();
    }
    return ok;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nV, nE, nH, nT;
    while (std::cin >> nV >> nE >> nH >> nT) {
        // Input & sort edges:
        std::vector<Edge> edges;
        for (int i = 0, u, v; i < nE; ++i) 
        { std::cin >> u >> v; edges.push_back(Edge(u,v)); }
        std::sort(all(edges));
        // Creating lists with adjacents, sort each list:
        vvi next(1+nV);
        for (auto &e : edges) 
        { next[e.u].push_back(e.v); next[e.v].push_back(e.u); }
        for (int u = 1; u <= nV; ++u) { std::sort(all(next[u])); }
        // Check each edge if this edge is hidra`s body:
        vi fi, se, same; int u = 6, v = 7;
        bool ok = false;
        if (!ok) {
            for (auto &e : edges) {
                fi.clear(); se.clear();
                u = e.u, v = e.v;
                if (difference(next, u, v, nH, nT, fi, se, same)) {
                    ok = true;
                    break;
                }
            }
        }
        // Revert all edges, sort and check again:
        if (!ok) {
            for (auto &e : edges) { std::swap(e.u, e.v); }
            std::sort(all(edges));
            for (auto &e : edges) {
                fi.clear(); se.clear();
                u = e.u, v = e.v;
                if (difference(next, u, v, nH, nT, fi, se, same)) {
                    ok = true;
                    break;
                }
            }
        }
        // Output answer:
        if (ok) {
            std::cout << "YES\n";
            std::cout << u << ' ' << v << "\n";
            assert((int)fi.size() >= nH);
            fi.resize(nH);
            for (auto &it : fi) { std::cout << it << ' '; }
            std::cout << "\n";
            assert((int)se.size() >= nT);
            se.resize(nT);
            for (auto &it : se) { std::cout << it << ' '; }
            std::cout << "\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}