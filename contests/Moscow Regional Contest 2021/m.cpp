#include <bits/stdc++.h>
template<typename T> // очередь с приоритетами на минимум:
using PQLess = std::priority_queue<T,std::vector<T>,std::greater<T>>;
using ld = long double;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем + строим граф:
    int n,m,T; std::cin >> n >> m >> T;
    std::vector<std::vector<std::pair<int,ld>>> adj(1+n);
    while (m --> 0) {
        int u, v, l, c;
        std::cin >> u >> v >> l >> c;
        ld cost = std::sqrt(l*1.0L*c);
        adj[u].emplace_back(v,cost);
        adj[v].emplace_back(u,cost);
    }
    // запускаем дейкстру:
    PQLess<std::pair<ld,int>> pq;
    pq.push({0,1});
    std::vector<ld> dist(1+n, 1e18L);
    while (pq.size()) {
        auto [d,u] = pq.top(); pq.pop();
        if (dist[u] <= d) continue;
        dist[u] = d;
        for (auto &[v,cost] : adj[u])
            pq.push({d+cost,v});
    }
    // выводим ответ:
    std::cout << std::setprecision(12) << std::fixed << dist[n] * dist[n] / T << std::endl;
    return 0;
}