#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = (int)1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        vector dp(k+1, vector(n+1, 0));
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            x %= mod;
            if (x < 0) x += mod;
            a[i] = x;
        }
        // инициализация динамики: подпоследовательности длины 1
        for (int i = n-1; i >= 0; i--)
            dp[1][i] = (a[i] + dp[1][i+1]) % mod;
        // вычисление динамики:
        for (int cnt = 2; cnt <= k; cnt++)
            for (int i = n-1; i >= 0; i--)
                dp[cnt][i] = (a[i] * 1LL * dp[cnt-1][i+1] % mod + dp[cnt][i+1]) % mod;
        // вывод ответа:
        cout << dp[k][0] << endl;
    }
}