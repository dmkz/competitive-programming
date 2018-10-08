/*
    Problem: 400A. Inna and Choose Options
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

bool solve(const std::string& s, int a, int b) {
    for (int i = 0; i < b; ++i) {
        if (s[i] != 'X') continue;
        bool flag = true;
        for (int g = 0; g < a; ++g) {
            if (s[i+g*b] != s[i]) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;
}

int main() {
    int nT; std::cin >> nT;
    while (nT--) {
        std::string s; std::cin >> s;
        std::vector<std::pair<int,int>> answ;
        for (int a : {1,2,3,4,6,12}) {
            if (solve(s,a,12/a)) {
                answ.push_back(std::make_pair(a,12/a));
            }
        }
        std::cout << answ.size();
        for (auto& it : answ) {
            std::cout << ' ' << it.first << 'x' << it.second;
        }
        std::cout << '\n';
    }
    return 0;
}