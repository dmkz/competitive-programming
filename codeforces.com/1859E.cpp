/*
    problem: 1859E. Maximum Monogonosity
    solution: dynamic programming, lazy dp, dp optimization, O(n*k)
*/
#include <bits/stdc++.h>

void remax(auto &x, const auto &y) { x = (x < y ? y : x); }

using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;

const ll INF = (ll)1e18L;

struct LazyDiagonalDpPrefixMax {
    using Func = std::function<ll(int,int)>;
    int nRows, nCols;
    Func func;
    vvl dpMax;
    vvb calculated;
    LazyDiagonalDpPrefixMax(int nRows_, int nCols_, Func func_)
        : nRows(nRows_), nCols(nCols_), func(func_)
    {
        dpMax.assign(nRows, vl(nCols, -INF));
        calculated.assign(nRows, vb(nCols, false));
    }
    ll operator()(int r, int c) {
        if (r < 0 || r >= nRows || c < 0 || c >= nCols)
            return -INF;
        if (calculated[r][c])
            return dpMax[r][c];
        calculated[r][c] = 1;
        return dpMax[r][c] = std::max(func(r, c), (*this)(r-1,c-1));
    }
};
ll solve(int n, int k, vl a, vl b) {
    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);
    vvl dp(n+1, vl(1+k,-INF));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        dp[i][0] = 0;
    // dp[index][sum]
    // модуль раскрывается в виде 4 вариантов:
    // 1. a[i] - b[j] + a[j] - b[i]
    // 2. a[i] - b[j] - a[j] + b[i]
    // 3. -a[i] + b[j] + a[j] - b[i]
    // 4. -a[i] + b[j] - a[j] + b[i]
    // сгруппируем всё, что содержит j, и всё, что содержит i, и внесём содержащее j
    // внутрь динамики:
    // 1. (a[j] - b[j]) + (a[i] - b[i])
    // 2. -(a[j] + b[j]) + (a[i] + b[i])
    // 3. (a[j] + b[j]) - (a[i] + b[i])
    // 4. -(a[j] - b[j]) - (a[i] - b[i])
    // надо поддерживать 4 динамики и брать максимум из них
    LazyDiagonalDpPrefixMax dp1(n+1, k+1, [&](int j, int remLen) {
        return dp[j-1][remLen] + (a[j] - b[j]);
    });
    LazyDiagonalDpPrefixMax dp2(n+1, k+1, [&](int j, int remLen) {
        return dp[j-1][remLen] - (a[j] + b[j]);
    });
    LazyDiagonalDpPrefixMax dp3(n+1, k+1, [&](int j, int remLen) {
        return dp[j-1][remLen] + (a[j] + b[j]);
    });
    LazyDiagonalDpPrefixMax dp4(n+1, k+1, [&](int j, int remLen) {
        return dp[j-1][remLen] - (a[j] - b[j]);
    });
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int totalLen = 1; totalLen <= std::min(i, k); totalLen++) {
            const int remLen = totalLen - 1;
            const int j = i - totalLen + remLen + 1;
            ll v1 = dp1(j,remLen) + (a[i] - b[i]);
            ll v2 = dp2(j,remLen) + (a[i] + b[i]);
            ll v3 = dp3(j,remLen) - (a[i] + b[i]);
            ll v4 = dp4(j,remLen) - (a[i] - b[i]);
            remax(dp[i][totalLen], std::max<ll>({v1,v2,v3,v4}));
        }
        for (int len = 0; len <= k; len++)
            remax(dp[i][len], dp[i-1][len]);
    }
    return dp[n][k];
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int n, k; std::cin >> n >> k;
        vl a(n), b(n);
        for (int i = 0, x; i < n; i++) {
            std::cin >> x;
            a[i] = x;
        }
        for (int i = 0, x; i < n; i++) {
            std::cin >> x;
            b[i] = x;
        }
        std::cout << (int64_t)solve(n,k,a,b) << std::endl;
    }
    return 0;
}
