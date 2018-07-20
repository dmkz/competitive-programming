/*
    Problem: 620C. Pearls in a Row
    
    Solution: greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    
    std::set<int> before;
    
    int left = 0;
    std::vector<std::pair<int, int>> answ;
    for (int i = 0; i < n; ++i) {
        if (before.find(a[i]) != before.end()) {
            answ.push_back({left, i});
            left = i+1;
            before.clear();
        } else {
            before.insert(a[i]);
        }
    }
    if (answ.size() == 0) {
        std::cout << "-1" << std::endl; return 0;
    }
    
    if (!before.empty()) {
        answ.back().second = n-1;
    }
    
    std::cout << answ.size() << std::endl;
    for (auto& it : answ) {
        std::cout << it.first+1 << " " << it.second+1 << "\n";
    }
    
    return 0;
}