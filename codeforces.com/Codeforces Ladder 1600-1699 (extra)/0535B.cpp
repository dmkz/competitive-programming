/*
    Problem: 535B. Tavas and SaDDas
    
    Solution: brute force, binary search, bitmasks, O(2^len)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    std::vector<int> arr;
    for (int len = 1; len <= 9; ++len) {
        for (int mask = 0; mask < (1 << len); ++mask) {
            int number = 0;
            for (int bit = len-1; bit >= 0; --bit) {
                number = number * 10 + (((mask >> bit) & 1) ? 7 : 4);
            }
            arr.push_back(number);
        }
    }
    assert(std::is_sorted(arr.begin(), arr.end()));
    int lucky;
    while (std::cin >> lucky) {
        int pos = int(std::lower_bound(arr.begin(), arr.end(), lucky) - arr.begin())+1;
        std::cout << pos << std::endl;
    }
    return 0;
}