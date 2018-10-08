/*
    Problem: 519A. A and B and Chess
    
    Solution: implementation, O(n*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> w(256);
    w['Q'] = w['q'] = 9;
    w['R'] = w['r'] = 5;
    w['B'] = w['b'] = 3;
    w['N'] = w['n'] = 3;
    w['P'] = w['p'] = 1;
    int sw = 0, sb = 0;
    for (int r = 0; r < 8; ++r) {
        std::string s; std::cin >> s;
        for (auto& c : s) {
            if ('A' <= c && c <= 'Z') {
                sw += w[c];
            } else {
                sb += w[c];
            }
        }
    }
    if (sw < sb) {
        std::cout << "Black";
    } else if (sw > sb) {
        std::cout << "White";
    } else {
        std::cout << "Draw";
    }
    return 0;
}