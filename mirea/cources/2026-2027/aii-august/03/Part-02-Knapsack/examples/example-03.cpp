#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем предметы и вместимость рюкзака:
    int n, c; cin >> n >> c;
    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    // Сохраняем все строки и координаты предка для каждого оптимального состояния.
    vector<vector<ll>> dp(n + 1, vector<ll>(c + 1));
    vector<vector<pair<int, int>>> parent(n + 1, vector<pair<int, int>>(c + 1));
    for (int i = 1; i <= n; i++) {
        for (int x = 0; x <= c; x++) {
            // Сначала рассматриваем вариант, в котором предмет i не входит в набор.
            dp[i][x] = dp[i - 1][x];
            parent[i][x] = {i - 1, x};
            // Если предмет i улучшает ответ, переходим из состояния с вместимостью x - w[i].
            if (w[i] <= x && dp[i - 1][x - w[i]] + v[i] > dp[i][x]) {
                dp[i][x] = dp[i - 1][x - w[i]] + v[i];
                parent[i][x] = {i - 1, x - w[i]};
            }
        }
    }
    // Восстанавливаем ответ, переходя по массиву parent от оптимального состояния к нулевой строке.
    vector<int> answ;
    for (int i = n, x = c; i > 0;) {
        auto [prevI, prevX] = parent[i][x];
        // Если при переходе уменьшилась вторая координата, предмет i вошёл в набор.
        if (prevX != x)
            answ.push_back(i);
        i = prevI;
        x = prevX;
    }
    // Индексы предметов получены в обратном порядке.
    reverse(answ.begin(), answ.end());
    cout << dp[n][c] << '\n';
    for (auto it : answ)
        cout << it << ' ';
    cout << '\n';
}