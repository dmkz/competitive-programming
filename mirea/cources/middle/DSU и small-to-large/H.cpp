#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int,int>;

void setmax(auto &x, auto y) {
    if (x < y) x = y;
}

struct DSU {
    // внутри DSU храним центр и диаметр для каждого дерева:
    vector<int> center, diameter;
    
    DSU(int n) : center(1+n), diameter(1+n)
    {
        for (int u = 1; u <= n; u++)
            center[u] = u;
    }
    
    int getCenter(int u) {
        return u == center[u] ? u : center[u] = getCenter(center[u]);
    }
    
    void connect(int u, int v) {
        u = getCenter(u), v = getCenter(v);
        if (u == v) return;
        int du = (diameter[u]+1)/2;
        int dv = (diameter[v]+1)/2;
        if (du < dv) swap(u,v);
        setmax(diameter[u],du+1+dv);
        center[v] = u;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vvi adj(1+n);
    while (m --> 0) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    auto bfs = [&](int s) {
        // s - стартовая вершина
        // функция осуществяет bfs из стартовой вершины и находит расстояния от s
        // до всех остальных достижимых вершин
        map<int,int> dist;
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!dist.count(v)) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    };
    auto findMax = [&](const auto &distMap) {
        // distMap - это map<int,int>, где ключ - вершина, значение - расстояние
        // функция ищет вершину с максимальным расстоянием. возвращает пару (вершина, расстояние)
        pii best{0,0};
        for (auto &[vert, dist] : distMap) {
            setmax(best,pii(dist,vert));
        }
        return pii(best.second, best.first);
    };
    // сначала нужно заполнить dsu: найти центр и диаметр для каждого дерева
    DSU dsu(n);
    vi used(1+n);
    for (int u = 1; u <= n; u++) {
        if (used[u]) continue;
        // --- ЗДЕСЬ ИЩЕМ ДИАМЕТР И ЦЕНТР В ДЕРЕВЕ ---
        // найдём расстояния от вершины u до всех вершин в её компоненте:
        auto distFromU = bfs(u);
        // теперь нужно найти максимум:
        auto [v1, d1] = findMax(distFromU);
        // запустим bfs из v1:
        auto distFromV1 = bfs(v1);
        // и найдём максимум там:
        auto [v2, diameter] = findMax(distFromV1);
        // теперь нужно найти расстояния от v2 для поиска центра:
        auto distFromV2 = bfs(v2);
        // теперь нужно найти центр, зная все расстояния от концом диаметра до всех вершин:
        int center = -1, bestDiff = n;
        for (auto &[v, dv1] : distFromV1) {
            auto dv2 = distFromV2[v];
            if (abs(dv1-dv2) < bestDiff) {
                bestDiff = abs(dv1-dv2);
                center = v;
            }
        }
        assert(center != -1);
        // инициализируем dsu для этой компоненты:
        for (auto &[v, _] : distFromV1) {
            dsu.center[v] = center;
            used[v] = 1;
        }
        dsu.diameter[center] = diameter;
    }
    // обрабатываем все запросы:
    while (q --> 0) {
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            cout << dsu.diameter[dsu.getCenter(x)] << '\n';
        } else {
            int y; cin >> y;
            dsu.connect(x,y);
        }
    }
    return 0;
}