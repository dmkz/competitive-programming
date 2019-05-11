/*
    Problem: 461B. Appleman and Tree
    
    Solution: dynamic programming, dp on trees, dfs, combinatorics, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef long long ll;
const int mod = (int)1e9+7;
int add(int a, int b) { return (a += b) >= mod ? a -= mod : a; }
int sub(int a, int b) { return add(a, mod - b); }
int mul(int a, int b) { return int(1LL * a * b % mod); }
int pow(int a, int64_t n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) { res = mul(res, a); }
        a = mul(a,a); n >>= 1;
    }
    return res;
}
int inv(int a) { return pow(a, mod-2); }
int divmod(int a, int b) { return mul(a, inv(b)); }
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vvi next(n);
        for (int u = 1, p; u < n; ++u) {
            std::cin >> p;
            next[p].push_back(u);
            next[u].push_back(p);
        }
        vi color(n);
        for (int i = 0; i < n; ++i) { std::cin >> color[i]; }
        vi cnt0(n, -1), cnt1(n);
        std::function<void(int,int)> dfs = [&](int u, int p) {
            if (color[u] == 1) {
                cnt0[u] = 0;
                cnt1[u] = 1;
                return;
            }
            cnt0[u] = 1;
            cnt1[u] = 0;
            for (int v : next[u]) {
                if (v == p) { continue; }
                dfs(v, u);
                cnt0[u] = mul(cnt0[u], add(cnt0[v], cnt1[v]));
                cnt1[u] = add(cnt1[u], divmod(cnt1[v], add(cnt0[v], cnt1[v])));
            }
            cnt1[u] = mul(cnt1[u], cnt0[u]);
        };
        int answ = 1;
        for (int u = 0; u < n; ++u) {
            if (cnt0[u] == -1 && color[u] == 0) {
                dfs(u, -1);
                answ = mul(answ, cnt1[u]);
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}