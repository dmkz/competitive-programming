/*
    Problem: 508B. Anton and currency you all know
    
    Solution: greedy, math, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    const int n = (int)s.size();
    bool flag = false;
    int cand = -1;
    for (int i = 0; i+1 < n; ++i) {
        if ((s[i]-'0') % 2 == 1) continue;
        if (s[i] < s[n-1]) {
            std::swap(s[i], s[n-1]);
            flag = true;
            break;
        } else {
            cand = i;
        }
    }
    if (flag) {std::cout << s; return 0;}
    if (cand == -1) { std::cout << -1; return 0; }
    std::swap(s[cand], s[n-1]);
    std::cout << s;
    return 0;
}