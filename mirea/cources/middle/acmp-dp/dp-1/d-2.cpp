#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; cin >> n >> k;
    // dp[N][K] = количество вариантов
    // dp[кол-во разрядов][последняя цифра]
    vector dp(1+n, vector(k, 0));
    dp[1][0] = 0;
    for (int digit = 1; digit < k; digit++)
        dp[1][digit] = 1;
    for (int cnt = 2; cnt <= n; cnt++)
        for (int newDigit = 0; newDigit < k; newDigit++)
            for (int oldDigit = 0; oldDigit < k; oldDigit++)
                if (oldDigit + newDigit > 0)
                    dp[cnt][newDigit] += dp[cnt-1][oldDigit];
    int answ = 0;
    for (int digit = 0; digit < k; digit++)
        answ += dp[n][digit];
    cout << answ << endl;
}