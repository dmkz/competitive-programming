/*
    Problem: 471C. MUH and House of Cards
    
    Solution: number theory, math, O(sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

ll solve(ll n) {
    int answ = 0;
    for (int h = 1; (ll)h * h <= n; ++h) {
        ll need = 2 * h + 3LL * h * (h-1) / 2;
        if (need <= n && (n - need) % 3 == 0) {
            answ++;
        }
    }
    return answ;
}

int main() {
    ll n; while (std::cin >> n) std::cout << solve(n) << std::endl;
    
    return 0;
}