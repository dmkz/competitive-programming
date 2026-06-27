// максимальный поток, жадные алгоритмы
// Задача: H, Вердикт: ОК, Время: 48ms, Память: 2.02Mb
#include <bits/stdc++.h>

using ll = long long;
const int INF = (int)1e9+7;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

struct Graph {

    int n, s, t;

    vvi cost, flow;
    
    vi pointer, dist;

    Graph(int n_, int s_, int t_) : n(n_), s(s_), t(t_) {
        cost.assign(n, vi(n,0));
        flow.assign(n, vi(n,0));
        pointer.assign(n, 0);
        dist.assign(n,-1);
    }
    
    void add_edge(int u, int v, int cost_) {
        cost[u][v] = cost_;
    }
    
    bool bfs() {
        dist.assign(n, -1);
        std::queue<int> queue;
        queue.push(s);
        dist[s] = 0;
        while (!queue.empty()) {
            auto u = queue.front(); queue.pop();
            for (int v = 0; v < n; ++v) {
                if (dist[v] == -1 && flow[u][v] < cost[u][v]) {
                    dist[v] = dist[u] + 1;
                    queue.push(v);
                }
            }
        }
        return dist[t] != -1;
    }
    
    int dfs(int u, int value) {
        if (!value) return 0;
        if (u == t) return value;
        for (int& v = pointer[u]; v < n; ++v) {
            if (dist[v] != dist[u]+1) continue;
            int pushed = dfs(v, std::min(value, cost[u][v] - flow[u][v]));
            if (pushed) {
                flow[u][v] += pushed;
                flow[v][u] -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int dinic() {
        int value = 0, pushed;
        while (bfs()) {
            pointer.assign(n,0);
            while ((pushed = dfs(s, INF))) {
                value += pushed;
            }
        }
        return value;
    }
    
};

struct Station {
    int x, y, s;
};
struct Office {
    int x, y, e, r;
    
    bool includes(int x1, int y1) const {
        int dx = x - x1, dy = y - y1;
        return dx * 1LL * dx + dy * 1LL * dy <= r * 1LL * r;
    }
    
    bool includes(const Station &st) const {
        return includes(st.x, st.y);
    }
};
void solve() {
    // чтение данных:
    int n, m; std::cin >> n >> m;
    std::vector<Office> offices(n);
    for (auto &[x,y,e,r] : offices)
        std::cin >> x >> y >> e >> r;
    std::vector<Station> stations(m);
    for (auto &[x,y,s] : stations)
        std::cin >> x >> y >> s;
    // МТС ворует все самокаты:
    for (auto &[x,y,s] : stations)
        if (offices[0].includes(x, y)) {
            offices[0].e += s;
            s = 0;
        }
    const int MTS = offices[0].e;
    // Строим транспортную сеть
    const int nVert = 1 + m + (n-1) + 1;
    const int s = 0;
    const int t = nVert - 1;
    Graph graph(nVert, s, t);
    // проводим рёбра между станциями и офисами:
    vi count(m);
    for (int i = 0; i < m; i++)
        for (int j = 1; j < n; j++)
            if (offices[j].includes(stations[i])) {
                graph.add_edge(1 + i, 1 + m + j - 1, INF);
                count[i]++;
            }
    // проводим рёбра к станциям:
    int total{};
    for (int i = 0; i < m; i++)
        if (count[i]) {
            int cost = stations[i].s;
            graph.add_edge(s, 1 + i, cost);
            total += cost;
        }
    // проводим рёбра из офисов:
    for (int i = 1; i < n; i++) {
        const int cost = MTS - offices[i].e;
        if (cost < 0) {
            std::cout << "0\n";
            return;
        }
        graph.add_edge(1 + m + i - 1, t, cost);
    }
    // ищем поток + выводим ответ:
    std::cout << (graph.dinic() == total) << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
