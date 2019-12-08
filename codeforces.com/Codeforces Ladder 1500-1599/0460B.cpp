/*
    Problem: 460B. Little Dima and Equation
    Solution: math, number theory, brute force, implementation
*/
#include <iostream>
#include <vector>

typedef long long ll;
ll qpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n /= 2;
    }
    return res;
}

int main() {
    ll a, b, c;
    std::cin >> a >> b >> c;
    std::vector<ll> answ;
    for (ll sum = 0; sum <= 9*9; ++sum) {
        ll x = b * qpow(sum, a) + c;
        if (x <= 0 || x >= (ll)1e9) continue;
        ll sum2 = 0;
        do {
            sum2 += x % 10;
            x /= 10;
        } while (x > 0);
        if (sum2 == sum) {
            answ.push_back(b * qpow(sum, a) + c);
        }
    }
    std::cout << answ.size() << '\n';
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}