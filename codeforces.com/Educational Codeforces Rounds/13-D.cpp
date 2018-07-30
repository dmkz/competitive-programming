/*
    Problem: 678D. Iterated Linear Function
    
    Solution: geometric progression, pow, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

const ll mod = (ll)1e9+7;

ll pow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        n /= 2;
    }
    return res;
}

ll sum(ll a, ll n) {
    if (n == 1) {
        return 1;
    } else if (n % 2 == 1) {
        return (1 + a * sum(a, n-1)) % mod;
    } else {
        return (1 + a) * sum(a * a % mod, n / 2) % mod;
    }
}

ll solve(ll A, ll B, ll n, ll x) {
    return (pow(A, n) * x + B * sum(A, n)) % mod;
}

int main() {
    ll A, B, n, x;
    std::cin >> A >> B >> n >> x;
    std::cout << solve(A, B, n, x);
    return 0;
}