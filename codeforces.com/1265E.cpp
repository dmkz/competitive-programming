/*
    Problem: 1265E. Beautiful Mirrors
    Solution: probability theory, expected value, dynamic programming, O(n)
*/
#include <bits/stdc++.h>
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
const int mod = 998244353;
int add(int a, int b) { return (a += b) >= mod ? a -= mod : a; }
int sub(int a, int b) { return add(a, mod - b); }
int mul(int a, int b) { return int(1LL * a * b % mod); }
int pow(int a, int n) {
    int r = 1;
    while (n) {
        if (n & 1) { r = mul(a,r); }
        n >>= 1;
        a = mul(a,a);
    }
    return r;
}
int inv(int a) { return pow(a, mod-2); }
int main() {
    for (int n; std::cin >> n; ) {
        std::vector<int> p(n), c1(n), r(n, 1);
        for (int i = 0; i < n; i++) {
            int a; std::cin >> a;
            a = mul(a, inv(100));
            p[i] = a;
            int q = (mod+1-p[i]) % mod;
            if (i > 0) { c1[i] = (mod - q) % mod; } 
            else { c1[i] = p[0]; }
        }
        for (int i = n-1; i > 0; i--) {
            // mul by p[i-1] and add to (i-1) equation:
            r[i-1] = add(r[i-1], mul(r[i], p[i-1]));
            c1[i-1] = add(c1[i-1], mul(c1[i], p[i-1]));
        }
        std::cout << mul(r[0], inv(c1[0])) << std::endl;
    }
    return 0;
}