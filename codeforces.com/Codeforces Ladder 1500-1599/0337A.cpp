/*
    Problem: 337A. Puzzles
    Solution: greedy
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int k, n;
    std::cin >> k >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    int answ = (int)1e9;
    for (int i = 0; i + k - 1 < n; ++i) {
        answ = std::min(answ, arr[i+k-1]-arr[i]);
    }
    std::cout << answ;
    return 0;
}