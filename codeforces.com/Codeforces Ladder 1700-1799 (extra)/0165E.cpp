/*
    Problem: 165E. Compatible Numbers
    
    Solution: dynamic programming, bitmasks, O(AMAX * log(AMAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

std::vector<int> solve(std::vector<int> arr) {
    const int AMAX = 1 << 22;
    std::vector<int> answer(AMAX, -1); // bit equal to 1 - need be zero, 0 - any bit
    for (auto & it : arr) {
        answer[~it & (AMAX-1)] = it;
    }
    for (int mask = AMAX-1; mask >= 0; --mask) {
        if (answer[mask] == -1) { continue; }
        for (int bit = 0; bit < 22; ++bit) {
            if ((mask >> bit) & 1) {
                answer[mask ^ (1 << bit)] = answer[mask];
            }
        }
    }
    for (auto &it : arr) { it = answer[it]; }
    return arr;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto &it : arr) { std::cin >> it; }
        auto ret = solve(arr);
        for (auto &it : ret) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}