/*
    Problem: 803A. Maximal Binary Matrix
    
    Solution: constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n, k; std::cin >> n >> k;
    vvi a(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1 || k == 0) continue;
            if (i == j) {
                a[i][j] = 1;
                --k;
            } else if (k >= 2) {
                a[i][j] = 1;
                a[j][i] = 1;
                k -= 2;
            }
        }
    }
    if (k > 0) { std::cout << -1; return 0; }
    for (auto& row : a) {
        for (auto& it : row) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}