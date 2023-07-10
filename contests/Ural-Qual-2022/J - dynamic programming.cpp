/*
    solution: graphs, dynamic programming, O(n+m)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
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

using Record = std::pair<int, Fraction>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<Record>> out(n+1), in(n+1);
    while (m --> 0) {
        int from, to, s, w;
        std::cin >> from >> to >> s >> w;
        in[to].emplace_back(from, Fraction(s,w));
        out[from].emplace_back(to, Fraction(s,w));
    }
    vi visited(1+n), order;
    std::function<void(int)> topsort = [&](int u)
    {
        if (visited[u]) return;
        visited[u] = 1;
        for (auto [v,_] : out[u])
            topsort(v);
        order.push_back(u);
    };
    for (int u = 1; u <= n; u++)
        topsort(u);
    std::reverse(all(order));
    std::vector<Fraction> dp(1+n, Fraction(1e9+100, 1));
    for (int curr : order) {
        if (curr != 1)
            dp[curr] = Fraction();
        for (auto [prev,fr] : in[curr])
            setmax(dp[curr], std::min(dp[prev], fr));
    }
    while (q --> 0) {
        int a, b; std::cin >> a >> b;
        bool ok = dp[n] > Fraction(b, a);
        std::cout << (ok ? "YES\n" : "NO\n");
    }
}
