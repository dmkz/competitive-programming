/*
    Problem: 135A. Replacement
    
    Solution: constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    if (arr.back() == 1) arr.back()++; else arr.back() = 1;
    std::sort(arr.begin(), arr.end());
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    return 0;
}