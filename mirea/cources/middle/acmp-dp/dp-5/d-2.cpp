#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    // инициализация:
    vector dp(n+1, vector(n+1, 0LL));
    for (int k = 0; k <= n; k++)
        dp[k][k] = 1;
    // переходы:
    for (int nBlocks = 1; nBlocks <= n; nBlocks++)
        for (int lastRow = 1; lastRow <= nBlocks; lastRow++)
            for (int prevRow = 1; prevRow < lastRow; prevRow++)
                dp[nBlocks][lastRow] += dp[nBlocks - lastRow][prevRow];
    // считаем ответ:
    auto answer = dp[n][1];
    for (int lastRow = 2; lastRow <= n; lastRow++)
        answer += dp[n][lastRow];
    cout << answer << endl;
}
