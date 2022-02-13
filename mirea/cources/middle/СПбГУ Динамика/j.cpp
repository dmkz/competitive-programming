#include <bits/stdc++.h>
using namespace std;
int main() {
    // Сопоставим буквам цифры: a = 0, b = 1, c = 2
    // запрещено: 01
    // инициализация dp:
    int n; cin >> n;
    vector dp(3, vector(1+n,0LL));
    dp[2][0] = 1;
    // вычисление dp:
    for (int i = 1; i <= n; i++) {
        for (int prev = 0; prev < 3; prev++) {
            for (int curr = 0; curr < 3; curr++) {
                if (prev == 0 && curr == 1) continue;
                dp[curr][i] += dp[prev][i-1];
            }
        }
    }
    cout << dp[0][n] + dp[1][n] + dp[2][n] << endl;
}