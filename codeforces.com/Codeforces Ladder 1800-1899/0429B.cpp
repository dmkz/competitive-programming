/*
    Problem: 429B. Working out
    Solution: dynamic programming, brute force, O(n*m)
*/
#include <bits/stdc++.h>
template<typename A, typename B> A& remax(A& a, B b) { return a = (a < b ? b : a); }
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
const int NMAX = 1024;
using ll = long long;
ll arr[NMAX][NMAX], mxLU[NMAX][NMAX], mxLD[NMAX][NMAX], mxRU[NMAX][NMAX], mxRD[NMAX][NMAX];
int nRows, nCols;
const ll INF = (ll)1e12;
int main() {
    while (std::cin >> nRows >> nCols) {
        // INITIALIZATION
        std::fill(&arr[0][0],&arr[0][0]+NMAX*NMAX,-INF);
        std::fill(&mxLU[0][0],&mxLU[0][0]+NMAX*NMAX,-INF);
        std::fill(&mxLD[0][0],&mxLD[0][0]+NMAX*NMAX,-INF);
        std::fill(&mxRU[0][0],&mxRU[0][0]+NMAX*NMAX,-INF);
        std::fill(&mxRD[0][0],&mxRD[0][0]+NMAX*NMAX,-INF);
        // INPUT
        for (int r = 1; r <= nRows; r++)
            for (int c = 1; c <= nCols; c++)
                std::cin >> arr[r][c];
        // LEFT-UP
        mxLU[1][1] = arr[1][1];
        for (int r = 1; r <= nRows; r++)
            for (int c = 1; c <= nCols; c++)
                if (r > 1 || c > 1)
                    mxLU[r][c] = std::max(mxLU[r-1][c], mxLU[r][c-1]) + arr[r][c];
        // RIGHT-UP
        mxRU[1][nCols] = arr[1][nCols];
        for (int r = 1; r <= nRows; r++)
            for (int c = nCols; c >= 1; c--)
                if (r > 1 || c < nCols)
                    mxRU[r][c] = std::max(mxRU[r-1][c], mxRU[r][c+1]) + arr[r][c];
        // LEFT-DOWN
        mxLD[nRows][1] = arr[nRows][1];
        for (int r = nRows; r >= 1; r--)
            for (int c = 1; c <= nCols; c++)
                if (c > 1 || r < nRows)
                    mxLD[r][c] = std::max(mxLD[r+1][c], mxLD[r][c-1]) + arr[r][c];
        // RIGHT-DOWN
        mxRD[nRows][nCols] = arr[nRows][nCols];
        for (int r = nRows; r >= 1; r--)
            for (int c = nCols; c >= 1; c--)
                if (r < nRows || c < nCols)
                    mxRD[r][c] = std::max(mxRD[r+1][c], mxRD[r][c+1]) + arr[r][c];
        // BRUTE FORCE
        ll answ = -INF;
        for (int r = 2; r < nRows; r++) {
            for (int c = 2; c < nCols; c++) {
                remax(answ, mxLD[r][c-1] + mxRU[r][c+1] + mxLU[r-1][c] + mxRD[r+1][c]);
                remax(answ, mxLD[r+1][c] + mxRU[r-1][c] + mxLU[r][c-1] + mxRD[r][c+1]);
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}