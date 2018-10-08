/*
    Problem: 496B. Secret Combination
    
    Solution: strings, minimal shift, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

#define size(x) (int)(x).size()

std::string min_shift(std::string s) {
    std::string answ = s;
    for (int i = 0; i < size(s); ++i) {
        std::rotate(s.rbegin(), s.rbegin()+1, s.rend());
        answ = std::min(answ, s);
    }
    return answ;
}

int main() {
    int n; std::string s; std::cin >> n >> s;
    auto answ = min_shift(s);
    for (int i = 0; i < 9; ++i) {
        for (auto& it : s) it = char((it-'0'+1) % 10 + '0');
        answ = std::min(answ, min_shift(s));
    }
    std::cout << answ;
    return 0;
}