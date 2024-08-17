#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
void setmin(auto &x, const auto &y) {
    if (x > y) x = y;
}
using vi = std::vector<int>;
using pii = std::pair<int, int>;
using vpii = std::vector<pii>;
const int inf = (int)1e9+7;
struct DSU {
    
    vi sz, par, minTime;
    
    DSU(int n)
        : sz(n+1, 1)
        , par(n+1)
        , minTime(n+1, inf)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    int getPar(int u) {
        return (u == par[u] ? u :
            ([&]()
            {   // эвристика сжатия путей + обновление минимума на пути после
                // переподвершивания к новому корню
                int pu = getPar(par[u]);
                setmin(minTime[u], minTime[par[u]]);
                return par[u] = pu;
            }()));
    }
    
    void connect(int u, int v, int currTime) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        // присоединять "v" к "u"
        // мы точно знаем, что они не соединены друг с другом
        bool inU = isConnected(1, u);
        bool inV = isConnected(1, v);
        if (inU && !inV) {
            // вершина 1 была в множестве u
            // множество v упадёт в это время:
            minTime[v] = currTime;
        }
        if (inV && !inU) {
            // вершина 1 была в множестве v
            // множество u упадёт в это время:
            minTime[u] = currTime;
            // важно: присоединяем множество, в котором нет 1, к множеству, в котором она есть
            std::swap(u, v);
        }
        sz[u] += sz[v];
        par[v] = u;
    }
    
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;    
    // читаем все рёбра
    vi left(1+n), right(1+n);
    std::vector<pii> allConnections;
    for (int i = 1; i <= n; i++) {
        std::cin >> left[i] >> right[i];
        if (left[i] != -1)
            allConnections.push_back({i, 1});
        if (right[i] != -1)
            allConnections.push_back({i, 2});
    }
    // читаем запросы
    vpii queries(q);
    for (auto &[p,h] : queries)
        std::cin >> p >> h;
    // создаём систему неперескающихся множеств
    DSU dsu(n); // 1-индексакция
    {   // вырезаем рёбра, которые есть в запросах - их добавим позже
        vpii sortedQueries = queries;
        std::sort(all(sortedQueries));
        // соединяем по рёбрам, которые никогда не будут разрезаны
        
        for (auto &[p,h] : allConnections)
            // если ребра нет в запросе
            if (!std::binary_search(all(sortedQueries), pii(p,h)))
                // тогда мы его проведём
                dsu.connect(p, (h == 1 ? left[p] : right[p]), +inf);
    }
    // начинаем обрабатывать запросы
    vi answer(1+n, inf);
    for (int u = 1; u <= n; u++)
        // если вершина "u" никогда не упадёт, то ответ -1:
        if (dsu.isConnected(1, u))
            answer[u] = -1;
    // обрабатываем запросы в обрабатном порядке: вместо разрезания и связываем
    std::reverse(all(queries));
    int currTime = isz(queries);
    for (const auto &[p, h] : queries)
        dsu.connect(p, (h == 1 ? left[p] : right[p]), --currTime);
    // выводим ответы:
    for (int currVert = 1; currVert <= n; currVert++) {
        // ответ для вершины currVert это минимум на пути до корня:
        // минимальный момент времени когда она упадёт
        dsu.getPar(currVert); // сжимаем путь
        int answ = dsu.minTime[currVert]; // извлекаем ответ
        std::cout << (answ == inf ? -1 : answ) << "\n";
    }
}
