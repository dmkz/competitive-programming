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
    // Номер диагонали i + j задаёт порядок обработки состояний.
    const ll inf = 1LL << 60;
    vector<vector<ll>> dp(n, vector<ll>(m, -inf));
    // Путь может начинаться только в проходимой верхней левой клетке.
    if (cells[0][0] == '.') dp[0][0] = a[0][0];
    for (int d = 0; d <= n + m - 2; d++) {
        // На диагонали d перебираем только клетки, лежащие внутри сетки.
        int low = max(0, d - m + 1);
        int high = min(n - 1, d);
        for (int i = low; i <= high; i++) {
            int j = d - i;
            // Из недостижимой клетки продолжить путь нельзя.
            if (dp[i][j] == -inf) continue;
            // После шага вниз строка увеличивается на один.
            if (i + 1 < n && cells[i + 1][j] == '.')
                setmax(dp[i + 1][j], dp[i][j] + a[i + 1][j]);
            // После шага вправо столбец увеличивается на один.
            if (j + 1 < m && cells[i][j + 1] == '.')
                setmax(dp[i][j + 1], dp[i][j] + a[i][j + 1]);
        }
    }
    if (dp[n - 1][m - 1] == -inf) cout << "IMPOSSIBLE\n";
    else cout << dp[n - 1][m - 1] << '\n';
}