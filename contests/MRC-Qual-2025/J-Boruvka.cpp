#include <bits/stdc++.h>
#define int int64_t
using namespace std;
using tiii = tuple<int,int,int>;
using pii = pair<int,int>;

// Задача: J, Вердикт: OK, Время: 146ms, Память: 9.29Mb

// В задаче требуется найти вес минимального остовного дерева (MST) во взвешанном
// графе. Будем искать его с помощью алгоритма Борувки. Вес рёбер зависит от
// параметра "x" линейно, поэтому, если "x" может изменяться в пределах отрезка
// [L, R], то минимум по "x" достигается на концах отрезка. Найдём вес MST при
// x = L и при x = R. В качестве ответа выведем минимум из двух вариантов.

struct Edge {
    int u, v, a, b; // ребро между u и v с параметрами (a, b), вес = a + b * x
};

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        r.assign(n + 1, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

bool solve() {
// функция solve читает текущий тест и возвращает true, если прочла, иначе false
// решает задачу для текущего теста и выводит ответ на него

    // читаем количество вершин, ребёр, и границы по x:
    int n, m, l, r;
    cin >> n >> m >> l >> r;
    if (n == 0) // тесты кончились
        return false;
    
    // читаем рёбра графа и сохраняем их в массиве edges
    // edges: список рёбер в виде (u, v, a, b), вес при фиксированном x равен a + b * x
    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        edges.push_back({u, v, a, b});
    }

    // лямбда функция findAnswer находит ответ для заданного значения x
    // находим вес минимального остовного дерева алгоритмом Борувки
    auto findAnswer = [&](int x)
    {
        // алгоритм Борувки жадно повторяет следующие шаги:
        // пока есть несколько компонент, для каждой компоненты выбираем минимальное
        // исходящее из неё ребро и объединяем компоненты этими рёбрами
        DSU dsu(n);
        int components = n;
        int answ = 0;
        vector<pair<int,int>> best(n + 1); // для каждой компоненты: (вес, индекс ребра)

        while (components > 1) {
            for (int i = 1; i <= n; i++) best[i] = {LLONG_MAX, -1};

            // для каждой компоненты найдём лучшее исходящее ребро
            for (int i = 0; i < (int)edges.size(); i++) {
                const auto &e = edges[i];
                int cu = dsu.find(e.u), cv = dsu.find(e.v);
                if (cu == cv) continue;
                int w = e.a + e.b * x;
                if (w < best[cu].first) best[cu] = {w, i};
                if (w < best[cv].first) best[cv] = {w, i};
            }

            bool merged = false;
            // объединяем компоненты выбранными рёбрами
            for (int i = 1; i <= n; i++) {
                int idx = best[i].second;
                if (idx == -1) continue;
                const auto &e = edges[idx];
                int cu = dsu.find(e.u), cv = dsu.find(e.v);
                if (cu == cv) continue;
                int w = best[i].first;
                if (dsu.unite(cu, cv)) {
                    answ += w;
                    components--;
                    merged = true;
                }
            }

            // если объединений не произошло, граф может быть несвязным — выходим
            if (!merged) break;
        }
        return answ;
    };

    // в силу того, что функции на рёбрах — линейные, то минимум достигается
    // на одном из концов отрезка. Проверим x = l и x = r и выберем минимум
    cout << min(findAnswer(l), findAnswer(r)) << endl;
    return true;
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (solve());
}