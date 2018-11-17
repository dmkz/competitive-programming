/*
    Problem: 599D. Spongebob and Squares
    
    Solution: math, brute force, O(cbrt(x))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef unsigned long long ll;
typedef std::vector<ll> vl;

const ll MAX = (ll)1e18L;

ll cnt(ll n, ll m, const vl& sum) {
    if (n < m) return cnt(m, n, sum);
    return sum[m] + m * (m+1) / 2 * (n - m);
}

struct Pair {
    ll n, m;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.n < b.n || (a.n == b.n && a.m < b.m);
}

bool operator==(const Pair& a, const Pair& b) {
    return a.n == b.n && a.m == b.m;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    vl sum{0};
    for (int i = 1; sum.back() < MAX; ++i) {
        sum.push_back(sum.back() + (ll)i * i);
    }
    ll x;
    while (std::cin >> x) {
        std::vector<Pair> answ, stack;
        ll m = 1;
        while (m < (int)sum.size() && x >= sum[m]) {
            // sum[m] + m * (m+1) / 2 * (n - m) <= x
            ll n = (x - sum[m]) * 2 / (m * (m+1)) + m;
            while (cnt(n+1,m,sum)<=x)++n;
            while (cnt(n,m,sum)>x)--n;
            if (n < m) break;
            if (cnt(n, m, sum) == x) {
                answ.push_back(Pair{m, n});
                stack.push_back(Pair{n, m});
            }
            ++m;
        }
        if (stack.back() == answ.back()) { stack.pop_back(); }
        std::cout << answ.size() + stack.size() << '\n';
        for (auto it : answ) {
            std::cout << it.n << ' ' << it.m << '\n';
        }
        while (!stack.empty()) {
            auto it = stack.back(); stack.pop_back();
            std::cout << it.n << ' ' << it.m << '\n';
        }
        std::cout << std::endl;
    }
    return 0;
}