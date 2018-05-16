#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    int nRows, nCols; 
    scanf("%d %d", &nRows, &nCols);
    std::vector<std::vector<char>> field(nRows, std::vector<char>(nCols));
    int min_row = nRows;
    int min_col = nCols;
    int max_row = -1;
    int max_col = -1;
    for (int row = 0; row < nRows; ++row) {
        char buf[1001]; 
        scanf("%1000s", buf);
        for (int col = 0; col < nCols; ++col) {
            char c = buf[col];
            field[row][col] = c;
            if (c == '*') {
                min_row = std::min(min_row, row);
                min_col = std::min(min_col, col);
                max_row = std::max(max_row, row);
                max_col = std::max(max_col, col);
            }
        }
    }
    
    int w = max_col - min_col + 1;
    int h = max_row - min_row + 1;
    
    if (max_col == -1 || std::abs(w-h) > 4) {
        std::cout << "CIRCLE\n"; 
        return 0;
    }
    
    // maxSide[r][c] = max side of square with 4 corners: [r-side+1][c-side+1], [r-side+1][c], [r][c-side+1], [r][c]
    std::vector<std::vector<int>> maxSide(nRows, std::vector<int>(nCols)); 
    
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            if (field[row][col] == '.') continue;
            if (row == 0 || col == 0) {
                maxSide[row][col] = 1;
            } else {
                maxSide[row][col] = 1 + std::min({maxSide[row-1][col], maxSide[row][col-1], maxSide[row-1][col-1]});
            }
        }
    }

    for (int row = std::max(1, min_row); row <= std::min(max_row, nRows-2); ++row) {
        for (int col = std::max(1, min_col); col <= std::min(max_col, nCols-2); ++col) {
            int side = maxSide[row][col];
            if (side == 0) {
                continue;
            }
            
            assert(row-side+1 >= min_row && col - side + 1 >= min_col);
            assert(w >= side && h >= side);
            
            if (
                w - side <= 4 && h - side <= 4 && 
                row - side + 1 - min_row <= 2 && max_row - row <= 2 && 
                col - side + 1 - min_col <= 2 && max_col - col <= 2
            ) {
                std::cout << "SQUARE" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "CIRCLE" << std::endl;
    return 0;
}