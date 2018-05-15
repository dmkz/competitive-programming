#pragma GCC diagnostic ignored "-Wunused-result"
 
#include <bits/stdc++.h>
 
int main() {
    int nRows, nCols; scanf("%d %d", &nRows, &nCols);
    std::vector<std::vector<char>> map(1+nRows+1, std::vector<char>(1+nCols+1, '.'));
    for (int row = 1; row <= nRows; ++row) {
        for (int col = 1; col <= nCols; ++col) {
            scanf(" %c", &map[row][col]);
        }
    }
     
    for (int row = 1; row <= nRows; ++row) {
        for (int col = 1; col <= nCols; ++col) {
            if (map[row][col] == '*') {
                continue;
            }
            int count = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (!(dr == 0 && dc == 0)) {
                        count += map[row+dr][col+dc] == '*';
                    }
                }
            }
            if (count == 0 && map[row][col] != '.') {
                std::cout << "NO" << std::endl;
                return 0;
            }
            if (count > 0 && map[row][col] != '0' + count) {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }
    
    std::cout << "YES" << std::endl;
     
    return 0;
}