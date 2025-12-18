#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using pil = std::pair<int, ll>;
using pli = std::pair<ll, int>;
template<typename T>
using PQLess = std::priority_queue<T, std::vector<T>, std::greater<T>>;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vvi = std::vector<vi>;
void setmin(auto &x, const auto &y) { if (x > y) x = y; }

struct MinCostMaxFlow {
    struct Edge {
        int to, rev, cap;
        ll cost;
    };
    int N;
    std::vector<std::vector<Edge>> g;
    MinCostMaxFlow(int n = 0) {
        init(n);
    }
    void init(int n) {
        N = n;
        g.assign(N, {});
    }
    void addEdge(int s, int t, int cap, ll cost) {
        Edge a{t, isz(g[t]), cap, cost};
        Edge b{s, isz(g[s]), 0, -cost};
        g[s].push_back(a);
        g[t].push_back(b);
    }
    pil minCostFlow(int s, int t, int need) {
        const ll inf = (ll)1e18L;
        vl pot(N, 0), dist(N);
        vi pv(N), pe(N);
        int flow = 0;
        ll cost = 0;
        while (flow < need) {
            std::fill(all(dist), inf);
            dist[s] = 0;
            PQLess<pli> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if (d != dist[u])
                    continue;
                for (int i = 0; i < isz(g[u]); i++) {
                    const Edge &e = g[u][i];
                    if (e.cap <= 0) continue;
                    ll nd = d + e.cost + pot[u] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == inf)
                break;
            for (int u = 0; u < N; u++)
                if (dist[u] < inf)
                    pot[u] += dist[u];
            int aug = need - flow;
            for (int u = t; u != s; u = pv[u])
                setmin(aug, g[pv[u]][pe[u]].cap);
            for (int u = t; u != s; u = pv[u]) {
                Edge &e = g[pv[u]][pe[u]];
                Edge &re = g[u][e.rev];
                e.cap -= aug;
                re.cap += aug;
                cost += 1LL * aug * e.cost;
            }
            flow += aug;
        }
        return {flow, cost};
    }
};
auto findMinCostMaxFlow(int nItems, int nGroups, const vvi& cost) {
    int groupSize = nItems / nGroups;
    int rem = nItems - nGroups * groupSize;
    int S = 0; // исток
    int firstItem = 1;
    int lastItem = firstItem + nItems;
    int firstGroup  = lastItem + nGroups;
    int remainderNode = firstGroup + nGroups;
    int T = remainderNode + 1; // сток
    int nVert = T + 1; // число вершин
    MinCostMaxFlow flow(nVert);
    auto itemNode = [&](int i){ return firstItem + i; };
    auto mainGroup = [&](int g){ return lastItem + g; };
    auto extraGroup = [&](int g){ return firstGroup + g; };
    for (int i = 0; i < nItems; i++)
        flow.addEdge(S, itemNode(i), 1, 0);
    for (int i = 0; i < nItems; i++)
        for (int g = 0; g < nGroups; g++) {
            int c = cost[i][g];
            flow.addEdge(itemNode(i), mainGroup(g), 1, c);
            flow.addEdge(itemNode(i), extraGroup(g), 1, c);
        }
    for (int g = 0; g < nGroups; g++) {
        flow.addEdge(mainGroup(g), T, groupSize, 0);
        flow.addEdge(extraGroup(g), remainderNode, 1, 0);
    }
    flow.addEdge(remainderNode, T, rem, 0);
    return flow.minCostFlow(S, T, nItems).second;
}
int getCost(int a, int b) {
    return (a + b - 1) / b * b - a;
}
void solve() {
    int n, m;
    std::cin >> n >> m;
    vi a(n), b(m);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int j = 0; j < m; j++)
        std::cin >> b[j];
    vvi cost(n, vi(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cost[i][j] = getCost(a[i], b[j]);
    std::cout << findMinCostMaxFlow(n, m, cost) << '\n';
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
