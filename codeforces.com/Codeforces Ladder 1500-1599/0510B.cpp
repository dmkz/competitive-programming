/*
    Problem: 510B. Fox And Two Dots
    Solution: dfs, O(n*m)
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <cassert>

int main() {
    int nR, nC;
    std::cin >> nR >> nC;
    
    std::vector<std::string> color(nR);
    for (auto& it : color) std::cin >> it;
    
    std::vector<std::vector<bool>> visited(nR, std::vector<bool>(nC));
    
    std::function<void(int,int,int,int)> visit = [&](int curr_row, int curr_col, int prev_row, int prev_col) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr * dr + dc * dc != 1) continue;
                int nr = curr_row+dr;
                int nc = curr_col+dc;
                if (0 > nr || nr >= nR || 0 > nc || nc >= nC) continue;
                if (color[nr][nc] != color[curr_row][curr_col]) continue;
                if (nr == prev_row && nc == prev_col) continue;
                if (visited[nr][nc]) {
                    std::cout << "Yes";
                    std::exit(0);
                }
                visited[nr][nc] = true;
                visit(nr,nc,curr_row,curr_col);
            }
        }
    };
    for (int r = 0; r < nR; ++r) {
        for (int c = 0; c < nC; ++c) {
            if (!visited[r][c]) {
                visited[r][c] = true;
                visit(r,c,-1,-1);
            }
        }
    }
    std::cout << "No";
    return 0;
}