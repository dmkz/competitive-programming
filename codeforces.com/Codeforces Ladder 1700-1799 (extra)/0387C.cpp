/*
    Problem: 387C. George and Number
    
    Solution: greedy, strings, comparison, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

int compare(const std::string& s, const std::string& t) {
    if (s.size() < t.size()) return -1;
    if (s.size() > t.size()) return 1;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] < t[i]) return -1;
        if (s[i] > t[i]) return 1;
    }
    return 0;
}

int solve(std::string& s) {
    if (s.empty()) {
        return 0;
    }
    std::string t;
    while (s.back() == '0') {
        t.push_back('0');
        s.pop_back();
    }
    assert(!s.empty());
    t.push_back(s.back());
    std::reverse(t.begin(),t.end());
    s.pop_back();
    if (compare(s,t) != -1) {
        return 1+solve(s);
    } else {
        return 1;
    }
}

int main() {
    std::string s;
    while (std::cin >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}