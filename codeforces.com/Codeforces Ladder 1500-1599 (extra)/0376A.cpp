/*
    Problem: 376A. Lever
    
    Solution: math, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

int main() {
    std::string s; std::cin >> s;
    const int n = (int)s.size(); int mid = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '^') { mid = i; }
        if (s[i] == '=') { s[i] = '0'; }
    }
    int64_t ls = 0, rs = 0;
    for (int l = mid-1; l >= 0; --l) {
        ls += (s[l] - '0') * (mid - l);
    }
    for (int r = mid+1; r < n; ++r) {
        rs += (s[r] - '0') * (r - mid);
    }
    if (rs < ls) {
        std::cout << "left";
    } else if (rs > ls) {
        std::cout << "right";
    } else {
        std::cout << "balance";
    }
    return 0;
}