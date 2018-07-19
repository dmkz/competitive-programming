/*
    Problem: 660C. Hard Process
    
    Solution: two pointers, greedy, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, limit;
    std::cin >> n >> limit;
    
    std::vector<int> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
    }
    int l = 0, r = -1, count = 0, answ = 0, left = 0, right = -1;
    while (l < n) {
        while (r+1 < n && count < limit) {
            count += (arr[++r] == 0);
        }
        while (r+1 < n && arr[r+1] == 1) {
            ++r;
        }
        
        int temp = r - l + 1;
        if (temp > answ) {
            answ = temp;
            left = l;
            right = r;
        }        
        count -= (arr[l++] == 0);        
    }
    for (int i = left; i <= right; ++i) {
        arr[i] = 1;
    }
    std::cout << right - left + 1 << '\n';
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    return 0;
}