/*
    Problem: 145A. Lucky Conversion
    
    Solution: sorting, greedy, constructive, set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

int main() {
    std::string s, t; std::cin >> s >> t;
    for (auto& it : s) it = (it == '4');
    for (auto& it : t) it = (it == '4');
    std::vector<std::set<int>> pos(2);
    const int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) {
            pos[s[i]].insert(i);
        }
    }
    int answ = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) {
            pos[s[i]].erase(i);
            if (!pos[t[i]].empty()) {
                auto it = *pos[t[i]].begin();
                std::swap(s[i], s[it]);
                pos[t[i]].erase(it);
            } else {
                s[i] = t[i];
            }
            answ++;
        }
        
    }
    std::cout << answ;
    return 0;
}