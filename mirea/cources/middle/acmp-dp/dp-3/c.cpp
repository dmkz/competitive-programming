#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &item : a)
        cin >> item;
    // dp[i][k] = число способов среди первых i животных выбрать k
    vector dp(n, vector(4, 0LL));
    // инициализация
    dp[0][0] = 1;
    dp[0][1] = a[0];
    // переходы
    for (int i = 1; i < n; i++)
        for (int was = 0; was <= 3; was++) {
            // берём это животное a[i] различными способами
            if (was + 1 <= 3)
                dp[i][was+1] += a[i] * dp[i-1][was];
            // не берём это животное
            dp[i][was] += dp[i-1][was];
        }
    // выводим ответ:
    cout << dp[n-1][3] << endl;
}
