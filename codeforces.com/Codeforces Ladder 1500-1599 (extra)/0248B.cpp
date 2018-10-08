/*
    Problem: 248B. Chilly Willy
    
    Solution: math, brute forse, number theory, O(210*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <string>
#include <cassert>

bool inc(std::string& s) {
    int p = (int)s.size()-1;
    while (p >= 0 && s[p] == '9') { s[p] = '0'; --p; };
    if (p < 0) return false;
    s[p]++;
    return true;
}

std::string solve(int n) {
    if (n <= 2) return "-1";
    std::string answ = "1" + std::string(n-1, '0');
    while (true) {
        int rem = 0;
        for (auto& it : answ) {
            rem = (rem * 10 + (it - '0')) % 210;
        }
        if (rem == 0) return answ;
        assert(inc(answ));
    }
    return "-1";
}

int main() {
    int n; scanf("%d", &n);
    printf("%s\n", solve(n).c_str());
    return 0;
}