/*
    solution: graphs, binary search, bfs, O(log(q)*m)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void setmax (auto &x, const auto &y) {
    if (x < y) x = y;
}
using ll = long long;
using vi = std::vector<int>;

struct Fraction {
    ll a, b;
    Fraction(ll a_ = 0, ll b_ = 1) : a(a_), b(b_) { }
};

bool operator<(Fraction L, Fraction R) {
    return L.a * R.b < R.a * L.b;
}

bool operator>(Fraction L, Fraction R) {
    return R < L;
}

using Edge = std::tuple<int, int, int, int>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<Edge> edges(m);
    for (auto &[from,to,s,w] : edges)
        std::cin >> from >> to >> s >> w;
    std::vector<std::pair<Fraction, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int a, b; std::cin >> a >> b;
        queries[i] = {Fraction(b, a), i};
    }
    std::sort(all(queries));
    int low = -1, high = q;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        auto [b,a] = queries[mid].first;
        std::vector<vi> adj(1+n);
        for (auto &[u,v,s,w] : edges) {
            ll delta = (ll)a * s - (ll)b * w;
            if (delta > 0)
                adj[u].push_back(v);
        }
        vi visited(1+n, 0);
        visited[1] = 1;
        vi q = {1};
        for (int i = 0; i < isz(q); i++)
            for (int v : adj[q[i]])
                if (!visited[v]) {
                    visited[v] = 1;
                    q.push_back(v);
                }
        if (visited[n]) low = mid;
        else high = mid;
    }
    std::vector<std::string> answ(q);
    for (int i = 0; i <= low; i++) {
        auto [_, id] = queries[i];
        answ[id] = "YES";
    }
    for (int i = high; i < q; i++) {
        auto [_, id] = queries[i];
        answ[id] = "NO";
    }
    for (auto &it : answ)
        std::cout << it << "\n";
}
