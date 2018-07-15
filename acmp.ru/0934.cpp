/*
    "Балда": сортировка, строки, O(n*log(n)*mxLen)
*/

#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>


int main() {
    int n; scanf("%d", &n);
    
    std::vector<std::string> words(n);
    
    std::map<std::string, std::vector<int>> groups;
    
    for (auto& it : words) {
        char buf[41]; scanf("%40s", buf);
        it = buf;
    }
    
    for (int i = 0; i < n; ++i) {
        auto s = words[i];
        std::sort(s.begin(), s.end());
        groups[s].push_back(i);
    }
    
    auto less = [&](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() > b.size() || (a.size() == b.size() && words[a.front()] < words[b.front()]);
    };
    
    std::set<std::vector<int>, decltype(less)> set(less);
    
    for (auto& it : groups) {
        std::sort(it.second.begin(), it.second.end(), [&](const int i, const int j) {
            return words[i] < words[j];
        });
        set.insert(it.second);
        if (set.size() > 5u) {
            set.erase(std::prev(set.end()));
        }
    }
    
    for (auto g : set) {
        printf("Group of size %d: ", (int)g.size());
        g.erase(std::unique(g.begin(), g.end(), [&](const int i, const int j){return words[i] == words[j];}), g.end());
        for (auto& it : g) {
            printf("%s ", words[it].c_str());
        }
        printf(".\n");
    }
    
    
    return 0;
}