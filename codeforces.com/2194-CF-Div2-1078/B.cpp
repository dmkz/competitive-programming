// математика, жадные алгоритмы
#include <bits/stdc++.h>
using ll = long long;
using vi = std::vector<int>;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    vi a(n);
    for (auto &it : a)
        std::cin >> it;
    // сколько из каждого банка
    vi s(n);
    ll S{};
    for (int i = 0; i < n; i++) {
        s[i] = a[i] / x * y;
        S += s[i];
    }
    // находим ответ, перебирая банк назначения
    ll answ{};
    for (int i = 0; i < n; i++) {
        S -= s[i];
        ll curr = a[i] + S;
        remax(answ, curr);
        S += s[i];
    }
    std::cout << answ << std::endl;
}
main() {
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
