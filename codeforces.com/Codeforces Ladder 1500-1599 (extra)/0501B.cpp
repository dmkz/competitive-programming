/*
    Problem: 501B. Misha and Changing Handles
    
    Solution: implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

int main() {
    int n; std::cin >> n;
    int nUsers = 0;
    std::map<std::string, int> id;
    std::set<std::string> used;
    std::vector<std::string> first(n);
    std::vector<std::string> last(n);
    for (int i = 0; i < n; ++i) {
        std::string s, t;
        std::cin >> s >> t;
        if (id.find(s) == id.end()) {
            id[s] = nUsers++;
            first[id[s]] = s;
        }
        used.insert(s);
        if (used.find(t) == used.end()) {
            id[t] = id[s];
            last[id[t]] = t;
        }
        used.insert(t);
    }
    std::vector<std::pair<std::string, std::string>> answ;
    for (int i = 0; i < n; ++i) {
        if (!first[i].empty() && !last[i].empty()) {
            answ.push_back(std::make_pair(first[i], last[i]));
        }
    }
    std::cout << answ.size() << '\n';
    for (auto& p : answ) {
        std::cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}