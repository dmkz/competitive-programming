/*
    Problem: 1016B. Segment Occurrences
    
    Solution: implementation, brute force, O(q*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    std::string s, t;
    std::cin >> s >> t;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        int j;
        for (j = 0; i + j < n && j < m; ++j) {
            if (s[i+j] != t[j]) {
                break;
            }
        }
        arr[i] = (j == m);
    }
    while (q--) {
        int l, r; std::cin >> l >> r; --l, --r;
        int res = 0;
        for (int i = l; i + m - 1 <= r; ++i) {
            res += arr[i];
        }
        std::cout << res << '\n';
    }
    return 0;
}