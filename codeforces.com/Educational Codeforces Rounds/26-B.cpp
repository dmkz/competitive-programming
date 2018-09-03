/*
    Problem: 837B. Flag of Berland
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef std::vector<std::string> vs;

vs rotate(vs arr) {
    int nRows = (int)arr.size(), nCols = (int)arr[0].size();
    vs ret(nCols, std::string(nRows,'?'));
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            ret[c][nRows-r-1] = arr[r][c];
        }
    }
    return ret;
}

bool check_on_char(std::string& s, const char c) {
    for (auto& it : s) {
        if (it != c) return false;
    }
    return true;
}

int check(int nRows, int nCols, const vs& arr) {
    if (nRows % 3 != 0) return 0;
    char fi = '?', se = '?', th = '?';
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            if (r < nRows / 3) {
                if (fi == '?') {
                    fi = arr[r][c];
                } else if (fi != arr[r][c]) {
                    return 0;
                }
            } else if (r < nRows / 3 * 2) {
                if (se == '?') {
                    se = arr[r][c];
                } else if (se != arr[r][c]) {
                    return 0;
                }
            } else {
                if (th == '?') {
                    th = arr[r][c];
                } else if (th != arr[r][c]) {
                    return 0;
                }
            }
        }
    }
    std::vector<char> chars{fi, se, th};
    std::sort(chars.begin(), chars.end());
    return (chars[0] == 'B' && chars[1] == 'G' && chars[2] == 'R') ? 1 : 0;
}

int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    vs field(nRows);
    for (auto& it : field) {
        std::cin >> it;
    }
    int answ = -1;
    if (nCols < 3) {
        answ = check(nRows, nCols, field);
    } else if (!check_on_char(field[0], 'R') && !check_on_char(field[0], 'G') && !check_on_char(field[0], 'B')) {
        answ = check(nCols, nRows, rotate(field));
    } else {
        answ = check(nRows, nCols, field);
    }
    assert(answ != -1);
    printf(answ ? "YES" : "NO");
    return 0;
}