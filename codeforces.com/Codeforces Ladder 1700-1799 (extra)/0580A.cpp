/*
    Problem: 580A. Kefa and First Steps
    
    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int maxNonDecLen(const std::vector<int>& arr) {
    int answ = 0, last = 0, len = 0;
    for (auto &curr : arr) {
        if (last <= curr) {
            len++;
        } else {
            answ = std::max(answ, len);
            len = 1;
        }
        last = curr;
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(1+n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        std::cout << maxNonDecLen(arr) << std::endl;
    }
    return 0;
}