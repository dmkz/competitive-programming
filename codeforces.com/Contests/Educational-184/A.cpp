// Решение: перебор
#include <bits/stdc++.h>
using vi = std::vector<int>;
using ll = long long;
using pli = std::pair<ll, int>;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
void solve() {
    int n, a; std::cin >> n >> a;
    vi arr(n);
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    auto cost = [&](int b) {
        ll resultA{}, resultB{};
        for (auto it : arr) {
            ll costA = std::abs(it - a);
            ll costB = std::abs(it - b);
            if (costA <= costB)
                resultA += 1;
            else
                resultB += 1;
        }
        return std::make_pair(resultA, resultB);
    };
    auto answ = pli(0LL, a);
    for (int b : {a-1, a+1}) {
        auto [_, rb] = cost(b);
        remax(answ, pli(rb, b));
    }
    std::cout << answ.second << std::endl;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
