/*
    задача: Игра - 2
    решение: динамическое программирование, теория игр, O(n^2)
*/
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    int n; cin >> n;
    vi a(n); for (auto &it : a) cin >> it;
    // инициализация динамики:
    vvi dp(n, vi(n));
    for (int i = 0; i < n; i++)
        dp[i][i] = a[i];
    // вычисление состояний динамики в порядке возрастания длины:
    for (int len = 2; len <= n; len++)
        for (int i = 0, j = len - 1; j < n; i++, j++)
            dp[i][j] = max(a[i] - dp[i+1][j], a[j] - dp[i][j-1]);
    // вывод ответа:
    cout << (dp[0][n-1] > 0 ? 1 : (dp[0][n-1] < 0 ? 2 : 0));
}
