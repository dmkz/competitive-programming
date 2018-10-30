/*
    Problem: 252A. Little Xor
    
    Solution: brute force, xor, implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; 
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        int max = 0;
        for (int i = 0; i < n; ++i) {
            int res = 0;
            for (int j = i; j < n; ++j) {
                res ^= arr[j];
                max = std::max(max, res);
            }
        }
        std::cout << max << std::endl;
    }
    return 0;
}