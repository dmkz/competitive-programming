/*
    Problem: 678A. Johny Likes Numbers
    
    Solution: implementation, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int main() {
    ll n, k;
    std::cin >> n >> k;
    std::cout << (n / k + 1) * k;
    return 0;
}