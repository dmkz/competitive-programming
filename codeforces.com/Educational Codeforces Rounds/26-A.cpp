/*
    Problem: 837A. Text Volume
    
    Solution: implementation, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int f(const std::string& s) {
    int ret = 0;
    for (auto& it : s) {
        ret += 'A' <= it && it <= 'Z';
    }
    return ret;
}

int main() {
    int n , answ = 0; std::cin >> n;
    while (n--) {
        std::string s;
        std::cin >> s;
        answ = std::max(answ, f(s));
    }
    std::cout << answ;
    return 0;
}