#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
void setmax(auto &x, auto y) { if (x < y) x = y; }
int main() {
    freopen("ladder.in", "rt", stdin);
    freopen("ladder.out", "wt", stdout);
    // читаем ступеньки 1 ... n. Нулевая ступенька равна нулю:
    int n; cin >> n;
    vector<int> a(1+n);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // считаем динамику:
    vector<int> dp(n+1, -INF);
    dp[0] = a[0]; // инициализация
    for (int i = 1; i <= n; i++) {
        // переходы
        dp[i] = dp[i-1] + a[i]; // прыжок длины 1
        if (i - 2 >= 0) // прыжок длины 2
            setmax(dp[i], dp[i-2] + a[i]);
    }
    cout << dp[n] << endl;
}