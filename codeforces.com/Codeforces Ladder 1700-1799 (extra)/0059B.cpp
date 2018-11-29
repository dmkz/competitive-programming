/*
    Problem: 59B. Fortune Telling
    
    Solution: sorting, greedy, math, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int solve(const std::vector<int>& arr) {
    std::vector<int> odd, even;
    for (auto it : arr) {
        if (it % 2 == 1) {
            odd.push_back(it);
        } else {
            even.push_back(it);
        }
    }
    std::sort(even.begin(), even.end());
    std::sort( odd.begin(),  odd.end());
    int answ = std::accumulate(even.begin(), even.end(), 0);
    answ += std::accumulate(odd.begin(), odd.end(), 0);
    if (odd.empty()) {
        return 0;
    } else if (odd.size() % 2 == 0) {
        answ -= odd.front();
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto &it : arr) std::cin >> it;
        std::cout << solve(arr) << std::endl;
    }
    return 0;
}