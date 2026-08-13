#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void setmax(auto& x, const auto& y) {
    if (x < y) x = y;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды и проходимость ступеней:
    int n; cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    string cells; cin >> cells;
    // dp[i][r] — лучший путь к ступени i после r двойных прыжков подряд.
    const ll inf = 1LL << 60;
    vector<vector<ll>> dp(n + 1, vector<ll>(3, -inf));
    // Перед лестницей робот не сделал ни одного двойного прыжка.
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int r = 0; r <= 2; r++) {
            // Из недостижимого состояния нельзя продолжить путь.
            if (dp[i][r] == -inf) continue;
            // Одинарный прыжок сбрасывает длину серии двойных прыжков.
            if (i + 1 <= n && cells[i] == '.')
                setmax(dp[i + 1][0], dp[i][r] + a[i + 1]);
            // После двух двойных прыжков следующий двойной прыжок запрещён.
            if (r < 2 && i + 2 <= n && cells[i + 1] == '.')
                setmax(dp[i + 2][r + 1], dp[i][r] + a[i + 2]);
        }
    }
    // Выбираем лучшее допустимое состояние на последней ступени:
    ll answ = max({dp[n][0], dp[n][1], dp[n][2]});
    if (answ == -inf) cout << "IMPOSSIBLE\n";
    else cout << answ << '\n';
}