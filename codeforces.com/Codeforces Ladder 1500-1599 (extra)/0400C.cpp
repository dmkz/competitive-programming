/*
    Problem: 400C. Inna and Huge Candy Matrix
    
    Solution: math, geometry, O(q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <tuple>

void solve(int &row, int &col, int nRows, int nCols, int nRight, int nCenter, int nLeft) {
    nRight %= 4; nLeft %= 4; nCenter %= 2;
    while (nRight--) {
        std::tie(row, col) = std::make_pair(col, nRows-row+1);
        std::swap(nRows, nCols);
    }
    if (nCenter) {
        col = nCols-col+1;
    }
    nRight = 4 - nLeft;
    while (nRight--) {
        std::tie(row, col) = std::make_pair(col, nRows-row+1);
        std::swap(nRows, nCols);
    }
}

int main() {
    int nRows, nCols, nRight, nCenter, nLeft, nQueries;
    scanf("%d %d %d %d %d %d",&nRows,&nCols,&nRight,&nCenter,&nLeft,&nQueries);
    while (nQueries--) {
        int row, col; scanf("%d %d", &row, &col);
        solve(row, col, nRows, nCols, nRight, nCenter, nLeft);
        printf("%d %d\n", row, col);
    }
    return 0;
}