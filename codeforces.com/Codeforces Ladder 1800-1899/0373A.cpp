/*
    Problem: 373A. Collecting Beats is Fun
    Solution: strings, counting, implementation, O(n^2)
*/
#include <bits/stdc++.h>
int main() {
    for (int k; std::cin >> k; ) {
        std::vector<int> cnt(256);
        for (int i = 0; i < 4; i++) {
            std::string s;
            std::cin >> s;
            for (auto it : s) {
                cnt[it]++;
            }
        }
        bool ok = true;
        for (char c = '1'; c <= '9'; c++) {
            ok = ok && cnt[c] <= 2 * k;
        }
        std::cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}