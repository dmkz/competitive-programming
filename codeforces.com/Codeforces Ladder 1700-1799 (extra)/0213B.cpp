/*
    Problem: 213B. Numbers
    
    Solution: dynamic programming, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>

namespace Numeric {
    const int mod = (int)1e9+7;
    std::vector<int> fact, ifact;
    static int& addto(int& a, int b) { return (a += b) >= mod ? (a -= mod) : a; }
    static int& subfrom(int& a, int b) { return (a -= b) < 0 ? (a += mod) : a; }
    static int add(int a, int b) { return addto(a,b); }
    static int sub(int a, int b) { return subfrom(a,b); }
    static int mul(int a, int b) { return int(1LL * a * b % mod); }
    static int pow(int a, int n) { 
        int res = 1;
        while (n > 0) {
            if (n & 1) {
                res = mul(res, a);
            }
            a = mul(a, a);
            n >>= 1;
        }
        return res;
    }
    static int inverse(int a) { return pow(a, mod-2); }
    
    void calcFactorials(const int NMAX) {
        fact.resize(1+NMAX);
        ifact.resize(1+NMAX);
        fact[0] = fact[1] = 1;
        for (int i = 2; i <= NMAX; ++i) {
            fact[i] = mul(fact[i-1], i);
        }
        ifact[NMAX] = inverse(fact[NMAX]);
        for (int i = NMAX-1; i >= 0; --i) {
            ifact[i] = mul(i+1, ifact[i+1]);
        }
    }
    
    int binCoeff(int n, int k) {
        assert(0 <= k && k <= n && n <= (int)fact.size());
        return mul(fact[n], mul(ifact[k], ifact[n-k]));
    }
}

int main() {
    using namespace Numeric;
    const int NMAX = 100;
    calcFactorials(NMAX);
    int n;
    while (std::cin >> n) {
        std::vector<int> low(10);
        for (auto &it : low) { 
            std::cin >> it;
        }
        std::vector<std::vector<int>> dp(10, std::vector<int>(1+n));
        for (int minDigit = 9; minDigit >= 0; --minDigit) {
            dp[minDigit][0] = (std::accumulate(low.begin()+minDigit, low.end(), 0) == 0);
            for (int len = 1; len <= n; ++len) {
                if (minDigit == 9) {
                    dp[minDigit][len] = (low[minDigit] <= len);
                } else if (minDigit == 0) {
                    for (int ci = low[minDigit]; ci <= len-1; ++ci) {
                        addto(dp[minDigit][len], mul(dp[minDigit+1][len-ci], binCoeff(len-1, ci)));
                    }
                } else {
                    for (int ci = low[minDigit]; ci <= len; ++ci) {
                        addto(dp[minDigit][len], mul(dp[minDigit+1][len-ci], binCoeff(len, ci)));
                    }
                }
            }
        }
        int res = 0;
        for (int len = 1; len <= n; ++len) {
            addto(res, dp[0][len]);
        }
        std::cout << res << std::endl;
    }
    return 0;
}