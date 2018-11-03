/*
    Problem: 451C. Predict Outcome of the Game
    
    Solution: math, equations, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

bool solve(ll n, ll k, ll d1, ll d2) {
    if (n % 3 != 0) return false;
    // c1 >= c2, c2 >= c3
    ll tmp = 2 * d1 + d2 + k;
    if (tmp % 3 == 0) {
        ll c1 = tmp / 3;
        ll c2 = c1 - d1;
        ll c3 = c2 - d2;
        if (k == c1 + c2 + c3 && c1 >= c2 && c2 >= c3 && c3 >= 0) {
            if (c1 <= n / 3 && c2 <= n / 3 && c3 <= n / 3) {
                return true;
            }
        }
    }
    // c1 >= c2, c3 >= c2
    tmp = k - d1 - d2;
    if (tmp >= 0 && tmp % 3 == 0) {
        ll c2 = tmp / 3;
        ll c1 = d1 + c2;
        ll c3 = d2 + c2;
        if (k == c1 + c2 + c3 && c1 >= c2 && c3 >= c2 && c2 >= 0) {
            if (c1 <= n / 3 && c2 <= n / 3 && c3 <= n / 3) {
                return true;
            }
        }
    }
    // c2 >= c1, c2 >= c3
    tmp = d1 + d2 + k;
    if (tmp >= 0 && tmp % 3 == 0) {
        ll c2 = tmp / 3;
        ll c1 = c2 - d1;
        ll c3 = c2 - d2;
        if (k == c1 + c2 + c3 && c2 >= c1 && c2 >= c3 && c1 >= 0 && c3 >= 0) {
            if (c1 <= n / 3 && c2 <= n / 3 && c3 <= n / 3) {
                return true;
            }
        }
    }
    // c2 >= c1, c3 >= c2
    tmp = k + 2 * d2 + d1;
    if (tmp >= 0 && tmp % 3 == 0) {
        ll c3 = tmp / 3;
        ll c2 = c3 - d2;
        ll c1 = c2 - d1;
        if (k == c1 + c2 + c3 && c2 >= c1 && c3 >= c2 && c1 >= 0) {
            if (c1 <= n / 3 && c2 <= n / 3 && c3 <= n / 3) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nT; std::cin >> nT;
    while (nT--) {
        ll n, k, d1, d2;
        std::cin >> n >> k >> d1 >> d2;
        std::cout << (solve(n, k, d1, d2) ? "yes" : "no") << "\n";
    }
    return 0;
}