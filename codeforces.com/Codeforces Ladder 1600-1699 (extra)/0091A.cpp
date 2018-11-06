/*
    Problem: 91A. Newspaper Headline
    
    Solution: greedy, strings, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()

int solve(const std::string& s, const std::string& t) {
    std::vector<std::vector<int>> pos(256);
    for (int i = 0; i < (int)s.size(); ++i) {
        pos[s[i]].push_back(i);
    }
    int last = -1, answ = 1;
    for (auto curr : t) {
        auto it = std::upper_bound(all(pos[curr]), last);
        if (it == pos[curr].end()) {
            answ++;
            it = pos[curr].begin();
        }
        if (it == pos[curr].end()) {
            return -1;
        }
        last = *it;
    }
    return answ;
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