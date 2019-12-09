/*
    Problem: 1151E. Number of Components
    Solution: math, combinatorics, contribution to the sum, O(n)
*/
#include <bits/stdc++.h>
int main() {
    for (int n; std::cin >> n; ) {
        int64_t answ = 0;
        for (int prev = -1, curr = -1, i = 0; i < n; i++) {
            prev = curr;
            std::cin >> curr;
            answ += (n - curr + 1LL) * (curr - 1 + 1LL);
            if (prev == -1) continue;
            int min = std::min(prev,curr);
            int max = std::max(prev,curr);
            answ -= (min - 1 + 1LL) * (n - max + 1LL);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}