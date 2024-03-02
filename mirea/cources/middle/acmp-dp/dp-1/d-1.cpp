#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; cin >> n >> k;
    // dp[N][2] = количество вариантов
    // dp[кол-во разрядов][нулевая цифра на конце или нет]
    vector dp(1+n, vector(2, 0));
    dp[1][0] = 0;
    dp[1][1] = k-1;
    for (int cnt = 2; cnt <= n; cnt++) {
        // поставить нулевую цифру
        dp[cnt][0] = dp[cnt-1][1];
        // поставить ненулевую цифру
        dp[cnt][1] = (k - 1) * (dp[cnt-1][0] + dp[cnt-1][1]);
    }
    cout << dp[n][0] + dp[n][1] << endl;
}