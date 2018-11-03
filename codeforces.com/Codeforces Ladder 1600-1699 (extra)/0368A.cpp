/*
    Problem: 368A. Sereja and Coat Rack
    
    Solution: math, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n, d, m;
    while (std::cin >> n >> d) {
        std::vector<int> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        std::sort(arr.begin(), arr.end(), std::less<int>());
        std::cin >> m;
        while ((int)arr.size() > m) { arr.pop_back(); }
        while ((int)arr.size() < m) { arr.push_back(-d); }
        std::cout << std::accumulate(arr.begin(), arr.end(), 0) << std::endl;
    }
    return 0;
}