/*
    Problem: 354A. Vasya and Robot
    Solution: greedy, dynamic programming, O(n)
*/
#include <bits/stdc++.h>
int main() {
    for (int n, l, r, ql, qr; std::cin >> n >> l >> r >> ql >> qr;) {
        std::vector<int> w(n);
        for (auto &it : w) std::cin >> it;
        std::vector<int> s{0};
        for (auto &it : w) s.push_back(s.back() + it);
        int min = INT_MAX;
        for (int left = 0; left <= n; ++left) {
            int curr = s[left] * l + (s.back() - s[left]) * r;
            int right = n - left;
            if (left <= right) { curr += std::max(0,(right-left-1))*qr; }
            else { curr += std::max(0,left-right-1) * ql; }
            min = std::min(curr, min);
        }
        std::cout << min << std::endl;
    }
}