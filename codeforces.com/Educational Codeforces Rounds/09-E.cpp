/*
    Problem: 632E. Thief in a Shop
    
    Solution: dynamic programming, O(n*k*MAX_A)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k;
    std::cin >> n >> k;
    std::vector<int> coins(n);
    for (auto& it : coins) {
        std::cin >> it;
    }
    // Sort and erase repeated coins:
    std::sort(coins.begin(), coins.end());
    coins.erase(std::unique(coins.begin(), coins.end()), coins.end());
    // Check that all coins is odd or even:
    bool all_even = true, all_odd = true;
    for (auto& coin : coins) {
        if (coin % 2 == 1) all_even = false;
        if (coin % 2 == 0) all_odd  = false;
    }
    // DP:
    const int last = coins.back() * k;
    std::vector<char> prev(1+last), curr(1+last);
    curr[0] = true;
    for (int i = 1; i <= k; ++i) {
        prev.swap(curr);
        for (int j = 0, lim = coins.back() * i; j <= lim; ++j) {
            curr[j] = 0;
        }
        for (int sum = i * coins.front(), lim = i * coins.back(); sum <= lim; ++sum) {
            if ((all_even && sum % 2 == 1) || (all_odd && sum % 2 != i % 2)) {
                continue;
            }
            for (auto coin : coins) {
                if (sum - coin < 0) {
                    break;
                }
                if (prev[sum - coin]) {
                    curr[sum] = true;
                    break;
                }
            }
        }
    }
    // Output answer:
    for (int sum = 1; sum <= last; ++sum) {
        if (curr[sum]) {
            std::cout << sum << ' ';
        }
    }
    
    return 0;
}