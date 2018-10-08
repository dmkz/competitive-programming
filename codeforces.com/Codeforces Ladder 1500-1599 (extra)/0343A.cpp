/*
    Problem: 343A. Rational Resistance
    
    Solution: number theory, math, gcd, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <iostream>
typedef long long ll;
int main() {
    ll a, b;
    while (std::cin >> a >> b) {
        ll answ = 0;
        while (b != 0) {
            answ += a / b;
            auto rem = a % b;
            a = b;
            b = rem;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}