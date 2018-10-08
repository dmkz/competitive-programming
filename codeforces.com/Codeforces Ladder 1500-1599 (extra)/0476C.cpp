/*
    Problem: 476C. Dreamoon and Sums
    
    Solution: math, number theory, arifmetic progression, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

const ll mod = (ll)1e9+7;

int main() {
    ll a, b; 
    while (std::cin >> a >> b) {
        ll answ = 0;
        for (ll r = 1; r < b; ++r) {
            answ = (answ + a * r + (a+1) * a % mod * ((mod+1)/2) % mod * r % mod * b % mod) % mod;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}