#include <bits/stdc++.h>
void setmin(auto &x, const auto &y) { if (x > y) x = y; }
using namespace std;
const int inf = (int)1e9;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем блоки
    int n; cin >> n;
    vector a(n, pair(0, 0));
    for (auto &[m,k] : a)
        cin >> m >> k;
    // считаем динамику:
    // dp[i][j] = за какую минимальную цену можно объединить блоки на отрезке
    // [i, j]. Объединённый блок будет иметь параметры (mi, kj)
    vector dp(n, vector(n, inf));
    // инициализация динамики: блоки длины 1 уже объединены:
    for (int i = 0; i < n; i++)
        dp[i][i] = 0;
    // переходы
    for (int len = 2; len <= n; len++)
        for (int i = 0, j = len - 1; j < n; i++, j++) {
            // считаем динамику для отрезка [i, j] длины len
            auto [mi, ki] = a[i];
            auto [mj, kj] = a[j];
            // перебираем где произошло соединение
            for (int mid = i; mid < j; mid++)
                setmin(dp[i][j], dp[i][mid] + dp[mid+1][j] + mi * kj);
        }
    // выводим ответ
    cout << dp[0][n-1] << endl;
}
