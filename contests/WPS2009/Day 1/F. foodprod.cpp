/*
    Problem: F. foodprod
    Solution: binary search, brute force, O(n log(n))
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef std::pair<ll,ll> pll;
typedef std::pair<ll,pll> plll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (ll n, f, gh, ph, gf, pf; std::cin >> n >> f >> gh >> ph >> gf >> pf; ) {
        plll answ(LLONG_MAX,pll(0,0));
        for (ll nf = 0; nf <= n; ++nf) {
            ll nh = (nf + f - 1) / f;
            if (ph > 0) {
                ll low = nh-1, high = INT_MAX;
                while (high - low > 1) {
                    ll mid = (low + high) / 2;
                    if (nf * pf + mid * ph >= n) { high = mid; }
                    else { low = mid; }
                }
                nh = high;
            }
            if (nf * pf + nh * ph >= n) {
                answ = std::min(answ, 
                    plll(gf * nf + gh * nh, pll(nh, nf)));
            }
        }
        assert(answ.first < LLONG_MAX);
        ll nh, np, cost;
        nh = answ.second.first;
        np = answ.second.second;
        cost = answ.first;
        std::cout << nh << ' ' << np << ' ' << cost << std::endl;
    }
    return 0;
}