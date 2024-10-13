#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
/*
    dpTree[i][j] = кратчайшее расстояние между редкими деревьями i и j (i --> j)
    идём от s до редкого дерева
    проходим все редкие деревья
    идём от последнего редкого дерева до t
    
    dpTreeVertDirect[i][j] - по прямым рёбрам
    dpTreeVertReversed[i][j] - по обратным рёбрам
*/

using ll = long long;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using pli = std::pair<ll, int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;

const ll inf = (ll)1e18L;

template<typename T>
using PQLess = std::priority_queue<T, std::vector<T>, std::greater<T>>;

vl dijkstra(int start, int n, const vvpii &edges) {
    vl dist(n+1, +inf);
    PQLess<std::pair<ll, int>> q;
    q.push({0, start});
    while (isz(q)) {
        auto [d, vert] = q.top();
        q.pop();
        if (dist[vert] <= d)
            continue;
        dist[vert] = d;
        for (const auto &[nextVert, delta] : edges[vert])
            q.push({d+delta,nextVert});
    }
    return dist;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем особые вершины
    int n, m, k; std::cin >> n >> m >> k;
    vi trees(k);
    for (auto &it : trees)
        std::cin >> it;
    std::sort(all(trees));
    // функция находит индекс особой вершины по её номеру
    auto getTreeIndex = [&](int v) {
        int i = int(std::lower_bound(all(trees), v) - trees.begin());
        assert(i < isz(trees));
        assert(trees[i] == v);
        return i;
    };
    // списки смежности, состоящие из прямых и обратных рёбер:
    vvpii direct(1+n), reversed(1+n);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        direct[from].emplace_back(to, cost);
        reversed[to].emplace_back(from, cost);
    }
    // расстояние от каждой особой вершины до всех остальных (k x n чисел) по прямым
    // и обратным рёбрам:
    vvl dpTreeVertDirect(k); // [i][j] - по прямым рёбрам
    vvl dpTreeVertReversed(k); //[i][j] - по обратным рёбрам
    for (int i = 0; i < k; i++) {
        dpTreeVertDirect[i] = dijkstra(trees[i], n, direct);
        dpTreeVertReversed[i] = dijkstra(trees[i], n, reversed);
    }
    // отвечаем на запросы
    int q; std::cin >> q;
    while (q --> 0) {
        // читаем данные из запроса и заменяем особые вершины их номерами
        int s, t, p; std::cin >> s >> t >> p;
        vi picked(p);
        for (auto &it : picked) {
            std::cin >> it;
            it = getTreeIndex(it);
        }
        // будем считать динамику dp[last][mask] = сколько нужно потратить, чтобы обойти
        // множество особых вершин mask, остановившись в last
        // инициализируем расстояниями от s до особых вершин:
        vvl dp(p, vl(1 << p, inf));
        for (int i = 0; i < p; i++)
            dp[i][1<<i] = dpTreeVertReversed[picked[i]][s];
        // переходы:
        for (int mask = 1; mask < (1 << p); mask++)
            for (int last = 0; last < p; last++)
                for (int prev = 0; prev < p; prev++)
                    if (((mask>>last)&1) && ((mask>>prev)&1) && prev != last) {
                        ll delta = dpTreeVertDirect[picked[prev]][trees[picked[last]]];
                        setmin(dp[last][mask], dp[prev][mask ^ (1 << last)] + delta);
                    }
        // добавляем рёбра до вершины t при вычислении ответа:
        ll answ = inf;
        for (int last = 0; last < p; last++) {
            ll delta = dpTreeVertDirect[picked[last]][t];
            setmin(answ, dp[last][(1<<p)-1] + delta);
        }
        if (answ >= inf)
            answ = -1;
        // выводим ответ
        std::cout << answ << '\n';
    }
}
