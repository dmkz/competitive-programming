#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n;
    vector<long double> dp(1+n, 0);
    dp[0] = 1;
    for (int cnt = 1; cnt <= n; cnt++) {
        dp[cnt] += dp[cnt-1];
        if (cnt >= 2)
            dp[cnt] += dp[cnt-2];
        if (cnt >= 3)
            dp[cnt] += dp[cnt-3];
    }
    cout << fixed << setprecision(0);
    cout << dp[n] << endl;
}