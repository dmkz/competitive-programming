/*
    Problem: 69E. Subsegments
    
    Solution: two pointers, std::set, std::map, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>

const int INF = (int)1e9+7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, k;
    while (std::cin >> n >> k) {
        std::vector<int> arr(1+n, -INF);
        std::map<int,int> count;
        for (int i = 1; i <= n; ++i) {
            std::cin >> arr[i];
        }
        for (auto it : arr) {
            count[it] = 0;
        }
        std::vector<std::set<int>> items(1+n);
        for (int i = 0; i < k; ++i) {
            count[arr[i]]++;
        }
        for (auto p : count) {
            items[p.second].insert(p.first);
        }
        std::vector<int> answ;
        for (int i = k; i <= n; ++i) {
            // add right item
            auto it = count.find(arr[i]);
            items[it->second].erase(it->first);
            it->second++;
            items[it->second].insert(it->first);
            // cur left item
            it = count.find(arr[i-k]);
            items[it->second].erase(it->first);
            it->second--;
            items[it->second].insert(it->first);
            if (items[1].empty()) {
                answ.push_back(-INF);
            } else {
                answ.push_back(*items[1].rbegin());
            }
        }
        for (auto it : answ) {
            if (it == -INF) {
                std::cout << "Nothing\n";
            } else {
                std::cout << it << "\n";
            }
        }
    }
    return 0;
}