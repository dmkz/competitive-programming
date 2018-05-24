#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int nRows, nCols; std::cin >> nRows >> nCols;
    std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols));
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            std::cin >> arr[r][c];
        }
    }
    std::vector<std::vector<int>> map(10*nRows+2, std::vector<int>(10*nCols+2));
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            // 10 * r + 1, ..., 10 * r + 10
            // 10 * c + 1, ..., 10 * c + 10
            if (r > 0 && arr[r][c] != arr[r-1][c]) {
                const int i = 10 * r + 1;
                const int min_j = 10 * c + 1;
                const int max_j = 10 * c + 10;
                for (int j = min_j; j <= max_j; ++j) {
                    map[i][j] = 1;
                }
            }
            if (c > 0 && arr[r][c] != arr[r][c-1]) {
                const int j = 10 * c + 1;
                const int min_i = 10 * r + 1;
                const int max_i = 10 * r + 10;
                for (int i = min_i; i <= max_i; ++i) {
                    map[i][j] = 1;
                }
            }
            if (r+1 < nRows && arr[r][c] != arr[r+1][c]) {
                const int i = 10 * r + 10;
                const int min_j = 10 * c + 1;
                const int max_j = 10 * c + 10;
                for (int j = min_j; j <= max_j; ++j) {
                    map[i][j] = 1;
                }
            }
            if (c+1 < nCols && arr[r][c] != arr[r][c+1]) {
                const int j = 10 * c + 10;
                const int min_i = 10 * r + 1;
                const int max_i = 10 * r + 10;
                for (int i = min_i; i <= max_i; ++i) {
                    map[i][j] = 1;
                }
            }
            if (r > 0 && c > 0 && arr[r][c] != arr[r-1][c-1]) {
                map[10*r+1][10*c+1] = 1;
            }
            if (r > 0 && c+1 < nCols && arr[r][c] != arr[r-1][c+1]) {
                map[10*r+1][10*c+10] = 1;
            }
            if (r+1 < nRows && c > 0 && arr[r][c] != arr[r+1][c-1]) {
                map[10*r+10][10*c+1] = 1;
            }
            if (r+1 < nRows && c+1 < nCols && arr[r][c] != arr[r+1][c+1]) {
                map[10*r+10][10*c+10] = 1;
            }
        }
    }
    int count = 0;
    for (int r = 2; r < 10 * nRows; ++r) {
        for (int c = 2; c < 10 * nCols; ++c) {
            count += map[r][c];
        }
    }
    std::cout << std::fixed << std::setprecision(3) << count / 100.0 * 3;
    return 0;
}