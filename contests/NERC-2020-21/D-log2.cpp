#include <bits/stdc++.h>
using namespace std;
void setmax (auto &x, const auto &y) { if (x < y) x = y; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, d; cin >> n >> d;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // в динамике храним логарифмы
    vector dp(n+1, vector(10, pair(-1e100L, -1)));
    dp[0][1] = pair(0.0L, -1);
    for (int i = 0; i < n; i++)
        for (int prevRem = 0; prevRem < 10; prevRem++) {
            // берём это число
            int currRem = prevRem * a[i] % 10;
            setmax(dp[i+1][currRem], pair(dp[i][prevRem].first + log2l(a[i]), prevRem));
            // не берём это число
            setmax(dp[i+1][prevRem], pair(dp[i][prevRem].first, -1));
        }
    if (dp[n][d].first < 0) {
        cout << "-1\n";
        return 0;
    }
    // иначе достижимо
    vector<int> answ;
    for (int i = n-1; i >= 0; i--)
        if (auto [_, prevRem] = dp[i+1][d]; prevRem != -1) {
            answ.push_back(a[i]);
            d = prevRem;
        }
    if (answ.size() == 0) cout << "-1\n";
    else {
        cout << answ.size() << "\n";
        for (auto it : answ)
            cout << it << ' ';
        cout << endl;
    }
}
