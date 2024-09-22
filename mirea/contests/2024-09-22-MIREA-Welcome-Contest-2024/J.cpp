#include <bits/stdc++.h>
const int mod = 998244353;
void solve() {
    // читаем данные
    int n, m; std::cin >> n >> m;
    std::vector<std::string> s(n);
    for (auto &it : s)
        std::cin >> it;
    // запускаем динамику
    std::vector dp(n+1, std::vector(n+1, std::vector(m+1, 0)));
    std::vector calculated(n+1, std::vector(n+1, std::vector(m+1, false)));
    std::function<int(int,int,int)> calc = [&](int l, int r, int k)
    {
        // полуинтервал [l, r) в столбце k
        if (l == r) // один способ заполнить подотрезок длины 0
            return 1;
        if (k == m) {
            if (l+1 == r) // один способ заполнить подотрезок длины 1
                return 1;
            return 0;
        }
        if (calculated[l][r][k])
            return dp[l][r][k];
        std::vector<int> t(n+1);
        t[l] = 1;
        for (int d = 0; d < 10; d++)
            for (int i = r - 1; i >= l; i--)
                for (int j = i + 1; j <= r; j++) {
                    // чтобы смогли поставить цифру d, надо изначально
                    // либо звёздочку либо эту цифру:
                    if (s[j-1][k] != '*' && s[j-1][k] != char('0' + d))
                        break;
                    t[j] = (t[j] + t[i] * 1LL * calc(i, j, k + 1)) % mod;
                }
        calculated[l][r][k] = true;
        return (dp[l][r][k] = t[r]);
    };
    std::cout << calc(0, n, 0) << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
