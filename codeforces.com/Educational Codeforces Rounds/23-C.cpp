/*
    Problem: 817C. Really Big Numbers
    
    Solution: math, number theory, O(cbrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define all(x) (x).begin(), (x).end()
#define size(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vll;

int sum(ll number) {
    int ret = 0;
    do {
        ret += int(number % 10);
        number /= 10;
    } while (number > 0);
    return ret;
}

ll naive(ll begin, ll after, ll diff) {
    ll ret = 0;
    for (ll num = begin; num < after; ++num) {
        ret += num - sum(num) >= diff;
    }
    return ret;
}

ll solve(ll n, ll s) {
    ll after = std::min(n+1, s+100000);
    return naive(s, after, s) + std::max(ll(0), n - after + 1);
}

int main() {
    ll n, s; std::cin >> n >> s;
    std::cout << solve(n,s);
    return 0;
}