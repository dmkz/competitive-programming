/*
    problem: 1032. Игра после сессии
    solution: dynamic programming, two pointers, O(n^2)
*/
#include <bits/stdc++.h>
const int16_t INF = 30000, N = 5050;
void setmax(auto &x, const auto &y) {
    x = (x < y ? y : x);
}

int16_t dp[N][N];
int64_t a[N];

int16_t read() {
    int16_t n; std::cin >> n;
    for (int16_t i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a,a+n);
    return n;
}

void solve() {
    // read:
    const int16_t n = read();
    int16_t answ{1};
    for (int16_t curr = n-1; curr >= 0; curr--) {
        int16_t next = curr + 1, res = -INF;
        for (int16_t prev = curr-1; prev >= 0; prev--) {
            const auto diff = 2 * a[curr] - a[prev];
            while (next < n && diff > a[next])
            {
                const int16_t x = dp[curr][next];
                res = res < x ? x : res;
                next++;
            }
            if (res+1 <= 2) res = 1;
            dp[prev][curr] = res+1;
            setmax(answ, res+1);
        }
    }
    std::cout << answ << '\n';
}
int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt--) solve();
}
