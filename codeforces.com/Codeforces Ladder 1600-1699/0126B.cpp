/*
    Problem: 126B. Password
    
    Solution: prefix-function, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

std::string solve(const std::string& s) {
    const int n = (int)s.size();
    std::vector<int> pref(1+n);
    for (int i = 1, len = 0; i < n; ++i) {
        while (len > 0 && s[len] != s[i]) {len = pref[len];}
        len += (s[len] == s[i]);
        pref[i+1] = len;
    }
    std::vector<int> cnt(1+n);
    for (int i = 0; i < n; ++i) {
        cnt[pref[i]]++;
    }
    int len = pref[n];
    while (len > 0 && cnt[len] == 0) {
        len = pref[len];
    }
    return len == 0 ? "Just a legend" : s.substr(0, len);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}