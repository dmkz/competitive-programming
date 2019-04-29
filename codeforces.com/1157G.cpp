/*
    Problem: 1157G. Inverse of Rows and Columns
    
    Solution: brute force, constructive, O((n+m)^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
namespace Solver {
    int nRows, nCols;
    vvi arr; vi rows, cols;
    const int UNDEF = -1;
    bool input() {
        bool flag = bool(std::cin >> nRows >> nCols);
        if (flag) {
            rows.assign(nRows, UNDEF);
            cols.assign(nCols, UNDEF);
            arr.assign(nRows, vi(nCols,0));
            for (int r = 0; r < nRows; ++r) {
                for (int c = 0; c < nCols; ++c) {
                    std::cin >> arr[r][c];
                }
            }
        }
        return flag;
    }
    void fillCols(const int row, const int res) {
        for (int col = 0; col < nCols; ++col) {
            cols[col] = arr[row][col] ^ rows[row] ^ res;
        }
    }
    bool fillRows(const int begin, const int after, const int res) {
        for (int r = begin; r < after; ++r) {
            for (int c = 0; c < nCols; ++c) {
                assert(cols[c] != UNDEF);
                if (rows[r] == UNDEF) {
                    rows[r] = arr[r][c] ^ res ^ cols[c];
                }
                if (res != (rows[r] ^ arr[r][c] ^ cols[c])) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool solveFixed(const int row, const int invFirst, const int invLast) {
        // all rows from 0 to row-1 set to zeros
        // all rows from row+1 to isz(rows) set to ones
        // check what we can do with given row
        assert(nRows > 1);
        std::fill(all(rows), UNDEF);
        rows.front() = invFirst;
        rows.back()  = invLast;
        if (row != 0) { fillCols(0, 0); }
        else {
            assert(row != nRows-1);
            fillCols(nRows-1,1);
        }
        if (!fillRows(0,row,0)) { return false; }
        if (!fillRows(row+1,nRows,1)) { return false; }
        // brute number of zeros in given row
        for (int nZ = 0; nZ <= nCols; ++nZ) {
            rows[row] = UNDEF;
            bool flag = true;
            for (int c = 0; c < nCols; ++c) {
                const int res = (c >= nZ);
                if (rows[row] == UNDEF) {
                    rows[row] = arr[row][c] ^ res ^ cols[c];
                }
                if (res != (rows[row] ^ arr[row][c] ^ cols[c])) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return true;
            }
        }
        return false;
    }
    
    bool solve() {
        if (nRows == 1) {
            // we can got all zeros
            rows[0] = 0; 
            cols = arr[0];
            return true;
        } 
        if (nCols == 1) {
            // we can got all zeros too
            cols[0] = 0;
            for (int r = 0; r < nRows; ++r) { rows[r] = arr[r][0]; }
            return true;
        }
        for (int invFirst = 0; invFirst < 2; invFirst++) {
            for (int invLast = 0; invLast < 2; invLast++) {
                for (int r = 0; r < nRows; ++r) {
                    if (solveFixed(r, invFirst, invLast)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void check() {
        vi v;
        for (int r = 0; r < nRows; ++r) {
            for (int c = 0; c < nCols; ++c) {
                assert(rows[r] != UNDEF);
                assert(cols[c] != UNDEF);
                v.push_back(arr[r][c] ^ rows[r] ^ cols[c]);
            }
        }
        assert(std::is_sorted(all(v)));
    }
}

int main() {
    using namespace Solver;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    while (input()) {
        if (solve()) {
            check();
            std::cout << "YES\n";
            for (auto it : rows) { std::cout << it; }
            std::cout << "\n";
            for (auto it : cols) { std::cout << it; }
            std::cout << std::endl;
        } else {
            std::cout << "NO" << std::endl; 
        }
    }
    return 0;
}