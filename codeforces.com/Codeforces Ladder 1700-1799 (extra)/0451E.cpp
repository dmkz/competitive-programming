/*
    Problem: 451E. Devu and Flowers
    
    Solution: combinatorics, bitmasks, inclusion–exclusion principle, O(n * 2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef long long ll;

const int mod = (int)1e9+7;

int add(int a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int pow(int a, int n) {
    if (a < 2) { return a; }
    int res = 1;
    while (n > 0) {
        if (n & 1) { res = mul(res, a); }
        n >>= 1; a = mul(a,a);
    }
    return res;
}

int inverse(int a) { return pow(a, mod-2); }

int inverseFact[21];

int C(ll n, ll k) {
    if (n < k) { return 0; }
    int res = 1;
    for (ll i = 0; i < k; ++i) {
        res = mul(res, int((n - i) % mod));
    }
    return mul(res, inverseFact[k]);
}

int solve(const ll s, const std::vector<ll>& limit) {
    // Solve problem using inclusion–exclusion principle:
    const int n = (int)limit.size();
    int res = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int nOnes = __builtin_popcount(mask);
        ll sum = 0;
        for (int bit = 0; bit < n; ++bit) {
            if ((mask >> bit) & 1) { sum += limit[bit]; }
        }
        int coeff = C(s - sum - nOnes + n - 1, n - 1);
        if (nOnes % 2 == 1) { res = add(res, mod - coeff); }
        else { res = add(res, coeff); }
    }
    return res;
}

int main() {
    // Precalc inverse factorials:
    inverseFact[0] = 1;
    for (int i = 1; i <= 20; ++i) { inverseFact[i] = mul(i, inverseFact[i-1]); }
    inverseFact[20] = inverse(inverseFact[20]);
    for (int i = 19; i >= 0; --i) { inverseFact[i] = mul(i+1, inverseFact[i+1]); }
    // Input and call solve function:
    int n; ll s;
    while (std::cin >> n >> s) {
        std::vector<ll> limit(n);
        for (auto &it : limit) { std::cin >> it; }
        std::cout << solve(s, limit) << std::endl;
    }
    return 0;
}