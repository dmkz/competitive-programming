// двудольные графы, циклы, СЛАУ
// Задача: E, Вердикт: OK, Время: 139ms, Память: 21.50Mb
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#include <cassert>
#define int ll
using ll = long long;
using tiii = std::tuple<int,int,int>;
using vtiii = std::vector<tiii>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
using vl = std::vector<ll>;
using vi = std::vector<int>;
int lowpos(const auto &c, const auto &x) {
    return int(std::lower_bound(all(c), x) - c.begin());
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    vtiii edges(m);
    vvpii adj(n+1);
    for (auto &[u,v,s] : edges) {
        std::cin >> u >> v >> s;
        if (u > v) std::swap(u, v);
        adj[u].emplace_back(v, s);
        adj[v].emplace_back(u, s);
    }
    std::sort(all(edges));
    auto findEdgeId = [&](int u, int v) {
        if (u > v) std::swap(u, v);
        return lowpos(edges, tiii(u,v,-1e6));
    };
    auto findEdgeSum = [&](int u, int v) {
        if (u > v) std::swap(u, v);
        int i = findEdgeId(u,v);
        assert(0 <= i && i < isz(edges));
        assert(std::get<0>(edges[i]) == u);
        assert(std::get<1>(edges[i]) == v);
        return std::get<2>(edges[i]);
    };
    vl num(1+n);
    std::vector<bool> vis;
    auto check = [&]() {
        for (const auto &[u,v,s] : edges)
            if (num[u] + num[v] != s)
                return false;
        return true;
    };
    auto solve = [&](int start, ll x) {
        num.assign(n+1, 0);
        vis.assign(n+1, false);
        num[start] = x;
        vis[start] = 1;
        std::queue<int> q;
        q.push(start);
        while (q.size()) {
            auto u = q.front();
            q.pop();
            for (const auto &[v, s] : adj[u]) {
                num[v] = s - num[u];
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
        ll sum=0;
        for (int i = 1; i <= n; i++)
            sum += std::abs(num[i]);
        return std::make_pair(sum, check());
    };
    // определяем, является ли граф двудольным:
    vi from(n+1);
    bool isBipartite=true;
    vi color(n+1,-1);
    color[1] = 0;
    int fi = 0, se = 0;
    std::function<void(int)> dfs = [&](int u){
        if (!isBipartite)
            return;
        for (const auto &[v, _] : adj[u]) {
            if (!isBipartite)
                return;
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                from[v] = u;
                dfs(v);
            } else if (color[v] != 1 - color[u]) {
                isBipartite = false;
                fi = u, se = v;
            }
        }
    };
    dfs(1);
    // если граф - двудольный, то решений бесконечно много
    if (isBipartite) {
        auto [_, ok] = solve(1, 0);
        if (!ok) {
            std::cout << "No\n";
        } else {
            // x[i] = A[i] + B[i] * x[1], где B[i] = +/-1
            // после solve(1, 0) в num[i] уже лежат A[i]
            // |A[i] + B[i] * x| = |x - q[i]|, q[i] = -B[i] * A[i]
            vl cand;
            cand.reserve(n);
            for (int i = 1; i <= n; i++)
                cand.push_back(color[i] == 0 ? -num[i] : num[i]);
            // медиана минимизирует сумму модулей:
            std::nth_element(cand.begin(), cand.begin() + n/2, cand.end());
            ll bestX = cand[n/2];
            solve(1, bestX);
            std::cout << "Yes\n";
            for (int i = 1; i <= n; i++)
                std::cout << num[i] << ' ';
            std::cout << std::endl;
        }        
    } else {
        // есть цикл нечётной длины
        // надо его найти!
        //bool debug = 1;
        //watch("cycle", fi, se);
        //for (int u = 1; u <= n; u++) {
        //    std::cout << "from[" << u << "] = " << from[u] << std::endl;
        //}
        vi cycle;
        for (int u = fi; u != se; u = from[u])
            cycle.push_back(u);
        cycle.push_back(se);
        vl rhs;
        for (int i = 0; i + 1 < isz(cycle); i++) {
            int u = cycle[i], v = cycle[i+1];
            rhs.push_back(findEdgeSum(u,v));
        }
        rhs.push_back(findEdgeSum(cycle.front(), cycle.back()));
        ll last = rhs.back();
        for (int i = 0; i + 1 < isz(rhs); i++)
            if (i % 2 == 0) {
                last -= rhs[i];
            } else {
                last += rhs[i];
            }
        auto [_, ok] = solve(cycle.back(), last/2);
        if (!ok) {
            std::cout << "No\n";
        } else {
            std::cout << "Yes\n";
            for (int i = 1; i <= n; i++)
                std::cout << num[i] << ' ';
            std::cout << std::endl;
        }
    }
}
