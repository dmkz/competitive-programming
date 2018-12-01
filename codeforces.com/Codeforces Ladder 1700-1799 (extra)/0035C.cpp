/*
    Problem: 35C. Fire Again
    
    Solution: grid graphs, BFS, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#include <algorithm>

const int INF = (int)1e9+1;

struct Point {
    int row, col;
};

Point solve(const int nR, const int nC, const std::vector<Point>& start) {
    std::vector<std::vector<int>> minTime(1+nR+1, std::vector<int>(1+nC+1,INF));
    for (int r = 0; r <= nR+1; ++r) {
        minTime[r].front() = minTime[r].back() = 0;
    }
    for (int c = 0; c <= nC+1; ++c) {
        minTime.front()[c] = minTime.back()[c] = 0;
    }
    std::queue<Point> queue;
    for (auto pt : start) {
        queue.push(pt);
        minTime[pt.row][pt.col] = 0;
    }
    while (!queue.empty()) {
        auto pt = queue.front(); queue.pop();
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr*dr+dc*dc == 1) {
                    int nr = pt.row+dr, nc = pt.col+dc;
                    if (minTime[nr][nc] > minTime[pt.row][pt.col]+1) {
                        minTime[nr][nc] = minTime[pt.row][pt.col]+1;
                        queue.push(Point{nr,nc});
                    }
                }
            }
        }
    }
    auto min = start.front();
    for (int r = 1; r <= nR; ++r) {
        for (int c = 1; c <= nC; ++c) {
            if (minTime[r][c] > minTime[min.row][min.col]) {
                min = Point{r,c};
            }
        }
    }
    return min;
}

int main() {
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    int nR, nC;
    while (std::cin >> nR >> nC) {
        int k; std::cin >> k;
        std::vector<Point> start;
        for (int i = 0; i < k; ++i) {
            int r, c; std::cin >> r >> c;
            start.push_back(Point{r,c});
        }
        auto pt = solve(nR, nC, start);
        std::cout << pt.row << ' ' << pt.col << std::endl;
    }
    return 0;
}