/*
    Problem: 329B. Biridian Forest
    
    Solution: bfs, grid graph, greedy, O(n * m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <cassert>

typedef std::vector<char> vc;
typedef std::vector<vc> vvc;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Point {
    int row, col;
};

const int INF = (int)1e9+1;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nRows, nCols;
    while (std::cin >> nRows >> nCols) {
        vvc arr(1+nRows+1, vc(1+nCols+1, 'T'));
        Point fi{-1,-1}, se{-1,-1};
        for (int r = 1; r <= nRows; ++r) {
            std::string s; std::cin >> s;
            for (int c = 1; c <= nCols; ++c) {
                arr[r][c] = s[c-1];
                if (arr[r][c] == 'S') {
                    fi = {r,c};
                }
                if (arr[r][c] == 'E') {
                    se = {r,c};
                }
            }
        }
        assert(fi.row >= 0 && se.row >= 0);
        vvi dist(1+nRows+1, vi(1+nCols+1, INF));
        dist[se.row][se.col] = 0;
        std::queue<Point> queue;
        queue.push(se);
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr * dr + dc * dc != 1) continue;
                    Point next{curr.row+dr, curr.col+dc};
                    if (arr[next.row][next.col] == 'T') continue;
                    if (dist[next.row][next.col] == INF) {
                        dist[next.row][next.col] = dist[curr.row][curr.col]+1;
                        queue.push(next);
                    }
                }
            }
        }
        int limit = dist[fi.row][fi.col], answ = 0;
        for (int r = 1; r <= nRows; ++r) {
            for (int c = 1; c <= nCols; ++c) {
                if (dist[r][c] <= limit && '0' <= arr[r][c] && arr[r][c] <= '9') {
                    answ += int(arr[r][c] - '0');
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}