// динамическое программирование
// Задача: D, Вердикт: OK, Время: 192ms, Память: 30.78Mb
#include <bits/stdc++.h>
using ll = long long;
using vi = std::vector<int>;
using vl = std::vector<ll>;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    vi c(n), p(n);
    for (int i = 0; i < n; i++) std::cin >> c[i];
    for (int i = 0; i < n; i++) std::cin >> p[i];
    // строим префикс суммы:
    vl pref={0};
    for (auto it : p)
        pref.push_back(pref.back() + it);
    const ll inf = (ll)1e18L;
    vl maxResult(n+1, -inf);
    maxResult[0] = 0;
    vl bestCompensation(m+1, -inf);
    for (int i = 0; i < n; i++) {
        // берём i-й элемент
        ll best = pref[i+1] + bestCompensation[c[i]];
        remax(bestCompensation[c[i]], (maxResult[i] - pref[i]));
        maxResult[i+1] = std::max(maxResult[i], best);
    }
    std::cout << maxResult[n] << std::endl;
}
