/*
    Problem: 41D. Pawn
    
    Solution: dynamic programming, O(k*n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>

struct Point {
    int rem, row, col;
};
bool operator==(const Point& a, const Point& b) { return a.rem == b.rem && a.row == b.row && a.col == b.col; }
bool operator!=(const Point& a, const Point& b) { return !(a == b); }
int main() {
    // Using static arrays for fast memory access:
    const int NMAX = 102, KMAX = 11, INF = (int)1e9+7;
    static int max[KMAX][NMAX][NMAX];
    static Point from[KMAX][NMAX][NMAX];
    // Input parameters of problem:
    int nRows, nCols, k;
    while (std::cin >> nRows >> nCols >> k) {
        ++k;
        memset(&max[0][0][0], -INF, NMAX * NMAX * KMAX * sizeof(int));
        // Input field:
        std::vector<std::vector<int>> value(1+nRows+1, std::vector<int>(1+nCols+1, 0));
        for (int i = 1; i <= nRows; ++i) {
            std::string s; std::cin >> s;
            for (int j = 1; j <= nCols; ++j) {
                value[i][j] = int(s[j-1]-'0');
            }
        }
        // Init dynamic programming parameters:
        const auto& back = value[nRows];
        for (int col = 1; col <= nCols; ++col) {
            max[back[col]%k][nRows][col] = back[col];
            from[back[col]%k][nRows][col] = Point{back[col]%k, nRows, col};
        }
        // Function for update answer in one cell from another cell:
        std::function<void(int,int,int,int,int)> update = [&](int nr, int nc, int rem, int cr, int cc) {
            int& toMax = max[(rem+value[nr][nc])%k][nr][nc];
            int fromMax = max[rem][cr][cc]+value[nr][nc];
            if (toMax < fromMax) {
                toMax = fromMax;
                from[(rem+value[nr][nc])%k][nr][nc] = Point{rem, cr,cc};
            }
        };
        // 3D - dynamic programming:
        for (int row = nRows; row >= 2; --row) {
            for (int rem = 0; rem < k; ++rem) {
                for (int col = 1; col <= nCols; ++col) {
                    update(row-1,col-1, rem, row, col);
                    update(row-1,col+1, rem, row, col);
                }
            }
        }
        // Finding maximum possible sum with remainder equal to 0:
        int startCol = 1;
        for (int col = 2; col <= nCols; ++col) {
            if (max[0][1][col] > max[0][1][startCol]) {
                startCol = col;
            }
        }
        // If no answer output -1:
        if (max[0][1][startCol] < 0) {
            std::cout << "-1\n";
            continue;
        }
        // Output answer, and getting path with maximum total sum:
        std::cout << max[0][1][startCol] << "\n";
        Point curr{0, 1, startCol};
        std::string answ;
        while (curr != from[curr.rem][curr.row][curr.col]) {
            auto next = from[curr.rem][curr.row][curr.col];
            if (next.col > curr.col) {
                answ.push_back('L');
            } else {
                answ.push_back('R');
            }
            curr = next;
        }
        std::cout << curr.col << '\n';
        std::reverse(answ.begin(), answ.end());
        std::cout << answ << '\n';
    }
    return 0;
}