/*
    Problem: 359B. Permutation
    
    Solution: constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, k; std::cin >> n >> k;
    std::vector<int> arr(2*n);
    for (int i = 0; i < 2*n; ++i) {
        arr[i] = i+1;
    }
    for (int i = 0; i < k; ++i) {
        std::swap(arr[2*i], arr[2*i+1]);
    }
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    return 0;
}