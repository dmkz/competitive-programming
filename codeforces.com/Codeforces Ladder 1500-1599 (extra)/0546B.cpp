/*
    Problem: 546B. Soldier and Badges
    
    Solution: greedy, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    int64_t answ = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] <= arr[i-1]) {
            int val = arr[i-1]+1;
            answ += val - arr[i];
            arr[i] = val;
        }
    }
    std::cout << answ;
    return 0;
}