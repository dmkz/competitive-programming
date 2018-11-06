/*
    Problem: 305C. Ivan and Powers of Two
    
    Solution: math, number theory, greedy, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>

typedef uint32_t Int;

Int solve(const std::vector<Int>& inp) {
    std::vector<Int> powers;
    Int max = 0;
    for (auto& it : inp) {
        for (Int p = std::max(max, it); p <= it+17; ++p) {
            powers.push_back(p);
        }
        max = std::max(it+18, max);
    }
    const int n = (int)powers.size();
    std::vector<Int> count(n);
    int p = 0;
    for (auto it : inp) {
        while (powers[p] < it) ++p;
        assert(it == powers[p]);
        count[p]++;
    }
    for (p = 0; p < n; ++p) {
        if (count[p] <= 1) {
            continue;
        }
        assert(p+1 < n);
        count[p+1] += (count[p] >> 1);
        count[p] = (count[p] & 1);
    }
    while (count.back() == 0) {
        count.pop_back();
        powers.pop_back();
    }
    return powers.back()+1 - std::accumulate(count.begin(), count.end(), Int(0));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    Int n;
    while (std::cin >> n) {
        std::vector<Int> inp(n);
        for (auto& it : inp) {
            std::cin >> it;
        }
        std::cout << solve(inp) << std::endl;
    }
    return 0;
}