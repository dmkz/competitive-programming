#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<ll,ll>;
using vpll = std::vector<pll>;
using vvpll = std::vector<vpll>;
using vl = std::vector<ll>;
int main() {
    // строим дерево и считаем ксор на пути до корня (вершина 1)
    int n; std::cin >> n;
    vvpll adj(1+n);
    for (int i = 1; i < n; i++) {
        int u, v; ll w;
        std::cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vl xorPath(1+n);
    std::function<void(int,int)> dfs = [&](int u, int p) {
        for (auto &[v, w] : adj[u])
            if (v != p) {
                xorPath[v] = (xorPath[u] ^ w);
                dfs(v, u);
            }
    };
    dfs(1, 0);
    // теперь начинаем считать ответ. решаем отдельно для каждого бита
    // надо посчитать, сколько пар (u,v) дадут 1 в i-м бите
    // 1 дадут только числа с противоположными битами, то есть
    // ответ это кол-во единиц умножить на кол-во нулей
    const int mod = (int)1e9+7;
    ll pow2 = 1, answ = 0;
    for (int bit = 0; bit < 60; bit++) {
        ll cnt[2]{};
        for (int u = 1; u <= n; u++)
            cnt[(xorPath[u] >> bit) & 1]++;
        answ = (answ + cnt[0] * cnt[1] % mod * pow2 % mod) % mod;
        pow2 = pow2 * 2 % mod;
    }
    std::cout << answ << std::endl;
    return 0;
}
