/*
    Problem: 548B. Mike and Fun
    
    Solution: implementation, brute force, greedy, O((n+m)*q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nRows, nCols, nQueries;
    while (std::cin >> nRows >> nCols >> nQueries) {
        std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols));
        for (int r = 0; r < nRows; ++r) {
            for (int c = 0; c < nCols; ++c) {
                std::cin >> arr[r][c];
            }
        }
        std::vector<int> maxInRow(nRows, -1);
        std::function<int(int)> calcInRow = [&](int row) {
            if (maxInRow[row] == -1) {
                int p = 0, max = 0;
                while (p < nCols) {
                    while (p < nCols && arr[row][p] == 0) ++p;
                    int prev = p;
                    while (p < nCols && arr[row][p] == 1) ++p;
                    max = std::max(p - prev, max);
                }
                maxInRow[row] = max;
            }
            return maxInRow[row];
        };
        while (nQueries--) {
            int row, col; std::cin >> row >> col; row--, col--;
            maxInRow[row] = -1;
            arr[row][col] = 1 - arr[row][col];
            int ans = 0;
            for (int r = 0; r < nRows; ++r) {
                ans = std::max(ans, calcInRow(r));
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}