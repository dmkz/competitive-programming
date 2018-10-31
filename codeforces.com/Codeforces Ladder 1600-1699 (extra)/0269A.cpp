/*
    Problem: 269A. Magical Boxes
    
    Solution: greedy, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

struct Box {
    ll side, count;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Precalc max sides diff for limits in problem:
    ll limit = 0, pow = 1;
    while (pow < (ll)2e9) {
        limit++;
        pow *= 4;
    }
    // Solution:
    int n;
    while (std::cin >> n) {
        std::vector<Box> boxes(n);
        for (auto& it : boxes) {
            std::cin >> it.side >> it.count;
        }
        std::sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
            return a.side > b.side;
        });
        for (int i = n-2; i >= 0; --i) {
            auto& prev = boxes[i+1];
            auto& curr = boxes[i];
            ll sideDiff = curr.side - prev.side;
            if (sideDiff >= limit) {
                continue;
            }
            // how many boxes we need?
            ll factor = 1;
            while (sideDiff--) { factor *= 4; }
            if (curr.count * factor >= prev.count) {
                continue;
            }
            // (curr.count + x) * factor >= prev.count
            ll extra = (prev.count - curr.count * factor + factor - 1) / factor;
            curr.count += extra;
        }
        auto& rem = boxes[0];
        // x * factor >= count
        ll side = rem.side+1, factor = 4;
        while (factor < rem.count) {
            side++;
            factor *= 4;
        }
        std::cout << side << std::endl;
    }
    return 0;
}