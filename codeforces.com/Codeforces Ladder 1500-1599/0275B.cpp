/*
    Problem: 275B. Convex Shape
    Solution: dynamic programming, brute force
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    
    std::vector<std::vector<bool>> arr(nRows, std::vector<bool>(nCols));
    
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            char ch; scanf(" %c", &ch);
            arr[r][c] = (ch == 'B');
        }
    }
    
    std::vector<std::vector<int>> mxD(nRows, std::vector<int>(nCols));
    auto mxR = mxD, mxL = mxD, mxU = mxD;
    for (int r = nRows - 1; r >= 0; --r) {
        for (int c = 0; c < nCols; ++c) {
            mxD[r][c] = arr[r][c] ? (r+1 < nRows ? mxD[r+1][c] + 1 : 1) : 0;
        }
    }
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            mxU[r][c] = arr[r][c] ? (r-1 >= 0 ? mxU[r-1][c] + 1 : 1) : 0;
        }
    }
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            mxL[r][c] = arr[r][c] ? (c-1 >= 0 ? mxL[r][c-1] + 1 : 1) : 0;
        }
    }
    for (int r = 0; r < nRows; ++r) {
        for (int c = nCols-1; c >= 0; --c) {
            mxR[r][c] = arr[r][c] ? (c+1 < nCols ? mxR[r][c+1] + 1 : 1) : 0;
        }
    }
    
    for (int r1 = 0; r1 < nRows; ++r1) {
        for (int c1 = 0; c1 < nCols; ++c1) {
            if (!arr[r1][c1]) continue;
            for (int r2 = r1; r2 < nRows; ++r2) {
                for (int c2 = 0; c2 <= c1; ++c2) {
                    if (!arr[r2][c2]) continue;
                    int rlen = r2-r1+1;
                    int clen = c1-c2+1;
                    bool flag = (mxD[r1][c1] >= rlen && mxR[r2][c2] >= clen)||(mxL[r1][c1] >= clen && mxU[r2][c2] >= rlen);
                    if (!flag) {
                        printf("NO");
                        return 0;
                    }
                }
                for (int c2 = c1; c2 < nCols; ++c2) {
                    if (!arr[r2][c2]) continue;
                    int rlen = r2-r1+1;
                    int clen = c2-c1+1;
                    bool flag = (mxD[r1][c1] >= rlen && mxL[r2][c2] >= clen)||(mxR[r1][c1] >= clen && mxU[r2][c2] >= rlen);
                    if (!flag) {
                        printf("NO");
                        return 0;
                    }
                }
            }
        }
    }
    printf("YES");
    return 0;
}