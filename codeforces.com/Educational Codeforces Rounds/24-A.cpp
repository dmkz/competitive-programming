/*
    Problem: 818A. Diplomas and Certificates
    
    Solution: math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int64_t n, k, s; std::cin >> n >> k;
    //(k+1) * s <= n / 2
    s = n / 2 / (k+1);
    std::cout << s << " " << k * s << " " << n - (k+1)*s;
    return 0;
}