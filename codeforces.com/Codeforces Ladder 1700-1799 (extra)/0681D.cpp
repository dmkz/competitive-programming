/*
    Problem: 681D. Gifts by the List
    
    Solution: constructive, trees, topological sorting, DFS, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cassert>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

vi solve(const int nVert, const vvi &next, const vi &want) {
    // Topological sorting:
    vi order, visited(1+nVert,0);
    std::function<void(int,int)> topsort = [&](int u, int p) {
        if (visited[u]) return;
        visited[u] = 1;
        for (int v : next[u]) {
            if (v == p) continue;
            topsort(v, u);
        }
        order.push_back(u);
    };
    for (int u = 1; u <= nVert; ++u) {
        topsort(u,0);
    }
    // Choose only needed vertices:
    vi need(1+nVert);
    for (int i = 1; i <= nVert; ++i) {
        need[want[i]] = true;
    }
    {
        vi temp = order; order.clear();
        for (int u : temp) {
            if (need[u]) { order.push_back(u); }
        }
    }
    // Check that correct answer was costructed:
    vi what(1+nVert);
    std::function<void(int,int,int)> mark = [&](int u, int p, int w) {
        assert(!what[u]);
        what[u] = w;
        for (int v : next[u]) {
            if (v == p || what[v]) continue;
            mark(v,u,w);
        }
    };
    for (int u : order) {
        mark(u,0,u);
    }
    for (int u = 1; u <= nVert; ++u) {
        if (what[u] != want[u]) return vi{};
    }
    return order;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        vi want(1+nVert);
        vvi next(1+nVert);
        for (int i = 0, p, q; i < nEdges; ++i) {
            std::cin >> p >> q;
            next[p].push_back(q);
        }
        for (int i = 1; i <= nVert; ++i) {
            std::cin >> want[i];
        }
        vi answ = solve(nVert, next, want);
        if (answ.empty()) {
            std::cout << -1 << std::endl;
        } else {
            std::cout << answ.size() << '\n';
            for (auto it : answ) {
                std::cout << it << '\n';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}