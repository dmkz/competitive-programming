/*
    Problem: 288C. Polo the Penguin and XOR operation
    
    Solution: greedy, math, xor, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

void solve(std::vector<int>& arr, int end, int64_t &answ) {
    if (end < 0) {
        return;
    }
    assert(arr[end] == -1);
    int mask = 1;
    while (mask < end) mask *= 2;
    --mask;
    int begin = (~end) & mask;
    assert(arr[begin] == -1);
    for (int i = begin, j = end; i <= j; ++i, --j) {
        arr[i] = j;
        arr[j] = i;
        answ += 2 * (i ^ j);
    }
    solve(arr, begin-1, answ);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        int64_t answ = 0;
        std::vector<int> arr(1+n, -1);
        solve(arr, n, answ);
        std::cout << answ << '\n';
        for (auto it : arr) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}