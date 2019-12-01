/*
    Problem: 374C. Inna and Dima
    Solution: graphs, dfs, cycles, O(n*m)
*/
#include <bits/stdc++.h>
template<typename A, typename B> A& remax(A& a, B b) { return a = (a < b) ? b : a; }
const auto is_sync_off = [](){std::ios_base::sync_with_stdio(0); std::cin.tie(0); return 0;}();
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
namespace Solution {
    int nRows, nCols;
    std::vector<std::string> arr;
    vvi color, steps;
    bool cycleExists;
    void init(int nR, int nC) {
        nRows = nR;
        nCols = nC;
        color.assign(nR,vi(nC,0));
        steps = color;
        cycleExists = false;
    }
    void input() {
        arr.resize(nRows);
        for (auto &it : arr) std::cin >> it;
    }
    void find_cycle(int r, int c) {
        if (cycleExists || color[r][c] == 2) return;
        color[r][c] = 1;
        char next = '?';
        switch(arr[r][c]) {
            case 'D': next = 'I'; break;
            case 'I': next = 'M'; break;
            case 'M': next = 'A'; break;
            case 'A': next = 'D'; break;
        }
        auto &ret = steps[r][c];
        ret = 1;
        for (int dr = -1; !cycleExists && dr <= 1; dr++) {
            for (int dc = -1; !cycleExists && dc <= 1; dc++) {
                if (dr * dr + dc * dc != 1) continue;
                int nr = r + dr;
                int nc = c + dc;
                if (nr < 0 || nr >= nRows || nc < 0 || nc >= nCols) continue;
                if (arr[nr][nc] != next) continue;
                if (color[nr][nc] == 1) {
                    cycleExists = true;
                    return;
                } else if (color[nr][nc] == 0) {
                    find_cycle(nr,nc);
                }
                remax(ret, steps[nr][nc]+1);
            }
        }
        color[r][c] = 2;
    }
    std::string solve() {
        int max = 0;
        for (int r = 0; r < nRows; r++) {
            for (int c = 0; c < nCols; c++) {
                if (arr[r][c] != 'D') continue;
                find_cycle(r,c);
                if (cycleExists) { return "Poor Inna!"; }
                max = std::max(max, steps[r][c]);
            }
        }
        max /= 4;
        return max == 0 ? "Poor Dima!" : std::to_string(max);
    }
}
int main() {
    using namespace Solution;
    for (int nRows, nCols; std::cin >> nRows >> nCols; ) {
        init(nRows, nCols);
        input();
        std::cout << solve() << std::endl;
    }
}