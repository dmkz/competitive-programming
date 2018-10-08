/*
    Problem: 603A. Alternative Thinking
    
    Solution: two pointers, dynamic programming, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::string s; std::cin >> n >> s; 
    s = "?" + s + "?";
    
    std::vector<std::vector<int>> pref(2, std::vector<int>(1+n+1));
    auto suff = pref;
    for (int i = 1; i <= n; ++i) {
        pref[0][i] = pref[0][i-1];
        pref[1][i] = pref[1][i-1];
        int c = (s[i] == '1');
        pref[c][i] = std::max(pref[c][i], 1 + pref[1-c][i-1]);
    }
    for (int i = n; i >= 1; --i) {
        suff[0][i] = suff[0][i+1];
        suff[1][i] = suff[1][i+1];
        int c = (s[i] == '1');
        suff[c][i] = std::max(suff[c][i], 1 + suff[1-c][i+1]);
    }
    int l = 1, r = 1, answ = 1;
    while (l <= n) {
        if (r < l) ++r;
        while (r+1 <= n && (s[r+1]-'0') == 1 - (s[r]-'0')) {
            ++r;
        }
        // reverse [l, r];
        int cl = s[l]-'0';
        int cr = s[r]-'0';
        answ = std::max(answ, pref[cl][l-1] + (r-l+1) + suff[cr][r+1]);
        ++l;
    }
    std::cout << answ;
    return 0;
}