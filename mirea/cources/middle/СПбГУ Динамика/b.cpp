#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
void setmax(auto &x, auto y) { if (x < y) x = y; }
int main() {
    freopen("lepus.in", "rt", stdin);
    freopen("lepus.out", "wt", stdout);
    // читаем клетки:
    int n; cin >> n;
    string s; cin >> s;
    // считаем динамику:
    vector<int> dp(n, -INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'w') continue;
        // переходы
        for (int delta : {1,3,5})
            if (i - delta >= 0)
                setmax(dp[i],dp[i-delta]+(s[i]=='\"'));
    }
    setmax(dp.back(),-1);
    cout << dp.back() << endl;
}