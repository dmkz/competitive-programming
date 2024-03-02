#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
int main() {
    int n; cin >> n;
    // было: dp[конец] => максимальная длина
    vector<int> dp(n+2, inf); // dp[длина] => минимальный конец
    dp[0] = -inf;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto it = lower_bound(dp.begin(), dp.end(), x);
        *it = x;
    }
    int answ = 0;
    while (dp[answ+1] != inf)
        answ++;
    cout << answ << endl;
}