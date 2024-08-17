#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

using vi = std::vector<int>;
using ll = long long;

struct DSU {
    vi sz, par;
    
    DSU(int n) : sz(n+1, 1), par(n+1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    int getPar(int u) {
        return (par[u] == u ? u : par[u] = getPar(par[u])); 
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
    }
    
    int getSize(int u) {
        return sz[getPar(u)];
    }
   
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    ll s;
    int n, m; std::cin >> n >> m >> s;
    // читаем рёбра (вес, u, v, номер)
    std::vector<std::tuple<int,int,int,int>> edges(m);
    for (int i = 1; auto &[w, u, v, id] : edges) {
        std::cin >> u >> v >> w;
        id = i++;
    }
    // сортируем по убыванию весов
    std::sort(all(edges), std::greater<>());
    // запускаем алгоритм поиска максимального остовного дерева
    // запоминаем веса и номера рёбер, которые в него не вошли
    DSU dsu(n);
    std::vector<std::pair<int, int>> canErase;
    for (const auto &[w, u, v, id] : edges) {
        if (dsu.isConnected(u, v)) {
            // ребро u <-> v весом w и номером id можем удалить
            canErase.emplace_back(w, id);
            continue;
        }
        dsu.connect(u, v);        
    }
    // набираем как можно больше минимальных ребёр которые мы можем удалить:
    std::vector<int> answ;
    while (isz(canErase) && canErase.back().first <= s) {
        answ.push_back(canErase.back().second);
        s -= canErase.back().first;
        canErase.pop_back();
    }
    // выводим номера выбранных ребёр:
    std::sort(all(answ));
    std::cout << isz(answ) << "\n";
    for (auto it : answ)
        std::cout << it << ' ';
    std::cout << "\n";
}
