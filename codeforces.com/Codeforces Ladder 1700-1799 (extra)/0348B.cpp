/*
    Problem: 348B. Apple Tree
    
    Solution: binary search, gcd, lcm, trees, dfs, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>

typedef long long ll;

template<typename T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

template<typename T>
T lcm(T a, T b) { return a / gcd(a, b) * b; }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<ll> weight(1+n);
        std::vector<std::vector<int>> next(1+n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> weight[i];
        }
        for (int i = 1, u, v; i < n; ++i) {
            std::cin >> u >> v;
            next[u].push_back(v);
            next[v].push_back(u);
        }
        #define all(x) (x).begin(), (x).end()
        ll total = std::accumulate(all(weight), ll(0));
        bool ok = true;
        std::function<ll(int,int,ll)> visit = [&](int u, int p, ll min) {
            if (!ok) { return (ll)0; }
            int nSubtrees = 0;
            for (int v : next[u]) {
                nSubtrees += (v != p);
            }
            if (nSubtrees == 0) { return min; }
            if (nSubtrees > total / min) {
                ok = false;
                return (ll)0;
            }
            ll ret = min;
            for (int v : next[u]) {
                if (!ok || v == p) { continue; }
                ret = lcm(ret, visit(v, u, min * nSubtrees));
            }
            return ret;
        };
        ll minPossibleSum = visit(1, 0, 1);
        if (!ok) {
            std::cout << total << std::endl;
            continue;
        }
        std::function<ll(int,int,ll,bool&)> check = [&](int u, int p, ll w, bool& ok) {
            if (!ok) { return (ll)0; }
            int nSubtrees = 0;
            for (int v : next[u]) { nSubtrees += (v != p); }
            ll ret = 0;
            if (nSubtrees == 0) {
                ok = ok && w <= weight[u];
                ret += weight[u] - w;
                return ret;
            }
            for (int v : next[u]) {
                if (v == p) { continue; }
                if (ok) {
                    assert(w % nSubtrees == 0);
                    ret += check(v, u, w / nSubtrees, ok);
                }
            }
            return ret;
        };
        ll low = 0, high = total / minPossibleSum + 1;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            ok = true;
            check(1,0,minPossibleSum * mid, ok);
            if (ok) { low = mid; } 
            else { high = mid; }
        }
        ok = true;
        ll res = check(1,0,minPossibleSum * low, ok);
        assert(ok);
        std::cout << res << std::endl;
    }
    return 0;
}