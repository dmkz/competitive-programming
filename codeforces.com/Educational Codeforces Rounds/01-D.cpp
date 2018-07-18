/*
    Problem: 598D. Igor In the Museum
    
    Solution: dfs, connected components, O(n*m)
*/

#include <iostream>
#include <vector>
#include <functional>
#include <string>

int main() {    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRows, nCols, nQueries;
    std::cin >> nRows >> nCols >> nQueries;
    
    std::vector<std::string> field(nRows);
    for (int row = 0; row < nRows; ++row) {
        std::cin >> field[row];
    }
    
    std::vector<std::vector<int>> colors(nRows, std::vector<int>(nCols, -1));
    std::vector<int> count;
    
    std::function<void(int, int, int)> calc = [&](int row, int col, int color) {
        colors[row][col] = color;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc == 1) {
                    if (field[row+dr][col+dc] == '*') {
                        count[color]++;
                    } else if (colors[row+dr][col+dc] != color) {
                        calc(row+dr, col+dc, color);
                    }
                }
            }
        }
    };
    
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            if (field[row][col] == '.' && colors[row][col] == -1) {
                int color = (int)count.size();
                count.push_back(0);
                calc(row, col, color);
            }
        }
    }
    
    for (int q = 0; q < nQueries; ++q) {
        int row, col;
        std::cin >> row >> col;
        --row, --col;
        std::cout << count[colors[row][col]] << "\n";
    }
    
    return 0;
}