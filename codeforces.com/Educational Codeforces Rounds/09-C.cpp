/*
    Problem: 632C. The Smallest String Concatenation
    
    Solution: sorting, strings, O(n*log(n)*W)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<std::string> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
        
    }
    std::stable_sort(arr.begin(), arr.end(), [](const std::string& s1, const std::string& s2) {
        return s1 + s2 < s2 + s1;
    });
    
    for (auto& it : arr) {
        std::cout << it;
    }
    
    return 0;
}