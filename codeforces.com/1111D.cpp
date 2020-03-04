/*
    Problem: 1111D. Destroy the Colony
    Solution: dynamic programming, combinatorics, knapsack, removing from knapsack, O(n * |A|^2)
*/

#include <bits/stdc++.h>

#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using vi = std::vector<int>;
using vvi = std::vector<vi>;

template<class C, class X>
int lowpos(const C& c, const X& x) {
    return int(std::lower_bound(all(c), x) - c.begin());
}

template<class C>
C& reuniq(C& c) {
    c.erase(std::unique(all(c)), c.end());
    return c;
}

const int mod = (int)1e9+7, NMAX = 100100;

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

template<class T>
int pow(int a, T n) {
    int res(1);
    while (n > 0) {
        if (n & 1) res = mul(a, res);
        n /= 2;
        a = mul(a,a);
    }
    return res;
}

namespace Fact {
    
    int fact[NMAX+1], ifact[NMAX+1];
    
    void init() {
        fact[0] = 1;
        for (int i = 1; i <= NMAX; i++) {
            fact[i] = mul(i, fact[i-1]);
        }
        ifact[NMAX] = pow(fact[NMAX], mod-2);
        for (int i = NMAX; i >= 1; i--) {
            ifact[i-1] = mul(i, ifact[i]);
        }
    }
    
    int get(int n) {
        return fact[n];
    }
    
    int getInv(int n) {
        return ifact[n];
    }
    
}

namespace DP {
    
    int dp[NMAX+1];
    
    void init() {
        std::memset(dp, 0, sizeof dp);
        dp[0] = 1;
    }
    
    void add(int x) {
        for (int sum = NMAX; sum >= x; sum--) {
            dp[sum] += dp[sum-x];
            if (dp[sum] >= mod) dp[sum] -= mod;
        }
    }
    
    void rem(int x) {
        for (int sum = x; sum <= NMAX; sum++) {
            dp[sum] -= dp[sum-x];
            if (dp[sum] < 0) dp[sum] += mod;
        }
    }
    
    int get(int sum) {
        return dp[sum];
    }
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    Fact::init();
    DP::init();
    
    // input and counting:
    std::string input; std::cin >> input;
    std::string alp = input;
    std::sort(all(alp));
    reuniq(alp);
    const int nLetters = isz(alp);
    vi s, cnt(nLetters);
    for (char c : input) {
        s.push_back(lowpos(alp, c));
        cnt[s.back()]++;
    }
    const int n = isz(s);
    
    // Calculate constant W - number of all correct ways to arrange items
    // if they are divided by two groups:
    int W = mul(Fact::get(n/2), Fact::get(n/2));
    for (int c : cnt) W = mul(W, Fact::getInv(c));
    
    // Calculate all answers:
    for (int i = 0; i < nLetters; DP::add(cnt[i++]));
    vvi answ(nLetters, vi(nLetters));
    for (int i = 0; i < nLetters; i++) {
        DP::rem(cnt[i]);
        answ[i][i] = mul(2, mul(W, DP::get(n/2)));
        for (int j = i+1; j < nLetters; j++) {
            DP::rem(cnt[j]);
            answ[i][j] = answ[j][i] = mul(2, mul(W, DP::get(n/2)));
            DP::add(cnt[j]);
        }
        DP::add(cnt[i]);
    }
    
    // Answer on queries:
    int nQ; std::cin >> nQ;
    while (nQ--) {
        int i, j; std::cin >> i >> j;
        i = s[i-1], j = s[j-1];
        std::cout << answ[i][j] << '\n';
    }
    return 0;
}