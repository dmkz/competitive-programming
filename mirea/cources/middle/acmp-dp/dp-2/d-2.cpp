#include <bits/stdc++.h>
using namespace std;
const int undefined = (int)1e9+7;
int main() {
    int n; cin >> n;
    vector a(n, 0);
    for (auto &it : a)
        cin >> it;
    
    vector dp(n, vector(n, undefined));
    
    function<int(int, int)> solve = [&](int L, int R) -> int
    {
        if (L > R)
            return 0;
        if (dp[L][R] == undefined)
            return dp[L][R] = max(a[L] - solve(L+1, R), a[R] - solve(L, R-1));
        return dp[L][R];
    };

    int result = solve(0, n-1);
    if (result > 0)
        cout << "1";
    else if (result < 0)
        cout << "2";
    else
        cout << "0";
}
