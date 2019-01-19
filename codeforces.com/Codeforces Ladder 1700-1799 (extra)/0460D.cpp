/*
    Problem: 460D. Little Victor and Set
    
    Solution: math, brute force, constructive, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;
typedef std::vector<ll> vl;

vl solve(ll a, ll b, int k) {
    if (k == 1) { return vl{a,(ll)1,a}; }
    if (b - a <= 10) {
        ll min = -1, set = 0, cnt = b - a + 1;
        for (ll mask = 1; mask < (1 << cnt); ++mask) {
            if (__builtin_popcount(mask) <= k) {
                ll ret = 0;
                for (ll bit = 0; bit < cnt; ++bit) {
                    if ((mask >> bit) & 1) { ret ^= (a + bit); }
                }
                if (min == -1 || min > ret) {
                    min = ret;
                    set = mask;
                }
            }
        }
        vl answ{(ll)min, (ll)__builtin_popcount(set)};
        for (ll bit = 0; bit < cnt; ++bit) {
            if ((set >> bit) & 1) { answ.push_back(a + bit); }
        }
        return answ;
    }
    if (k == 2) {
        return vl{(ll)1, (ll)2, (ll)(a+1)/2*2, (ll)(a+1)/2*2+1};
    }
    if (k >= 4) {
        return vl{(ll)0, (ll)4, (ll)(a+1)/2*2, (ll)(a+1)/2*2+1, (ll)(a+1)/2*2+2, (ll)(a+1)/2*2+3};
    }
    if (a == 1) {
        return vl{ll(0), (ll)3, ll(1), ll(2), ll(3)};
    }
    
    // check if can got result 0 with 3 terms:
    ll pow = 1;
    while (pow <= a) { pow *= 2; }
    ll fi = a;
    ll se = pow | (a & ((pow / 2) - 1));
    ll th = pow | (pow / 2);
    if (th <= b) {
        assert((fi ^ se ^ th) == 0);
        return vl{ll(0), (ll)3, fi, se, th};
    }
    return vl{(ll)1, (ll)2, (ll)(a+1)/2*2, (ll)(a+1)/2*2+1};
}


int main() {
    ll a, b; int k;
    while (std::cin >> a >> b >> k) {
        vl answ = solve(a, b, k);
        std::cout << answ[0] << std::endl << answ[1] << std::endl;
        for (int i = 2; i < (int)answ.size(); ++i) {
            std::cout << answ[i] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}