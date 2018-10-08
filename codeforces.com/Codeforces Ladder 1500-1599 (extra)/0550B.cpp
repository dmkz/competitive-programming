/*
    Problem: 550B. Preparing Olympiad
    
    Solution: bitmasks, brute force, implementation, O(n*2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
const int INF = (int)1e9+7;
int main() {
    int n, Min, Max, Diff;
    std::cin >> n >> Min >> Max >> Diff;
    std::vector<int> cost(n);
    for (auto& it : cost) std::cin >> it;
    int answ = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        int cnt = 0, min = INF, max = -INF, sum = 0;
        for (int i = 0; i < n; ++i) {
            if (((mask >> i) & 1) == 0) continue;
            cnt++;
            min = std::min(min, cost[i]);
            max = std::max(max, cost[i]);
            sum += cost[i];
        }
        answ += cnt >= 2 && sum >= Min && sum <= Max && max - min >= Diff;
    }
    std::cout << answ;
    return 0;
}