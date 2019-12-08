/*
    Problem: 377A. Maze
    Solution: graphs, dfs
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>

int main() {
    int nRows, nCols, need;
    std::cin >> nRows >> nCols >> need;
    
    std::vector<std::string> map(nRows);
    for (auto& it : map) std::cin >> it;
    
    std::vector<std::vector<bool>> visited(nRows, std::vector<bool>(nCols));
    
    std::function<void(int,int)> visit = [&](int row, int col) {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr*dr+dc*dc != 1) continue;
                int nr = row + dr;
                int nc = col + dc;
                if (nr < 0 || nr >= nRows || nc < 0 || nc >= nCols || map[nr][nc] != '.' || visited[nr][nc]) continue;
                visited[nr][nc] = true;
                visit(nr,nc);
            }
        }
        if (need > 0) {
            --need;
            assert(map[row][col] == '.');
            map[row][col] = 'X';
        }
    };
    
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            if (!visited[r][c] && map[r][c] == '.') {
                visited[r][c] = true;
                visit(r,c);
            }
        }
    }
    for (auto& it : map) std::cout << it << '\n';
    return 0;
}