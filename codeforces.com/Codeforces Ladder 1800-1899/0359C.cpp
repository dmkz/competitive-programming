/*
    Problem: 359C. Prime Number
    Solution: number theory, gcd, std::map, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
const int mod = (int)1e9+7;
int pow(int a, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) {
            r = int(1LL * a * r % mod);
        }
        a = int(1LL * a * a % mod);
        n >>= 1;
    }
    return r;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, p; std::cin >> n >> p; ) {
        std::vector<ll> a(n);
        ll s = 0;
        for (auto &it : a) {
            std::cin >> it;
            s += it;
        }
        std::map<ll,ll> cnt;
        for (auto it : a) {
            cnt[s-it]++;
        }
        while (cnt.begin()->second % p == 0) {
            auto it = cnt.begin();
            cnt[it->first+1] += it->second / p;
            cnt.erase(cnt.begin());
        }
        s = std::min(s, cnt.begin()->first);
        std::cout << pow(p, s) << std::endl;
    }
    return 0;
}