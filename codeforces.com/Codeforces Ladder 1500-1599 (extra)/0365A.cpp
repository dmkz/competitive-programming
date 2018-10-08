/*
    Problem: 365A. Good Number
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int n, k; std::cin >> n >> k;
    int answ = 0;
    while (n--) {
        std::string s; std::cin >> s;
        std::sort(s.begin(), s.end());
        s.erase(std::unique(s.begin(), s.end()), s.end());
        answ += (int)s.size() >= k && s[k] == char('0' + k);
    }
    std::cout << answ;
    return 0;
}