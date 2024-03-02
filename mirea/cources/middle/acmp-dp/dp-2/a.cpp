#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> y(n);
    for (auto &item : y)
        cin >> item;
    vector<int> dp(n);
    for (int i = 1; i < n; i++)
        dp[i] = min(abs(y[i] - y[i-1]) + dp[i-1],   // прыгаем через 1 платфотму
                    i-2>=0?(3*abs(y[i]-y[i-2])+dp[i-2]):inf);// через 2 платформы сразу
    cout << dp.back() << endl;
}
