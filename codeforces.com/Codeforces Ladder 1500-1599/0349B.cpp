/*
    Problem: 349B. Color the Fence
    Solution: greedy, implementation
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
int main() {
    int have; std::cin >> have;
    std::vector<int> cost(1+9);
    for (int i = 1; i <= 9; ++i) {
        std::cin >> cost[i];
    }
    int imin = 9;
    for (int i = 9; i >= 1; --i) {
        if (cost[imin] > cost[i]) {
            imin = i;
        }
    }
    if (cost[imin] > have) {
        std::cout << -1; return 0;
    }
    
    std::string answ(have / cost[imin], '0' + imin);
    have %= cost[imin];
    for (auto& c : answ) {
        for (int i = imin; i <= 9; ++i) {
            if (have+cost[c-'0'] >= cost[i]) {
                have = have + cost[c-'0'] - cost[i];
                c = '0' + i;
            }
        }
    }
    std::cout << answ;
    return 0;
}