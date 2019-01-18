/*
    Problem: 223B. Two Strings
    
    Solution: dynamic programming, greedy, stack, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

std::string solve(std::string s, std::string t) {
    const int n = (int)s.size();
    const int m = (int)t.size();
    s = "^" + s + "$";
    t = "#" + t + "@";
    std::vector<int> maxLT(1 + n + 1), maxRT(1+n+1);
    for (int i = 1, p = 1; i <= n; ++i) {
        if (p <= m && s[i] == t[p]) { maxLT[i] = maxLT[i-1] + 1; p++; }    
        else { maxLT[i] = maxLT[i-1]; }
    }

    for (int i = n, p = m; i >= 1; --i) {
        if (p >= 1 && s[i] == t[p]) { maxRT[i] = maxRT[i+1] + 1; p--; } 
        else { maxRT[i] = maxRT[i+1]; }
    }

    std::vector<std::vector<int>> lens(256);
    for (int i = m; i >= 1; --i) { lens[t[i]].push_back(i-1); }

    for (int i = 1; i <= n; ++i) {
        int lt = maxLT[i-1], rt = maxRT[i+1];
        auto &v = lens[s[i]];
        while (!v.empty() && !(v.back() <= lt && m - v.back() - 1 <= rt)) {
            v.pop_back();
        }
        if (v.empty()) { return "No"; }
    }

    return "Yes";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s, t;
    while (std::cin >> s >> t) {
        std::cout << solve(s, t) << std::endl;
    }
    return 0;
}