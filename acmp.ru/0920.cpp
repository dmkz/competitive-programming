// динамическое программирование по подмножествам, O(3^n)
#include <bits/stdc++.h>
using vi = std::vector<int>;
using vvi = std::vector<vi>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
main() {
    // читаем данные:
    int n; std::cin >> n;
    vvi a(n, vi(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> a[i][j];
    // для каждой маски посчитаем, можем ли собрать клетку или нет
    vi isValidCage(1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i < n; i++) if ((mask >> i) & 1)
            for (int j = 0; j < n; j++) if ((mask >> j) & 1)
                ok &= (a[i][j] == 0);
        isValidCage[mask] = ok;
    }
    // теперь считаем динамику по подмножествам:
    vi dp(1 << n, n);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++)
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
            if (isValidCage[sub])
                remin(dp[mask], dp[mask ^ sub] + 1);
    std::cout << dp.back() << std::endl;
}
