/*
    Problem: 612B. HDD is Outdated Technology
    
    Solution: math, sequences, implementation, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        int value; std::cin >> value; --value;
        pos[value] = i;
    }
    int64_t sum = 0;
    for (int i = 1; i < n; ++i)
        sum += std::abs(pos[i] - pos[i-1]);
    std::cout << sum << std::endl;
    return 0;
}