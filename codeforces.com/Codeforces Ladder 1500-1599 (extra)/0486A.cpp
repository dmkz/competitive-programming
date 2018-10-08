/*
    Problem: 486A. Calculating Function
    
    Solution: implementation, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
typedef long long ll;
int main() {
    ll n; std::cin >> n;
    if (n % 2 == 0) {
        std::cout << n / 2;
    } else {
        std::cout << n / 2 - n;
    }
    return 0;
}