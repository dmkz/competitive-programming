/*
    Problem: 484A. Bits
    
    Solution: constructive, greedy, bits, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

ll solve(ll a, ll b) {
    ll number = 0;
    for (int p = 61; p >= 0; --p) {
        if (((a >> p) & 1) != ((b >> p) & 1)) {
            ll var1 = number + (1LL << (p+1)) - 1;
            number += (1LL << p) - 1;
            if (var1 <= b) {
                number = var1;
            }
            break;
        } else {
            number += ((a >> p) & 1) << p;
        }
    }
    return number;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    while (n--) {
        ll a, b;
        std::cin >> a >> b;
        std::cout << solve(a, b) << '\n';
    }
    return 0;
}