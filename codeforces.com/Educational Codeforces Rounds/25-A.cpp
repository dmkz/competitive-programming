/*
    Problem: 825A. Binary Protocol
    
    Solution: implementation, two pointers, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::string s; int n;
    std::cin >> n >> s; s += '0';
    int i = 0, answ = 0;
    while (i <= n) {
        int r = i;
        while (s[r] == '1') ++r;
        answ = answ * 10 + (r - i);
        i = r+1;
    }
    std::cout << answ;
    return 0;
}