/*
    Problem: 721C. Journey
    
    Solution: dynamic programming, graphs, topsort, O(n * m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

struct Edge {
    int vertex, time;
};

void remin(int& a, int b) {
    if (a > b) a = b;
}

int main() {
    int n, m, time;
    std::cin >> n >> m >> time;
    std::vector<std::vector<Edge>> next(1+n), prev(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v, t; std::cin >> u >> v >> t;
        next[u].push_back(Edge{v,t});
        prev[v].push_back(Edge{u,t});
    }
    
    const int NMAX = 5000;
    static int minTime[1+NMAX][1+NMAX]; // [vertex][count]
    std::fill(&minTime[0][0],&minTime[0][0]+(1+NMAX)*(1+NMAX), time+1);
    std::vector<int> order, visited(n);
    std::function<void(int)> topsort = [&](int u) {
        if (visited[u]) return;
        visited[u] = 1;
        for (auto& e : next[u]) {
            topsort(e.vertex);
        }
        order.push_back(u);
    };
    for (int i = 1; i <= n; ++i) topsort(i);
    std::reverse(order.begin(), order.end());
    minTime[1][1] = 0;
    for (int u : order) {
        for (int k = 0; k < n; ++k) {
            for (auto& e : next[u]) {
                remin(minTime[e.vertex][k+1], minTime[u][k]+e.time);
            }
        }
    }
    int count = 0, vert = n;
    for (int k = 0; k <= n; ++k) {
        if (minTime[n][k] <= time) {
            count = k;
        }
    }
    std::vector<int> answ{n};
    for (int cnt = count; cnt > 1; --cnt) {
        for (auto& e : prev[vert]) {
            if (minTime[vert][cnt] - e.time == minTime[e.vertex][cnt-1]) {
                answ.push_back(e.vertex);
                vert = e.vertex;
                break;
            }
        }
    }
    std::reverse(answ.begin(), answ.end());
    std::cout << (int)answ.size() << "\n";
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}