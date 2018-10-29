/*
    Problem: 103A. Testing Pants for Sadness
    
    Solution: math, combinatorics, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int main() {
    int n;
    while (std::cin >> n) {
        ll answ = n;
        for (int i = 1, a; i <= n; ++i) {
            std::cin >> a;
            answ += (ll)i * (a-1);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}