/*
    Problem: 7261. Difficult path
    
    Solution: dynamic programming, probability theory, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

typedef long double ld;

ld solve(const int steps, const int dist) {
    std::vector<ld> curr(2 * steps+1);
    curr[steps] = 1;
    auto next = curr;
    for (int i = 1; i <= steps; ++i) {
        for (int st = 0; st < (int)next.size(); ++st) {
            next[st] = (st-1 >= 0 ? curr[st-1] * 0.5 : 0) + (st+1 < (int)next.size() ? curr[st+1] * 0.5 : 0);
        }
        curr = next;
    }
    return steps+dist < (int)curr.size() ? curr[steps+dist] : ld(0);
}

int main() {
    std::cout << std::fixed << std::setprecision(7);
    int steps, dist;
    while (std::cin >> steps >> dist) {
        std::cout << solve(steps, dist) << std::endl;
    }
    return 0;
}