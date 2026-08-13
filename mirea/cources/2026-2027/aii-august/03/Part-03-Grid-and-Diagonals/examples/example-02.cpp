#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void setmax(auto& x, const auto& y) {
    // Заменяем значение, только если кандидат его улучшает.
    if (x < y) x = y;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем проходимость и значения клеток:
    int n, m; cin >> n >> m;
    vector<string> cells(n);
    for (auto& it : cells)
        cin >> it;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (auto& row : a)
        for (auto& it : row)
            cin >> it;
    // dp[i][j] хранит наибольшую сумму на пути до клетки (i, j), а диагонали задают порядок обхода.
    const ll inf = 1LL << 60;
    vector<vector<ll>> dp(n, vector<ll>(m, -inf));
    // Путь может начинаться только в проходимой верхней левой клетке.
    if (cells[0][0] == '.') dp[0][0] = a[0][0];
    // Перечисляем четыре разрешённых хода коня.
    const int di[] = {2, 1, -1, 2};
    const int dj[] = {1, 2, 2, -1};
    for (int d = 0; d <= n + m - 2; d++) {
        // На диагонали d перебираем только клетки, лежащие внутри сетки.
        int low = max(0, d - m + 1);
        int high = min(n - 1, d);
        for (int i = low; i <= high; i++) {
            int j = d - i;
            // Из недостижимой клетки продолжить путь нельзя.
            if (dp[i][j] == -inf) continue;
            // Каждый ход ведёт на диагональ с большим номером.
            for (int move = 0; move < 4; move++) {
                int ni = i + di[move], nj = j + dj[move];
                // Обновляем состояние только для проходимой клетки внутри сетки.
                if (0 <= ni && ni < n && 0 <= nj && nj < m && cells[ni][nj] == '.')
                    setmax(dp[ni][nj], dp[i][j] + a[ni][nj]);
            }
        }
    }
    if (dp[n - 1][m - 1] == -inf) cout << "IMPOSSIBLE\n";
    else cout << dp[n - 1][m - 1] << '\n';
}