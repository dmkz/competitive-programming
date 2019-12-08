/*
    Problem: 152C. Pocket Book
    Solution: combinatorics, sorting
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

const int mod = (int)1e9+7;

inline int mul(int a, int b) {
    return int(ll(a) * b % mod);
}

int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    
    std::vector<std::vector<char>> arr(nCols, std::vector<char>(nRows));
    for (int r = 0; r < nRows; ++r) {
        std::string s; std::cin >> s;
        for (int c = 0; c < nCols; ++c) {
            arr[c][r] = s[c];
        }
    }
    int res = 1;
    for (auto& it : arr) {
        std::sort(it.begin(), it.end());
        it.erase(std::unique(it.begin(), it.end()), it.end());
        res = mul(res, (int)it.size());
    }
    std::cout << res;
    return 0;
}