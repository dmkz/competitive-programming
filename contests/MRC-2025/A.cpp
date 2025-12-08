// Задача: A, Вердикт: OK, Время: 227ms, Память: 23.38Mb 
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
// шаблоны
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using tiii = std::tuple<int,int,int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vtiii = std::vector<tiii>;
using vs = std::vector<std::string>;
int lowpos(const auto &v, const auto &x) {
    return int(std::lower_bound(all(v), x) - v.begin());
}
// решение
bool solve() {
    // читаем диагонали (главные и побочные) и, пересекая их середины,
    // строим из них крестики:
    int n, m; std::cin >> n >> m;
    vtiii a(n), b(m);
    std::map<int, pii> columnByY;
    for (auto &[x,y,z] : a) {
        std::cin >> x >> y >> z;
        columnByY[y] = {x, z};
    }
    std::vector<std::pair<pii, pii>> cross;
    std::vector<pii> edges;
    vpii vertices;
    // для каждой побочной диагонали ищем главую диагональ и объединяем их в крест:
    for (auto &[u,v,w] : b) {
        std::cin >> u >> v >> w;
        if (auto it = columnByY.find(v); it != columnByY.end()) {
            auto [x, z] = it->second;
            // сам крест:
            // x   u
            //   y
            // w   z
            // будет соединять два столбца ориентированным ребром:
            // {x, w} --> {u, z}
            cross.push_back({{x, w},{u, z}});
            vertices.emplace_back(x, w);
            vertices.emplace_back(u, z);
        }
    }
    // сортируем вершины, сжимаем координаты, строим граф
    std::sort(all(vertices));
    vertices.erase(std::unique(all(vertices)), vertices.end());
    int nVert = isz(vertices);
    vvi adj(nVert);
    for (const auto &[from, to] : cross) {
        int u = lowpos(vertices, from);
        int v = lowpos(vertices, to);
        adj[u].push_back(v);
    }
    // запускаем поиск цикла
    bool foundCycle = false;
    vi color(nVert);
    std::function<void(int)> dfs = [&](int u) {
        if (color[u] == 2)
            return;
        assert(color[u] == 0);
        color[u] = 1;
        for (int v : adj[u])
            if (color[v] == 1) foundCycle = true;
            else dfs(v);
        color[u] = 2;
    };
    for (int u = 0; u < nVert; u++)
        dfs(u);
    return foundCycle;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << vs{"NO","YES"}[solve()] << "\n";
}