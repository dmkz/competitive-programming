/*
    Problem: 108A. Palindromic Times
    
    Solution: strings, palindrome, O(MAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>

bool is_palindromic(int m) {
    char buf[6];
    sprintf(buf, "%02d:%02d", m / 60 % 24, m % 60);
    std::string s(buf); auto t = s;
    std::reverse(t.begin(), t.end());
    return s == t;
}

int main() {
    int h, m; scanf("%d:%d", &h, &m);
    m += h * 60;
    while (!is_palindromic(++m));
    printf("%02d:%02d", m / 60 % 24, m % 60);
    return 0;
}