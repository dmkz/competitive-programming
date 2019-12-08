/*
    Problem: 313B. Ilya and Queries
    Solution: dynamic programming, prefix sums
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s; s = '?' + s + '?';
    std::vector<int> pref{0}; const int n = (int)s.size()-2;
    for (int i = 1; i <= n; ++i) {
        pref.push_back(pref.back() + (s[i] == s[i+1]));
    }
    int nQ;
    std::cin >> nQ;
    while (nQ--) {
        int l, r; std::cin >> l >> r;
        std::cout << pref[r-1] - pref[l-1] << '\n';
    }
    return 0;
}