#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int int64_t
using i128 = __int128;
const int NMAX = 100100;
int32_t main() {
    int n; std::cin >> n;
    std::vector<int> a(n+1);
    for (auto &it : a) std::cin >> it;
    std::reverse(all(a));
    // сравнивать нужно a[i] * i! против a[j] * j!, причём a[i] и a[j] должны быть одного знака
    std::vector<std::pair<int, int>> pos, neg;
    for (int i = 0; i < isz(a); i++)
        if (a[i] > 0) pos.emplace_back(a[i], i);
        else neg.emplace_back(a[i], i);
    // теперь будем сортировать в порядке возрастания
    // a[i] * i! < a[j] * j!. Случаи:
    // 1. Если i >= j, то a[i] * (i!/j!) < a[j]
    // 2. Если i < j, то a[i] < a[j] * (j! / i!)
    // отношение a[i] / a[j] может быть порядка 10^{18}, поэтому нужно предварительно подсчитать
    // для каждого факториала с какими другими факториалами отношение не превысит 10^{18}
    std::vector adj(NMAX+1, std::vector<std::pair<int, __int128>>{});
    const int inf = 2e18L;
    for (int i = 0; i <= NMAX; i++) {
        // fact[j] / fact[i] = (i+1) * (i+2) * ... * j <= 10^{18}
        int j = i;
        __int128 prod = 1;
        adj[i] = {{i, 1}};
        while (prod * (j+1) < inf) {
            prod *= (++j);
            adj[i].emplace_back(j, prod);
        }
    }
    // теперь можем начать сортировать:
    auto cmp = [&](const auto &lhs, const auto &rhs) {
        auto [ai, i] = lhs;
        auto [aj, j] = rhs;
        if (i <= j) {
            // a[i] < a[j] * (j!/i!)
            int coeff = inf;
            auto it = std::lower_bound(all(adj[i]), std::make_pair(j, i128{}));
            if (it != adj[i].end()) coeff = it->second;
            return a[i] < __int128(a[j]) * coeff;
        } else {
            // a[i] * (i! / j!) < a[j]
            int coeff = inf;
            auto it = std::lower_bound(all(adj[j]), std::make_pair(i, i128{}));
            if (it != adj[j].end()) coeff = it->second;
            return __int128(a[i]) * coeff < a[j];
        }
    };
    std::sort(all(pos), cmp);
    std::sort(all(neg), cmp);
    const int mod = 998244353;
    std::vector<int> fact(n+1, 1);
    for (int i = 2; i <= n; i++)
        fact[i] = (fact[i-1] * i) % mod;
    // сначала минимум
    if (!neg.empty()) {
        auto [aj, j] = neg.front();
        auto se = (aj % mod * fact[j] % mod + mod) % mod;
        std::cout << se << '\n';
    } else {
        int answ = inf;
        for (auto &[ai, _] : pos)
            answ = std::min(answ, ai);
        std::cout << answ % mod << '\n';
    }
    // теперь максимум
    if (!pos.empty()) {
        auto [ai, i] = pos.back();
        auto fi = (ai % mod * fact[i] % mod + mod) % mod;
        std::cout << fi << '\n';
    } else {
        int answ = -inf;
        for (auto &[ai, _] : neg)
            answ = std::max(answ, ai);
        std::cout << (answ % mod + mod) % mod << '\n';
    }
    return 0;
}