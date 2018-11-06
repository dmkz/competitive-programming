/*
    Problem: 676C. Vasya and String
    
    Solution: two pointers, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>

int solve(int n, int limit, const std::string& s) {
    int lt = 0, rt = -1, nB = 0, answ = 0;
    while (lt < n) {
        while (rt+1 < n && nB + (s[rt+1] == 'b') <= limit) {
            nB += (s[rt+1] == 'b');
            rt++;
        }
        answ = std::max(answ, rt-lt+1);
        nB -= (s[lt] == 'b');
        ++lt;
    }
    return answ;
}

int main() {
    int n, limit;
    while (std::cin >> n >> limit) {
        std::string s; std::cin >> s;
        int res = solve(n, limit, s);
        for (auto& it : s) {
            it = char(it - 'a' + 'b');
        }
        res = std::max(res, solve(n, limit, s));
        std::cout << res << std::endl;
    }
    return 0;
}