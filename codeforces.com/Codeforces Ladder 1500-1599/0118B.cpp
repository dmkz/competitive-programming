/*
    Problem: 118B. Present from Lena
    Solution: constructive, implementation
*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
int main() {
    int n; std::cin >> n;
    std::vector<std::string> map(2*n+1, std::string(2*n+1, ' '));
    for (int r = 0; r <= n; ++r) {
        char val = '0';
        for (int c = n - r; c <= n; ++c) {
            map[r][c] = val++;
        }
        --val;
        for (int c = n+1; c <= n + r; ++c) {
            map[r][c] = --val;
        }
    }
    for (int r = n; r <= 2*n; ++r) {
        char val = '0';
        for (int c = r-n; c <= n; ++c) {
            map[r][c] = val++;
        }
        --val;
        for (int c = n+1; c <= 3*n - r; ++c) {
            map[r][c] = --val;
        }
    }
    
    for (int i = 0; i <= 2*n; ++i) {
        int j = 2*n;
        for (; j >= 0 && map[i][j] == ' '; --j);
        for (int k = 0; k <= j; ++k) {
            std::cout << map[i][k];
            if (k != j) {
                std::cout << ' ';
            }
        }
        if (i != 2*n) {
            std::cout << '\n';
        }
    }
    return 0;
}