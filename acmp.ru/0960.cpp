/*
    "Три буквы": динамическое программирование, префикс-суммы, суффикс-суммы, O(n)
*/

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

int main() {
    char buf[100000+1];
    scanf("%100000s", buf);
    std::string s(buf);
    int n = (int)s.size();
    s = "?" + s + "?";
    std::vector<int> pref(n+2, 0), suff(n+2, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s[i] == 'a');
    }
    for (int i = n; i >= 1; --i) {
        suff[i] = suff[i+1] + (s[i] == 'c');
    }
    long long answ = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'b') {
            answ += 1LL * pref[i-1] * suff[i+1];
        }
    }
    std::cout << answ;
    return 0;
}