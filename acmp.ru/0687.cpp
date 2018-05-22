#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols));
    for (auto& row : arr) {
        for (auto& it : row) {
            std::cin >> it;
        }
    }
    
    std::vector<std::vector<int>> best(nRows, std::vector<int>(nCols, INT_MAX));
    std::vector<std::vector<int>> from(nRows, std::vector<int>(nCols, -1));
    for (int col = 0; col+1 < nCols; ++col) {
        for (int row = 0; row < nRows; ++row) {
            if (col == 0) {
                best[row][col] = arr[row][col];
            }
            if (row-1 >= 0 && best[row][col] + arr[row-1][col+1] < best[row-1][col+1]) {
                best[row-1][col+1] = best[row][col] + arr[row-1][col+1];
                from[row-1][col+1] = row;
            }
            if (best[row][col]+arr[row][col+1] < best[row][col+1]) {
                best[row][col+1] = best[row][col] + arr[row][col+1];
                from[row][col+1] = row;
            }
            if (row+1 < nRows && best[row][col] + arr[row+1][col+1] < best[row+1][col+1]) {
                best[row+1][col+1] = best[row][col] + arr[row+1][col+1];
                from[row+1][col+1] = row;
            }
        }
    }
    
    std::vector<int> path;
    int curr = -1;
    int result = INT_MAX;
    for (int row = 0; row < nRows; ++row) {
        if (result > best[row].back()) {
            result = best[row].back();
            curr = row;
        }
    }
    assert(curr != -1);
    path.push_back(curr);
    for (int col = nCols-1; col >= 1; --col) {
        path.push_back(from[curr][col]);
        curr = from[curr][col];
    }
    std::reverse(path.begin(), path.end());
    for (auto& it : path) {
        std::cout << it+1 << ' ';
    }
    std::cout << std::endl << result << std::endl;
    return 0;
}