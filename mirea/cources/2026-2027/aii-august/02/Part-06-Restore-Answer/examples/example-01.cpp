#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды и строку доступности клеток:
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& it : a)
        cin >> it;
    string cells; cin >> cells;
    // Инициализируем те же состояния, что в задаче из предыдущей части:
    const ll inf = 1LL << 60;
    vector<ll> dp(n, -inf);
    vector<int> parent(n, -1);
    if (cells[0] == '.') dp[0] = a[0];
    // Вычисляем тот же переход и сохраняем выбранного предка:
    for (int i = 1; i < n; i++) {
        if (cells[i] == '.') {
            // При равенстве оставляем прыжок на одну клетку, как в исходной динамике.
            int prev = i - 1;
            if (i >= 2 && dp[i - 2] > dp[prev]) prev = i - 2;
            if (dp[prev] != -inf) {
                // Значение и выбранное ребро перехода обновляются вместе.
                dp[i] = dp[prev] + a[i];
                parent[i] = prev;
            }
        }
    }
    // Выводим -1 или восстанавливаем маршрут по предкам:
    if (dp[n - 1] == -inf) cout << -1 << '\n';
    else {
        // Идём по сохранённым предкам и разворачиваем маршрут.
        vector<int> path;
        for (int i = n - 1; i != -1; i = parent[i])
            path.push_back(i + 1);
        reverse(path.begin(), path.end());
        cout << dp[n - 1] << '\n' << path.size() << '\n';
        for (auto it : path)
            cout << it << ' ';
        cout << '\n';
    }
}