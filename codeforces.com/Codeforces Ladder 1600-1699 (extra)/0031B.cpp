/*
    Problem: 31B. Sysadmin Bob
    
    Solution: strings, implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

bool cut(std::string& s, std::string& ret) {
    int p = 0;
    while (p < (int)s.size() && 'a' <= s[p] && s[p] <= 'z') ++p;
    if (p == 0 || p == (int)s.size()) { return false; }
    assert(s[p] == '@');
    int save = p;
    ++p;
    while (p < (int)s.size() && 'a' <= s[p] && s[p] <= 'z') ++p;
    if (p == save) return false;
    if (p == (int)s.size()) {
        ret = s;
        s.clear();
        return p - save >= 2;
    }
    assert(s[p] == '@');
    if (p - save <= 2) {
        return false;
    }
    ret = s.substr(0, p-1);
    s = s.substr(p-1);
    return true;
}

int main() {
    std::string s;
    while (std::cin >> s) {
        std::string answ = "", temp;
        while (!s.empty()) {
            if (!cut(s, temp)) {
                s.clear();
                answ = "No solution";
                break;
            }
            temp.push_back(',');
            answ += temp;
        }
        if (answ.back() == ',') { answ.pop_back(); }
        std::cout << answ << std::endl;
    }
    return 0;
}