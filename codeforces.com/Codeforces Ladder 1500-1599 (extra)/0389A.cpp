/*
    Problem: 389A. Fox and Number Game
    
    Solution: constructive, greedy, gcd, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int main() {
    int n; std::cin >> n;
    std::vector<int> x(n);
    for (auto& it : x) std::cin >> it;
    int gcd = x[0];
    for (int i = 1; i < n; ++i) {
        gcd = ::gcd(x[i], gcd);
    }
    std::cout << gcd * n;
    return 0;
}