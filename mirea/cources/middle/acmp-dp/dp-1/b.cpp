#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
const int inf = (int)1e9+7;
int main() {
    int n; cin >> n;
    vector<int> x(n);
    for (auto &it : x)
        cin >> it;
    sort(all(x));
    vector<int> dp(n, inf);
    for (int i = 1; i < n; i++)
        dp[i] = (x[i] - x[i-1]) + std::min(dp[i-1], (i-2>=0?dp[i-2]:0));
    cout << dp.back() << endl;
    return 0;
}
