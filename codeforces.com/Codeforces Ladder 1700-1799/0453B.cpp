/*
    Problem: 453B. Little Pony and Harmony Chest
    
    Solution: dynamic programming, bitmasks, O(n*60*2^17)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
template<typename X, typename Y> X& remin(X& x, const Y& y) { return x = (x < y) ? x : y; }
const vi primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const int INF = (int)1e9+7;
struct State {
    int sum, from, number;
};
bool operator<(const State& a, const State& b) {
    return a.sum < b.sum || (a.sum == b.sum && (a.from < b.from || (a.from == b.from && a.number < b.number)));
}
int main() {
    vi numMask(61);
    vvi numPrev(61);
    int totalSize = 0;
    for (int num = 1; num <= 60; ++num) {
        int mask = 0;
        for (int ip = 0; ip < isz(primes); ip++) {
            if (num % primes[ip] == 0) {
                mask |= 1 << ip;
            }
        }
        numMask[num] = mask;
        for (mask = 0; mask < (1 << isz(primes)); ++mask) {
            if ((numMask[num] & mask) == 0) {
                numPrev[num].push_back(mask);
            }
        }
        totalSize += isz(numPrev[num]);
    }
    for (int n; std::cin >> n; ) {
        vi arr(1+n);
        for (int i = 1; i <= n; i++) { std::cin >> arr[i]; }
        std::vector<std::vector<State>> dp(1+n, std::vector<State>(1<<isz(primes), State{INF,0,0}));
        dp[0][0] = State{0,0,0};
        for (int i = 1; i <= n; i++) {
            for (int num = 1; num <= 60; ++num) {
                for (int prev : numPrev[num]) {
                    auto st = dp[i-1][prev];
                    remin(dp[i][prev | numMask[num]], State{st.sum + std::abs(num-arr[i]), prev, num});
                }
            }
        }
        auto st = dp[n][0];
        for (int mask = 0; mask < (1 << isz(primes)); ++mask) {
            remin(st, dp[n][mask]);
        }
        vi answ(1+n);
        for (int i = n; i >= 1; --i) {
            answ[i] = st.number;
            st = dp[i-1][st.from];
        }
        for (int i = 1; i <= n; i++) {
            std::cout << answ[i] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}