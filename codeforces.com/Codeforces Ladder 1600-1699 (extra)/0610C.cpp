/*
    Problem: 610C. Harmony Analysis
    
    Solution: math, constructive, O(4^k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

typedef std::vector<char> vc;
typedef std::vector<vc> vvc;

void solve(vvc& arr, int r, int c, int k, bool reversed) {
    if (k == 0) {
        arr[r][c] = reversed ? '*' : '+';
        return;
    }
    solve(arr, r, c, k-1, reversed);
    solve(arr, r, c + (1 << (k-1)), k-1, reversed);
    solve(arr, r + (1 << (k-1)), c, k-1, reversed);
    solve(arr, r + (1 << (k-1)), c + (1 << (k-1)), k-1, !reversed);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int k;
    while (std::cin >> k) {
        vvc arr(1 << k, vc(1 << k, '?'));
        solve(arr, 0, 0, k, false);
        for (auto& row : arr) {
            std::cout << std::string(row.begin(), row.end()) << "\n";
        }
    }
    return 0;
}