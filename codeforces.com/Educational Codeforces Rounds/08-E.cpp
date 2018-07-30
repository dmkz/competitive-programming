/*
    Problem: 628E. Zbazi в Zeydabad
    
    Solution: fenwick, events, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize ("O3")
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

struct Fenwick {
    
    std::vector<int> data;
    
    Fenwick(int size) : data(size, 0) { }
    
    void inc(int p, int val) {
        while (p < (int)data.size()) {
            data[p] += val; p |= p+1;
        }
    }
    
    int get(int r) const {
        int answ = 0;
        while (r >= 0) {
            answ += data[r]; 
            r = (r & (r+1)) - 1;
        }
        return answ;
    }

    int get(int l, int r) const {
        return get(r) - (l == 0 ? 0 : get(l-1));
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    
    std::vector<std::string> field(nRows);
    for (auto& it : field) std::cin >> it;
    
    std::vector<std::vector<int>> mxL(nRows, std::vector<int>(nCols));
    auto mxR = mxL, mxD = mxL;
    for (int r = 0; r < nRows; ++r) {
        mxL[r][0] = (field[r][0] == 'z');
        for (int c = 1; c < nCols; ++c) {
            mxL[r][c] = (field[r][c] == 'z') ? (mxL[r][c-1]+1) : 0;
        }
    }
    for (int r = 0; r < nRows; ++r) {
        mxR[r].back() = (field[r].back() == 'z');
        for (int c = nCols-2; c >= 0; --c) {
            mxR[r][c] = (field[r][c] == 'z') ? (mxR[r][c+1]+1) : 0;
        }
    }
    for (int r = 0; r < nRows; ++r) {
        for (int c = nCols-1; c >= 0; --c) {
            if (r == 0 || c == nCols-1) {
                mxD[r][c] = (field[r][c] == 'z');
            } else {
                mxD[r][c] = (field[r][c] == 'z') ? mxD[r-1][c+1]+1 : 0;
            }
        }
    }
    int64_t answ = 0;
    std::vector<std::vector<int>> queue(nCols);
    for (int d = 0; d < nRows + nCols; ++d) {
        int c = std::min(nCols-1, d);
        int r = d - c;
        Fenwick fw(nCols);
        
        while (true) {
            if (c < 0 || r < 0 || c >= nCols || r >= nRows) break;
            if (field[r][c] == 'z') {
                fw.inc(c, 1);
                answ += fw.get(c, c+std::min(mxD[r][c], mxR[r][c])-1);
                queue[c-mxL[r][c]+1].push_back(c);
            }
            
            while (!queue[c].empty()) {
                auto curr = queue[c].back();
                queue[c].pop_back();
                fw.inc(curr, -1);
            }
            
            c--,r++;
        }
    }
    std::cout << answ;
    return 0;
}