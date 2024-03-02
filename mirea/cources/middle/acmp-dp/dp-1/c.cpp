#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;
void setmin(auto &x, auto y) {
    if (x > y)
        x = y;
}
int main() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (auto &[x, y] : a)
        cin >> x >> y;
    sort(a.begin(), a.end());
    auto f = [&](int i, int j) {
        auto [ageI, riskI] = a[i];
        auto [ageJ, riskJ] = a[j];
        if (i < j)
            return riskJ;
        return riskI;
    };
    vector<int> dp(n + 1, inf);
    dp[0] = 0;
    for (int cnt = 2; cnt <= n; cnt++) {
        if (cnt >= 2)
            setmin(dp[cnt], f(cnt-1, cnt-2) + dp[cnt-2]);
        if (cnt >= 3)
            setmin(dp[cnt], f(cnt-1, cnt-2) + f(cnt-2, cnt-3) + dp[cnt-3]);
    }
    cout << dp[n] << endl;
}