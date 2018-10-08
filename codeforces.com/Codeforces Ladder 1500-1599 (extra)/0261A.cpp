/*
    Problem: 261A. Maxim and Discounts
    
    Solution: sorting, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int m; std::cin >> m;
    int min = (int)1e9+1;
    for (int i = 0; i < m; ++i) {
        int v; std::cin >> v; 
        min = std::min(min, v);
    }
    int n; std::cin >> n;
    std::vector<int> items(n);
    for (auto& it : items) std::cin >> it;
    std::sort(items.begin(), items.end(), std::greater<int>());
    int p = 0, sum = 0;
    while (p < n) {
        int after = std::min(p+min,n);
        while (p < after) {
            sum += items[p++];
        }
        p = std::min(p+2, n);
    }
    std::cout << sum;
    return 0;
}