/*
    Problem: 487B. Strip
    Solution: binary search, sparse table, dynamic programming, O(n log(n))
*/
#include <bits/stdc++.h>
const int NMAX = 100100, PMAX = 17, INF = (int)1e9;
int n, s, minLen, arr[NMAX], dp[PMAX][NMAX], min[PMAX][NMAX], max[PMAX][NMAX];
void input() {
    std::cin >> n >> s >> minLen;
    for (int i = 0; i < n; i++) std::cin >> arr[i];
}
void build() {
    for (int i = 0; i < n; i++) min[0][i] = max[0][i] = arr[i];
    for (int p = 1; p < PMAX; p++) {
        for (int i = 0; i + (1 << p) <= n; i++) {
            min[p][i] = std::min(min[p-1][i], min[p-1][i+(1 << (p-1))]);
            max[p][i] = std::max(max[p-1][i], max[p-1][i+(1 << (p-1))]);
        }
    }
}
int getDiff(int l, int r) {
    int len = r - l + 1;
    int p = std::ilogb(len);
    int mx = std::max(max[p][l], max[p][r+1-(1<<p)]);
    int mn = std::min(min[p][l], min[p][r+1-(1<<p)]);
    return mx - mn;
}
int getMinDP(int l, int r) {
    int len = r - l + 1;
    int p = std::ilogb(len);
    return std::min(dp[p][l], dp[p][r+1-(1<<p)]);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    input();
    build();
    for (int i = 0; i < NMAX; i++) {
        dp[0][i] = (i == n) ? 0 : INF;
    }
    for (int p = 1; p < PMAX; p++) {
        for (int i = 0; i + (1 << p) - 1 < NMAX; i++) {
            dp[p][i] = std::min(dp[p-1][i], dp[p-1][i+(1<<(p-1))]);
        }
    }
    for (int i = n-minLen; i >= 0; i--) {
        int low = i + minLen - 2, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (getDiff(i, mid) <= s) low = mid;
            else high = mid;
        }
        assert(low < n);
        // [i + l - 1, low] - can close current segment
        // need query to [i + l, low+1]
        if (i + minLen <= low + 1) {
            dp[0][i] = std::min(dp[0][i], 1 + getMinDP(i+minLen,low+1));
        }
        for (int p = 1; p < PMAX; p++) {
            if (i + (1 << p) - 1 < NMAX) {
                dp[p][i] = std::min(dp[p-1][i], dp[p-1][i+(1<<(p-1))]);
            }
        }
    }
    if (dp[0][0] >= INF) { std::cout << -1 << std::endl; }
    else { std::cout << dp[0][0] << std::endl; }
    return 0;
}