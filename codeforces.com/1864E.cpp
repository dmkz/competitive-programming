/*
    Problem: 1864E. Guess Game
    Solution: combinatorics, implicit prefix trie, bitwise_or, O(n log(n))
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
const int mod = 998244353;
using ll = long long;
using vi = std::vector<int>;
ll binpow(ll a, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = r * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return r;
}
ll solve(const auto &a, int s, int f, int startBit = 31) {
    if (s > f)
        return 0;
    if (startBit < 0)
        return ({ ll len = f - s + 1; len * len % mod; });
    int low = s-1, high = f+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if ((a[mid] >> startBit) & 1) high = mid;
        else low = mid;
    }
    // [s, low] - zeros
    // [high, f] - ones
    ll cnt0 = low - s + 1;
    ll cnt1 = f - high + 1;
    ll res = solve(a,s,low,startBit-1);
    (res += cnt0 * cnt1 * 3) %= mod;
    (res += cnt1 * cnt1 + solve(a,high,f,startBit-1)) %= mod;
    return res;
}
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        ll n; std::cin >> n;
        vi a(n);
        for (auto &it : a)
            std::cin >> it;
        std::sort(all(a));
        std::cout << solve(a,0,n-1) * binpow(n*n%mod,mod-2) % mod << std::endl;
    }
}
