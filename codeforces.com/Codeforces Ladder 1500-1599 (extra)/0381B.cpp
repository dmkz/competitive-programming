/*
    Problem: 381B. Sereja and Stairs
    
    Solution: sorting, constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    std::vector<int> p1, p2;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            if (p1.empty() || p1.back() < arr[i]) {
                p1.push_back(arr[i]);
            }
        } else {
            if (p2.empty() || p2.back() < arr[i]) {
                p2.push_back(arr[i]);
            }
        }
    }
    while (!p2.empty() && p2.back() == p1.back()) {
        p2.pop_back();
    }
    while (!p2.empty()) {
        p1.push_back(p2.back());
        p2.pop_back();
    }
    
    std::cout << p1.size() << '\n';
    for (auto& it : p1) {
        std::cout << it << ' ';
    }
    return 0;
}