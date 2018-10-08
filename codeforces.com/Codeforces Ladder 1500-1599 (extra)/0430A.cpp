/*
    Problem: 430A. Points and Segments (easy)
    
    Solution: sorting, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
int main() {
    int n, m; std::cin >> n >> m;
    std::vector<std::pair<int,int>> arr(n);
    for (int i = 0; i < n; ++i) {
        auto& it = arr[i];
        std::cin >> it.first;
        it.second = i;
    }
    std::sort(arr.begin(), arr.end());
    std::vector<int> answ(n);
    for (int i = 0; i < n; ++i) {
        answ[arr[i].second] = i % 2;
    }
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}